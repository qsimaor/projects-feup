#include "download.h"

int parse(char *input, struct URL *url) {
    regex_t regex;
    int isMatched;

    // Check if input matches BAR regex
    regcomp(&regex, BAR, 0);
    isMatched = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    if (isMatched) return -1;

    // Check if input matches AT regex
    regcomp(&regex, AT, 0);
    isMatched = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);

    if (isMatched) { //ftp://<host>/<url-path>
        sscanf(input, HOST_REGEX, url->host);
        strcpy(url->user, DEFAULT_USER);
        strcpy(url->password, DEFAULT_PASSWORD);
    } else { // ftp://[<user>:<password>@]<host>/<url-path>
        sscanf(input, HOST_AT_REGEX, url->host);
        sscanf(input, USER_REGEX, url->user);
        sscanf(input, PASS_REGEX, url->password);
    }

    sscanf(input, RESOURCE_REGEX, url->resource);
    strcpy(url->file, strrchr(input, '/') + 1);

    struct hostent *h;
    if (strlen(url->host) == 0) return -1;
    if ((h = gethostbyname(url->host)) == NULL) {
        printf("Invalid hostname '%s'\n", url->host);
        exit(-1);
    }
    strcpy(url->ip, inet_ntoa(*((struct in_addr *) h->h_addr)));

    return !(strlen(url->host) && strlen(url->user) && 
           strlen(url->password) && strlen(url->resource) && strlen(url->file));
}

int createSocket(char *ip, int port) {
    int sockfd;
    struct sockaddr_in server_addr;

    // Initialize server_addr to zeros
    memset(&server_addr, 0, sizeof(server_addr));

    // Set the values for server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    // Create the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("connect()");
        exit(EXIT_FAILURE);
    }

    return sockfd;
}

int authConn(const int socket, const char* user, const char* pass) {
    char answer[MAX_LENGTH];

    // Send user command
    dprintf(socket, "user %s\n", user);
    if (readResponse(socket, answer) != SV_READY4PASS) {
        printf("Unknown user '%s'. Abort.\n", user);
        exit(EXIT_FAILURE);
    }

    // Send password command
    dprintf(socket, "pass %s\n", pass);
    return readResponse(socket, answer);
}

int passiveMode(const int socket, char *ip, int *port) {
    char answer[MAX_LENGTH];
    int ipParts[4], portParts[2];

    // Send PASV command
    dprintf(socket, "PASV\n");
    if (readResponse(socket, answer) != SV_PASSIVE) return -1;

    // Parse the response
    sscanf(answer, PASSIVE_REGEX, &ipParts[0], &ipParts[1], &ipParts[2], &ipParts[3], &portParts[0], &portParts[1]);

    // Calculate the port number
    *port = portParts[0] * 256 + portParts[1];

    // Format the IP address
    sprintf(ip, "%d.%d.%d.%d", ipParts[0], ipParts[1], ipParts[2], ipParts[3]);

    return SV_PASSIVE;
}

int readResponse(const int socket, char* buffer) {
    char byte;
    int index = 0, responseCode;
    ResponseState state = START;
    memset(buffer, 0, MAX_LENGTH);

    while (state != END) {
        read(socket, &byte, 1);

        if (state == START) {
            if (byte == ' ') state = SINGLE;
            else if (byte == '-') state = MULTIPLE;
            else if (byte == '\n') state = END;
            else buffer[index++] = byte;
        } else if (state == SINGLE) {
            if (byte == '\n') state = END;
            else buffer[index++] = byte;
        } else if (state == MULTIPLE) {
            if (byte == '\n') {
                memset(buffer, 0, MAX_LENGTH);
                state = START;
                index = 0;
            } else buffer[index++] = byte;
        }
    }

    sscanf(buffer, RESPCODE_REGEX, &responseCode);
    return responseCode;
}

int requestResource(const int socket, char *resource) {
    char answer[MAX_LENGTH];

    // Send RETR command
    dprintf(socket, "retr %s\n", resource);

    return readResponse(socket, answer);
}

int getResource(const int socketA, const int socketB, char *filename) {
    FILE *fd = fopen(filename, "wb");
    if (fd == NULL) {
        perror("Error opening or creating file");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_LENGTH];
    ssize_t bytes;
    while ((bytes = read(socketB, buffer, MAX_LENGTH)) > 0) {
        if (fwrite(buffer, 1, bytes, fd) != bytes) {
            perror("Error writing to file");
            fclose(fd);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fd);

    return readResponse(socketA, buffer);
}

int closeConnection(const int socketA, const int socketB) {
    char answer[MAX_LENGTH];

    // Send QUIT command
    dprintf(socketA, "quit\n");
    if (readResponse(socketA, answer) != SV_GOODBYE) return -1;

    // Close the sockets
    int closeA = close(socketA);
    int closeB = close(socketB);

    return closeA || closeB;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./download ftp://[<user>:<password>@]<host>/<url-path>\n");
        exit(EXIT_FAILURE);
    } 

    struct URL url;
    memset(&url, 0, sizeof(url));
    if (parse(argv[1], &url) != 0) {
        printf("Parse error. Usage: ./download ftp://[<user>:<password>@]<host>/<url-path>\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Host: %s\nResource: %s\nFile: %s\nUser: %s\nPassword: %s\nIP Address: %s\n", url.host, url.resource, url.file, url.user, url.password, url.ip);

    char answer[MAX_LENGTH];
    int socketA = createSocket(url.ip, FTP_PORT);
    if (socketA < 0 || readResponse(socketA, answer) != SV_READY4AUTH) {
        printf("Socket to '%s' and port %d failed\n", url.ip, FTP_PORT);
        exit(EXIT_FAILURE);
    }
    
    if (authConn(socketA, url.user, url.password) != SV_LOGINSUCCESS) {
        printf("Authentication failed with username = '%s' and password = '%s'.\n", url.user, url.password);
        exit(EXIT_FAILURE);
    }
    
    int port;
    char ip[MAX_LENGTH];
    if (passiveMode(socketA, ip, &port) != SV_PASSIVE) {
        printf("Passive mode failed\n");
        exit(EXIT_FAILURE);
    }

    int socketB = createSocket(ip, port);
    if (socketB < 0) {
        printf("Socket to '%s:%d' failed\n", ip, port);
        exit(EXIT_FAILURE);
    }

    if (requestResource(socketA, url.resource) != SV_READY4TRANSFER) {
        printf("Unknown resouce '%s' in '%s:%d'\n", url.resource, ip, port);
        exit(EXIT_FAILURE);
    }

    if (getResource(socketA, socketB, url.file) != SV_TRANSFER_COMPLETE) {
        printf("Error transfering file '%s' from '%s:%d'\n", url.file, ip, port);
        exit(EXIT_FAILURE);
    }

    if (closeConnection(socketA, socketB) != 0) {
        printf("Sockets close error\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}