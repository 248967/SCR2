/*
 * zad3.c
 *
 *  Created on: 2 gru 2020
 *      Author: izabela
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main (int argc, char **argv)
{
	int c;
	FILE *stream_fifo;

	// Stworzenie potoku FIFO
	char *myfifo = "/tmp/myfifo";	//ścieżka dla FIFO
	if (mkfifo(myfifo, 0666)==-1)			// stworzenie fifo, nadanie uprawnień
	{
		fprintf (stderr, "Nie udało się stworzyć FIFO\n");
		return -1;
	}

	if (argc < 2)
	{
		fprintf (stderr, "Użycie: %s nazwy_plików\n", argv[0]);
		return -1;
	}

	FILE *plikwej[argc-1];	//deklaracja tablicy wskaźników plików wejściowych

	for (int i = 1; i < argc; i++)
	{
		//otwarcie pliku do czytania
		plikwej[i-1] = fopen ( argv [i], "r");
		if ( plikwej[i] == NULL )
		{
			printf ( "Brak pliku\n" );
			return -1;
		}

		stream_fifo = fopen(myfifo, "w");  //otworzenie fifo do zapisu
		//czytam po kolei znaki z pliku wejściowego i zapisuje do potoku FIFO
		while ((c = fgetc (plikwej[i])) != EOF )
		{
			fprintf (stream_fifo, "%c", c);
			//fprintf (stderr, "\n %c \n", c);
		}

		fclose(stream_fifo);


		fclose(plikwej[i]);
	}

	return 0;
}
