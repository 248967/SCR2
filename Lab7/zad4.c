/*
 * zad4.c
 *
 *  Created on: 13 sty 2021
 *      Author: izabela
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS	5

void *PrintHello(void *threadid)
{
   int i;
   double myresult=0.0;
   printf("thread=%ld: starting...\n", threadid);
   for (i=0; i<1000000; i++)
      myresult += sin(i) * tan(i);
   printf("thread=%ld result=%e. Done.\n",threadid,myresult);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NUM_THREADS];
int rc;
long t;
for(t=0;t<NUM_THREADS;t++){
  printf("Main: creating thread %ld\n", t);
  rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
  if (rc){
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }
printf("Main: Done.\n");
pthread_exit(NULL);							//naprawa
}


/****************************************************************************************************
 Obserwacja skompilowane programu: Wątki startują, ale niekończą swojej pracy (nie widać, żeby zwróciły wynik obliczeń),
 a nawet nie wszystkie zdązą wystartować.

Problem - program nie zawiera pthread_exit w main - co powoduje, że kończy swoją prace po stworzeniu wątków nie czekając
na nie - a jak sam sie zamyka to też zamyka wątki.

Użycie pthread_exit powoduje, że main czeka aż zakończą się  wszystkie wątki.



 */

