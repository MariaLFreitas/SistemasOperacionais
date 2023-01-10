#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define JAVALIS 20
#define GAULESES 5
#define true 1

sem_t sem_mesa,sem_cozinheiro,sem_gaules,sem_retira,sem_libera;
int javali=JAVALIS;
char gauleses[]={'M','A','R','I','A'};

void RetiraJavali(char gaules){
    sem_wait(&sem_gaules);
    if(javali==0){
        sem_post(&sem_cozinheiro);
        printf("Gaules %c acordou o cozinheiro.\n",gaules);
        sem_wait(&sem_retira);
    }
    if(javali>0){
        javali--;
    }
    sem_post(&sem_libera);
}

void ColocaJavali(){
    sem_wait(&sem_cozinheiro);
        javali=JAVALIS;
        sem_post(&sem_retira);
}

void *Gaules(void *threadid){
    while(true){
        sem_wait(&sem_mesa);
        sem_post(&sem_gaules);
        RetiraJavali(gauleses[(int)threadid]);
        sem_wait(&sem_libera);
        printf("Gaules %c está comendo.\n",gauleses[(int)threadid]);
        sem_post(&sem_mesa);
    }
    pthread_exit(NULL);
}

void *Cozinheiro(){
    while(true){
       ColocaJavali();
    }
    pthread_exit(NULL);
}

int main(){

    sem_init(&sem_mesa,0,1);
    sem_init(&sem_cozinheiro,0,0);
    sem_init(&sem_gaules,0,0);
    sem_init(&sem_libera,0,0);
    sem_init(&sem_retira,0,0);

    pthread_t threads[6];
    for(int i=0;i<GAULESES;i++)
    pthread_create(&threads[i],NULL,Gaules,(void*)i);

    pthread_create(&threads[GAULESES], NULL, Cozinheiro, NULL);

    for(int i = 0; i <= GAULESES; i++)
        pthread_join(threads[i], NULL);

}