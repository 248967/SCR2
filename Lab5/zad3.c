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


int main (int argc, char **argv)
{
  FILE *stream_fifo;

  // Stworzenie potoku FIFO
  char *myfifo = "/tmp/myfifo";	//ścieżka dla FIFO
  if (mkfifo(myfifo, 0666))			// stworzenie fifo, nadanie uprawnień
  {
    fprintf (stderr, "Nie udało się stworzyć FIFO\n");
    return -1;
  }

  if (argc < 2)
  {
	fprintf (stderr, "Użycie: %s nazwy_plików\n", argv[0]);
	return -1;
  }

  FILE *plikwej[argc];	//deklaracja tablicy wskaźników plików wejściowych

  for (int i = 1; i < argc; i++)
  {
  	//otwarcie pliku do czytania
	plikwej[i] = fopen ( argv [i], "r");
   	if ( plikwej[i] == NULL )
   	{
   	  printf ( "Brak pliku\n" );
   	  return -1;
   	}


    fclose(plikwej[i]);
  }

   return 0;
}
