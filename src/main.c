#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "table.h"

#ifdef __unix__
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

const int CLOCK = 5000;
const int MAX_CLOCK = 50000;
const int CHANCE = 50;

table_t table;

void delay(int m_seconds);
void *philosopher(void *index);

void delay(int milli_seconds)
{
#ifdef __unix__
    usleep(milli_seconds * 1000);
#endif
#ifdef _WIN32
    Sleep(milli_seconds);
#endif
}

void *philosopher(void *index)
{

    unsigned int ph = *(int *)index;
    int i;

    srand(ph);

    while (1)
    {

        delay(1000 / CLOCK);
        i = rand() % 101;

        if (i < CHANCE)
        {
            if (table_get_state(&table, ph) == EATING)
            {
                table_exec(&table, FINISH_EATING, ph);
            }

            else
            {
                table_set_hungry(&table, ph);
            }
        }
    }
}

int main()
{
    int n[5];
    pthread_t T[5];

    table_init(&table);

    for (int i = 0; i < 5; i++)
    {
        n[i] = i;
        pthread_create(&T[i], NULL, philosopher, (void *)&n[i]);
    }

    for (int i = 0; i < MAX_CLOCK; i++)
    {
        delay(1000 / CLOCK);

        table_exec(&table, CHECK_EXEC, 0);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_cancel(T[i]);
    }

    table_destroy(&table);
}