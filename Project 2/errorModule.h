/**
 * Specifications on the implementation of the Error Creation Module
 */
#include <time.h>
#include "dataFrame.h"

#ifndef ERROR_HEADER
#define ERROR_HEADER

/**
 * Function that introduces a variable number of errors to the message of a data frame
 */
struct dataFrame* addErrors(struct dataFrame*, int);

#endif