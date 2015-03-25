#include "holes.h"

/*This .c file is created to take out queue functions that do no require the values of
*both the global variables (memorySize and processCount)*/

/* Create an isEmpty queue */
void createQ(){
    front = rear = NULL;
}

/* Display if queue is isEmpty or not */
void isEmpty(){
     if ((front == NULL) && (rear == NULL)){
        printf("\n Queue isEmpty");
    }
    else{
       printf("Queue not isEmpty");
    }
}

/* Returns the front element of queue */
int frontelement(){
    if ((front != NULL) && (rear != NULL)){
        return(front->processSz);
    }
    else
        return 0;
}