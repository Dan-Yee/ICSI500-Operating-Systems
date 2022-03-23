/**
 * Implementation of the Application which runs the Producer and Consumer concurrently using fork().
 */

#include "application.h"
#include "producer.h"
#include "consumer.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int communicationPipe[2];

/**
 * Function used by the Consumer to read a dataframe from the interprocess communication pipe
 */
struct dataFrame* readFromPipe(struct dataFrame* frame) {
    if(read(communicationPipe[0], frame, sizeof(struct dataFrame)) > 0) {
        return frame;
    } else {
        return NULL;
    }
}

/**
 * Function used by the Producer to write a dataframe to the interprocess communication pipe
 */
void writeToPipe(struct dataFrame* frame) {
    if((write(communicationPipe[1], frame, sizeof(struct dataFrame))) == -1) {
        perror("Error Writing To The Pipe\n");
        exit(-1);
    }
}

/**
 * Driver function that concurrently runs the Producer and Consumer with fork(), allowing them to communicate with each other via a pipe
 */
int main(int argc, char** argv) {
    if(pipe(communicationPipe) < 0) {
        perror("Error Piping\n");
        exit(-1);
    }

    pid_t pid = fork();

    if(pid > 0) {                                                           // PARENT PROCESS - used to execute the Producer
        close(communicationPipe[0]);                                        // close the reading end of the pipe
        if(argc == 5) {
            if(strcmp(argv[2], "ERRORON") == 0) {                   // enable Error Creation Module with a variable number of errors introduced to each frame
                if(strcmp(argv[4], "HAMMING") == 0) {
                    printf("Producer running using HAMMING CODE with Error Creation module ENABLED, introducing %s bit errors for each even frame\n", argv[3]);
                    printf("Input File Name: %s\n\n", argv[1]);
                    producer(argv[1], ERROR_ON, strtol(argv[3], NULL, 10), HAMMING);
                } else {
                    printf("Producer running using CRC-32 with Error Creation module ENABLED, introducing %s bit errors for each even frame\n", argv[3]);
                    printf("Input File Name: %s\n\n", argv[1]);
                    producer(argv[1], ERROR_ON, strtol(argv[3], NULL, 10), CRC);
                }
            } else {
                if(strcmp(argv[4], "HAMMING") == 0) {
                    printf("Producer running using HAMMING CODE with Error Creation module DISABLED\n");
                    printf("Input File Name: %s\n\n", argv[1]);
                    producer(argv[1], ERROR_OFF, 0, HAMMING);
                } else {
                    printf("Producer running using CRC-32 with Error Creation module DISABLED\n");
                    printf("Input File Name: %s\n\n", argv[1]);
                    producer(argv[1], ERROR_OFF, 0, CRC);
                }
            }
        } else {
            perror("Expected number of arguments is 5\n");
            exit(-1);
        }
        close(communicationPipe[1]);                                        // close the writing end of the pipe
        wait(NULL);
    } else if(pid == 0) {                                                   // CHILD PROCESS - used to execute the Consumer
        close(communicationPipe[1]);                                        // close the writing end of the pipe
        if(argc == 5) {
            if(strcmp(argv[4], "HAMMING") == 0) {
                printf("Consumer running using Hamming\n");
                consumer(HAMMING);
            } else {
                printf("Consumer running using Cyclic Redundancy Checker (CRC-32)\n");
                consumer(CRC);
            }
        } else {
            perror("Expected number of arguments is 5\n");
            exit(-1);
        }
        close(communicationPipe[0]);                                        // close the reading end of the pipe
    } else {
        perror("Error Forking a New Process\n");
        exit(-1);
    }
    return 0;
}