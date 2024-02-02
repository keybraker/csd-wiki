#include <stdio.h>
#include <assert.h>

/*string length
 Returns the length of string pcStr.
 It is a checked runtime error for pcStr to be NULL.*/

size_t ms_length(const char pcStr[])
{
    size_t uiLength = 0U;
    assert(pcStr != NULL);
    while (pcStr[uiLength] != '\0')
        uiLength++;
    return uiLength;
}

/*string copy
 Returns combined string with "\0" in between
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_copy(char pcStr1[], char pcStr2[])
{

    int i = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);

    while (pcStr2[i] != '\0')
    {
        pcStr1[i] = pcStr2[i];
        i++;
    }

    pcStr1[i] = '\0';
    return pcStr1;
}

/*string n copy
 Returns combined string of length n with "\0" in between
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_ncopy(char pcStr1[], char pcStr2[], size_t n)
{
    int i = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);
    assert(n >= 0);

    while (i != n)
    {
        pcStr1[i] = pcStr2[i];
        i++;
    }

    pcStr1[i] = '\0';
    return pcStr1;
}

/*string cat
 Returns combined string with length without "\0"
 of the first array.
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_concat(char pcStr1[], char pcStr2[])
{

    int i = 0, j = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);

    while (pcStr1[i] != '\0')
    {
        i++;
    }
    while (pcStr2[j] != '\0')
    {
        pcStr1[i] = pcStr2[j];
        j++;
        i++;
    }

    pcStr1[i] = '\0';
    return pcStr1;
}

/*string n cat
 Returns combined string with length of n without "\0"
 of the first array.
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_nconcat(char pcStr1[], char pcStr2[], size_t n)
{

    int i = 0, j = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);
    assert(n >= 0);

    while (pcStr1[i] != '\0')
    {
        i++;
    }
    while (j != n)
    {
        pcStr1[i] = pcStr2[j];
        j++;
        i++;
    }

    pcStr1[i] = '\0';
    return pcStr1;
}

/*string compare
 Returns 1 if pcStr1<pcStr2, -1 pcStr1<pcStr2, 0 pcStr1=pcStr2
 It is a checked runtime error for pcStr to be NULL.*/

size_t ms_compare(char pcStr1[], char pcStr2[])
{

    size_t i = 0, j = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);

    while (pcStr1[i] != '\0')
    {
        i++;
    }
    while (pcStr2[j] != '\0')
    {
        j++;
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

/*string n compare
 Returns 1 if pcStr1<pcStr2, -1 pcStr1<pcStr2, 0 pcStr1=pcStr2
 It is a checked runtime error for pcStr to be NULL.*/

size_t ms_ncompare(char pcStr1[], char pcStr2[], size_t n)
{

    size_t i = 0, j = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);
    assert(n >= 0);

    while (pcStr1[i] != '\0')
    {
        i++;
    }
    while (pcStr2[j] != '\0')
    {
        j++;
    }

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

size_t ms_search(char pcStr1[], char pcStr2[])
{
    size_t i = 0, j = 0, times = 0, ni = 0, n = 0;

    assert(pcStr1 != NULL);
    assert(pcStr2 != NULL);

    while (pcStr1[j] != '\0')
    {
        printf("%c ", pcStr1[j]);
        j++;
    }
    j = 0;
    while (pcStr2[j] != '\0')
    {
        printf("%c ", pcStr2[j]);
        j++;
    }
    printf("pcStr1[i] != 0 => %c == 0\n", pcStr1[i]);
    while (pcStr1[i] != '\0')
    {
        printf("1)for %zu in: pcStr1[i] = pcStr2[0] => %c == %c\n", i, pcStr1[i], pcStr2[0]);
        if (cmpr(pcStr1[i], pcStr2[0]) == 1)
        {
            printf("2)for %zu in: pcStr1[i] = pcStr2[0] => %c == %c\n", i, pcStr1[i], pcStr2[0]);

            n = 0;
            times = 0;
            ni = i;

            printf("times = %zu < j =%zu \n", times, j);
            while (times < j)
            {
                printf("3) pcStr1[%zu] = pcStr2[%zu] => %c == %c\n", ni, times, pcStr1[ni], pcStr2[times]);
                if (cmpr(pcStr1[ni], pcStr2[times]) == 1)
                {
                    printf("in\n");
                    n++;
                }
                ni++;
                times++;
            }
            printf("n = j => %zu = %zu\n", n, j);
            if (n == j)
            {
                return i;
            }
        }
        i++;
    }
    return -1;
}
https: // www.google.com/cbk?cb_client=maps_sv.tactile&output=report&panoid=Ph8r7k5IefH8Jjv9cQ40SQ&hl=en&gl=gr&cbp=1%2C346%2C%2C0%2C0