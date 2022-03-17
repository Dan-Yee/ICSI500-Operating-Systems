/**
 * Implementation of the Producer (Transmitter)
 */
#include "application.h"
#include "producer.h"
#include "errorModule.h"

void producer(char* fileName, enum producerMode mode, int numOfErrors) {
    srand(time(0));
    struct dataFrame* frame;
    char readBuffer[64];
    int readCount, frameCount = 0;
    FILE* userInput = fopen(fileName, "r");
    FILE* producerOutput = fopen("pOutput.binf", "wb");

    if(userInput == NULL) {
        perror("Error Opening Input File\n");
        exit(-1);
    }

    if(producerOutput == NULL) {
        perror("Error Opening Producer Output File\n");
        exit(-1);
    }
    
    while(!feof(userInput)) {                                                                   // read until end of input file
        char synCode[17] = "\0";
        char msgLength[9] = "\0";
        char checkSumBin[33] = "\0";
        frameCount++;
        frame = malloc(sizeof(struct dataFrame));

        readCount = fread(&readBuffer, sizeof(char), 64, userInput);                            // read the next 64 characters of the message

        for(int i = 0; i < 2; i++)                                                              // create the SYN code (2222) and frame it
            strcat(synCode, addParityBit(charToBinary(22, synCode)));
        strcat(synCode, "\0");
        frameData(frame, synCode, SYN);

        addParityBit(charToBinary(readCount, msgLength));                                       // frame the message length
        strcat(msgLength, "\0");
        frameData(frame, msgLength, LENGTH);

        for(int i = 0; i < readCount; i++) {                                                    // frame the encoded message
            char currentChar[8] = "";
            addParityBit(charToBinary(readBuffer[i], currentChar));
            frameData(frame, currentChar, MESSAGE);
        }
        frameData(frame, "\0", MESSAGE);

        // Append CRC-32 Checksum Calculation to data frame
        uLongToBinary(crc_32(frame), checkSumBin);
        frameData(frame, checkSumBin, CHECKSUM);

        // Error Creation Module
        if(mode == ERROR_ON) {
            if(frameCount % 2 == 0) {
                printf("Error(s) Introduced to Frame %d\n", frameCount);
                addErrors(frame, numOfErrors);
            }
        }

        writeToPipe(frame);                                                                     // write the frame to the Pipe for the Consumer to read from

        if((fwrite(frame, sizeof(struct dataFrame), 1, producerOutput)) != 1) {                 // "transmit" frame by writing it to file
            perror("Error Writing Data Frame\n");
            exit(-1);
        }
    }
    free(frame);
    fclose(userInput);
    fclose(producerOutput);
}