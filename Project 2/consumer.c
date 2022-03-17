/**
 * Implementation of the Consumer (Receiver)
 */
#include "application.h"
#include "consumer.h"

void consumer(void) {
    struct dataFrame* frame = malloc(sizeof(struct dataFrame));
    FILE* consumerNormalOutput = fopen("cOutput.outf", "w");
    FILE* consumerUppercaseOutput = fopen("cUppercase.outf", "w");

    if(consumerNormalOutput == NULL) {
        perror("Error Opening Consumer Normal Output File\n");
        exit(-1);
    }

    if(consumerUppercaseOutput == NULL) {
        perror("Error Opening Consumer Uppercase Output File\n");
        exit(-1);
    }

    while(readFromPipe(frame) != NULL) {                                                            // readFromPipe returns NULL when no more data to read
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

            if((fwrite(&toWrite, sizeof(char), 1, consumerNormalOutput)) != 1) {                    // write the decoded character to the output file
                perror("Error Writing to Consumer Normal Output\n");
                exit(-1);
            }

            toWrite = (toWrite > 96 && toWrite < 123) ? (toWrite - 32) : toWrite;
            if((fwrite(&toWrite, sizeof(char), 1, consumerUppercaseOutput)) != 1) {                 // write the decoded character as an uppercase (if applicable) to another output file
                perror("Error Writing to Consumer Uppercase Output\n");
                exit(-1);
            }
        }
    }
    free(frame);
    fclose(consumerNormalOutput);
    fclose(consumerUppercaseOutput);
}