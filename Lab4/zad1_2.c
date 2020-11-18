/*
 * zad1_2.c
 *
 *  Created on: 17 lis 2020
 *      Author: izabela
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i;
int main(void) {
	do
	{
		i++;
		nanosleep((const struct timespec[]){{0, 100000000L}}, NULL);	//100 milisekund
	}while(1);
	return 0;
}
