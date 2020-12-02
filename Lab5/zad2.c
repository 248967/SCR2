/*
 * zad2.c
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
	//char bufor[5];  								//bufor do czytania paczkami

	//size_t bytes_read; 								 //używany do sprawdzenia ilości odczytanych znaków z potoku
	//char c;											//używany do odczytywania pliku wejściowego


	// Stworzenie potoku
	if (pipe (potok) == -1)
	{
		fprintf (stderr, "Nie udało się stworzyć potoku\n");
		return -1;
	}

	// Stworzenie procesu potomnego
	pid = fork ();

	if (pid == (pid_t) 0)										// jeśli proces potomny
	{
		//proces potomny zamknij potok do pisania, otwórz do czytania
		close (potok[1]);
		stream = fdopen (potok[0], "r");

		//podmiana stdin procesu na potok
		close(0);			//zamykamy stdin dla potomka
		dup(potok[0]);		// kopiujemy fd potoku na najniższy wolny file deskryptor czyli na 0 (stdin)
		close(potok[0]);	// dla porządku zamykamy potok[0]
		//wywolanie programu display
		execvp("/usr/bin/display", NULL);

		fclose(stream);
		return 0;
	}
	else if (pid < (pid_t) 0)			// nieudało się stworzyć procesu potomnego
	{
		fprintf (stderr, "Nie udało się stworzyć procesu potomnego.\n");
		return -1;
	}
	else								// jeśli rodzic
	{
		//sprawdzenie, czy podany plik wejściowy
		if (argc < 2)
		{
			fprintf (stderr, "Użycie: %s nazwa_pliku\n", argv[0]);
			return -1;
		}
		//otwarcie pliku wejściowego
		plikwej = fopen ( argv [1], "r");
		if ( plikwej == NULL )
		{
			printf ( "Brak pliku\n" );
			return -1;
		}

		//zamknij potok do czytania, otwórz do pisania
		close (potok[0]);
		stream = fdopen (potok[1], "w");

		fclose(stream);
		fclose(plikwej);
		return 0;

	}
}


