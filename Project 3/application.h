/**
 * Specifications on the implementation of the application - used to concurrently run the Producer and Consumer.
 */ 
#include "dataFrame.h"

#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

/**
 * Used by the Consumer to read a dataframe from the pipe for interprocess communication
 */
struct dataFrame* readFromPipe(struct dataFrame*);

/**
 * Used by the Producer to write a dataframe to the pipe for interprocess communication
 */
void writeToPipe(struct dataFrame*);

#endif