/*
 * mystring_ptrs.c
 * John Rambo
 * rambo@csd.uoc.gr
 * hy255
 * as2
 */

#include "mystring.h"

/*
 * finds the length of a C string
 */
size_t ms_length(const char *s)
{
  const char *p = s;
  assert(s != NULL);
  while (*p != '\0')
    p++;
  return (size_t)(p - s);
}

/*
 * copies a string from one location to another
 */
char *ms_copy(char *dest, const char *src)
{
  char *p = dest;
  const char *q = src;
  assert(src != NULL);
  while ((*p++ = *q++) != '\0')
    ;
  return dest;
}

/*
 * copies up to n bytes of a string from one location to another
 */
char *ms_ncopy(char *dest, const char *src, size_t len)
{
  char *p = dest;
  const char *q = src;
  assert(src != NULL);
  while (len > 0)
  {
    len--;
    if ((*p++ = *q++) == '\0')
    {
      /* a '\0' char is found at the end of src and we fill
   with '\0' chars*/
      while (len-- != 0)
        *p++ = '\0';
      break;
    }
  }
  return dest;
}

/*
 * appends the string src to dest
 */
char *ms_concat(char *dest, const char *src)
{
  char *s = dest;
  assert(src != NULL);
  /* move s to the end of dest */
  while (*s != '\0')
    s++;
  /* copy src next to dest */
  ms_copy(s, src);
  return dest;
}

/*
 * appends at most n characters of the string src to dest
 */
char *ms_nconcat(char *dest, const char *src, size_t len)
{
  char *s = dest;
  assert(src != NULL);
  /* copy src next to dest */
  while (*s != '\0')
    s++;
  /* copy len bytes from src to dest, but stop if '\0' comes */
  while (len != 0 && (*s = *src++) != '\0')
  {
    len--;
    s++;
  }
  /* null terminate */
  if (*s != '\0')
    *s = '\0';
  return dest;
}

/*
 * compares two strings numerically
 */
int ms_copmare(const char *s1, const char *s2)
{
  unsigned char uc1, uc2;
  /* move s1 and s2 to first different char or at end */
  while (*s1 != '\0' && *s1 == *s2)
  {
    s1++;
    s2++;
  }
  /* compare and return difference */
  uc1 = (*(unsigned char *)s1);
  uc2 = (*(unsigned char *)s2);
  if (uc1 < uc2)
    return -1;
  else if (uc1 > uc2)
    return 1;
  return 0;
}

/*
 * compares up to the first n bytes of two strings numerically
 */
int ms_ncompare(const char *s1, const char *s2, size_t len)
{
  unsigned char uc1, uc2;
  /* case len is 0 */
  if (len == 0)
    return 0;
  /* compare bytes */
  while (len-- > 0 && *s1 == *s2)
  {
    /* case end or null found return 0 */
    if (len == 0 || *s1 == '\0')
      return 0;
    s1++;
    s2++;
  }
  uc1 = (*(unsigned char *)s1);
  uc2 = (*(unsigned char *)s2);
  if (uc1 < uc2)
    return -1;
  else if (uc1 > uc2)
    return 1;
  return 0;
}

static char *findchar(const char *s, int c)
{
  /* scan s for the char c
     when finished points at end of string
     or at the char */
  while (*s != '\0' && *s != (char)c)
    s++;
  return ((*s == c) ? (char *)s : NULL);
}

/*
 * finds the first occurrence of little in big
 */
char *ms_search(const char *big, const char *little)
{
  size_t littlelen;
  assert(big != NULL);
  /* if little null */
  if (*little == '\0')
    return (char *)big;
  littlelen = ms_length(little);
  for (; (big = findchar(big, *little)) != NULL; big++)
    if (ms_ncompare(big, little, littlelen) == 0)
      return (char *)big;
  return NULL;
}
