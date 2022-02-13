#include "producer.h"
#include <stdio.h>

int main(void) {
    // Testing charToBinary and parityBit functions
    char c = 'A';
    char result[9];

    /*printf("'%c' in 8-bit binary is %s\n", c, charToBinary(c, result));
    printf("As an Integer, result is %d\n", binaryToInt(result));
    printf("After addParityBit() is %s\n", addParityBit(result));
    printf("After removeParityBit() is %s\n", removeParityBit(result));
    printf("As an Integer, result is %d\n", binaryToInt(result));*/

    // Testing dataFrame struct and related functions
    /*struct dataFrame frame;

    createDataFrame(&frame);
    charToBinary(22, result);
    addParityBit(result);
    frameData(&frame, result, 1);
    frameData(&frame, result, 1);

    charToBinary(3, result);
    addParityBit(result);
    frameData(&frame, result, 2);

    c = 'A';
    charToBinary(c, result);
    addParityBit(result);
    frameData(&frame, result, 3);

    c = 'B';
    charToBinary(c, result);
    addParityBit(result);
    frameData(&frame, result, 3);

    c = 'C';
    charToBinary(c, result);
    addParityBit(result);
    frameData(&frame, result, 3);

    testDisplay(frame);

    deleteDataFrame(&frame);*/

    producer();
}