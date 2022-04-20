#include "data.h"
#include "dataFrame.h"
#include "client.h"

#ifndef CLIENT_ENCODER_HEADER
#define CLIENT_ENCODER_HEADER

/**
 * Function that encodes the data from a specified file into dataframes
 * @return int - the number of data frames sent to the server
 */
void cEncoder(char*);

#endif