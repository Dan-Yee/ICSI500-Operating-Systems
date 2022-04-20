#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Thread function that switches instances of 'a' to 'A'
 * @return void* the modified String
 */
void* aThread(void*);

/**
 * @brief Thread function that switches instances of 'e' to 'E'
 * @return void* the modified String
 */
void* eThread(void*);

/**
 * @brief Thread function that switches instances of 'i' to 'I'
 * @return void* the modified String
 */
void* iThread(void*);

/**
 * @brief Thread function that switches instances of 'o' to 'O'
 * @return void* the modified String
 */
void* oThread(void*);

/**
 * @brief Thread function that switches instances of 'u' to 'U'
 * @return void* the modified String
 */
void* uThread(void*);

/**
 * @brief Thread function that sums up all instances of numeric digits and appends to the end of the string
 * @return void* thread exits, does not return
 */
void* digitThread(void*);

/**
 * @brief Function executed by the server to perform multi-threading
 * @return char* the modified String after all threads have executed
 */
char* threadFunc(char*);