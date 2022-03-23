/**
 * Implementation of functions used to perform Hamming code error detection and single-bit error correction
 */
#include "hamming.h"

/**
 * Function that inserts redundant parity bits as 'p', prior to parity calculation
 */
void insertRedundantBits(struct dataFrame* frame) {
    int dataLength = binaryToInt(removeParityBit(deframeData(frame, LENGTH))) * 8;
    int numOfBits = calcNumOfRedundant(dataLength);
    char* data = deframeData(frame, MESSAGE);

    for(int i = 0; i < numOfBits; i++) {
        int position = (int)(pow(2, i) - 1);
        char leftOfPosition[513] = "\0";
        char rightOfPosition[513] = "\0";
        char result[523] = "\0";

        // split the data bits in half at the position where the redundant bit goes
        strncpy(leftOfPosition, &data[0], position);
        strncpy(rightOfPosition, &data[position], 512);

        // insert the redundant parity bit represented by 'p'
        strcat(result, leftOfPosition);
        strcat(result, "p");
        strcat(result, rightOfPosition);

        // update dataCopy to contain the most recently inserted redundant parity bit
        strcpy(data, result);
    }
}

/**
 * Function that removes redundant bits inserted earlier by Hamming code
 */
void removeRedundantBits(struct dataFrame* frame) {
    int dataLength = binaryToInt(removeParityBit(deframeData(frame, LENGTH))) * 8;
    int numOfBits = calcNumOfRedundant(dataLength);
    char* data = deframeData(frame, MESSAGE);

    for(int parityCount = 0; parityCount < numOfBits; parityCount++) {
        int position = (int)pow(2, parityCount) - parityCount - 1;                                                                  // subtract parityCount to account for each parity bit removed before the next
        memmove(&data[position], &data[position + 1], strlen(data) - position);
    }
}

/**
 * Function that calculates the number of redundant parity bits required for Hamming code based on the length of the message
 * Uses 2^r >= m + r + 1 where r = number of redundant bits; m = data length in bits
 */
int calcNumOfRedundant(int dataLength) {
    int numOfRedundant = 1;
    
    while((pow(2, numOfRedundant)) <= (dataLength + numOfRedundant + 1))
        numOfRedundant++;
    return numOfRedundant;
}

/**
 * Function that calculates the parity of each redundant bit 'p' and sets it to 0 if even or 1 if odd
 * Used by the Producer to calculate the Hamming code word prior to transmission
 * Used by the Consumder to recalculate the Hamming code word after transmission
 */
void hammingCode(struct dataFrame* frame, enum executor executeMode) {
    int dataLength = binaryToInt(removeParityBit(deframeData(frame, LENGTH))) * 8;
    int numOfParityBits = calcNumOfRedundant(dataLength);
    char* hammingData = deframeData(frame, MESSAGE);
    int errorBitPosition = 0;

    for(int parityCount = 0; parityCount < numOfParityBits; parityCount++) {                                                        // controls which parity bit we are current looking at
        int checkAmount = (int)pow(2, parityCount);
        int parity = 0;

        for(int messageLoop = checkAmount - 1; messageLoop < dataLength + numOfParityBits; messageLoop += checkAmount * 2) {        // iterates through the entire message, skipping unchecked bits
            for(int parityCheck = 0; parityCheck < checkAmount; parityCheck++) {                                                    // iterates through the message, checking bits
                int bitPosition = messageLoop + parityCheck;

                if(hammingData[bitPosition] == '1')
                    parity++;
            }
        }
        if(hammingData[checkAmount - 1] == '1') parity--;                                                                           // do not include redundant bit in parity count

        if(executeMode == PRODUCER)
            hammingData[checkAmount - 1] = ((parity % 2) == 0) ? '0' : '1';                                                         // updates the redundant parity bit placeholder 'p'
        else if(executeMode == CONSUMER) {
            char recalculatedParity = ((parity % 2) == 0) ? '0' : '1';

            if(hammingData[checkAmount - 1] != recalculatedParity)                                                                  // update the position of the incorrect bit
                errorBitPosition += checkAmount;
        } else {
            perror("Execution Mode Not Recognized, expected PRODUCER or CONSUMER\n");
            exit(-1);
        }
    }
    if(executeMode == CONSUMER) {                                                                                                   // determine the position of the incorrect bit excluding redundant self
        errorBitPosition--;
        if(errorBitPosition > 0 && errorBitPosition < (dataLength + numOfParityBits)) {
            printf("Hamming Code: Error Detected at Bit %d. Error Corrected!\n", errorBitPosition); 
            hammingData[errorBitPosition] = (hammingData[errorBitPosition] == '1') ? '0' : '1';                                     // flip the incorrect bit to correct it
        }
    }
}