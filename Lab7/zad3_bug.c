/*
 * zad3_bug.c
 *
 *  Created on: 13 sty 2021
 *      Author: izabela
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS     8

	void *PrintHello(void *threadid)
	{
		long taskid;
		sleep(1);
		taskid = (long) threadid;										// było:  taskid = *(long *)threadid;
		printf("Hello from thread %ld\n", taskid);
		pthread_exit(NULL);
	}

	int main(int argc, char *argv[])
	{
		pthread_t threads[NUM_THREADS];
		int rc;
		long t;

		for(t=0;t<NUM_THREADS;t++)
		{
			printf("Creating thread %ld\n", t);
			rc = pthread_create(&threads[t], NULL, PrintHello, (void *) t);				//zmiana z &t na t, czyli z adresu na wartość zmiennej
			if (rc)
			{
				printf("ERROR; return code from pthread_create() is %d\n", rc);
				exit(-1);
			}
		}

		pthread_exit(NULL);
	}


/*****************************************************************************************************************************
 Przekazywanie zmiennych do wątków:

1) hello_arg1.c - pojedynczy argument przekazywany jest jako element tablicy taskids[t]
2) hello_arg2.c - poprzez strukturę danych - przekazywanie wielu argumentów


Program bug3.c po uruchomieniu zawsze pokazuje "Hello from thread 8", a w programie teoretycznie uruchamiane są wątki z numerami
od 0 do 7. Problem jest w przekazaniu zmiennej t do wątka. Przekazywany jest adres do zmiennej t, ale zanim wątki wystartują to
pętla tworząca wątki się zakończyła i wartość t ustawiła się na 8 - i wszystkie wątki wyświetlają jej końcową wartość - bo taka jest zapisana.

Żeby działało poprawnie trzeba zmienić:
pthread_create(&threads[t], NULL, PrintHello, (void *) &t);
na
pthread_create(&threads[t], NULL, PrintHello, (void *) t);

i poprawić w funkcji PrintHello:
taskid = *(long*) threadid;
na
taskid = (long) threadid;
 */
