#ifndef _LINK_LAYER_H_
#define _LINK_LAYER_H_

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define _POSIX_SOURCE 1
#define BAUDRATE 38400
#define MAX_PAYLOAD_SIZE 1000

#define BUF_SIZE 256
#define FALSE 0
#define TRUE 1

#define FLAG 0x7E
#define ESC 0x7D
#define A_ER 0x03
#define A_RE 0x01
#define C_SET 0x03
#define C_DISC 0x0B
#define C_UA 0x07
#define C_ACKNOWLEDGE(Nr) ((Nr << 7) | 0x05)
#define C_REJECTION(Nr) ((Nr << 7) | 0x01)
#define C_CONTROL(Ns) (Ns << 6)

typedef enum
{
   LlTx,
   LlRx,
} LinkLayerRole;

typedef enum {
    START,
    FLAG_RCV,
    ADDRESS_RCV,
    CONTROL_RCV,
    BCC1_OK,
    STOP_R,
    DATA_FOUND_ESC,
    READING_DATA,
    DISCONNECTED,
    BCC2_OK
} LinkLayerState;

typedef struct
{
    char serialPort[50];
    LinkLayerRole role;
    int baudRate;
    int nRetransmissions;
    int timeout;
} LinkLayer;


// Estabelece a conexão da camada de ligação de dados
int llopen(LinkLayer connectionParameters);

// Envia um pacote de dados pela camada de ligação
int llwrite(int descriptor, const unsigned char *dataBuffer, int bufferSize); 

// Espera e recebe um pacote de controlo
unsigned char secondaryReceiver(int descriptor);

// Realiza a função do transmissor primário
int primaryTransmitter(int descriptor, unsigned char *packet, int packetIdx);

// Lê e processa um pacote de dados
int llread(int fd, unsigned char *packet);

// Fecha a conexão da camada de ligação de dados
int llclose(int fd);

// Processa um byte recebido
void processReceivedByte(LinkLayerState* state, unsigned char byte);

// Realiza a configuração inicial da porta série
int connection(const char* port);

// Gerencia o sinal de alarme durante a comunicação
void alarmHandler(int signal);

// Lê o controlo da porta série
unsigned char readControlFrame (int portDescriptor);

//  Envia a supervisão
int sendSupervisionFrame(int portDescriptor, unsigned char addressField, unsigned char controlField);

#endif // _LINK_LAYER_H_


