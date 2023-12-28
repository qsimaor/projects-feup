#ifndef _APPLICATION_LAYER_H_
#define _APPLICATION_LAYER_H_

#include <stdio.h>

// Inicia a transferência ou recepção de um arquivo pela porta série
void applicationLayer(const char *serialPort, const char *role, int baudRate,
                      int nTries, int timeout, const char *filename);

// Extrai o nome e o tamanho do arquivo de um pacote de controle recebido
unsigned char* parseControlPacket(unsigned char* stream, int streamLength, unsigned long int *outputFileSize);

// Processa um pacote de dados recebido
void parseDataPacket(const unsigned char* packet, const unsigned int packetSize, unsigned char* buffer);

// Cria um pacote de controle com informações sobre o arquivo a ser transferido
unsigned char * getControlPacket(unsigned int type, const char *fileIdentifier, long fileSize, unsigned int *frameSize);

// Monta um pacote de dados com um segmento do arquivo a ser transmitido e seu número de sequência
unsigned char * getDataPacket(unsigned char seqNumber, const unsigned char *payload, int payloadSize, int *frameLength);

// Lê o conteúdo do arquivo para a memória
unsigned char * getData(FILE* fd, long int fileLength);

#endif // _APPLICATION_LAYER_H_
