#include "data.h"
#include "dataFrame.h"
#include "server.h"

#ifndef SERVER_ENCODER_HEADER
#define SERVER_ENCODER_HEADER

/**
 * @brief Function used by the Server to re-encode a String (char*) after changes were made to it before sending back to the Client
 */
void sEncoder(char*);

#endif