/*
 * zad5_join.c
 *
 *  Created on: 13 sty 2021
 *      Author: izabela
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS	4

void *BusyWork(void *t)
{
   int i;
   long tid;
   double result=0.0;
   tid = (long)t;
   printf("Thread %ld starting...\n",tid);
   for (i=0; i<1000000; i++)
   {
      result = result + sin(i) * tan(i);
   }
   result = result * tid;									//zmiana, aby wątki zwracały różne wartości
   printf("Thread %ld done. Result = %e\n",tid, result);
   pthread_exit((void*) t);
}

int main (int argc, char *argv[])
{
   pthread_t thread[NUM_THREADS];
   pthread_attr_t attr;
   int rc;
   long t;
   void *status;

   /* Initialize and set thread detached attribute */
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   for(t=0; t<NUM_THREADS; t++) {
      printf("Main: creating thread %ld\n", t);
      rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t);
      if (rc) {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
         }
      }

   /* Free attribute and wait for the other threads */
   pthread_attr_destroy(&attr);
   for(t=0; t<NUM_THREADS; t++) {
      rc = pthread_join(thread[t], &status);
      if (rc) {
         printf("ERROR; return code from pthread_join() is %d\n", rc);
         exit(-1);
         }
      printf("Main: completed join with thread %ld having a status of %ld\n",t,(long)status);
      }

printf("Main: program completed. Exiting.\n");
pthread_exit(NULL);
}


/**********************************************************************************************************************************************
 pthread_attr_setdetachstate - służy do ustawienia czy wątki będą tworzone w stanie detached czy joinable.
W stanie detached wątki zwalniają zasoby zaraz po zakończeniu.
W stanie joinable wątki MOGĄ oczekiwać na zakończeniu innego wątku i dopiero wtedy zwalniają zasoby

W programie join.c - funkcja pthread_join zawiesza dzialanie wołajacego wątku, w naszym przypadku w 4, aż do momentu, gdy wątek identyfikowany
 przez thread[t] nie zakończy działania i kod zakończenia wątku jest przekazywany do zmiennej status.


 */



