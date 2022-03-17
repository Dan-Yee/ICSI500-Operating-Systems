/**
 * Specifications on the implementation of a data frame for message "transmission"
 * Contains functions for the "Data Link" layer
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef DATAFRAME_HEADER
#define DATAFRAME_HEADER

/**
 * struct to represent a data frame that will be "sent"
 */
struct dataFrame {
    char synChar[17];
    char messageLength[9];
    char message[((64 * 8) + 1)];
};

enum dataEncoding {SYN, LENGTH, MESSAGE};

/**
 * Function to framing data together based on mode
 * Mode 1 - frame SYN Characters
 * Mode 2 - frame message
 */
void frameData(struct dataFrame*, char*, enum dataEncoding);

/**
 * Function to deframe the encoded data
 */
char* deframeData(struct dataFrame*, enum dataEncoding);

/**
 * For testing purposes only
 */
void testDisplay(struct dataFrame);

#endif