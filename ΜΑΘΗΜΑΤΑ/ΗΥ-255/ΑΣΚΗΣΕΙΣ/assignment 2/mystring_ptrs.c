#include <stdio.h>
#include <assert.h>

/*string length
 Returns the length of string pcStr.
 It is a checked runtime error for pcStr to be NULL.*/

size_t ms_length(const char *pcStr)
{
    size_t uiLength = 0U;
    assert(pcStr != NULL);
    while (*(pcStr + uiLength) != '\0')
        uiLength++;
    return uiLength;
}

/*string copy
 Returns combined string with "\0" in between
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_copy(char *pcStr1, char *pcStr2)
{

    int i = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);

    pcStr1 = pcStr2;
    i++;

    return pcStr1;
}

/*string n copy
 Returns combined string of length n with "\0" in between
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_ncopy(char *pcStr1, char *pcStr2, size_t n)
{

    int i = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);
    assert(n >= 0);

    for (i = 0; i < n; i++)
    {
        *(pcStr1 + i) = *(pcStr2 + i);
    }

    return pcStr1;
}

/*string cat
 Returns combined string with length without "\0"
 of the first array.
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_concat(char *pcStr1, char *pcStr2)
{

    int j = 0;
    size_t i = 0U;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);

    i = ms_length(pcStr1);

    while (*(pcStr2 + i) != '\0')
    {
        *(pcStr1 + i) = *(pcStr2 + j);
        j++;
        i++;
    }

    return pcStr1;
}

/*string n cat
 Returns combined string with length of n without "\0"
 of the first array.
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_nconcat(char *pcStr1, char *pcStr2, size_t n)
{

    size_t i = 0, j = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);
    assert(n >= 0);

    i = ms_length(pcStr1);
    j = ms_length(pcStr2);

    while (*(pcStr2 + i) != '\0' || j != n)
    {
        *(pcStr1 + i) = *(pcStr2 + j);
        j++;
        i++;
    }

    *(pcStr1 + i) = '\0';
    return pcStr1;
}

/*string compare
 Returns 1 if pcStr1<pcStr2, -1 pcStr1<pcStr2, 0 pcStr1=pcStr2
 It is a checked runtime error for pcStr to be NULL.*/

size_t ms_compare(char *pcStr1, char *pcStr2)
{

    size_t i = 0, j = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);

    i = ms_length(pcStr1);
    j = ms_length(pcStr2);

    printf(" %lu , ", i);
    printf(" %lu \n", j);

    if (i < j)
    {
        return 1;
    }
    else if (i > j)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/*string n compare
 Returns 1 if pcStr1<pcStr2, -1 pcStr1<pcStr2, 0 pcStr1=pcStr2
 It is a checked runtime error for pcStr to be NULL.*/

size_t ms_ncompare(char *pcStr1, char *pcStr2, size_t n)
{

    size_t i = 0, j = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);
    assert(n >= 0);

    i = ms_length(pcStr1);
    j = ms_length(pcStr2);

    printf(" %lu , ", i);
    printf(" %lu \n", j);

    if (n <= i)
    {
        i = n;
    }
    if (n <= j)
    {
        j = n;
    }

    if (i < j)
    {
        return 1;
    }
    else if (i > j)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/*String search
 Returns frist place of occurrence of pcStr2 in pcStr1
 It is a checked runtime error for pcStr to be NULL.*/
int cmpr(char a, char b)
{
    if (a == b)
    {
        return 1;
    }
    return 0;
}

size_t ms_search(char *pcStr1, char *pcStr2)
{
    size_t i = 0, j = 0, times = 0, ni = 0, n = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);

    while (pcStr1[j] != '\0')
    {
        j++;
    }
    j = 0;
    while (pcStr2[j] != '\0')
    {
        j++;
    }
    while (pcStr1[i] != '\0')
    {
        if (cmpr(pcStr1[i], pcStr2[0]) == 1)
        {

            n = 0;
            times = 0;
            ni = i;

            while (times < j)
            {
                if (cmpr(pcStr1[ni], pcStr2[times]) == 1)
                {
                    n++;
                }
                ni++;
                times++;
            }
            if (n == j)
            {
                return i;
            }
        }
        i++;
    }
    return -1;
}

int main()
{

    char *string1 = "ioannis", *string2 = "oan";
    char *stringcopy, *stringcat;
    size_t i, value = 0;

    printf("string1 : %s \n", string1);
    printf("string2 : %s \n", string2);

    /* testing ms_length */
    i = ms_length(string1);
    printf("ms_length of string1 : %lu \n", i);

    i = ms_length(string2);
    printf("ms_length of string2 : %lu \n", i);

    /* testing ms_copy */
    stringcopy = ms_copy(string1, string1);
    printf("ms_copy of string1 and string1 : %s \n", stringcopy);

    /* testing ms_ncopy */
    /*stringcopy = ms_ncopy(string1, string1, 4);
    printf("ms_ncopy of string1 and string1 : %s \n",stringcopy);
    */
    /* testing ms_concat */
    stringcat = ms_concat(string1, string1);
    printf("ms_concat of string1 and string1 : %s \n", stringcat);

    /* testing ms_nconcat */
    stringcat = ms_nconcat(string1, string1, 2);
    printf("ms_nconcat of string1 and string1 : %s \n", stringcopy);

    /* testing ms_compare */
    value = ms_compare(string2, string1);
    printf("ms_compare of string1 and string2 : %zu \n", value);

    /* testing ms_ncompare */
    value = ms_ncompare(string2, string1, 5);
    printf("ms_ncompare of string1 and string2 : %zu \n", value);

    /* testing ms_search */
    value = ms_search(string1, string2);
    printf("ms_search of string1 in string2 : %zu \n", value);

    return 0;
}
