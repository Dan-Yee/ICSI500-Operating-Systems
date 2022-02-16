/**
 * Implementation of the "Physical Layer"
 * Implements functions for converting a char to binary string and parity checking
 */
#include "data.h"

/**
 * Function that converts a character to its binary form
 */
char* charToBinary(const char character, char* result) {
    char binaryStr[9] = "00000000";

    for(int i = 7, j = 0; i >= 0 && j < 8; i--, j++)
        if(character & (1 << i))
            binaryStr[j] = '1';
    binaryStr[9] = '\0';
    strcpy(result, binaryStr);

    return result;
}

/**
 * Function that converts a binary string to int
 */
int binaryToInt(const char* string) {
    return (int)strtol(string, NULL, 2);
}

/**
 * Function that flips the parity bit on a binary string with even parity
 */
char* addParityBit(char* string) {
    int bitCount = 0;

    for(int i = 0; i < strlen(string); i++)
        if(string[i] == '1')
            bitCount++;
    if(bitCount % 2 == 0)
        string[0] = '1';
    return string;
}

/**
 * Function that removes the odd parity bit if needed
 */
char* removeParityBit(char* string) {
    if(string[0] == '1')
        string[0] = '0';
    return string;
}