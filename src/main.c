#include <semaphore.h>
#include <pthread.h>

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

void InitTable(Table *table)
{
    for (int i = 0; i < 5; i++)
    {
        table->state[i] == THINKING;
        sem_init(table->semaphores[i], 0, 1);
    }
}

void SetHungry(Table *table, int index)
{
    table->state[index] = HUNGRY;
    TryEat(table, index);

    if (table->state[index] != EATING)
    {
        sem_wait(table->semaphores[index]);
    }
}

int TryEat(Table *table, int index)
{
    // Invalid Index
    if (index > 4)
    {
        return -1;
    }

    if (table->state[index] == HUNGRY &&
        table->state[(index + 1) % 5] != EATING &&
        table->state[(index + 4) % 5] != EATING)
    {
        table->state[index] = EATING;
        sem_post(table->semaphores[index]);
    }
    return 0;
}

void FinishEating(Table *table, int index)
{
    table->state[index] = THINKING;

    TryEat(table, (index + 1) % 5);
    TryEat(table, (index + 4) % 5);
}

void philos(void *index)
{
    int ph = *(int *)index;
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
    for (int i = 0; i < 5; i++)
    {
        pthread_join(T[i], NULL);
    }
}