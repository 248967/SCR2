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

   int sumapunktowkolo=0;
   tid = (long)t;
   double *pi = malloc(sizeof *pi);	//robimy wskaźnik do zwrócenia wartości z wątku,
   //bo double nie konwertuje się do wskaźnika tak jak int i potem jest zwraca kompilator błąd przy np. printf w main



   printf("Startuje wątek nr %ld...\n",tid);
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
   //pi=4*sumapunktowkolo/iloscprob;
   //pi=(double)4*sumapunktowkolo/iloscprob;
   *pi=(double)4*sumapunktowkolo/iloscprob;

   printf("Pi=%f w wątku nr %ld\n",pi,tid);
   pthread_exit((void*) pi);
}


int main (int argc, char *argv[])
{
   pthread_t thread[NUM_THREADS];
   pthread_attr_t attr;
   int rc;
   long t;
   //void *status;
   double liczbapi;

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
	  rc = pthread_join(thread[t], (void*) &liczbapi);
      if (rc) {
         printf("ERROR; return code from pthread_join() is %d\n", rc);
         exit(-1);
         }
      printf("Main: completed join with thread %ld having a score of %f\n",t,liczbapi);
     }

printf("Main: program completed. Exiting.\n");
pthread_exit(NULL);
}
