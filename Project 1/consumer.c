/**
 * Implementation of the Consumer (Receiver)
 */
#include "consumer.h"

void consumer(void) {
    struct dataFrame* frame = malloc(sizeof(struct dataFrame));
    FILE* consumerInput = fopen("pOutput.binf", "rb");
    FILE* consumerOutput = fopen("cOutput.outf", "w");

    if(consumerInput == NULL) {
        perror("Error Opening Producer File\n");
        exit(-1);
    }

    if(consumerOutput == NULL) {
        perror("Error Opening Consumer Output File\n");
        exit(-1);
    }

    while((fread(frame, sizeof(struct dataFrame), 1, consumerInput)) == 1) {
        char* synCode = deframeData(frame, SYN);                                                    // deframe the data frame
        char* msgLength = deframeData(frame, LENGTH);
        char* message = deframeData(frame, MESSAGE);

        int length = binaryToInt(removeParityBit(msgLength));                                       // decode the message length
        char currentChar[9];
        char toWrite;

        for(int synCodeLoop = 0; synCodeLoop < 2; synCodeLoop++) {                                  // decode the SYN Code
            strncpy(currentChar, &synCode[synCodeLoop * 8], 8);
            currentChar[8] = '\0';
            
            if(binaryToInt(removeParityBit(currentChar)) != 22) {                                   // verify that the SYN code is present and correct
                perror("SYN character expected but not received\n");
                exit(-1);
            }
        }

        for(int decodeLoop = 0; decodeLoop < length; decodeLoop++) {                                // decode the encoded message 1 character at a time
            strncpy(currentChar, &message[decodeLoop * 8], 8);
            currentChar[8] = '\0';
            toWrite = (char)binaryToInt(removeParityBit(currentChar));

            if((fwrite(&toWrite, sizeof(char), 1, consumerOutput)) != 1) {                          // write the decoded character to the output file
                perror("Error Writing to Consumer Output\n");
                exit(-1);
            }
        }
    }
    free(frame);
    fclose(consumerInput);
    fclose(consumerOutput);
}