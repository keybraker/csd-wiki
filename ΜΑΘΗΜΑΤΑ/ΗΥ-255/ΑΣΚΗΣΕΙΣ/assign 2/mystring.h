/*
 * mystring.h
 * John Rambo
 * rambo@csd.uoc.gr
 * hy255
 * as2
 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/*
 * finds the length of a C string
 */
size_t ms_length(const char *);

/*
 * copies a string from one location to another
 */
char *ms_copy(char *dest, const char *src);

/*
 * copies up to n bytes of a string from one location to another
 */
char *ms_ncopy(char *dest, const char *src, size_t);

/*
 * appends the string src to dest
 */
char *ms_concat(char *dest, const char *src);

/*
 * appends at most n characters of the string src to dest
 */
char *ms_nconcat(char *dest, const char *src, size_t);

/*
 * compares two strings numerically
 */
int ms_copmare(const char *, const char *);

/*
 * compares up to the first n bytes of two strings numerically
 */
int ms_ncompare(const char *, const char *, size_t);

/*
 * finds the first occurrence of little in big
 */
char *ms_search(const char *big, const char *little);
