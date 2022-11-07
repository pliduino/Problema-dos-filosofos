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

typedef enum __table_funcs
{
    TRY_EAT,
    FINISH_EATING,
    CHECK_EXEC,
    PRINT
} table_funcs_t;

typedef struct __table table_t;

/// @brief Initializes a new table
/// @param table Pointer to a table_t
void table_init(table_t *table);

void table_destroy(table_t *table);

void table_exec(table_t *table, table_funcs_t func, unsigned int index);

/// @param table Pointer to a table_t
/// @return A copy of table.state
philosopher_state_t table_get_state(table_t *table, unsigned int index);

void table_set_hungry(table_t *table, unsigned int index);

#endif // !TABLE_H