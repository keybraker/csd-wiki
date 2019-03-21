/**********************************************************************
 * @file   print_stock.c                                              *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>                      *
 *                                                                    *
 * @brief  Prints stock of every present                              *
 *                                                                    *
 * for the needs of the Data Structures project by Ioannis Tsiakkas   *
 * Computer Science Department, University of Crete, Greece           *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int t_cnt = 0;

void printStock(struct present* P){
    
    if (P == stock_sentinel) { return; }
    
    printStock(P->lc);
    
    t_cnt++;
    if (t_cnt == 8) { printf("\n            "); t_cnt = 0; }
    printf("<%d:%d>, ",P->pid,P->stock_cnt);

    printStock(P->rc);

}

int print_stock(void) {
    
    printf("T\n\n    Stock = ");
    
    t_cnt = 0;
    printStock(stock_tree);
    
    printf("\n\nDONE\n\n");
    
    return 1;
}