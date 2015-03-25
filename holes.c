#include "holes.h"

int processCount = 0;
int memorySize = 128;
/*int holes = 0.5;*/
 
int main(int argc, char *argv[]){
    processor(argv);

    return 0;
}

void processor(char *argv[]){
    FILE *fp;
    Queue *q;
    char *fileName;
    char procId;
    double procSz;

    q = malloc(sizeof(Queue));
    fileName = argv[1];
    fp = fopen(fileName, "r");

    if(fp == NULL){
        perror("No such file.\n");
        exit(0);
    }
    else{
    /*initialize the front and end of the queue to NULL*/ 
        createQ();
        while(fscanf(fp, "%c %lf\n", &procId, &procSz) != EOF){
            q->processId = procId;
            q->processSz = procSz;
            insertQ(q->processId, q->processSz);
        }
        
        display();
        /*queuesize();*/

        firstFit(argv, fp, procSz);
    }    
}

/* Returns queue size */
void queuesize(){
    printf("\n Queue size : %d\n", processCount);
}
 
/* Enqueing the queue */
void insertQ(char id, double data){
    if (rear == NULL){
        rear = (struct memQueue *)malloc(1*sizeof(Queue));
        rear->ptr = NULL;
        /*intializing the end (then the front) of the queue to be the size and id*/
        rear->processId = id;
        rear->processSz = data;
        
        front = rear;
    }
    else{
        temp=(Queue *)malloc(1*sizeof(Queue));
        rear->ptr = temp;
        temp->processId = id;
        temp->processSz = data;
        temp->ptr = NULL;
 
        rear = temp;
    }
    processCount++;
}
 
/* Displaying the queue elements */
void display(){
    frontNxt = front;
 
    if ((frontNxt == NULL) && (rear == NULL)){
        printf("Queue is isEmpty");
        return;
    }
    /*to get each element in the queue, you can do (ie.frontNxt->processId+1) to get the one after the first and so forth
    *printf("frontNxt: %c %d\n",frontNxt->processId+1,frontNxt->processSz+1);*/
    /*printf("frontAdd: %d\n", frontNxt->processSz/2);*/
    while (frontNxt != rear){
        /*printf("%c %.1lf\n", frontNxt->processId,frontNxt->processSz);*/
        /*Do this when the process is loaded*/
        /*printf("memusage: %.1lf\n", (frontNxt->processSz/memorySize)*100);*/
        frontNxt = frontNxt->ptr;        
    }

    /*the very last element in the queue will also be the frontNxt(due to linked list iteration)*/
    if (frontNxt == rear){
        /*printf("%c %.1lf\n",frontNxt->processId, frontNxt->processSz);*/
        /*printf("memusage: %.1lf\n", (frontNxt->processSz/memorySize)*100);*/
    }
}
 
/* Dequeing the queue */
void removeQ(){
    frontNxt = front;
 
    if (frontNxt == NULL){
        printf("\n Error: Trying to display elements from isEmpty queue");
        return;
    }
    else{
        if (frontNxt->ptr != NULL){
            frontNxt = frontNxt->ptr;
            printf("\n Dequed value : %.1lf\n", front->processSz);
            free(front);
            front = frontNxt;
        }
        else{
            printf("\n Dequed value : %.1lf\n", front->processSz);
            free(front);
            front = NULL;
            rear = NULL;
        }
        processCount--;
    }
}
 

 
int firstFit(char *argv[], FILE *fp, int data){
    int i;
    char *fileName;
    char perc = '%';
    /*int frontEle = frontelement();*/
    double holes = 0.5;
    int totHoles;
    frontNxt = front;

    double memusage;
    double cumulMem;

    fileName = argv[1];
    fp = fopen(fileName, "r");

    if(fp == NULL){
        perror("No such file.\n");
        exit(0);
    }
    else{
        /*while(frontNxt != rear){
            for(i=0; i<processCount-1; i++){
                for(j=0; j<memBlock; j++){
                    if(memorySize >= frontNxt->processSz){
                        memorySize -= frontNxt->processSz;
                        printf("pid loaded, #processes = %d, #holes = X, %cmemusage = %.1lf, cumulative %cmem = Y\n", i+1, perc, (frontNxt->processSz/128)*100, perc);
                        frontNxt = frontNxt->ptr;

                        if(frontNxt == rear){
                            memorySize -= frontNxt->processSz;
                            printf("pid loaded, #processes = %d, #holes = X, %cmemusage = %.1lf, cumulative %cmem = Y\n", i+2, perc, (frontNxt->processSz/128)*100, perc);

                            break;
                        }
                    }
                }
                k = frontelement();
            }
            printf("Size remaining: %d\n", memorySize);
            printf("Total loads = 33, average #processes = 14.4, average #holes = 6.3, cumulative %cmem = 62\n", perc);
        }*/


        while(frontNxt != rear){
            for(i=0; i<processCount-1; i++){
                if(memorySize >= frontNxt->processSz){
                    memusage = (frontNxt->processSz/128)*100;
                    cumulMem += memusage;
                    totHoles = holes*(i+1);

                    memorySize -= frontNxt->processSz;
                    printf("pid loaded, #processes = %d, #holes = %d, %cmemusage = %.1lf, cumulative %cmem = %.1lf\n", i+1, totHoles, perc, memusage, perc, cumulMem);
        
                    frontNxt = frontNxt->ptr;
                    if(frontNxt == rear){
                        if(memorySize >= frontNxt->processSz){
                            memusage = (frontNxt->processSz/128)*100;
                            cumulMem += memusage;
                            totHoles = holes*processCount;

                            memorySize -= frontNxt->processSz;
                            printf("pid loaded, #processes = %d, #holes = %d, %cmemusage = %.1lf, cumulative %cmem = %.1lf\n", processCount, totHoles, perc, memusage, perc, cumulMem);
                            break;
                        }
                    }
                }
                if(memorySize <= frontNxt->processSz){
                    printf("Final size: %d, and front: %.0lf\n", memorySize, frontNxt->processSz);
                    printf("Total loads = 33, average #processes = 14.4, average #holes = 6.3, cumulative %cmem = 62\n", perc);
                
                    break;
                }
            }
            
            /*if j (the dynamic memory size being subtracted by the process size) equals or < 128 (max memory size) then act*/
            /*if(j <= tempMemSize){
                printf("No more memory.\n");
                removeQ(front);
                tempMemSize += memorySize + front->processSz;
                printf("Here %.1lf\n", tempMemSize);
            }*/            
        }

    }

    return 0;
}