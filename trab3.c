// Comando pra rodar : gcc -o trab3 trab3.c -lpthread -lm
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define NUM_THREADS 16
#define BILHAO 1000000000

double parc[8*NUM_THREADS];
double result=0;

void* calc_pi(void* i){
	long tid = (long)i;

  int termos = BILHAO/NUM_THREADS;
  int inicio = tid*termos;
  int fim = tid*termos + termos;

	for(int i=inicio; i<fim; i++){
		parc[8*tid] += pow(-1,i)/((2*i+1)*pow(3,i));
	}
    parc[8*tid] = parc[8*tid] * sqrt(12);
}

void* calc_pi2(void* i){
	long tid = (long)i;

  int termos = BILHAO/NUM_THREADS;
  int inicio = tid*termos;
  int fim = tid*termos + termos;

	for(int i=inicio; i<fim; i++){
		parc[8*tid] += pow(-1,i)/((2*i+1)*pow(2,2*i+1)) + pow(-1,i)/((2*i+1)*pow(3,2*i+1));
	}
    parc[8*tid] = parc[8*tid] * 4;
}

int main(){
	pthread_t threads[NUM_THREADS];

  for(int i=0; i<NUM_THREADS; i++)
    parc[8*i] = 0;

  for(int i=0; i<NUM_THREADS; i++)
    pthread_create(&threads[i], NULL, calc_pi,(void*)(intptr_t)i);

  for(int i=0; i<NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    result += parc[8*i];
  }

  printf("Pi: %lf \n",result);


  // for(int i=0; i<NUM_THREADS; i++)
  //   pthread_create(&threads[i], NULL, calc_pi2,(void*)(intptr_t)i);
  // for(int i=0; i<NUM_THREADS; i++){
  //   pthread_join(threads[i], NULL);
  //   result += parc[8*i];
  // }

  // printf("Pi2: %lf \n",result);


}



