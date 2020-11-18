/*
 * zad2.c
 *
 *  Created on: 17 lis 2020
 *      Author: izabela
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

int i;
int sig;	//numer odebranego sygnału
int iteracje=0; //liczba iteracji do ignorowania odebranych sygnałów

void sighandler(int signum) { // Procedura obsługi sygnału
	printf(" Kontrola odebrania sygnału %d \n",signum);      // polecenie kontrolne
	sig = signum;
}

int main(void) {

	signal(SIGALRM, sighandler);
	signal(SIGTERM, sighandler);
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);

	do
	{
		if(iteracje>0)		//osługa ignorowania sygnałów przez 1000 iteracji
		{
			iteracje--;
			sig=-1;
		}
		if(iteracje==0)		// minęło 1000 iteracji albo nie było włączone pomijanie
		{
		switch (sig)
		{
			case 14:
				printf("Przechwycony sygnał SIGALRM. Kończę pracę programu. \n");
				return 0;
		    break;

		    case 15:
		    	printf("Przechwycony sygnał SIGTERM. Działam dalej. \n");
		    	sig=-1;
		    break;

		    case 10:
		    	printf("Przechwycony sygnał SIGUSR1. Ignoruję sygnały przez 1000 następnych iteracji. \n");
		    	iteracje=100;     //testowo na 100
		    	sig=-1;
		    break;


		    case 12:
		    	sig=-1;
		    break;

		    //default:
		}
		}
		i++;
		nanosleep((const struct timespec[]){{0, 100000000L}}, NULL);	//100 milisekund

	}while(1);

	return 0;
}


