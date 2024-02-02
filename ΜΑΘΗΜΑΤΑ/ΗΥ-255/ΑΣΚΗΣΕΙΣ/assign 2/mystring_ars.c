/*
 * mystring_ars.c
 * John Rambo
 * rambo@csd.uoc.gr
 * hy255
 * as2
 */

#include "mystring.h"

/*
 * finds the length of a C string
 */
size_t ms_length(const char s[])
{
  const char *p = s;
  size_t i = 0;
  assert(s != NULL);
  while (p[i] != '\0')
    i++;
  return i;
}

/*
 * copies a string from one location to another
 */
char *ms_copy(char dest[], const char src[])
{
  char *p = dest;
  const char *q = src;
  size_t i = ms_length(dest);
  size_t j = 0;
  assert(src != NULL);
  while ((p[i++] = q[j++]) != '\0')
    ;
  return dest;
}

/*
 * copies up to n bytes of a string from one location to another
 */
char *ms_ncopy(char dest[], const char src[], size_t len)
{
  char *p = dest;
  const char *q = src;
  size_t i = ms_length(dest);
  size_t j = 0;
  assert(src != NULL);
  while (len > 0)
  {
    len--;
    if ((p[i++] = q[j++]) == '\0')
    {
      /* a '\0' char is found at the end of src and we fill
   with '\0' chars*/
      while (len-- != 0)
        p[i++] = '\0';
      break;
    }
  }
  return dest;
}

/*
 * appends the string src to dest
 */
char *ms_concat(char dest[], const char src[])
{
  char *s = dest;
  size_t i = ms_length(dest);
  assert(src != NULL);
  /* move s to the end of dest */
  while (s[i] != '\0')
    s[i++];
  /* copy src next to dest */
  ms_copy(s, src);
  return dest;
}

/*
 * appends at most n characters of the string src to dest
 */
char *ms_nconcat(char dest[], const char src[], size_t len)
{
  char *s = dest;
  size_t i = ms_length(dest);
  size_t j = 0;
  assert(src != NULL);
  /* copy src next to dest */
  while (s[i] != '\0')
    s[i++];
  /* copy len bytes from src to dest, but stop if '\0' comes */
  while (len != 0 && (s[i++] = src[j++]) != '\0')
  {
    len--;
    s[i++];
  }
  /* null terminate */
  if (s[i] != '\0')
    s[i] = '\0';
  return dest;
}

/*
 * compares two strings numerically
 */
int ms_copmare(const char s1[], const char s2[])
{
  unsigned char uc1, uc2;
  size_t i = 0;
  size_t j = 0;
  /* move s1 and s2 to first different char or at end */
  while (s1[i] != '\0' && s1[i] == s2[j])
  {
    s1[i++];
    s2[j++];
  }
  /* compare and return difference */
  uc1 = ((unsigned char)s1[i]);
  uc2 = ((unsigned char)s2[j]);
  if (uc1 < uc2)
    return -1;
  else if (uc1 > uc2)
    return 1;
  return 0;
}

/*
 * compares up to the first n bytes of two strings numerically
 */
int ms_ncompare(const char s1[], const char s2[], size_t len)
{
  unsigned char uc1, uc2;
  size_t i = 0;
  size_t j = 0;
  /* case len is 0 */
  if (len == 0)
    return 0;
  /* compare bytes */
  while (len-- > 0 && s1[i] == s2[j])
  {
    /* case end or null found return 0 */
    if (len == 0 || s1[i] == '\0')
      return 0;
    s1[i++];
    s2[j++];
  }
  uc1 = ((unsigned char)s1[i]);
  uc2 = ((unsigned char)s2[j]);
  if (uc1 < uc2)
    return -1;
  else if (uc1 > uc2)
    return 1;
  return 0;
}

static char *findchar(const char s[], int c)
{
  size_t i = 0;
  /* scan s for the char c
     when finished points at end of string
     or at the char */
  while (s[i] != '\0' && s[i] != (char)c)
    s[i++];
  return ((s[i] == c) ? (char *)s : NULL);
}

/*
 * finds the first occurrence of little in big
 */
char *ms_search(const char big[], const char little[])
{
  size_t littlelen;
  size_t i = 0;
  size_t j = 0;
  assert(big != NULL);
  /* if little null */
  if (little[j] == '\0')
    return (char *)big;
  littlelen = ms_length(little);
  for (; (big = findchar(big, little[j])) != NULL; big[i++])
    if (ms_ncompare(big, little, littlelen) == 0)
      return (char *)big;
  return NULL;
}
