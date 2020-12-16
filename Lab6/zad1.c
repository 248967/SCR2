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
	int fd;
	int *map;

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

	}

	// zwolnienie zmapowanej pamięci
	if (munmap(map, FILESIZE) == -1)
	{
		printf("Błąd odmapowania pliku");
	}


	close(fd);
	return 0;

}

