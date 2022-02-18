/**
 * Implementation of the Error Creation module 
 */
#include "errorCreate.h"
#include <stdio.h>
#include "data.h"

/**
 * Function that introduces a variable number of errors to the message of a dataFrame
 */
struct dataFrame* addErrors(struct dataFrame* frame, int numOfErrors) {
    for(int i = 0; i < numOfErrors; i++) {
        int randBit = rand() % ((binaryToInt(removeParityBit(frame->messageLength))) * 8);                      // pick a random bit from within the message of the frame

        printf("Error Byte: %d\n", (randBit / 8));
        printf("Error Bit: %d\n", (randBit - ((randBit / 8) * 8)));

        if((frame->message)[randBit] == 0)                                                                      // introduce the error by flipping the bit
            (frame->message)[randBit] = 1;
        else
            (frame->message)[randBit] = 0;
    }
    printf("\n");
    return frame;
}