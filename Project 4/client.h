#include "dataFrame.h"

#ifndef CLIENT_HEADER
#define CLIENT_HEADER

/**
 * Function used by the client's Producer to encode and write dataframe's to the socket 
 */
void clientSocketWrite(struct dataFrame*);

/**
 * Function used by the client's Consumer to read and decode the dataframe received from the server through the socket
 * 
 * @return struct dataFrame* 
 */
struct dataFrame* clientSocketRead(struct dataFrame*);

/* Used for data frames, testing with strings first
void clientSocketWrite(struct dataFrame*);

struct dataFrame* clientSocketRead(struct dataFrame*);
*/

#endif