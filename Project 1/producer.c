/**
 * Implementation of the Producer (Transmitter)
 */
#include "producer.h"

void producer(void) {
    struct dataFrame* frame;
    char readBuffer[64];
    int readCount;
    FILE* userInput = fopen("message.inpf", "r");
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
        char synCode[17] = "";
        char msgLength[9] = "";
        char nullTerminator[1] = "\0";
        frame = malloc(sizeof(struct dataFrame));

        readCount = fread(&readBuffer, sizeof(char), 64, userInput);                            // read the next 64 characters of the message

        for(int i = 0; i < 2; i++)                                                              // create the SYN code (2222) and frame it
            strcat(synCode, addParityBit(charToBinary(22, synCode)));
        strcat(synCode, nullTerminator);
        frameData(frame, synCode, SYN);

        addParityBit(charToBinary(readCount, msgLength));                                       // frame the message length
        strcat(msgLength, nullTerminator);
        frameData(frame, msgLength, LENGTH);

        for(int i = 0; i < readCount; i++) {                                                    // frame the encoded message
            char currentChar[8] = "";
            addParityBit(charToBinary(readBuffer[i], currentChar));
            frameData(frame, currentChar, MESSAGE);
        }
        frameData(frame, nullTerminator, MESSAGE);

        if((fwrite(frame, sizeof(struct dataFrame), 1, producerOutput)) != 1) {                 // "transmit" frame by writing it to file
            perror("Error Writing Data Frame\n");
            exit(-1);
        }
    }
    free(frame);
    fclose(userInput);
    fclose(producerOutput);
}