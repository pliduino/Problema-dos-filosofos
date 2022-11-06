#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#ifdef __unix__
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

const int CLOCK = 5;
const int CHANCE = 75;

typedef enum _state
{
    THINKING,
    HUNGRY,
    EATING
} PhilosopherState;

typedef struct _table
{
    PhilosopherState state[5];
    sem_t semaphores[5];

} Table;

Table table;

void table_init(Table *table);
void PrintTable(Table *table);
void table_set_hungry(Table *table, int index);
int table_try_eat(Table *table, int index);
void table_finish_eating(Table *table, int index);
void *philosopher(void *index);
void delay(int m_seconds);

void table_init(Table *table)
{
    for (int i = 0; i < 5; i++)
    {
        // table->state[i] == THINKING;
        sem_init(&(table->semaphores[i]), 0, 0);
    }
    PrintTable(table);
}

void table_set_hungry(Table *table, int index)
{
    table->state[index] = HUNGRY;

    table_try_eat(table, index);

    sem_wait(&(table->semaphores[index]));
}

int table_try_eat(Table *table, int index)
{
    // Invalid Index
    if (index > 4)
    {
        printf("INVALID INDEX");
        return -1;
    }

    if (table->state[index] == HUNGRY &&
        table->state[(index + 1) % 5] != EATING &&
        table->state[(index + 4) % 5] != EATING)
    {
        table->state[index] = EATING;
        sem_post(&(table->semaphores[index]));
    }
    return 0;
}

void table_finish_eating(Table *table, int index)
{
    table->state[index] = THINKING;

    table_try_eat(table, (index + 1) % 5);
    table_try_eat(table, (index + 4) % 5);
}

void *philosopher(void *index)
{

    int ph = *(int *)index;
    int i;

    srand(ph);

    printf("Philosopher %i started\n", ph);

    while (1)
    {

#ifdef _WIN32
        Sleep(1000 / CLOCK);
#endif
#ifdef __unix__
        usleep((1000 / CLOCK) * 1000);
#endif
        printf("%i: Executed\n", ph);
        i = rand() % 101;

        if (i < CHANCE)
        {
            if (table.state[ph] == EATING)
                table_finish_eating(&table, ph);
            else
                table_set_hungry(&table, ph);
        }
    }
}

void PrintTable(Table *table)
{
    printf("\n    %i", (int)table->state[0]);
    printf("\n   *** \n");
    printf("%i ***** %i\n", (int)table->state[4], (int)table->state[1]);
    printf(" ******* \n");
    printf("%i ***** %i\n", (int)table->state[3], (int)table->state[2]);
    printf("   *** \n");
}

void delay(int m_seconds)
{
    delay(1000 / CLOCK);
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

    // Unsyncs it with threads
    delay(100 / CLOCK);

    while (1)
    {
        delay(1000 / CLOCK);

        PrintTable(&table);
        CheckExec();
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(T[i], NULL);
    }
}