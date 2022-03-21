/**
 * Specifications on the implementation of the Error Detection module
 */
#include "dataFrame.h"

#ifndef CRC_HEADER
#define CRC_HEADER

/**
 * Function that calculates the checksum of a dataframe using CRC-32
 */
unsigned long crc_32(struct dataFrame*);

/**
 * Function that converts an unsigned long to its 32-bit binary representation - used to convert CRC-32 checksum
 */
char* uLongToBinary(unsigned long, char*);

/**
 * Function that converts a 32-bit binary str to its unsigned long value - convert CRC-32 checksum back to long
 */
unsigned long longBinaryToLong(const char*);

#endif