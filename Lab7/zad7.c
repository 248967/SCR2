/*
 * zad7.c
 *
 *  Created on: 13 sty 2021
 *      Author: izabela
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	40
#define iloscprob 50

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

	printf("Kończy się wątek nr %ld. Liczba Pi wynosi %f.\n",tid,*pi);
	//printf("Pi=%f w wątku nr %ld\n",&pi,tid);
	pthread_exit(pi);
}


int main (int argc, char *argv[])
{
	pthread_t thread[NUM_THREADS];
	pthread_attr_t attr;
	int rc;
	long t;
	//void *status;
	double *liczbapi=NULL;
	double tabelapi[NUM_THREADS];	//tabela z poszczegolnymi wynikami obliczenia liczby pi z wątków
	double sredniapi=0;

	//inicjacja funkcji losowej
	srand48(time(0));

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
		//kod zakończenia wątku thread[t] jest umieszczany w liczbapi
		//rc = pthread_join(thread[t], (void*) &liczbapi);
		rc = pthread_join(thread[t], (void**) &liczbapi);
		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}
		tabelapi[t]=*liczbapi;
		sredniapi=sredniapi+tabelapi[t];	//sumowanie wyników poszczególnych pi, potem będzie podzielone przez ilość wątków
		free(liczbapi);
		printf("Main: zakończony z wątkiem %ld mająwcy wynik pi= %f\n",t,tabelapi[t]);
	}

	sredniapi=sredniapi/NUM_THREADS;
	printf("Main: Średnia wartość Pi=%f. Program zakończony.\n",sredniapi);
	pthread_exit(NULL);
}

/************************************************************************************************************************************************************
Zakładamy, że kwadrat wyznaczają współrzędne (0,0), (0,1), (1,0), (1,1)
To środek wpisanego koła będzie w punkcie (0,5; 0,5) a jego promień to 0,5.

Punkt o współrzędnych (x,y) należy do koła o środku (a,b) i promieniu r gdy: (x-a)^2+(y-b)^2 <= r^2

Dobranie parametrów - zwiększenie ilości "prób" w pojedynczym wątku skutkowało, zwiększeniem ilości cyfr znaczących po przecinku w obliczeniach danego wątku
 i dokładności.

Przy zwiększeniu ilości watków nie widać dużego wpływu na dokładność liczby pi.
 */
