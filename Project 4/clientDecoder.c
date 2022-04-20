#include "clientDecoder.h"

void cDecoder(char* fileName) {
    struct dataFrame* currentFrame = malloc(sizeof(struct dataFrame));
    FILE* clientOutput = fopen("results.txt", "w");
    char* synCode;
    char* data;
    int msgLength = 0;

    if(clientOutput == NULL) {
        fprintf(stderr, "Client ERROR Opening Decoder .outf Output File\n");
        exit(1);
    }

    /**
     * cEncoder() sends an empty frame to signify the end of transmission. 
     * The Decoder should keep reading from the socket until an empty frame is received
     */
    do {                
        clientSocketRead(currentFrame);
        synCode = deframeData(currentFrame, SYN);
        msgLength = binaryToInt(removeParityBit(deframeData(currentFrame, LENGTH)));
        data = deframeData(currentFrame, MESSAGE);
        char currentChar[9] = "\0";
        char toWrite;

        if(msgLength == 0)
            break;
        for(int synCodeLoop = 0; synCodeLoop < 2; synCodeLoop++) {
            strncpy(currentChar, &synCode[synCodeLoop * 8], 8);
            currentChar[8] = '\0';

            if(binaryToInt(removeParityBit(currentChar)) != 22) {                                   // verify that the SYN code is present and correct
                fprintf(stderr, "Client Decoder ERROR: SYN Character expected but not received\n");
                exit(1);
            }
        }
        for(int decodeLoop = 0; decodeLoop < msgLength; decodeLoop++) {                             // decode the encoded message 1 character at a time
            strncpy(currentChar, &data[decodeLoop * 8], 8);
            currentChar[8] = '\0';
            toWrite = (char)binaryToInt(removeParityBit(currentChar));

            if((fwrite(&toWrite, sizeof(char), 1, clientOutput)) != 1) {                            // write the decoded character to the output file
                fprintf(stderr, "Client Decoder ERROR: Error Writing to .outf Output File\n");
                exit(1);
            }
        }
    } while(msgLength != 0);
    free(currentFrame);
    fclose(clientOutput);
}