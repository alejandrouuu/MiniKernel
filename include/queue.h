#ifndef QUEUE_H
#define QUEUE_H
#include <pthread.h>
#include "pcb.h"

#define QUEUE_CAPACITY 100
typedef struct
{
    pcb_t processes_array[QUEUE_CAPACITY];
    int in;
    int out;
    int count; // Cantidad de procesos en cola

    // POSIX
    pthread_mutex_t mutex;
    pthread_cond_t cond_not_empty;
    pthread_cond_t cond_not_full;
} ready_queue_t;

void queue_starter(ready_queue_t *q);
void enqueue(ready_queue_t *q, pcb_t process);
pcb_t dequeue(ready_queue_t *q);
#endif