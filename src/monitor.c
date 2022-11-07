#include <stdlib.h>
#include <stdio.h>
#include "monitor.h"

void monitor_init(monitor_t *monitor)
{
    sem_init(&(monitor->semaphore), 0, 1);
}

void monitor_add_func(monitor_t *monitor, void (*func)(void *table, unsigned int index))
{
    monitor->func_count++;
    monitor->funcs = realloc(monitor->funcs, sizeof(void *) * monitor->func_count);
    monitor->funcs[monitor->func_count - 1] = func;
}

void monitor_exec(monitor_t *monitor, int index, void *arg1, unsigned int arg2)
{
    sem_wait(&(monitor->semaphore));

    (*(monitor->funcs[index]))(arg1, arg2);

    sem_post(&(monitor->semaphore));
}

void monitor_destroy(monitor_t *monitor)
{
    free(monitor->funcs);
}