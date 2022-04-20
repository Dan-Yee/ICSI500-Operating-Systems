#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
#include "serverEncoder.h"
#include "serverDecoder.h"
#include "serverThreads.h"

int sockfd, newSockfd, portNo;
socklen_t clilen;
char buffer[256];
struct sockaddr_in server_address, client_address;
int n;

/**
 * @brief Function used by the Server to send data frames back to the Client over a socket
 * @param frame the frame being transmitted
 */
void serverSocketWrite(struct dataFrame* frame) {
    if(write(newSockfd, frame, sizeof(struct dataFrame)) < 0) {
        fprintf(stderr, "Server ERROR Writing To Socket\n");
        exit(1);
    }
}

/**
 * @brief Function used by the Server to read data frames sent by the Client over a socket
 * @param frame location to store the data frame read
 * @return struct dataFrame* - the data frame that was read
 */
struct dataFrame* serverSocketRead(struct dataFrame* frame) {
    if(read(newSockfd, frame, sizeof(struct dataFrame)) < 0) {
        return NULL;
    }
    return frame;
}

int main(int argc, char** argv) {
    if(argc < 2) {                                                                          // server must run on a port
        fprintf(stderr, "Server ERROR, no port provided\n");
        exit(1);
    }
    fprintf(stdout, "Run the Client by providing the Host and Port\n");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);                                               // create the server side socket
    if(sockfd < 0) {
        fprintf(stderr, "Server ERROR opening socket\n");
        exit(1);
    }

    bzero((char *)&server_address, sizeof(server_address));
    portNo = atoi(argv[1]);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(portNo);

    if(bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        fprintf(stderr, "Server ERROR binding to socket\n");
        exit(1);
    }

    listen(sockfd, 5);                                                                      // listen to a maximum of 5 clients at a time

    while(1) {                                                                              // infinite loop for the server to constantly beable to able to accept a client
        clilen = sizeof(client_address);
        newSockfd = accept(sockfd, (struct sockaddr*)&client_address, &clilen);
        if(newSockfd < 0) {
            fprintf(stderr, "Server ERROR on accept\n");
            exit(1);
        }
        
        char buffer[2000] = "\0";
        strcpy(buffer, sDecoder(buffer));                                                   // decode all incoming frames
        buffer[strlen(buffer)] = '\0';
        threadFunc(buffer);                                                                 // execute thread functions to modify data
        buffer[strlen(buffer)] = '\0';
        sEncoder(buffer);                                                                   // re-encode data and transmit back to client
        memset(buffer, 0, sizeof(buffer));                                                  // clear the buffer for the next client
    }
    close(newSockfd);
    close(sockfd);
    return 0;
}