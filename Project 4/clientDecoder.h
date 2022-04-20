#include "data.h"
#include "dataFrame.h"
#include "client.h"

#ifndef CLIENT_DECODER_HEADER
#define CLIENT_DECODER_HEADER

/**
 * Function that decodes the dataframes received from the server through a Socket
 * @param int the number of frames expected to be decoded
 */
void cDecoder(char*);

#endif