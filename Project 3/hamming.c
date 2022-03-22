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
    char dataCopy[523];

    strncpy(dataCopy, &data[0], 523);                                       // copy the message to prevent changes to the original message due to the use of pointers

    for(int i = 0; i < numOfBits; i++) {
        int position = (int)(pow(2, i) - 1);
        char leftOfPosition[513] = "\0";
        char rightOfPosition[513] = "\0";
        char result[523] = "\0";

        // split the data bits in half at the position where the redundant bit goes
        strncpy(leftOfPosition, &dataCopy[0], position);
        strncpy(rightOfPosition, &dataCopy[position], 512);

        // insert the redundant parity bit represented by 'p'
        strcat(result, leftOfPosition);
        strcat(result, "p");
        strcat(result, rightOfPosition);

        // update dataCopy to contain the most recently inserted redundant parity bit
        strcpy(dataCopy, result);
    }
    frameData(frame, dataCopy, HAMMINGCODE);
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
 */
void producerHammingCode(struct dataFrame* frame) {
    int dataLength = binaryToInt(removeParityBit(deframeData(frame, LENGTH))) * 8;
    int numOfParityBits = calcNumOfRedundant(dataLength);
    char* hammingData = deframeData(frame, HAMMINGCODE);

    for(int parityCount = 0; parityCount < numOfParityBits; parityCount++) {                                                        // controls which parity bit we are current looking at
        int checkAmount = (int)pow(2, parityCount);
        int parity = 0;

        for(int messageLoop = checkAmount - 1; messageLoop < dataLength + numOfParityBits; messageLoop += checkAmount * 2) {        // iterates through the entire message, skipping unchecked bits
            for(int parityCheck = 0; parityCheck < checkAmount; parityCheck++) {                                                    // iterates through the message, checking bits
                int bitPosition = messageLoop + parityCheck;
                if(hammingData[bitPosition] == 'p' || hammingData[bitPosition] == '0')
                    continue;
                else if(hammingData[bitPosition] == '1')
                    parity++;
            }
        }
        if((parity % 2) == 0)                                                                                                       // updates the redundant parity bit placeholder 'p'
            hammingData[checkAmount - 1] = '0';
        else
            hammingData[checkAmount - 1] = '1';
    }
}