/**********************************************************************
 * @file   search_present.c                                           *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>                      *
 *                                                                    *
 * @brief  Searches for present in presents list                      *
 *                                                                    * 
 * for the needs of the Data Structures project by Ioannis Tsiakkas   *
 * Computer Science Department, University of Crete, Greece           *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int search_pid(struct present* R,int pid){
    
    if ( R == NULL) { return 0 ; }
    if ( R == stock_sentinel) { return 0 ; }
    
    int one = search_pid(R->lc, pid);
    
    if (R->pid == pid) {
        
        printf("S <%d>\n\n",pid);
        printf("    <%d>, <%d>",R->stock_cnt,R->request_cnt);
        printf("\n\nDONE\n\n");
        return 1 ;
        
    }
    
    int two = search_pid(R->rc, pid);

    return (one+two);
}



int search_present(int pid) {
    
    if (search_pid(stock_tree, pid) == 0) {
        printf("\nS <%d>\n\n",pid);
        printf("    DIDN'T FIND PRESENT.");
        printf("\n\nDONE\n\n");
    }
    
    return 1;
    
}