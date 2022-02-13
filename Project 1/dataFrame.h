/**
 * Specifications on the implementation of a data frame for message transmission
 * Contains functions for the "Data Link" layer
 */
#include <stdlib.h>
#include <string.h>

#ifndef DATAFRAME_HEADER
#define DATAFRAME_HEADER

/**
 * struct to represent a data frame that will be "sent"
 */
struct dataFrame {
    char* synChar;
    char* messageLength;
    char* message;
};

/**
 * Function to create a new data frame
 */
void createDataFrame(struct dataFrame*);

/**
 * Function to delete an existing data frame
 */
void deleteDataFrame(struct dataFrame*);

/**
 * Function to framing data together based on mode
 * Mode 1 - frame SYN Characters
 * Mode 2 - frame message
 */
void frameData(struct dataFrame*, char*, int);

/**
 * Function to deframe the encoded data
 */
char* deframeData(struct dataFrame);

/**
 * For testing purposes only
 */
void testDisplay(struct dataFrame);

#endif