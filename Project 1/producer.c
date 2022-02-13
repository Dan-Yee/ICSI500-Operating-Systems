#include "producer.h"

void producer(void) {
    struct dataFrame frame;
    char result[9];
    FILE* userInput = fopen("message.inpf", "r");
    FILE* producerOutput = fopen("pOutput.binf", "w");
    char readBuffer[64];
    int readCount, writeCount;

    if(userInput == NULL) {
        perror("Error Opening Input File\n");
        exit(-1);
    }
    
    while(!feof(userInput)) {
        readCount = fread(&readBuffer, sizeof(char), 64, userInput);

        createDataFrame(&frame);                                                            // create the data frame to be "transmitted"

        charToBinary(22, result);                                                           // add the SYN code (2222) to the data frame
        addParityBit(result);
        frameData(&frame, result, 1);
        frameData(&frame, result, 1);

        charToBinary(readCount, result);                                                    // add the message length to the data frame
        addParityBit(result);
        frameData(&frame, result, 2);

        for(int i = 0; i < readCount; i++) {                                                // encode message in odd bit parity binary and add to data frame
            char currentChar = readBuffer[i];
            charToBinary(currentChar, result);
            addParityBit(result);
            frameData(&frame, result, 3);
        }
        testDisplay(frame);

        writeCount = fwrite(&frame, sizeof(struct dataFrame), 1, producerOutput);           // "transmit" frame by writing it to file
        deleteDataFrame(&frame);                                                            // delete the data frame that has been transmitted
    }
    fclose(userInput);
    fclose(producerOutput);
}