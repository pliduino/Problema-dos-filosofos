#ifndef TABLE_H
#define TABLE_H

#include <semaphore.h>
#include "monitor.h"

const int MAX_TRY_EAT_COUNT = 5;

/// @brief Philosopher possible states
typedef enum __philosopher_state
{
    THINKING,
    HUNGRY,
    EATING
} philosopher_state_t;

/// @brief List of functions contained inside table.monitor
typedef enum __table_funcs
{
    TRY_EAT,
    FINISH_EATING,
    CHECK_EXEC,
    PRINT
} table_funcs_t;

typedef struct __table table_t;

/// @brief Initializes a new table_t
table_t *table_init();

/// @brief Frees a table_t allocated memory
void table_destroy(table_t *table);

void table_exec(table_t *table, table_funcs_t func, int index);

/// @brief Returns a copy of table.state[index]
philosopher_state_t table_get_state(table_t *table, int index);

void table_set_hungry(table_t *table, int index);

#endif // !TABLE_H