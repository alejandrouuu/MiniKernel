#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "../include/queue.h"
#include "../include/metrics.h"

#define N_CPUS 2 // Cantidad de CPUs simuladas

ready_queue_t ready_queue;
extern void *cpu_simulator(void *arg);
extern void *metrics_generator(void *arg);

void *process_generator(void *arg)
{
    int pid_counter = 1;
    while (1)
    {
        int sleep_time = rand() % 3; // Duerme un tiempo aleatorio entre 0 y 2 segundos
        sleep(sleep_time);
        pcb_t new_process;

        new_process.pid = pid_counter++;
        new_process.burst_time = (rand() % 10) + 1;
        new_process.remaining_time = new_process.burst_time;
        new_process.priority = rand() % 5;
        new_process.arrival_time = time(NULL);
        new_process.state = 1; // Estado: Listo

        enqueue(&ready_queue, new_process);
        printf("[Generador] Proceso PID %d creado (Burst: %d).\n", new_process.pid, new_process.burst_time);
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    queue_starter(&ready_queue);

    printf("===========================================\n");
    printf("MiniKernel iniciado con %d CPUs simuladas\n", N_CPUS);
    printf("===========================================\n\n");

    pthread_t generator_thread;
    pthread_create(&generator_thread, NULL, process_generator, NULL);
    pthread_t cpu_threads[N_CPUS];
    int cpu_ids[N_CPUS];

    for (int i = 0; i < N_CPUS; i++)
    {
        cpu_ids[i] = i + 1;
        pthread_create(&cpu_threads[i], NULL, cpu_simulator, &cpu_ids[i]);
    }

    pthread_t metrics_thread;
    pthread_create(&metrics_thread, NULL, metrics_generator, NULL);
    pthread_join(generator_thread, NULL);
    return 0;
}