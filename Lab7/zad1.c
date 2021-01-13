/*
 * zad1.c
 *
 *  Created on: 13 sty 2021
 *      Author: izabela
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// funkcja wyświetlająca napis
void *HelloSCR(void *threadid)
{
	//identyfikator wątka
	int tid = *((int*)threadid);
	//wyświetlenie tekstu
	printf("Hello SCR. Written by thread %d \n", tid);
	//zakończenie wątku
	pthread_exit(NULL);
}

int main ()
{
	pthread_t threads[5];
	int indexes[5];
	int i;
	// tworzenie 5 wątków
	for( i=0; i < 5; i++ )
	{
		indexes[i] = i;
	    int result = pthread_create(&threads[i], NULL, HelloSCR, (void *)&(indexes[i]));
	    if (result !=0)
	    {
	         printf("Nie udało się utworzyć wątku.\n");
	    	 exit(-1);
	    }
	}
	pthread_exit(NULL);
}


