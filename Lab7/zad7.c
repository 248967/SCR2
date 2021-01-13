/*
 * zad7.c
 *
 *  Created on: 13 sty 2021
 *      Author: izabela
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	4
#define iloscprob 100

void *MonteCarlo(void *t)
{
   int i;
   long tid;
   double x,y;
   //void *pi;
   //double pi=0.0;
   float pi;
   double *wynik;
   int sumapunktowkolo=0;
   tid = (long)t;


   //printf("Thread %ld starting...\n",tid);
   for (i=0; i<iloscprob; i++)
   {
	  //inicjacja funkcji losowej
	  srand48(time(0));
	  x = drand48();
      y = drand48();

      //czy punkt należy do koła o środku (0,5;0,5) i promieniu 0,5
      if ( (x-0.5)*(x-0.5)+(y-0.5)*(y-0.5) <= (0.5*0.5) )
    	  sumapunktowkolo++;
   }
   //pole kwadratu wynosi 1, pole koła wynosi pi*0,25, więc pi=4*ilość punktów w kole / ilość punktów w kwadracie

   pi=(double)4*sumapunktowkolo/iloscprob;
   //pi=4;
   wynik =&pi;
   printf("iloscprob=%d\n",iloscprob);
   printf("sumapunktówkolo=%d\n",sumapunktowkolo);
   printf("Pi=%f\n",pi);
   printf("Piadres=%f\n",wynik);
   //*((double*)pi) = 100;
   //pthread_exit((void*) pi);
   pthread_exit((void*) wynik);
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
      rc = pthread_create(&thread[t], &attr, MonteCarlo, (void *)t);
      if (rc) {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
         }
      }

   /* Free attribute and wait for the other threads */
   pthread_attr_destroy(&attr);
   for(t=0; t<NUM_THREADS; t++)
   {
      //kod zakończenia wątku thread[t] jest umieszczany w status
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

