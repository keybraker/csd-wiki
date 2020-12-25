// ConsoleApplication2.cpp : Defines the entry point for the console application.


//

//#include "stdafx.h"


#include "language.h"

















PROGRAM_BEGIN

REGEX(r1) : START TEXT(a) END
REGEX(r2) : START TEXT(a)* TEXT(b) END
REGEX(r3) : START TEXT(a) DOT CHAR(s) OPTIONAL TEXT(b) END
REGEX(r4) : START[TEXT(abc)] CHAR(b) | TEXT(a)  END
REGEX(r5) : START TEXT(a)- TIMES {2} END
REGEX(r6) : START  TEXT(a) +TEXT(b) TIMES { 5, 7 } END




MATCH r1 WITH "a"
MATCH r2 WITH "ab"
MATCH r3 WITH "awb"
MATCH r4 WITH "a"
MATCH r5 WITH "abc"
MATCH r6 WITH "a"
 


PROGRAM_END





















