/**
 * Implementation of a Data Frame for message "transmission"
 */
#include "dataFrame.h"
#include "data.h"

/**
 * Function to framing data together based on mode:
 * Mode SYN: SYN Code (2222)
 * Mode LENGTH: Message Length
 * Mode MESSAGE: Encoded Message
 */
void frameData(struct dataFrame* frame, char* binaryStr, enum dataEncoding mode) {
    switch(mode) {
        case SYN:
            strcpy(frame->synChar, binaryStr);
            break;
        case LENGTH:
            strcpy(frame->messageLength, binaryStr);
            break;
        case MESSAGE:
            strcat(frame->message, binaryStr);
            break;
        default:
            perror("Invalid Mode Specified. Expected: SYN or LENGTH or MESSAGE or CHECKSUM\n");
            exit(-1);
            break;
    }
}

/**
 * Function to deframe the encoded data based on mode:
 * Mode SYN: SYN Code (2222)
 * Mode LENGTH: Message Length
 * Mode MESSAGE: Encoded Message
 */
char* deframeData(struct dataFrame* frame, enum dataEncoding mode) {
    switch(mode) {
        case SYN:
            return frame->synChar;
            break;
        case LENGTH:
            return frame->messageLength;
            break;
        case MESSAGE:
            return frame->message;
            break;
        default:
            perror("Invalid Mode Specified. Expected: SYN or LENGTH or MESSAGE or CHECKSUM\n");
            exit(-1);
            break;
    }
}

/**
 * Displays all relevant information of the data frame
 */
void displayFrame(struct dataFrame frame) {
    printf("SYN Char: %s\n", frame.synChar);
    printf("Message Length: %s\n", frame.messageLength);
    printf("Encoded Message: %s\n", frame.message);
}