#include <stdio.h>
#include <stdlib.h>

struct memQueue{
	char processId;
    double processSz;
    struct memQueue *ptr;
};

typedef struct memQueue Queue;

Queue *front, *rear, *temp, *frontNxt;
 
int frontelement();
void insertQ(char id, double data);
void removeQ();
void isEmpty();
void display();
void createQ();
void queuesize();
void processor(char *argv[]);
int firstFit(char *argv[], FILE *fp, int data);
 
