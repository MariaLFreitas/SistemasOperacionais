#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define JAVALIS 20
#define GAULESES 5
#define true 1

char gauleses[]={'M','A','R','I','A'};

typedef struct shm_t{
    int javali;
    sem_t mesa,cozinheiro,gaules,retira,libera;
}shm_t;

shm_t *ptr;

void RetiraJavali(char gaules){
    sem_wait(&ptr->gaules);
    if(ptr->javali==0){
        sem_post(&ptr->cozinheiro);
        printf("Gaules %c acordou o cozinheiro.\n",gaules);
        sem_wait(&ptr->retira);
    }
    if(ptr->javali>0){
        ptr->javali--;
    }
    sem_post(&ptr->libera);
}

void *Gaules(void *threadid){
    while(true){
        sem_wait(&ptr->mesa);
        sem_post(&ptr->gaules);
        RetiraJavali(gauleses[(int)threadid]);
        sem_wait(&ptr->libera);
        printf("Gaules %c está comendo.\n",gauleses[(int)threadid]);
        sem_post(&ptr->mesa);
        sleep(rand() % 4 + 1);
    }
    pthread_exit(NULL);
}



int main(){
    int fd = shm_open("/sharedmem",O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    ftruncate(fd,sizeof(shm_t));
    ptr=mmap(NULL,sizeof(shm_t),PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    sem_init(&ptr->cozinheiro, 1, 0);
    sem_init(&ptr->retira, 1, 0);
    sem_init(&ptr->libera, 1, 0);
    sem_init(&ptr->gaules, 1, 0);
    sem_init(&ptr->mesa, 1, 1);

    ptr->javali=JAVALIS;

    pthread_t threads[5];

    for(int i=0;i<GAULESES;i++){
        pthread_create(&threads[i], NULL, Gaules, (void*)(intptr_t)i);
    }

    for(int i=0;i<GAULESES;i++){
        pthread_join(&threads[i], NULL);
    }
    pthread_exit(NULL);

}