/**
 * Implementation of the Error Creation module 
 */
#include "errorModule.h"
#include "data.h"

/**
 * Function that introduces a variable number of errors to the message of a dataFrame
 */
struct dataFrame* addErrors(struct dataFrame* frame, int numOfErrors) {
    for(int i = 0; i < numOfErrors; i++) {
        int randBit = rand() % ((binaryToInt(removeParityBit(frame->messageLength))) * 8);                      // pick a random bit from within the message of the frame
        
        printf("Random Bit: %d\n", randBit);
        printf("Error Byte: %d\n", (randBit / 8));
        printf("Error Bit: %d\n", (randBit - ((randBit / 8) * 8)));
        
        (frame->message)[randBit] = ((frame->message)[randBit] == '0') ? '1' : '0';                             // introduce the error by flipping the bit
    }
    printf("\n");
    return frame;
}