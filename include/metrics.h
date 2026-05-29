#ifndef METRICS_H
#define METRICS_H
#include <pthread.h>

extern int completed_processes;
extern pthread_mutex_t metrics;

void *metrics_generator(void *arg);
#endif