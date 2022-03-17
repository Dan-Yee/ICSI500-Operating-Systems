/**
 * Implementation of the error detection modules which uses CRC and Hamming
 */
#include "errorDetection.h"
#include "data.h"
#include "dataFrame.h"
#include <zlib.h>

/**
 * Function that calculates the checksum of a dataframe using CRC-32 and appends the value to the end of the frame for transmission
 */
unsigned long crc_32(struct dataFrame* frame) {
    char encodedMessage[539] = "\0";
    char decodedMessage[67] = "\0";
    char decodedChar;
    int messageLength = binaryToInt(removeParityBit(deframeData(frame, LENGTH))); 

    strcat(encodedMessage, deframeData(frame, SYN));                                                    // combine all of the data frame into one String to apply CRC-32 to entire frame
    strcat(encodedMessage, deframeData(frame, LENGTH));
    strcat(encodedMessage, deframeData(frame, MESSAGE));

    for(int decodeLoop = 0; decodeLoop < (messageLength + 3); decodeLoop++) {                           // decode the entire message as one String
        char currentChar[9];
        strncpy(currentChar, &encodedMessage[decodeLoop * 8], 8);
        decodedChar = binaryToInt(removeParityBit(currentChar));
        strcat(decodedMessage, &decodedChar);
    }

    return crc32(0, (const void*)decodedMessage, strlen(decodedMessage));                               // calculate and return the CRC-32 checksum using zlib.crc32(...)
}

/**
 * Function that converts an unsigned long to its corresponding 32-bit binary representation 
 */
char* uLongToBinary(unsigned long value, char* result) {
    char binaryStr[33] = "00000000000000000000000000000000";

    for(int i = 31, j = 0; i >= 0 && j < 32; i--, j++)
        if((value >> i) & 1)
            binaryStr[j] = '1';
    binaryStr[33] = '\0';
    strcpy(result, binaryStr);

    return result;
}

/**
 * Function that converts a 32-bit binary string to its unsigned long value
 */
unsigned long longBinaryToLong(const char* string) {
    return (long)strtoll(string, NULL, 2);
}

/**
 * Function that calculates the Hamming code of a dataframe and perform single-bit error correction if needed
 */
void hamming(struct dataFrame* frame) {

}