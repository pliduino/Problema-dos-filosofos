#include <stdlib.h>
#include <stdio.h>
#include "monitor.h"

void monitor_init(monitor_t *monitor)
{
    sem_init(&(monitor->mutex), 0, 1);
}

void monitor_add_func(monitor_t *monitor, void (*func)(void *table, int index))
{
    monitor->func_count++;
    ;
    monitor->funcs = realloc(monitor->funcs, sizeof(void *) * monitor->func_count);
    monitor->funcs[monitor->func_count - 1] = func;
}

void monitor_exec(monitor_t *monitor, int func_index, void *arg1, int arg2)
{
    sem_wait(&(monitor->mutex));

    (*(monitor->funcs[func_index]))(arg1, arg2);

    sem_post(&(monitor->mutex));
}

void monitor_destroy(monitor_t *monitor)
{
    sem_destroy(&(monitor->mutex));
    free(monitor->funcs);
}