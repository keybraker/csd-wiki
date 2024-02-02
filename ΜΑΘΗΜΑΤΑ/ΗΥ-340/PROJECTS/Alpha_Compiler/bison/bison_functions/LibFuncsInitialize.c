#include "../bison_libs/DataStruct.h"

void libFuncInit()
{

	insert("print", function, LIBFUNC, 0, 0, 0, -1, -1);
	insert("input", function, LIBFUNC, 0, 0, 0, -1, -1);
	insert("objectmemberkeys", function, LIBFUNC, 0, 0, 0, -1, -1);
	insert("objecttotalmembers", function, LIBFUNC, 0, 0, 0, -1, -1);
	insert("objectcopy", function, LIBFUNC, 0, 0, 0, -1, -1);
	insert("totalarguments", function, LIBFUNC, 0, 0, 0, -1, -1);
	insert("argument", function, LIBFUNC, 0, 0, 0, -1, -1);
	insert("typeof", function, LIBFUNC, 0, 0, 0, -1, -1);
	insert("strtonum", function, LIBFUNC, 0, 0, 0, -1, -1);
	insert("sqrt", function, LIBFUNC, 0, 0, 0, -1, -1);
	insert("cos", function, LIBFUNC, 0, 0, 0, -1, -1);
	insert("sin", function, LIBFUNC, 0, 0, 0, -1, -1);
}