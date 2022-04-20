#include "clientEncoder.h"

/**
 * @brief Function that encodes the data from a specified file into dataframes
 * @param fileName the file to read and encode data from
 * @return int - the total number of data frames sent to the server
 */
void cEncoder(char* fileName) {
    struct dataFrame* newFrame;
    struct dataFrame* emptyFrame = malloc(sizeof(struct dataFrame));
    char readBuffer[64];
    int fileReadCount = 0;
    char synCode[17] = "\0";
    char binfFile[255] = "\0";
    FILE* clientInputFile = fopen(fileName, "r");

    frameData(emptyFrame, "0001011000010110", SYN);                                         // create an empty frame to be transmitted to signify end of transmission
    frameData(emptyFrame, "00000000", LENGTH);
    frameData(emptyFrame, "\0", MESSAGE);

    if(clientInputFile == NULL) {
        fprintf(stderr, "Client Encoder ERROR: Error Opening Client Input File\n");
        exit(1);
    }

    for(int i = 0; i < 2; i++)                                                              // create the SYN code (2222) and frame it
        strcat(synCode, addParityBit(charToBinary(22, synCode)));
    strcat(synCode, "\0");

    while(!feof(clientInputFile)) {
        char msgLength[9] = "\0";
        newFrame = malloc(sizeof(struct dataFrame));

        fileReadCount = fread(&readBuffer, sizeof(char), 64, clientInputFile);

        frameData(newFrame, synCode, SYN);                                                  // frame the SYN code
        addParityBit(charToBinary(fileReadCount, msgLength));                               // frame the message length
        strcat(msgLength, "\0");
        frameData(newFrame, msgLength, LENGTH);

        for(int i = 0; i < fileReadCount; i++) {                                            // frame the encoded message
            char currentChar[8] = "";
            addParityBit(charToBinary(readBuffer[i], currentChar));
            frameData(newFrame, currentChar, MESSAGE);
        }
        frameData(newFrame, "\0", MESSAGE);

        clientSocketWrite(newFrame);                                                        // send to server through Socket
    }
    clientSocketWrite(emptyFrame);                                                          // send an empty frame to signify the end of transmission
    free(newFrame);
    free(emptyFrame);
    fclose(clientInputFile);
}