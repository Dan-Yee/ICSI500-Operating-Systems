/**
 * Specifications on the implementation of the Error Detection module
 */
#include "dataFrame.h"

#ifndef ERROR_DETECTION
#define ERROR_DETECTION

enum detectionMode {CRC, HAMMING};                                          // enum for allowing the user to decide between using CRC or Hamming

/**
 * Function that calculates the checksum of a dataframe using CRC-32
 */
unsigned long crc_32(struct dataFrame*);

/**
 * Function that calculates the Hamming code of a dataframe and perform single-bit error correction if needed
 */
void hamming(struct dataFrame*);

#endif