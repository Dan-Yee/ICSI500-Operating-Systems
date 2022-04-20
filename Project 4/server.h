#include "dataFrame.h"

#ifndef SERVER_HEADER
#define SERVER_HEADER

/**
 * Function used by the server to write a dataframe to the socket back to the client
 */
void serverSocketWrite(struct dataFrame*);

/**
 * Function used by the server to read a dataframe from the socket from the client
 * @return struct dataFrame* the dataframe sent by the client and read by the server through the socket
 */
struct dataFrame* serverSocketRead(struct dataFrame*);

#endif