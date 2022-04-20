#include "serverDecoder.h"

/**
 * @brief Function used by the server to decode the message of all data frames received from the client
 * @param buffer location to store the entire decoded message
 * @return char* the entire decoded message
 */
char* sDecoder(char* buffer) {
    struct dataFrame* currentFrame = malloc(sizeof(struct dataFrame));
    char* synCode;
    char* data;
    char toWrite;
    char currentChar[9] = "\0";
    char totalBuffer[100000];
    int msgLength;
    int decodedLength = 0;

    memset(totalBuffer, 0, sizeof(totalBuffer));                                                        // clear the buffer to prevent interference of data between clients
    // continually tries to extract all the messages from every frame sent by the client until an empty frame is detected
    do {
        serverSocketRead(currentFrame);
        msgLength = binaryToInt(removeParityBit(deframeData(currentFrame, LENGTH)));
        synCode = deframeData(currentFrame, SYN);

        if(msgLength == 0)
            break;
        decodedLength += msgLength;

        for(int synCodeLoop = 0; synCodeLoop < 2; synCodeLoop++) {
            strncpy(currentChar, &synCode[synCodeLoop * 8], 8);
            currentChar[8] = '\0';

            if(binaryToInt(removeParityBit(currentChar)) != 22) {                                       // verify that the SYN code is present and correct
                fprintf(stderr, "Server Decoder ERROR: SYN Character expected but not received\n");
                exit(1);
            }
        }
        data = deframeData(currentFrame, MESSAGE);
        strcat(totalBuffer, data);
    } while(msgLength != 0);
    strcat(totalBuffer, "\0");

    for(int decodeLoop = 0; decodeLoop < decodedLength * 8; decodeLoop++) {                             // decode the encoded message 1 character at a time
        strncpy(currentChar, &totalBuffer[decodeLoop * 8], 8);
        currentChar[8] = '\0';
        toWrite = (char)binaryToInt(removeParityBit(currentChar));
        strcat(buffer, &toWrite);
        buffer[decodeLoop + 1] = '\0';
    }
    free(currentFrame);
    return buffer;
}