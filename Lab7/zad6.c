/*
 * zad6.c
 *
 *  Created on: 13 sty 2021
 *      Author: izabela
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NTHREADS	8
#define ARRAY_SIZE      2000000

void *Hello(void *threadid)
{
   double A[ARRAY_SIZE];
   int i;
   long tid;

   tid = (long)threadid;
   sleep(3);
   for (i=0; i<ARRAY_SIZE; i++)
   {
      A[i] = i * 1.0;
   }
   printf("%ld: Hello World!   %f\n", tid, A[ARRAY_SIZE-1]);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NTHREADS];
size_t stacksize;
pthread_attr_t attr;
int rc;
long t;
pthread_attr_init(&attr);
pthread_attr_getstacksize (&attr, &stacksize);
printf("Thread stack size = %li bytes (hint, hint)\n",stacksize);
for(t=0;t<NTHREADS;t++){
  rc = pthread_create(&threads[t], NULL, Hello, (void *)t);
  if (rc){
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }
printf("Created %ld th reads.\n", t);
pthread_exit(NULL);
}

/******************************************************************************************************************************************************
 Program nie działa - narzuszenie ochrony pamięci. Dzieje się tak, ponieważ wielkość stosu wątku została przekroczona. Aby to naprawić należy zmienić
 wielkość dopuszczalnego rozmiaru stosu - można to zrobić korzystając z funkcji pthread_attr_setstacksize - ustawiając wielkość stosu na rozmiar
 tablicy A + odpowiednio duży zapas na inne potrzeby. Można także zmniejszyć wielkość tablicy A.

 */

