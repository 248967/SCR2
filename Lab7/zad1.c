/*
 * zad1.c
 *
 *  Created on: 13 sty 2021
 *      Author: izabela
 */

#include <pthread.h>

// funkcja wyświetlająca napis
void *HelloSCR(void *threadid)
{
	//identyfikator wątka
	int tid = *((int*)threadid);
	//wyświetlenie tekstu
	printf("Hello SCR. Written by thread %d \n", tid);
	pthread_exit(NULL);
}

int main ()
{

}


