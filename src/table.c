#include "table.h"
#include <stdlib.h>
#include <stdio.h>

struct __table
{
    philosopher_state_t state[5];
    sem_t condition[5];
    sem_t block_mutex[5];
    monitor_t monitor;
};

void table_try_eat(void *p_table, int index)
{
    table_t *table = (table_t *)p_table;

    // Invalid Index
    if (index > 4)
    {
        printf("INVALID INDEX");
        return;
    }

    if (table->state[index] == HUNGRY &&
        table->state[(index + 1) % 5] != EATING &&
        table->state[(index + 4) % 5] != EATING)
    {
        table->state[index] = EATING;
        sem_post(&(table->condition[index]));
    }
}

void table_set_hungry(table_t *table, int index)
{
    table->state[index] = HUNGRY;

    monitor_exec(&(table->monitor), TRY_EAT, (void *)table, index);

    sem_wait(&(table->condition[index]));
}

void table_finish_eating(void *p_table, int index)
{
    table_t *table = (table_t *)p_table;

    table->state[index] = THINKING;

    table_try_eat(p_table, index);
    table_try_eat(p_table, (index + 4) % 5);
}

void table_print(void *p_table)
{
    table_t *table = (table_t *)p_table;

    printf("\n    %i", (int)table->state[0]);
    printf("\n   *** \n");
    printf("%i ***** %i\n", (int)table->state[4], (int)table->state[1]);
    printf(" ******* \n");
    printf("%i ***** %i\n", (int)table->state[3], (int)table->state[2]);
    printf("   *** \n");
}

void table_exec(table_t *table, table_funcs_t func, int index)
{

    if (index >= 0)
        sem_wait(&(table->block_mutex[index]));

    monitor_exec(&(table->monitor), func, table, index);

    if (index >= 0)
        sem_post(&(table->block_mutex[index]));
}

void table_check_exec(void *p_table, int index)
{

    table_t *table = (table_t *)p_table;

    table_print(table);

    for (int i = 0; i < 5; i++)
    {
        if ((table->state[i] == table->state[(i + 1) % 5]) && (table->state[i] == EATING))
        {
            printf("CHOPSTICK IS BEING USED 2 TIMES / STATES: (%i : %i) at %i", table->state[i], table->state[(i + 1) % 5], i);
            exit(0);
        }
    }
}

table_t *table_init()
{
    table_t *table = calloc(1, sizeof(table_t));

    for (int i = 0; i < 5; i++)
    {
        sem_init(&(table->condition[i]), 0, 0);
        sem_init(&(table->block_mutex[i]), 0, 1);
    }

    monitor_init(&(table->monitor));

    monitor_add_func(&(table->monitor), (void *)&table_try_eat);
    monitor_add_func(&(table->monitor), (void *)&table_finish_eating);
    monitor_add_func(&(table->monitor), (void *)&table_check_exec);
    monitor_add_func(&(table->monitor), (void *)&table_print);

    return table;
}

void table_destroy(table_t *table)
{
    monitor_destroy(&(table->monitor));
    for (int i = 0; i < 5; i++)
    {
        sem_destroy(&(table->condition[i]));
        sem_destroy(&(table->block_mutex[i]));
    }
    free(table);
}

philosopher_state_t table_get_state(table_t *table, int index)
{
    return table->state[index];
}