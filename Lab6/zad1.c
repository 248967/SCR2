/*
 * zad1.c
 *
 *  Created on: 16 gru 2020
 *      Author: izabela
 */

#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main (int argc, char **argv)
{
	int fd, fdw;
	int *map;
	char filename[50]; //nazwa wczytanego pliku w pętli
	struct stat sb;	//używane do sprawdzenia rozmiaru pliku
	long int filesize; //zmienna do rozmiaru pliku

	//otwórz plik do czytania i pisania, jesli nie istnieje stwórz go, jesli istnieje obetnij go
	fd = open("/tmp/plikdomapowania", O_RDWR | O_CREAT | O_TRUNC, (mode_t)0666);
	if (fd == -1)
	{
		printf("Błąd otwarcia pliku\n");
		exit(EXIT_FAILURE);
	}

	//mapowanie pliku - odczyt zapis, inicjalny rozmiar 4096
	map = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED)
	{
		close(fd);
		printf("Błąd mapowania pliku\n");
		exit(EXIT_FAILURE);
	}

	//głowna petla
	while(1)
	{
		//otwarcie pliku podanego przez użytkownika
		printf("Podaj nazwę pliku: ");
		scanf("%s", filename);
		fdw = open(filename, O_RDONLY);
		if (fdw == -1)
		{
			printf("Błąd otwarcia pliku\n");
			exit(EXIT_FAILURE);
		}

		// sprawdzenie rozmiaru pliku
		if (stat(filename, &sb) == -1)
		{
			printf("Nie udało się pobrać rozmiaru pliku\n");
			exit(EXIT_FAILURE);
		}
		filesize = sb.st_size;

		//zmiana wielkości pliku zmapowanego wyściowego fd
		if (ftruncate(fd,filesize) == -1)
		{
			exit(EXIT_FAILURE);
		}

		printf("Debug mmap zmiana\n");

		//mapowanie otwartego pliku do pamięci
		map = mmap(0, filesize, PROT_READ, MAP_SHARED, fdw, 0);
		if (map == MAP_FAILED)
		{
			close(fdw);
			printf("Błąd mapowania pliku wejściowego\n");
			exit(EXIT_FAILURE);
		}

		printf("Debug kopiowanie do pamięci");

		//kopiowanie pliku wejściowego do pamięci
		int num = read(fdw, map, filesize);
		printf ("Debug ilość bytów: %d \n", num);

	}

	// zwolnienie zmapowanej pamięci
	/*if (munmap(map, FILESIZE) == -1)
	{
		printf("Błąd odmapowania pliku");
	}*/


	close(fd);
	return 0;

}

