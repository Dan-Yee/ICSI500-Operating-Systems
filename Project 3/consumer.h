/**
 * Specifications on the implementation of the Consumer (Receiver)
 */
#include "dataFrame.h"
#include "data.h"
#include "crc.h"
#include <stdio.h>

#ifndef CONSUMER_HEADER
#define CONSUMER_HEADER

/**
 * Function to start the consumer after the Producer has finished "transmitting" data
 */
void consumer(enum detectionMode);

#endif