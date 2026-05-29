#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "../include/metrics.h"

int completed_processes = 0;
pthread_mutex_t metrics = PTHREAD_MUTEX_INITIALIZER;

void *metrics_generator(void *arg)
{
    int time = 0;
    while (1)
    {
        sleep(5); // Imprime cada 5 segundos
        time += 5;

        pthread_mutex_lock(&metrics);
        float throughput = (float)completed_processes / time; // Procesos completados por segundo

        printf("\n===========================================\n");
        printf("METRICAS DEL SCHEDULER (Tiempo = %d segundos)\n", time);
        printf("Procesos completados en total: %d\n", completed_processes);
        printf("Throughput actual: %.2f\n", throughput);
        printf("============================================\n\n");

        pthread_mutex_unlock(&metrics);
    }
    return NULL;
}