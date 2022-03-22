/**
 * Specifications on the implementating Hamming code error detection and single-bit error correction
 */
#include "dataFrame.h"
#include "data.h"
#include <math.h>

#ifndef HAMMING_HEADER
#define HAMMING_HEADER

/**
 * Function that inserts redundant parity bits as 'p', prior to parity calculation
 */
void insertRedundantBits(struct dataFrame*);

/**
 * Function that calculates the number of redundant parity bits required for Hamming code based on the length of the message
 * Uses 2^r >= m + r + 1 where r = number of redundant bits; m = data length in bits
 */
int calcNumOfRedundant(int);

/**
 * Function executed by the Producer to calculate the hamming code word prior to "transmission"
 * This function switches all the 'p''s inserted by insertRedundantBits(...) to it's correct parity
 */
void producerHammingCode(struct dataFrame*);

#endif