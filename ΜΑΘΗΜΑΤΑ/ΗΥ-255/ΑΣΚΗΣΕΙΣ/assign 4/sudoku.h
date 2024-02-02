/*
 * sudoku.h
 * John Rambo
 * rambo@csd.uoc.gr
 * hy255
 * as4
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "grid.h"

/*
 * read a sudoku grid from stdin and return an object Grid_T
 * initialized to these values
 * the input has the format:

1 2 3 4 5 6 7 8 9
4 5 6 7 8 9 1 2 3
7 8 9 1 2 3 4 5 6
2 3 4 5 6 7 8 9 1
5 6 7 8 9 1 2 3 4
8 9 1 2 3 4 5 6 7
3 4 5 6 7 8 9 1 2
6 7 8 9 1 2 3 4 5
9 1 2 3 4 5 6 7 8

 * each number is followed by a space. Each line is terminated with
 * \n. Values of 0 indicate empty grid cells.
 */
Grid_T sudoku_read(void);

/*
 * print the sudoku puzzle defined by g to stream s in the same format
 * as expected by sudoku_read()
 */
void sudoku_print(FILE *s, Grid_T g);

/*
 * print all row, col, sub-grid errors/conflicts found in puzzle g
 * some errors may be reported more than once
 */
void sudoku_print_errors(Grid_T g);

/*
 * return true iff puzzle g is correct
 */
int sudoku_is_correct(Grid_T g);

/*
 * sovle puzzle g and return the solved puzzle
 * if the puzzle has multiple solutions return one of the possible solutions
 */
Grid_T sudoku_solve(Grid_T g);

/*
 * returns true if solution g as returned by sudoku_solve has a
 * unique choice for each step (no backtracking required)
 * note: g must have been computed with the use of sudoku_solve()
 */
int sudoku_solution_is_unique(Grid_T g);

/*
 * generate and return a sudoku puzzle with "approximately" nelts
 * elements having non-0 value
 * the smaller nelts the harder may be to generate/solve the puzzle
 * for instance nelts=81 should return a completed and correct puzzle
 * if unique=1 the puzzle must have a unique choice at each step of
 * finding the solution
 */
Grid_T sudoku_generate(int nelts, int unique);
