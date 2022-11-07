#include "table.h"
#include <stdlib.h>
#include <stdio.h>

void table_try_eat(void *p_table, unsigned int index)
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
        sem_post(&(table->semaphores[index]));
    }
}

void table_set_hungry(table_t *table, unsigned int index)
{

    table->state[index] = HUNGRY;

    table_exec(table, TRY_EAT, index);

    sem_wait(&(table->semaphores[index]));
}

void table_finish_eating(void *p_table, unsigned int index)
{
    table_t *table = (table_t *)p_table;

    table->state[index] = THINKING;

    table_try_eat(p_table, index);
    table_try_eat(p_table, (index + 4) % 5);
}

void table_print(table_t *p_table)
{
    table_t *table = (table_t *)p_table;

    printf("\n    %i", (int)table->state[0]);
    printf("\n   *** \n");
    printf("%i ***** %i\n", (int)table->state[4], (int)table->state[1]);
    printf(" ******* \n");
    printf("%i ***** %i\n", (int)table->state[3], (int)table->state[2]);
    printf("   *** \n");
}

void table_exec(table_t *table, enum FUNCS func, unsigned int index)
{
    monitor_exec(&(table->monitor), func, table, index);
}

void table_check_exec(void *p_table, unsigned int index)
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

void table_init(table_t *table)
{
    for (int i = 0; i < 5; i++)
    {
        // table->state[i] == THINKING;
        sem_init(&(table->semaphores[i]), 0, 0);
    }

    monitor_init(&(table->monitor));
    monitor_add_func(&(table->monitor), (void *)&table_try_eat);
    monitor_add_func(&(table->monitor), (void *)&table_finish_eating);
    monitor_add_func(&(table->monitor), (void *)&table_check_exec);
    monitor_add_func(&(table->monitor), (void *)&table_print);
}

void table_destroy(table_t *table)
{
    monitor_destroy(&(table->monitor));
}