/*
 * zad7.c
 *
 *  Created on: 21 lis 2020
 *      Author: izabela
 */


#include <stdio.h>
char * napis = "Witajcie moi mili ...";
int main(){
  unsigned int index =0;
  for (index; ; index++){
    printf("%c",napis[index]);
  }
  return 0;
}
