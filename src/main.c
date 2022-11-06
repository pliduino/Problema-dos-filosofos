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

typedef enum _state
{
    THINKING,
    HUNGRY,
    EATING
} Philosopher;

typedef struct _table
{
    Philosopher state[5];
    sem_t semaphores[5];

} Table;

Table table;

void InitTable(Table *table);
void PrintTable(Table *table);
void SetHungry(Table *table, int index);
int TryEat(Table *table, int index);
void FinishEating(Table *table, int index);
void *philos(void *index);

void InitTable(Table *table)
{
    for (int i = 0; i < 5; i++)
    {
        // table->state[i] == THINKING;
        sem_init(&(table->semaphores[i]), 0, 0);
    }
    PrintTable(table);
}

void SetHungry(Table *table, int index)
{
    table->state[index] = HUNGRY;

    TryEat(table, index);

    sem_wait(&(table->semaphores[index]));
}

int TryEat(Table *table, int index)
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

void FinishEating(Table *table, int index)
{
    table->state[index] = THINKING;

    TryEat(table, (index + 1) % 5);
    TryEat(table, (index + 4) % 5);
}

void *philos(void *index)
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

        if (i < 30)
        {
            if (table.state[ph] == EATING)
                FinishEating(&table, ph);
            else
                SetHungry(&table, ph);
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

int main()
{
    int n[5];
    pthread_t T[5];

    InitTable(&table);

    for (int i = 0; i < 5; i++)
    {
        n[i] = i;
        pthread_create(&T[i], NULL, philos, (void *)&n[i]);
    }

// Unsyncs it with threads
#ifdef _WIN32
    Sleep(100 / CLOCK);
#endif
#ifdef __unix__
    usleep((100 / CLOCK) * 1000);
#endif

    while (1)
    {
#ifdef _WIN32
        Sleep(1000 / CLOCK);
#endif
#ifdef __unix__
        usleep((1000 / CLOCK) * 1000);
#endif

        PrintTable(&table);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(T[i], NULL);
    }
}