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
	    sleep(5);	//czekaj 5 sekund
	    printf("\n i= %d ",i);					//numer pliku - kontrola

		//otwarcie pliku do czytania
		plikwej[i-1] = fopen ( argv [i], "r");
		if ( plikwej[i-1] == NULL )
		{
			printf ( "Brak pliku\n" );
			return -1;
		}

		stream_fifo = fopen(myfifo, "w");  //otworzenie fifo do zapisu
		//czytam po kolei znaki z pliku wejściowego i zapisuje do potoku FIFO
		while ((c = fgetc (plikwej[i-1])) != EOF )
		{
			fprintf (stream_fifo, "%c", c);
			//fprintf (stdout, "\n %c \n", c);
		}

		fclose(stream_fifo);


		fclose(plikwej[i-1]);
	}

	return 0;
}

/**********************************************************************************
 * Program w petli odczytuje podane pliki i zapisuje je do FIFO. Przed zapisaniem
 * każdego pliku jest 5 s przerwy. FIFO odczytuję komendą tail -f -c 5 /tmp/myfifo.
 *  Ciekawa sprawa, że opcja -c, która powoduje odczytanie ostatnich n bytów
 *  zadziałała tylko na pierwszy plik. Pozostałe zostały odczytane w całości.
 */
