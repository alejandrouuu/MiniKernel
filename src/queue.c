#include "../include/queue.h"
#include <stdio.h>

// Inicializa la cola en 0 y las condiciones de carrera
void queue_starter(ready_queue_t *q)
{
    q->in = 0;
    q->out = 0;
    q->count = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->cond_not_empty, NULL);
    pthread_cond_init(&q->cond_not_full, NULL);
}

// Inserta un proceso en la cola
void enqueue(ready_queue_t *q, pcb_t process)
{
    pthread_mutex_lock(&q->mutex);

    // Cuando la cola esté llena el hilo duerme hasta que haya espacio de nuevo
    while (q->count == QUEUE_CAPACITY)
    {
        pthread_cond_wait(&q->cond_not_full, &q->mutex);
    }

    q->processes_array[q->in] = process; // Se inserta el proceso
    q->in = (q->in + 1) % QUEUE_CAPACITY;
    q->count++;

    pthread_cond_signal(&q->cond_not_empty); // Despierta a la CPU si hay elemenos en cola
    pthread_mutex_unlock(&q->mutex);
}

// Extrae un proceso de la cola
pcb_t dequeue(ready_queue_t *q)
{
    pcb_t process;
    pthread_mutex_lock(&q->mutex);

    // Si la cola está vacía, la CPU duerme hasta que entre un proceso.
    while (q->count == 0)
    {
        pthread_cond_wait(&q->cond_not_empty, &q->mutex);
    }

    process = q->processes_array[q->out]; // Se extrae el proceso
    q->out = (q->out + 1) % QUEUE_CAPACITY;
    q->count--;

    pthread_cond_signal(&q->cond_not_full); // Despierta a los hilos si la cola está vacía
    pthread_mutex_unlock(&q->mutex);
    return process;
}