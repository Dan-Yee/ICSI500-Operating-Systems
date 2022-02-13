/**
 * Implementation of a Data Frame
 */
#include "dataFrame.h"
#include <stdio.h>

/**
 * Function to create a new data frame
 */
void createDataFrame(struct dataFrame* frame) {
    frame->synChar = (char*)malloc(16 * sizeof(char));
    frame->messageLength = (char*)malloc(8 * sizeof(char));
    frame->message = (char*)malloc((64 * 8) * sizeof(char));
}

/**
 * Function to delete an existing data frame
 */
void deleteDataFrame(struct dataFrame* frame) {
    free(frame->synChar);
    free(frame->messageLength);
    free(frame->message);
}

/**
 * Function to framing data together based on mode
 * Mode 1 - frame SYN Characters
 * Mode 2 - frame message
 */
void frameData(struct dataFrame* frame, char* binaryChar, int mode) {
    switch(mode) {
        case 1:
            strcat(frame->synChar, binaryChar);
            break;
        case 2:
            strcpy(frame->messageLength, binaryChar);
            break;
        case 3:
            strcat(frame->message, binaryChar);
            break;
        default:
            perror("Invalid Frame Mode Specified");
            exit(-1);
            break;
    }
}

/**
 * Function to deframe the encoded data
 */
char* deframeData(struct dataFrame frame) {
    return frame.message;
}

/**
 * Displays the data frame for testing purposes
 */
void testDisplay(struct dataFrame frame) {
    printf("SYN Char: %s\n", frame.synChar);
    printf("Message Length: %s\n", frame.messageLength);
    printf("Encoded Message: %s\n", frame.message);
}