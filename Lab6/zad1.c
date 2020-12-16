/*
 * zad1.c
 *
 *  Created on: 16 gru 2020
 *      Author: izabela
 */

#include <stdio.h>
#include <sys/mman.h>


int main (int argc, char **argv)
{
	int fd;
	int *map;

	while(1)
	{
		//void * mmap (void *address, size_t length, int protect, int flags, int filedes, off_t offset);

		//otwórz plik do czytania i pisania, jesli nie istnieje stwórz go, jesli istnieje obetnij go
		fd = open("/tmp/plikdomapowania", O_RDWR | O_CREAT | O_TRUNC, (mode_t)0666);
		if (fd == -1)
		{
			printf("Błąd otwarcia pliku\n");
			exit(EXIT_FAILURE);
		}

		map = mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);
		if (map == MAP_FAILED)
		{
			close(fd);
			printf("Błąd mapowania pliku\n");
			exit(EXIT_FAILURE);
		}
	}


	// zwolnienie zmapowanej pamięci
	if (munmap(map, FILESIZE) == -1)
	{
		printf("Błąd odmapowania pliku");
	}


	close(fd);
	return 0;

}

