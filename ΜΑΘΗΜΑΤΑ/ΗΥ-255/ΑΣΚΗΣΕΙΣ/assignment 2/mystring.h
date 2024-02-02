/*string length
 Returns the length of string pcStr.
 It is a checked runtime error for pcStr to be NULL.*/

size_t ms_length(const char pcStr[]);

/*string copy
 Returns combined string with "\0" in between
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_copy(char pcStr1[], char pcStr2[]);

/*string n copy
 Returns combined string of length n with "\0" in between
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_ncopy(char pcStr1[], char pcStr2[], size_t n);

/*string cat
 Returns combined string with length without "\0"
 of the first array.
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_concat(char pcStr1[], char pcStr2[]);

/*string n cat
 Returns combined string with length of n without "\0"
 of the first array.
 It is a checked runtime error for pcStr to be NULL.*/

char *ms_nconcat(char pcStr1[], char pcStr2[], size_t n);

/*string compare
 Returns 1 if pcStr1<pcStr2, -1 pcStr1<pcStr2, 0 pcStr1=pcStr2
 It is a checked runtime error for pcStr to be NULL.*/

size_t ms_compare(char pcStr1[], char pcStr2[]);

/*string n compare
 Returns 1 if pcStr1<pcStr2, -1 pcStr1<pcStr2, 0 pcStr1=pcStr2
 It is a checked runtime error for pcStr to be NULL.*/

size_t ms_ncompare(char pcStr1[], char pcStr2[], size_t n);

/*String search
 Returns first place of occurrence of pcStr2 in pcStr1
It is a checked runtime error for pcStr to be NULL.*/

/*cmpr checks the length of both strings and returns one of three values
one of three values -1, 0, 1*/

int cmpr(char a, char b);

size_t ms_search(char pcStr1[], char pcStr2[]);
