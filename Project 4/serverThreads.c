#include "serverThreads.h"

char string[100000];

/**
 * @brief Thread function that switches instances of 'a' to 'A'
 * @return void* the modified String
 */
void* aThread(void* noargs) {
    for(int i = 0; i < strlen(string); i++) {
        if(string[i] == 'a')
            string[i] = 'A';
    }
    return (void*)string;
}

/**
 * @brief Thread function that switches instances of 'e' to 'E'
 * @return void* the modified String
 */
void* eThread(void* noargs) {
    for(int i = 0; i < strlen(string); i++) {
        if(string[i] == 'e')
            string[i] = 'E';
    }
    return (void*)string;
}

/**
 * @brief Thread function that switches instances of 'i' to 'I'
 * @return void* the modified String
 */
void* iThread(void* noargs) {
    for(int i = 0; i < strlen(string); i++) {
        if(string[i] == 'i')
            string[i] = 'I';
    }
    return (void*)string;
}

/**
 * @brief Thread function that switches instances of 'o' to 'O'
 * @return void* the modified String
 */
void* oThread(void* noargs) {
    for(int i = 0; i < strlen(string); i++) {
        if(string[i] == 'o')
            string[i] = 'O';
    }
    return (void*)string;
}

/**
 * @brief Thread function that switches instances of 'u' to 'U'
 * @return void* the modified String
 */
void* uThread(void* noargs) {
    for(int i = 0; i < strlen(string); i++) {
        if(string[i] == 'u')
            string[i] = 'U';
    }
    return (void*)string;
}

/**
 * @brief Thread function that sums up all instances of numeric digits and appends to the end of the string
 * @return void* thread exits, does not return
 */
void* digitThread(void* noargs) {
    int sum = 0;
    char append[255];
    for(int i = 0; i < strlen(string); i++) {
        switch(string[i]) {
            case '1':
                sum += 1;
                break;
            case '2':
                sum += 2;
                break;
            case '3':
                sum += 3;
                break;
            case '4':
                sum += 4;
                break;
            case '5':
                sum += 5;
                break;
            case '6': 
                sum += 6;
                break;
            case '7':
                sum += 7;
                break;
            case '8':
                sum += 8;
                break;
            case '9':
                sum += 9;
                break;
        }
    }
    sprintf(append, "%d", sum);
    strcat(string, append);
    pthread_exit(NULL);
}

/**
 * @brief Function executed by the server to perform multi-threading
 * @return char* the modified String after all threads have executed
 */
char* threadFunc(char* data) {
    pthread_t threadA, threadE, threadI, threadO, threadU, threadDigit;
    void* returnedString = "\0";
    memset(string, 0, sizeof(string));                                                         // clear the string to prevent interference of data between clients
    strcpy(string, data);

    pthread_create(&threadA, NULL, aThread, NULL);
    pthread_create(&threadE, NULL, eThread, NULL);
    pthread_create(&threadI, NULL, iThread, NULL);
    pthread_create(&threadO, NULL, oThread, NULL);
    pthread_create(&threadU, NULL, uThread, NULL);
    pthread_create(&threadDigit, NULL, digitThread, NULL);
    pthread_join(threadA, &returnedString);
    pthread_join(threadE, &returnedString);
    pthread_join(threadI, &returnedString);
    pthread_join(threadO, &returnedString);
    pthread_join(threadU, &returnedString);
    pthread_join(threadDigit, NULL);

    strcpy(data, (char*)returnedString);
    return data;
}