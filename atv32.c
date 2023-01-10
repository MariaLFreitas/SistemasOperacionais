#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NUM_THREADS 16
#define BILHAO 1000000000

double parc[8*NUM_THREADS];
double result=0;

void* pi(void* i){
	long tid = (long)i;

  int termos = BILHAO/NUM_THREADS;
  int inicio = tid*termos;
  int fim = tid*termos + termos;


	for(int i=inicio; i<fim; i++){
		parc[8*tid] += pow(-1,i)/(2*i+1);
	}
}

/*void* pi_2(void* i){
	long tid = (long)i;
  int termos = BILHAO/NUM_THREADS;
  int inicio = tid*termos;
  int fim = tid*termos + termos;
	for(int i=inicio; i<fim; i++){
		parc[8*tid] += pow(-1,i)/((2*i+1)*pow(3,i));
	}
}*/
int main(void){
	pthread_t threads[NUM_THREADS];
  for(int i=0; i<NUM_THREADS; i++){
    parc[8*i] = 0;
  }
  for(int i=0; i<NUM_THREADS; i++){
    pthread_create(&threads[i], NULL, pi,(void*)(intptr_t)i);
  }
  for(int i=0; i<NUM_THREADS; i++){
    pthread_join(threads[i], NULL);
    result += parc[8*i];
  }
  //printf para a funcao pi
  printf("Pi: %f\n",4*result);

  //printf para a funcao pi_2
 // printf("Pi: %f\n",sqrt(12)*result);

}