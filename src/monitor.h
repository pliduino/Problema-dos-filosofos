
#ifndef MONITOR_H
#define MONITOR_H

#include <semaphore.h>

typedef struct __monitor
{
    sem_t mutex;
    void (**funcs)(void *table, int index);
    int func_count;

} monitor_t;

void monitor_init(monitor_t *monitor);

void monitor_exec(monitor_t *monitor, int index, void *arg1, int arg2);

void monitor_add_func(monitor_t *monitor, void (*func)(void *table, int index));

void monitor_destroy(monitor_t *monitor);

#endif // !MONITOR_H