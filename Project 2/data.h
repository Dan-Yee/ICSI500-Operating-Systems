/**
 * Specifications on the implementation of the "Physical Layer"
 * Specifies functions for converting char to binary and binary to int
 */
#include <string.h>
#include <stdlib.h>

#ifndef DATA_HEADER
#define DATA_HEADER

/**
 * Function to convert a char to a 8-bit binary string
 */
char* charToBinary(const char, char*);

/**
 * Function to convert a binary string to an int
 */
int binaryToInt(const char*);

/**
 * Function to check the parity and add a parity bit if necessary
 */
char* addParityBit(char*);

/**
 * Function to remove the odd parity bit if necessary
 */
char* removeParityBit(char*);

#endif