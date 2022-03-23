/**
 * Specifications on the implementation of the application - used to concurrently run the Producer and Consumer.
 */ 
#include "dataFrame.h"
#include "crc.h"
#include "hamming.h"

#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

enum detectionMode {CRC, HAMMING};                                          // enum for allowing the user to decide between using CRC or Hamming

/**
 * Used by the Consumer to read a dataframe from the pipe for interprocess communication
 */
struct dataFrame* readFromPipe(struct dataFrame*);

/**
 * Used by the Producer to write a dataframe to the pipe for interprocess communication
 */
void writeToPipe(struct dataFrame*);

#endif