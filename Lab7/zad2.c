/*
 * zad2.c
 *
 *  Created on: 13 sty 2021
 *      Author: izabela
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#define NTHREADS	32

void *Hello(void *threadid)
{
   int i;
   double result=0.0;
   sleep(3);
   for (i=0; i<10000; i++) {
     result = result + sin(i) * tan(i);
     }
   printf("%ld: Hello World!\n", threadid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NTHREADS];
int rc;
long t;
for(t=0;t<NTHREADS;t++){
  rc = pthread_create(&threads[t], NULL, Hello, (void *)t);
  if (rc){
    printf("ERROR: return code from pthread_create() is %d\n", rc);
    printf("Code %d= %s\n",rc,strerror(rc));
    exit(-1);
    }
   }
printf("main(): Created %ld threads.\n", t);
pthread_exit(NULL);
}

/*****************************************************************************************************
Kolejność wykonania wątków jest za każdym razem inna.

Wynika to pewnie z tego, że wątki startują równolegle, ale ponieważ w Linux są wątki jądra
to system operacyjny przydziela dostęp do procesorów i w praktyce za każdym inna jest kolejność
obsługi wątków. Programista nie ma tutaj wpływu na kolejności obsługi wątków.


W Linux mamy mapowanie na wątki jądra 1 : 1 i o przydziale dostępu do procesorów decyduje OS.
Linux nie odróżnia wątków od procesów.

*******************************************************************************************************/


