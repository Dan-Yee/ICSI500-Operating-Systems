#include "serverEncoder.h"

/**
 * @brief Function used by the Server to re-encode the decoded data after changes were made so it can be transmitted back to the client
 * @param message the message to be encoded
 */
void sEncoder(char* message) {
    struct dataFrame* newFrame = malloc(sizeof(struct dataFrame));
    struct dataFrame* emptyFrame = malloc(sizeof(struct dataFrame));
    char buffer[65] = "\0";
    char synCode[17] = "\0";
    char msgLength[9] = "\0";
    int encodeLoop = 0;

    frameData(emptyFrame, "0001011000010110", SYN);                                         // create an empty frame to be transmitted to signify end of transmission
    frameData(emptyFrame, "00000000", LENGTH);
    frameData(emptyFrame, "\0", MESSAGE);

    for(int i = 0; i < 2; i++)                                                              // create the SYN code (2222) and frame it
        strcat(synCode, addParityBit(charToBinary(22, synCode)));
    strcat(synCode, "\0");

    do {
        newFrame = malloc(sizeof(struct dataFrame));
        frameData(newFrame, synCode, SYN);
        strncpy(buffer, &message[encodeLoop * 64], 64);
        strcat(buffer, "\0");
        addParityBit(charToBinary(strlen(buffer), msgLength));                              // frame the message length
        strcat(msgLength, "\0");
        frameData(newFrame, msgLength, LENGTH);

        for(int charLoop = 0; charLoop < strlen(buffer); charLoop++) {                      // frame the encoded message
            char currentChar[8] = "\0";
            addParityBit(charToBinary(buffer[charLoop], currentChar));
            frameData(newFrame, currentChar, MESSAGE);
        }
        frameData(newFrame, "\0", MESSAGE);
        serverSocketWrite(newFrame);
        encodeLoop++;
    } while(encodeLoop * 64 < strlen(message));
    serverSocketWrite(emptyFrame);                                                          // transmit empty frame to signify end of transmission
    free(newFrame);
    free(emptyFrame);
}