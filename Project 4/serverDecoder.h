#include "data.h"
#include "dataFrame.h"
#include "server.h"

#ifndef SERVER_DECODER_HEADER
#define SERVER_DECODER_HEADER

/**
 * @brief Function used by the Server that decodes all data frames sent to the server by the client
 * @return char* the decoded message string is returned and used as a parameter for sEncoder() after threads are executed
 */
char* sDecoder(char*);

#endif