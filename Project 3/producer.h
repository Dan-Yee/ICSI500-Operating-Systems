/**
 * Specifications on the implementation of the Producer (transmitter)
 */
#include "dataFrame.h"
#include "data.h"
#include "errorModule.h"
#include "application.h"
#include <stdio.h>

#ifndef PRODUCER_HEADER
#define PRODUCER_HEADER

enum producerMode {ERROR_OFF, ERROR_ON};                        // enum for testing purposes - ERROR_ON enables the Error Creation Model, otherwise it is disabled

/**
 * Function to start the "transmission" based on message from data file
 */
void producer(char*, enum producerMode, int, enum detectionMode);

#endif