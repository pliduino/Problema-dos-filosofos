#ifndef TABLE_H
#define TABLE_H

#include <semaphore.h>
#include "monitor.h"

typedef enum __philosopher_state
{
    THINKING,
    HUNGRY,
    EATING
} philosopher_state_t;

enum FUNCS
{
    TRY_EAT,
    FINISH_EATING,
    CHECK_EXEC,
    PRINT
};

typedef struct __table
{
    philosopher_state_t state[5];
    sem_t semaphores[5];
    monitor_t monitor;

} table_t;

void table_init(table_t *table);

void table_destroy(table_t *table);

void table_exec(table_t *table, enum FUNCS func, unsigned int index);

void table_set_hungry(table_t *table, unsigned int index);

#endif // !TABLE_H