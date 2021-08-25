#include <string.h>
#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED
#define MAX_BUFFER_SIZE 200
//Extra memory when we save the key and the memory is buffer size is reached
#define EXTRA_BUFFER_SIZE 50

int initBuffer();
int isBufferFull();
void clearBuffer();
void freeBuffer();

char *buffer;

int initBuffer(){
    buffer = malloc((MAX_BUFFER_SIZE+EXTRA_BUFFER_SIZE) * sizeof(char));
    clearBuffer();
    return buffer == NULL ? 0 : 1;
}

int isBufferFull(){
    return strlen(buffer) > MAX_BUFFER_SIZE ? 1 : 0;
}

void clearBuffer(){
    if(buffer != NULL){
        memset(buffer,0,MAX_BUFFER_SIZE+EXTRA_BUFFER_SIZE);
    }
}

void freeBuffer() {
    if(buffer != NULL) {
        free(buffer);
    }
}

#endif // BUFFER_H_INCLUDED
