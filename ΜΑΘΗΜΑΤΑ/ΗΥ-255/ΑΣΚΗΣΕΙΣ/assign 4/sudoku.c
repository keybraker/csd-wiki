/*
 * sudoku.c
 * John Rambo
 * rambo@csd.uoc.gr
 * hy255
 * as4
 */

#include <ctype.h>
#include <assert.h>
#include "sudoku.h"

#define  DIM     9
#define  SUBDIM  (DIM/3)
#define  CELLS   (DIM*DIM)

/*
 * complete all possible choices for each element in grid defined by g
 */
static void sudoku_init_choices(Grid_T *g){
  int i, j, k, l, n;
  /* set grid to initial state */
  grid_set_unique(g);                 /* set unique solution */
  for (i = 0; i < DIM; i++) {         /* access */
    for (j = 0; j < DIM; j++){        /* every element */
      grid_set_count(g, i, j);        /* set choices count */
      grid_clear_choice(g, i, j, 0);  /* clear zero choice for all */
      for (n = 1; n < DIM + 1; n++) {
        grid_set_choice(g, i, j, n);  /* set all choices */
      }
    }
  }
  /* limit grid element choices by existing values */
  for (i = 0; i < DIM; i++) {                          /* access */
    for (j = 0; j < DIM; j++){                         /* every element */
      n = grid_read_value(*g, i, j);                   /* get value */
      if (n != 0) {                                    /* if filled */
        grid_clear_count(g, i, j);                     /* clear count */
        for (n = 1; n < DIM + 1; n++) {
          grid_clear_choice(g, i, j, n);               /* clear all choices */
        }
        continue;
      }
      assert(n == 0);     /* here n must be 0 */
      for (k = 0; k < DIM; k++) {
        n = grid_read_value(*g, i, k);         /* read in row */
        grid_remove_choice(g, i, j, n);        /* remove existing */
        n = grid_read_value(*g, k, j);         /* read in colunm */
        grid_remove_choice(g, i, j, n);        /* remove existing */
      }
      /* compute sub-grid */
  		for (k = (i/SUBDIM)*SUBDIM; k < (i/SUBDIM)*SUBDIM+SUBDIM; k++) {
  			for (l = (j/SUBDIM)*SUBDIM; l < (j/SUBDIM)*SUBDIM+SUBDIM; l++) {
          n = grid_read_value(*g, k, l);       /* read in sub-grid */
          grid_remove_choice(g, i, j, n);      /* remove existing */
        }
      }
    }
  }
  return;
}

static int sudoku_exclusive_method(Grid_T g, int i, int j, int n){
  int k, l;
  int flag = FALSE;
  /* compute sub-grid */
  if (grid_choice_is_valid(g, i, j, n)) {
    flag = TRUE;
    for (k = (i/SUBDIM)*SUBDIM; k < (i/SUBDIM)*SUBDIM+SUBDIM; k++) {
      for (l = (j/SUBDIM)*SUBDIM; l < (j/SUBDIM)*SUBDIM+SUBDIM; l++) {
        /* check sub-grid */
        if (((k != i) ^ (l != j)) && grid_choice_is_valid(g, k, l, n))
          flag = FALSE;
      }
    }
  }
  return flag;
}

/*
 * returns true if grid defined by g has errors and false otherwise
 * prints all errors only if argument print is true
 */
static int sudoku_has_errors(Grid_T g, int print){
  int i, j, k, l, n;
  int has_errors = FALSE;
  for (i = 0; i < DIM; i++) {                          /* access */
    for (j = 0; j < DIM; j++){                         /* every element */
      n = grid_read_value(g, i, j);                    /* get value */
      if (n == 0) {                                    /* blank */
        continue;
      }
      for (k = 0; k < DIM; k++) {
        if (k != j && n == grid_read_value(g, i, k)) { /* check row */
          has_errors = TRUE;
          if (print)
            fprintf(stderr, "conflict (row) of value %d in elements \
[%d,%d] - [%d,%d]\n",
                    n, i, j, i, k);
        }
        if (k != i && n == grid_read_value(g, k, j)) { /* check column */
          has_errors = TRUE;
          if (print)
            fprintf(stderr, "conflict (column) of value %d in elements \
[%d,%d] - [%d,%d]\n",
                    n, i, j, k, j);
        }
      }
      /* compute sub-grid */
  		for (k = (i/SUBDIM)*SUBDIM; k < (i/SUBDIM)*SUBDIM+SUBDIM; k++) {
  			for (l = (j/SUBDIM)*SUBDIM; l < (j/SUBDIM)*SUBDIM+SUBDIM; l++) {
          /* check sub-grid */
          if (((k != i) ^ (l != j)) && n == grid_read_value(g, k, l)) {
            has_errors = TRUE;
            if (print)
              fprintf(stderr, "conflict (sub-grid) of value %d in elements \
[%d,%d] - [%d,%d]\n",
                      n, i, j, k, l);
          }
        }
  		}
    }
  }
  return (has_errors);
}

/*
 * returns true if grid defined by g has blanks and false otherwise
 */
static int sudoku_count_blanks(Grid_T g){
  int i, j, n;
  int has_blanks = FALSE;
  for (i = 0; i < DIM; i++) {                          /* access */
    for (j = 0; j < DIM; j++){                         /* every element */
      n = grid_read_value(g, i, j);                    /* get value */
      if (n == 0)                                      /* blank */
        has_blanks++;
    }
  }
  return (has_blanks);
}

/*
 * searches for a unique choice and returns one if exists
 * otherwise returns another good choice
 * returns false when puzzle is complete
 */
static int sudoku_try_next(Grid_T g, int *row, int *col){
  int i, j, k, n;
  int nchoice = 1;                      /* number of choices wanted */
  while (nchoice < DIM + 1) {
    for (i = 0; i < DIM; i++) {                          /* access */
      for (j = 0; j < DIM; j++){                         /* every element */
        /* n = grid_read_value(g, i, j); */                    /* get value */
        /* if (n != 0) */                                      /* is filled */
          /* continue; */
        /* assert(n == 0); */                                  /* empty */
        n = grid_read_count(g, i, j);
        if (n == 0)
          continue;
        if (n == nchoice) {
          for (k = 1; k < DIM + 1; k++) {
            if (grid_choice_is_valid(g, i, j, k)) {
              *row = i;
              *col = j;
              return k;
            }
          }
        }
/* 
        for (k = 1; k < DIM + 1; k++) {
          if (sudoku_exclusive_method(g, i, j, k)) {
            *row = i;
            *col = j;
            return k;
          }
        }
 */
      }
    }
    nchoice++;                /* not unique choice */
  }
  return FALSE;
}

/*
 * searches for a unique choice and returns one if exists
 * otherwise returns another good choice
 * returns false when puzzle is complete
 */
static int sudoku_try_next_rand(Grid_T g, int *row, int *col){
  int i, j, k, n;
  int nchoice = DIM + 1;                      /* max number of choices  */
  for (i = 0; i < DIM; i++) {                          /* access */
    for (j = 0; j < DIM; j++){                         /* every element */
      n = grid_read_count(g, i, j);
      if (n > 0 && n < nchoice)       /* if there is elt with less choices */
        nchoice = n;
    }
  }
  while (nchoice < DIM + 1) {
    i = rand()%DIM;
    j = rand()%DIM;
    n = grid_read_count(g, i, j);
    if (n == nchoice) {
      while (TRUE) {
        k = rand()%DIM + 1;
        if (grid_choice_is_valid(g, i, j, k)) {
          *row = i;
          *col = j;
          return k;
        }
      }
    }
  }
  return FALSE;
}

/*
 * removes from element i,j the choice n and
 * returns the number of choices for the element before the removal
 */
static int sudoku_remove_choice(Grid_T *g, int i, int j, int n){
  int nchoice;
  nchoice = grid_read_count(*g, i, j);
  grid_remove_choice(g, i, j, n);
  return nchoice;
}

/*
 * applies the choice n to the element i,j 
 */
static void sudoku_apply_choice(Grid_T *g, int i, int j, int n){
  grid_update_value(g, i, j, n);
  return;
}

/*
 * removes from row r, column c and relevant sub-grid the choice n
 */
static void sudoku_eliminate_choice(Grid_T *g, int r, int c, int n){
  int k, l;
  for (k = 0; k < DIM; k++) {
    grid_remove_choice(g, r, k, n);        /* remove from row */
    grid_remove_choice(g, k, c, n);        /* remove from column */
  }
  /* compute sub-grid */
  for (k = (r/SUBDIM)*SUBDIM; k < (r/SUBDIM)*SUBDIM+SUBDIM; k++) {
    for (l = (c/SUBDIM)*SUBDIM; l < (c/SUBDIM)*SUBDIM+SUBDIM; l++) {
      grid_remove_choice(g, k, l, n);      /* remove from sub-grid */
    }
  }
  return;
}

/*
 * returns a complete grid using the sudoku_try_next() function
 */
static Grid_T sudoku_generate_complete(void){
  Grid_T new_g;
  int i, j, n, stop;
  int ready_puzzle[CELLS] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 
                              4, 5, 6, 7, 8, 9, 1, 2, 3, 
                              7, 8, 9, 1, 2, 3, 4, 5, 6, 
                              2, 3, 4, 5, 6, 7, 8, 9, 1, 
                              5, 6, 7, 8, 9, 1, 2, 3, 4, 
                              8, 9, 1, 2, 3, 4, 5, 6, 7, 
                              3, 4, 5, 6, 7, 8, 9, 1, 2, 
                              6, 7, 8, 9, 1, 2, 3, 4, 5, 
                              9, 1, 2, 3, 4, 5, 6, 7, 8 };
  stop = DIM + 1;
  while ((stop--) != 0) {               /* not guarranteed so limit tries */
    for (i = 0; i < DIM; i++) {                          /* access */
      for (j = 0; j < DIM; j++){                         /* every element */
        grid_update_value(&new_g, i, j, 0);              /* init zero */
      }
    }
    sudoku_init_choices(&new_g);
    while ((n = sudoku_try_next_rand(new_g, &i, &j))) {
      sudoku_remove_choice(&new_g, i, j, n);
      sudoku_apply_choice(&new_g, i, j, n);
      sudoku_eliminate_choice(&new_g, i, j, n);
    }
    if (sudoku_is_correct(new_g))
      return new_g;
  }
  n = 0;
  for (i = 0; i < DIM; i++) {                          /* access */
    for (j = 0; j < DIM; j++){                         /* every element */
      grid_update_value(&new_g, i, j, ready_puzzle[n++]);/* init ready */
    }
  }
  sudoku_init_choices(&new_g);
  return new_g;
}
 
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
Grid_T sudoku_read(void){
  Grid_T g;
  char str[2];
  int n;
  int count = 0;
  int i = 0, j = 0;
  str[1] = '\0';
  while ((str[0] = getchar()) != EOF) {
    if (str[0] == '\n') {             /* if newline */
      i++;                            /* next row */
      j = 0;                          /* beginning */
      continue;                       /* next loop */
    }
    if (isdigit((int)str[0])) {       /* if number */
      n = atoi(str);                  /* string to integer */
      if (n < 0 || n > DIM) {         /* check int range */
        fprintf(stderr, "wrong input\n");
        exit(EXIT_FAILURE);
      }
      grid_update_value(&g, i, j, n);  /* save value */
      j++;                            /* increment column */
      count++;                        /* increment count */
    } else if (str[0] != ' ') {       /* check if not space */
      fprintf(stderr, "wrong input\n");
      exit(EXIT_FAILURE);
    }
  }
  if (count != CELLS) {               /* check total inputs */
    fprintf(stderr, "wrong input\n");
    exit(EXIT_FAILURE);
  }
  return g;
}

/*
 * print the sudoku puzzle defined by g to stream s in the same format
 * as expected by sudoku_read()
 */
void sudoku_print(FILE *s, Grid_T g){
  int i, j;
  for (i = 0; i < DIM; i++) {
    for (j = 0; j < DIM; j++){
      fprintf(s, "%d ", grid_read_value(g, i, j));
    }
    fprintf(s, "\n");
  }
  return;
}

/*
 * print all row, col, sub-grid errors/conflicts found in puzzle g
 * some errors may be reported more than once
 */
void sudoku_print_errors(Grid_T g){
  sudoku_has_errors(g, TRUE);
  return;
}

/*
 * return true iff puzzle g is correct
 */
int sudoku_is_correct(Grid_T g){
  return (!sudoku_has_errors(g, FALSE) && !sudoku_count_blanks(g));
}

/* int glbcnt = 0; */

/*
 * sovle puzzle g and return the solved puzzle
 * if the puzzle has multiple solutions return one of the possible solutions
 */
Grid_T sudoku_solve(Grid_T g){
  Grid_T tmp_g, sol;
  int i, j;
  int n;
  int nchoice;
  while ((n = sudoku_try_next_rand(g, &i, &j))) { /* probl */
    nchoice = sudoku_remove_choice(&g, i, j, n);
    if (nchoice == 1) {
      sudoku_apply_choice(&g, i, j, n);
      sudoku_eliminate_choice(&g, i, j, n);
    } else {
      grid_clear_unique(&g);
      tmp_g = g;
      sudoku_apply_choice(&tmp_g, i, j, n);
      /* sudoku_eliminate_choice(&tmp_g, i, j, n); */
      /* printf("[backtracking] lvl: %d\n", ++glbcnt); */
      sol = sudoku_solve(tmp_g);
      if (sudoku_is_correct(sol))
        return sol;
    }
  }
  return g;
}

/*
 * returns true if solution g as returned by sudoku_solve has a
 * unique choice for each step (no backtracking required)
 * note: g must have been computed with the use of sudoku_solve()
 */
int sudoku_solution_is_unique(Grid_T g){
  return (grid_read_unique(g));
}

/*
 * generate and return a sudoku puzzle with "approximately" nelts
 * elements having non-0 value
 * the smaller nelts the harder may be to generate/solve the puzzle
 * for instance nelts=81 should return a completed and correct puzzle
 * if unique=1 the puzzle must have a unique choice at each step of 
 * finding the solution
 */
Grid_T sudoku_generate(int nelts, int unique){
  Grid_T new_g, tmp_g;
  int i, j, remain;
  remain = CELLS;
  new_g = sudoku_generate_complete();
  while (remain != nelts) {
    i = rand()%DIM;
    j = rand()%DIM;
    if (grid_read_value(new_g, i, j) == 0)
      continue;
    grid_update_value(&tmp_g, i, j, 0);     /* set random cell to zero */
    sudoku_init_choices(&tmp_g);
    if (unique) {
      if (sudoku_solution_is_unique(sudoku_solve(tmp_g)))
        sudoku_init_choices(&new_g);
        grid_update_value(&new_g, i, j, 0);
        remain--;
    } else {
      sudoku_init_choices(&new_g);
      grid_update_value(&new_g, i, j, 0);
      remain--;
    }
  }
  return new_g;
}

int main(int argc, char **argv){
  Grid_T init, final;
  int n, number;
  srand(getpid());
  switch (argc) {
    case 1:         /* sudoku */
      init = sudoku_read();
      sudoku_print(stderr, init);
      sudoku_init_choices(&init);
      final = sudoku_solve(init);
      if (sudoku_is_correct(final)) {
        if (sudoku_solution_is_unique(final))
          fprintf(stderr, "puzzle has a unique solution:\n");
        else
          fprintf(stderr, "puzzle has a solution:\n");
      } else {
        fprintf(stderr, "puzzle does not have solution:\n");
      }
      sudoku_print(stdout, final);
      sudoku_print_errors(final);
      break;
    case 2:         /* check solution */
      if (argv[1][0] == '-' && 
          argv[1][1] == 'c' && 
          argv[1][2] == '\0') {
        init = sudoku_read();
        sudoku_print(stderr, init);
        if (sudoku_is_correct(init))
            fprintf(stderr, "puzzle solution is correct.\n");
        else
          fprintf(stderr, "puzzle solution is not correct.\n");
        sudoku_print_errors(init);
      }
      break;
    case 4:         /* generate puzzle */
      if (argv[3][0] == '-' && 
          argv[3][1] == 'u' && 
          argv[3][2] == '\0')
        ;
      else
        break;
    case 3:
      if (argv[1][0] == '-' && 
          argv[1][1] == 'g' && 
          argv[1][2] == '\0') {
        n = 0;
        number = TRUE;
        while (argv[2][n] != '\0')
          if (!isdigit((int)argv[2][n++])) {
            number = FALSE;
        }
        if (number) {
          n = atoi(argv[2]);
          if (argc == 4)
            init = sudoku_generate(n, TRUE);
          else
            init = sudoku_generate(n, FALSE);
          sudoku_print(stdout, init);
        }
      }
      break;
    default:
      fprintf(stderr,
"wrong number of arguments\n\
available options:\n\
sudoku [-c] / [-g nelts [-u]]\n");
  }
  
  return 0;
}
