#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "client.h"
#include "clientEncoder.h"
#include "clientDecoder.h"

int sockfd, portNo, n;
struct sockaddr_in server_address;
struct hostent* server;

/**
 * @brief Function used by the Client's Producer to write data frame's to the socket 
 * @param frame the frame to be written
 */
void clientSocketWrite(struct dataFrame* frame) {
    if(write(sockfd, frame, sizeof(struct dataFrame)) < 0) {
        fprintf(stderr, "Client ERROR Writing To Socket\n");
        exit(1);
    }
}

/**
 * @brief Function used by the Client's Consumer to read data frame's from the socket
 * @param frame location to store the data frame read from the socket
 * @return struct dataFrame* the data frame read from the socket
 */
struct dataFrame* clientSocketRead(struct dataFrame* frame) {
    if(read(sockfd, frame, sizeof(struct dataFrame)) < 0) {
        fprintf(stderr, "Client ERROR Reading From Socket\n");
        exit(1);
    }
    return frame;
}

/**
 * Main function that controls the Client's connection to the Server using a Socket 
 */
int main(int argc, char** argv) {
    if(argc < 3) {                                                      // ensure the minimum number of arguments is supplied to the program
        fprintf(stderr, "Usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portNo = atoi(argv[2]);                                             // get the port number from command line
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {                // create the Socket and check for errors
        fprintf(stderr, "ERROR opening socket\n");
        exit(0);
    }

    if((server = gethostbyname(argv[1])) == NULL) {                     // Ensure the Server exists on the provided hostname before continuing
        fprintf(stderr, "ERROR, unknown host name\n");
        exit(0);
    }

    bzero((char*)&server_address, sizeof(server_address));              // setup communications information
    server_address.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char*)&server_address.sin_addr.s_addr, server->h_length);
    server_address.sin_port = htons(portNo);

    // connect to the Server through the Socket and check for errors
    if(connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {   
        fprintf(stderr, "ERROR connecting. Check server address or port number\n");
        exit(0);
    }

    char fileName[255];
    printf("Enter Input File Name: ");
    scanf("%s", fileName);

    pid_t pid = fork();
    if(pid > 0) {                                                       // PARENT process executes client side encoder
        cEncoder(fileName);
        wait(NULL);
    } else if(pid == 0) {                                               // CHILD process executes client side decoder
        cDecoder(fileName);
    } else {
        fprintf(stderr, "Client ERROR: Error executing fork();\n");
        exit(1);
    }
    close(sockfd);
    return 0;
}