// Application layer protocol implementation

#include "application_layer.h"
#include "link_layer.h"
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <math.h>

void applicationLayer(const char *serialPort, const char *role, int baudRate,
                      int nTries, int timeout, const char *filename)
{
    LinkLayer linkLayer;
    strcpy(linkLayer.serialPort,serialPort);
    linkLayer.role = strcmp(role, "tx") ? LlRx : LlTx;
    linkLayer.baudRate = baudRate;
    linkLayer.nRetransmissions = nTries;
    linkLayer.timeout = timeout;

    int fd = llopen(linkLayer);
    if (fd < 0) {
        perror("Connection error\n");
        exit(-1);
    }

    switch (linkLayer.role) {

        case LlTx: {
            
            FILE* file = fopen(filename, "rb");
            if (file == NULL) {
                perror("File not found\n");
                exit(-1);
            }

            int prev = ftell(file);
            fseek(file,0L,SEEK_END);
            long int fileSize = ftell(file)-prev;
            fseek(file,prev,SEEK_SET);

            unsigned int cpSize;
            unsigned char *controlPacketStart = getControlPacket(2, filename, fileSize, &cpSize);
            if(llwrite(fd, controlPacketStart, cpSize) == -1){ 
                printf("Exit: error in start packet\n");
                exit(-1);
            }

            unsigned char sequence = 0;
            unsigned char* content = getData(file, fileSize);
            long int bytesLeft = fileSize;

            while (bytesLeft >= 0) { 

                int dataSize = bytesLeft > (long int) MAX_PAYLOAD_SIZE ? MAX_PAYLOAD_SIZE : bytesLeft;
                unsigned char* data = (unsigned char*) malloc(dataSize);
                memcpy(data, content, dataSize);
                int packetSize;
                unsigned char* packet = getDataPacket(sequence, data, dataSize, &packetSize);
                
                if(llwrite(fd, packet, packetSize) == -1) {
                    printf("Exit: error in data packets\n");
                    exit(-1);
                }
                
                bytesLeft -= (long int) MAX_PAYLOAD_SIZE; 
                content += dataSize; 
                sequence = (sequence + 1) % 255;   
            }

            unsigned char *controlPacketEnd = getControlPacket(3, filename, fileSize, &cpSize);
            if(llwrite(fd, controlPacketEnd, cpSize) == -1) { 
                printf("Exit: error in end packet\n");
                exit(-1);
            }
            llclose(fd);
            break;
        }

        case LlRx: {

            unsigned char *packet = (unsigned char *)malloc(MAX_PAYLOAD_SIZE);
            int packetSize = -1;
            while ((packetSize = llread(fd, packet)) < 0);
            unsigned long int rxFileSize = 0;
            unsigned char* name = parseControlPacket(packet, packetSize, &rxFileSize); 

            FILE* newFile = fopen((char *) name, "wb+");
            while (1) {    
                while ((packetSize = llread(fd, packet)) < 0);
                if(packetSize == 0) break;
                else if(packet[0] != 3){
                    unsigned char *buffer = (unsigned char*)malloc(packetSize);
                    parseDataPacket(packet, packetSize, buffer);
                    fwrite(buffer, sizeof(unsigned char), packetSize-4, newFile);
                    free(buffer);
                }
                else continue;
            }

            fclose(newFile);
            break;

        default:
            exit(-1);
            break;
    }}
}

unsigned char* parseControlPacket(unsigned char* stream, int streamLength, unsigned long int *outputFileSize) {
    // Extracting the file size from the packet
    unsigned char sizeDescriptor = stream[2]; // size of the file size field
    unsigned char fileSizeBytes[sizeDescriptor]; 
    memcpy(fileSizeBytes, stream + 3, sizeDescriptor); 
    *outputFileSize = 0; // Ensure the file size starts at 0
    for(int index = 0; index < sizeDescriptor; ++index) {
        *outputFileSize |= (unsigned long)(fileSizeBytes[sizeDescriptor - index - 1]) << (index * 8);
    }

    // Extracting the file name from the packet
    unsigned char nameLength = stream[3 + sizeDescriptor + 1]; // size of the file name field
    unsigned char *fileName = (unsigned char*)malloc(nameLength + 1); // +1 for the null-terminator
    memcpy(fileName, stream + 3 + sizeDescriptor + 2, nameLength); 
    fileName[nameLength] = '\0'; // Null-terminate the file name

    return fileName; // Return the extracted file name
}

void parseDataPacket(const unsigned char* packet, const unsigned int packetSize, unsigned char* buffer) {
    memcpy(buffer,packet+4,packetSize-4);
    buffer += packetSize+4;
}

unsigned char * getControlPacket(unsigned int type, const char *fileIdentifier, long fileSize, unsigned int *frameSize) {
    // Determine the size of the file size field based on the value
    int fileSizeFieldLength = (int) ceil(log2(fileSize + 1) / 8);
    int fileIdentifierLength = strlen(fileIdentifier);
    *frameSize = 1 + 2 + fileSizeFieldLength + 2 + fileIdentifierLength; // Calculate total frame size
    unsigned char *controlFrame = (unsigned char *)malloc(*frameSize);

    unsigned int position = 0;
    controlFrame[position++] = type; // Type of control frame
    controlFrame[position++] = 0; // Separator
    controlFrame[position++] = fileSizeFieldLength; // File size field length

    // Encode the file size into the frame
    for (int i = fileSizeFieldLength - 1; i >= 0; i--) {
        controlFrame[position++] = (fileSize >> (i * 8)) & 0xFF;
    }

    // Add file identifier length and content
    controlFrame[position++] = 1; // Separator
    controlFrame[position++] = fileIdentifierLength;
    memcpy(controlFrame + position, fileIdentifier, fileIdentifierLength);

    return controlFrame;
}

unsigned char * getDataPacket(unsigned char seqNumber, const unsigned char *payload, int payloadSize, int *frameLength) {
    *frameLength = 4 + payloadSize; // 1 byte for type, 1 for sequence number, 2 for size, and the rest for payload
    unsigned char *dataFrame = (unsigned char *)malloc(*frameLength);

    dataFrame[0] = 1; // Data frame type identifier
    dataFrame[1] = seqNumber;
    dataFrame[2] = (payloadSize >> 8) & 0xFF;
    dataFrame[3] = payloadSize & 0xFF;
    memcpy(dataFrame + 4, payload, payloadSize);

    return dataFrame;
}

unsigned char * getData(FILE* fd, long int fileLength) {
    unsigned char* content = (unsigned char*)malloc(sizeof(unsigned char) * fileLength);
    fread(content, sizeof(unsigned char), fileLength, fd);
    return content;
}