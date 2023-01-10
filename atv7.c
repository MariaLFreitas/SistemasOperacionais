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


typedef struct shm_t{
    int javali;
    sem_t mesa,cozinheiro,gaules,retira,libera;
}shm_t;

shm_t *ptr;

void ColocaJavali(){
    sem_wait(&ptr->cozinheiro);
        ptr->javali=JAVALIS;
        sem_post(&ptr->retira);
}

void *Cozinheiro(){
    while(true){
       ColocaJavali();
    }
    pthread_exit(NULL);
}

int main(){
    int fd = shm_open("/sharedmem",O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    ftruncate(fd,sizeof(shm_t));
    ptr=mmap(NULL,sizeof(shm_t),PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);


    ptr->javali=JAVALIS;

    pthread_t thread;

    pthread_create(&thread, NULL, Cozinheiro, NULL);
    pthread_join(thread, NULL);
    pthread_exit(NULL);

}