#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "../include/queue.h"
#include "../include/pcb.h"
#include "../include/metrics.h"

#define QUANTUM 3 // Tiempo máximo de ejecución por turno
extern ready_queue_t ready_queue;

void *cpu_simulator(void *arg)
{
    int cpu_id = *((int *)arg);
    while (1)
    {
        pcb_t process = dequeue(&ready_queue);
        printf("[CPU ID %d] Ejecutando PID %d (Tiempo restante: %d)\n", cpu_id, process.pid, process.remaining_time);

        // Si al proceso le falta menos del QUANTUM para finalizar, le asigna lo que necesita
        int time_to_run = (process.remaining_time > QUANTUM) ? QUANTUM : process.remaining_time;

        // Simulamos el tiempo de procesamiento
        usleep(time_to_run * 200000);

        process.remaining_time -= time_to_run;

        if (process.remaining_time > 0) // Si aún no finaliza, el proceso hará la cola otra vez
        {
            printf("[CPU ID %d] PID %d vuelve a la cola.\n", cpu_id, process.pid);
            enqueue(&ready_queue, process);
        }
        else
        {
            process.state = 2; // Estado: Terminado
            pthread_mutex_lock(&metrics);
            completed_processes++;
            pthread_mutex_unlock(&metrics);
            printf("[CPU ID %d] PID %d Terminado \n", cpu_id, process.pid);
        }
    }
    return NULL;
}