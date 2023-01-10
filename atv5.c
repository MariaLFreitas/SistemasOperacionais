#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <semaphore.h>
#include <unistd.h>

sem_t a, b, c, d, d_aux, e, f, f_aux, g, h, h_aux;
int x, y, z, u, H, j;
void *procP1(void *v)
{
    sem_wait(&a);
    x = 1;
    y = 1;
    z = 2;
    sem_post(&b);
    sem_post(&e);
    sem_post(&g);
    sem_wait(&e);
    y = y + 2;
    sem_post(&d_aux);
    sem_post(&h);
    sem_wait(&f);
    u = H + j / 3;
}

void *procP2(void *v)
{
    sem_wait(&b);
    x = x * 2;
    sem_post(&c);
    sem_wait(&c);
    x = x + 1;
    sem_post(&d);
    sem_wait(&d);
    H = y + x;
    sem_post(&f);
}

void *procP3(void *v)
{
    sem_wait(&g);
    z = z / 2;
    sem_post(&h_aux);
    sem_wait(&h);
    sem_post(&f_aux);
}


int main()
{
    pthread_t thread[3];
    sem_init(&a, 0, 1);
    sem_init(&b, 0, 0);
    sem_init(&c, 0, 0);
    sem_init(&d, 0, 0);
    sem_init(&d_aux, 0, 0);
    sem_init(&e, 0, 0);
    sem_init(&f, 0, 0);
    sem_init(&f_aux, 0, 0);
    sem_init(&g, 0, 0);
    sem_init(&h, 0, 0);
    sem_init(&h_aux, 0, 0);

    pthread_create(&thread[0], NULL, &procP1, NULL);
    pthread_create(&thread[1], NULL, &procP2, NULL);
    pthread_create(&thread[2], NULL, &procP3, NULL);

    for (int i = 0; i < 3; i++)
    {
        pthread_join(thread[i], NULL);
    }

    printf("x= %d\n", x);
    printf("y= %d\n", y);
    printf("z= %d\n", z);
    printf("h= %d\n", H);
    printf("j= %d\n", j);
    printf("U=%d\n", u);
    exit(0);
}

// pa
// {
//     sem_wait(&a);
//     x = 1;
//     y = 1;
//     z = 2;
//     sem_post(&b);
//     sem_post(&e);
//     sem_post(&g);
// }
// pb
// {
//     sem_wait(&b);
//     x = x * 2;
//     sem_post(&c);
// }
// pc
// {
//     sem_wait(&c);
//     x = x + 1;
//     sem_post(&d);
// }
// pe
// {
//     sem_wait(&e);
//     y = y + 2;
//     sem_post(&d_aux);
//     sem_post(&h);
// }
// pd
// {
//     sem_wait(&d);
//     H = y + x;
//     sem_post(&f);
// }
// pg
// {
//     sem_wait(&g);
//     z = z / 2;
//     sem_post(&h_aux);
// }
// pf
// {
//     sem_wait(&f);
//     u = H + j / 3;
// }
// ph
// {
//     sem_wait(&h);
//     sem_post(&f_aux);
// }