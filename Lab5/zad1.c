/*
 * zad1.c
 *
 *  Created on: 2 gru 2020
 *      Author: izabela
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main (int argc, char **argv)
{
	pid_t pid;
	int potok[2];									//deklaracja potoku
	FILE *plikwej;									// wskaźnik do pliku wejściowego

	FILE *stream;									// wskaźnik do użycia do czytania potoku
	char bufor[5];  								//bufor do czytania paczkami



	// Stworzenie potoku
	if (pipe (potok) == -1)
	{
		fprintf (stderr, "Nie udało się stworzyć potoku\n");
		return -1;
	}

	// Stworzenie procesu potomnego
	pid = fork ();

	if (pid == (pid_t) 0)				// jeśli proces potomny
	{
		return 0;
	}
	else if (pid < (pid_t) 0)			// nieudało się stworzyć procesu potomnego
	{
		fprintf (stderr, "Nie udało się stworzyć procesu potomnego.\n");
		return -1;
	}
	else								// jeśli rodzic
	{
		return 0;

	}
}
