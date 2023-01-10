#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5
sem_t sem1, sem2, sem3;

void *thread(void *arg)
{
    long proc = (long)arg;
    int random = 1 + (rand() % 5);

    if (proc == 65){
        printf("Iniciando A\n");
        sleep(random);
        printf("Finalizando processo A\n");
        sem_post(&sem1);
    }

    else if (proc == 66){
        printf("Iniciando B\n");
        sleep(random);
        printf("Finalizando processo B\n");
        sem_post(&sem2);
    }

    else if (proc == 67){
        printf("Iniciando C\n");
        sem_wait(&sem2);
        sleep(random);
        printf("Finalizando processo C\n");
        sem_post(&sem3);
        sem_post(&sem3);
    }

    else if (proc == 68){
        printf("Iniciando D\n");
        sem_wait(&sem3);
        sleep(random);
        printf("Finalizando processo D\n");
    }

    else if (proc == 69){
        printf("Iniciando E\n");
        sem_wait(&sem3);
        sleep(random);
        printf("Finalizando processo E\n");
    }
}

int main(void)
{
    long proc;
    pthread_t threads[NUM_THREADS];

    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 0);

    for (proc = 65; proc < 70; proc++)
    {
        pthread_create(&threads[proc], NULL, thread, (void *)proc);
    }

    for (proc = 65; proc < 70; proc++)
    {
        pthread_join(threads[proc], NULL);
    }

    return 0;
}