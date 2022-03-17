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
        close(communicationPipe[0]);                                        // close the reading end of the ppipe
        if(argc == 4 && strtol(argv[2], NULL, 10) == 1) {                   // enable Error Creation Module with a variable number of errors introduced to each frame
            printf("Producer running with Error Creation module ENABLED, introducing %s bit errors for each even frame\n\n", argv[2]);
            printf("Input File Name: %s\n", argv[1]);
            producer(argv[1], ERROR_ON, strtol(argv[3], NULL, 10));
        } else {
            printf("Producer running with Error Creation module DISABLED\n\n");
            producer(argv[1], ERROR_OFF, 0);
        }
        close(communicationPipe[1]);                                        // close the writing end of the pipe
    } else if(pid == 0) {                                                   // CHILD PROCESS - used to execute the Consumer
        close(communicationPipe[1]);                                        // close the writing end of the pipe
        consumer();
        close(communicationPipe[0]);                                        // close the reading end of the pipe
    } else {
        perror("Error Forking a New Process\n");
        exit(-1);
    }
    return 0;
}