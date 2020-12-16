/*
 * zad2.c
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
#include <string.h>


int main ()
{
	pid_t pid;
	int fd, fdw;
	int *map;
	char filename[50]; //nazwa wczytanego pliku w pętli
	struct stat sb;	//używane do sprawdzenia rozmiaru pliku
	long int filesize; //zmienna do rozmiaru pliku

	pid = fork ();
	if (pid == (pid_t) 0)
	{
		//proces potomny
		//wywolanie programu qiv
		execlp("qiv", "qiv", "--watch", "/tmp/plikdomapowania", NULL);
		return 0;
	}
	else if (pid < (pid_t) 0)
	{
		// fork nieudany
		fprintf (stderr, "Nie udało się stworzyć procesu potomnego.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		//proces rodzic

		//otwórz plik do czytania i pisania, jesli nie istnieje stwórz go
		fd = open("/tmp/plikdomapowania", O_RDWR | O_CREAT, (mode_t)0666);
		if (fd == -1)
		{
			fprintf (stderr, "Błąd otwarcia pliku\n");
			exit(EXIT_FAILURE);
		}

		//mapowanie pliku - odczyt zapis, inicjalny rozmiar 4096
		map = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if (map == MAP_FAILED)
		{
			close(fd);
			fprintf (stderr, "Błąd mapowania pliku\n");
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
				fprintf (stderr, "Błąd otwarcia pliku\n");
				close(fd);
				exit(EXIT_FAILURE);
			}

			// sprawdzenie rozmiaru pliku
			if (stat(filename, &sb) == -1)
			{
				fprintf (stderr, "Nie udało się pobrać rozmiaru pliku\n");
				close(fdw);
				close(fd);
				exit(EXIT_FAILURE);
			}
			filesize = sb.st_size;

			//zmiana wielkości pliku zmapowanego wyściowego fd
			if (ftruncate(fd,filesize) == -1)
			{
				close(fdw);
				close(fd);
				exit(EXIT_FAILURE);
			}

			//printf("Debug mmap zmiana\n");

			//mapowanie otwartego pliku fd do pamięci
			map = mmap(0, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
			if (map == MAP_FAILED)
			{
				fprintf (stderr, "Błąd mapowania pliku wejściowego\n");
				close(fdw);
				close(fd);
				exit(EXIT_FAILURE);
			}

			//printf("Debug kopiowanie do pamięci");

			//kopiowanie pliku wejściowego do pamięci
			int num = read(fdw, map, filesize);
			//printf ("Debug ilość bytów: %d \n", num);

			//synchronizacja pamięci z plikiem
			if (msync(map, filesize, MS_SYNC) == -1)
			{
				fprintf(stderr, "Msync nieudany\n");
			}

		}

	}

	// zwolnienie zmapowanej pamięci i zamknięcie plików - program tu teorytycznie nie wejdzie, ale zostawiam dla pewności
	if (munmap(map, filesize) == -1)
	{
		fprintf (stderr, "Błąd odmapowania pliku");
	}


	close(fd);
	close(fdw);
	return 0;

}
