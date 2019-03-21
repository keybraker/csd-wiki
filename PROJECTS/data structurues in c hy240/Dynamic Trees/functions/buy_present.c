/**********************************************************************
 * @file   buy_present.c                                              *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>                      *
 *                                                                    *
 * @brief  Creates a tree of Presents                                 *
 *                                                                    *
 * for the needs of the Data Structures project by Ioannis Tsiakkas   *
 * Computer Science Department, University of Crete, Greece           *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int i=0, until_eight = 0;

struct present *stock_tree = NULL;
struct present *stock_sentinel = NULL;

void printPresentsTree(struct present* R){
    
    if ( R != NULL) {
        if (R != stock_sentinel) {
            
            printPresentsTree(R->lc);
            printPresentsTree(R->rc);
            
            if (until_eight == 8) {
                printf("\n              ");
                until_eight=0;
            }
            printf("<%d:%d>, ",R->pid,R->stock_cnt);
            until_eight++;
        }
    }
    
}

void left_all(struct present* R, int pid, int stock_cnt){
    if (i % 2 == 0) {
        R = R->rc;
    }
    while ( R->lc != stock_sentinel ){
        R = R->lc;
    }
    //printf(" ΒΑΖΩ ΤΟ <%d> ΑΡΙΣΤΕΡΟ ΠΑΙΔΙ ΤΟΥ <%d>\n",pid,R->pid);
    struct present* newPresent = (struct present *)malloc(sizeof(struct present));
    
    newPresent->pid = pid;
    newPresent->stock_cnt = stock_cnt;
    newPresent->request_cnt = 0; // giving 0 just in case
    newPresent->parent = R; // set father
    
    newPresent->rc = stock_sentinel; // rc of first leaf is sentinel
    newPresent->lc = stock_sentinel; // lc of first leaf is sentinel
    
    R->lc = newPresent;
    
    return;
    
}

void insertInTree(struct present* R, int pid, int stock_cnt){
    
    if (R->lc != stock_sentinel && R->rc != stock_sentinel) {
        
        if (R->lc->pid > R->rc->pid) { //printf(" <%d> > <%d> ->",R->lc->pid,R->rc->pid);
            if (pid > R->lc->pid) { //printf(" ΠΑΩ ΑΡΙΣΤΕΡΑ ΤΟΥ <%d> ΣΤΟ <%d>  ->",R->pid,R->lc->pid);
                insertInTree(R->lc, pid, stock_cnt);
            }else if (pid > R->rc->pid) { //printf(" ΠΑΩ ΔΕΞΙΑ ΤΟΥ <%d> ΣΤΟ <%d> ->",R->pid,R->rc->pid);
                insertInTree(R->rc, pid, stock_cnt);
            }else{ //printf(" ΤΣΕΚΑΡΩ ->");
                if (R->pid > R->rc->pid) {//printf(" ΠΑΩ ΔΕΞΙΑ ΤΟΥ <%d> ΣΤΟ <%d> ->",R->pid,R->rc->pid);
                    insertInTree(R->rc, pid, stock_cnt);
                }else{ //printf(" ΠΑΩ ΔΕΞΙΑ ΚΑΙ ΤΕΡΜΑ ΑΡΙΣΤΕΡΑ ΤΟΥ <%d> ->",R->pid);
                    left_all(R,pid,stock_cnt);
                    return;
                }
            }
        }else{ //printf(" <%d> > <%d> ->",R->lc->pid,R->rc->pid);
            if (pid > R->rc->pid) { //printf(" ΠΑΩ ΔΕΞΙΑ ΤΟΥ <%d> ΣΤΟ <%d> ->",R->pid,R->rc->pid);
                insertInTree(R->rc, pid, stock_cnt);
            }else if (pid > R->lc->pid) { //printf(" ΠΑΩ ΑΡΙΣΤΕΡΑ ΤΟΥ <%d> ΣΤΟ <%d>  ->",R->pid,R->lc->pid);
                insertInTree(R->lc, pid, stock_cnt);
            }else{ //printf(" ΤΣΕΚΑΡΩ ->");
                if (R->pid > R->lc->pid) {//printf(" ΠΑΩ ΑΡΙΣΤΕΡΑ ΤΟΥ <%d> ΣΤΟ <%d>  ->",R->pid,R->lc->pid);
                    insertInTree(R->lc, pid, stock_cnt);
                }else{ //printf(" ΠΑΩ ΚΑΤΕΥΘΕΙΑΝ ΤΕΡΜΑ ΑΡΙΣΤΕΡΑ ΤΟΥ <%d> ->",R->pid);
                    left_all(R,pid,stock_cnt);
                    return;
                }
            }
        }
        
    }else if (R->lc == stock_sentinel && R->rc == stock_sentinel) { //printf(" ΟΠΟΥ ΘΕΛΩ, ΑΛΛΑ ΒΑΖΩ ΤΟ <%d> ΑΡΙΣΤΕΡΟ ΠΑΙΔΙ ΤΟΥ <%d>\n",pid,R->pid);
        
        struct present* newPresent = (struct present *)malloc(sizeof(struct present));
        
        newPresent->pid = pid;
        newPresent->stock_cnt = stock_cnt;
        newPresent->request_cnt = 0; // giving 0 just in case
        newPresent->parent = R; // set father
        
        newPresent->rc = stock_sentinel; // rc of first leaf is sentinel
        newPresent->lc = stock_sentinel; // lc of first leaf is sentinel
        
        R->lc = newPresent;
        
        return;
        
    }else if (R->lc != stock_sentinel){ //printf(" ΜΟΝΟ ΤΟ lc ΥΠΑΡΧΕΙ ->");
        
        if (R->lc->pid < pid && R->lc->pid > R->pid) { //printf(" ΠΑΩ ΑΡΙΣΤΕΡΑ ΤΟΥ <%d> ΣΤΟ <%d> ->",R->pid,R->lc->pid);
            insertInTree(R->lc, pid, stock_cnt);
        }else{ //printf(" ΒΑΖΩ ΤΟ <%d> ΔΕΞΙ ΠΑΙΔΙ ΤΟΥ <%d>\n",pid,R->pid);

            struct present* newPresent = (struct present *)malloc(sizeof(struct present));
            
            newPresent->pid = pid;
            newPresent->stock_cnt = stock_cnt;
            newPresent->request_cnt = 0; // giving 0 just in case
            newPresent->parent = R; // set father
            
            newPresent->rc = stock_sentinel; // rc of first leaf is sentinel
            newPresent->lc = stock_sentinel; // lc of first leaf is sentinel
            
            R->rc = newPresent;
            
            return;
        }
        
    }else if (R->rc != stock_sentinel){ //printf(" ΜΟΝΟ ΤΟ rc ΥΠΑΡΧΕΙ ->");
        
        if (R->rc->pid < pid  && R->rc->pid > R->pid) { //printf(" ΠΑΩ ΔΕΞΙΑ ΤΟΥ <%d> ΣΤΟ <%d> ->",R->pid,R->lc->pid);
            insertInTree(R->rc, pid, stock_cnt);
        }else{ //printf(" ΒΑΖΩ ΤΟ <%d> ΑΡΙΣΤΕΡΟ ΠΑΙΔΙ ΤΟΥ <%d>\n",pid,R->pid);
            
            struct present* newPresent = (struct present *)malloc(sizeof(struct present));
            
            newPresent->pid = pid;
            newPresent->stock_cnt = stock_cnt;
            newPresent->request_cnt = 0; // giving 0 just in case
            newPresent->parent = R; // set father
            
            newPresent->rc = stock_sentinel; // rc of first leaf is sentinel
            newPresent->lc = stock_sentinel; // lc of first leaf is sentinel
            
            R->rc = newPresent;
            
            return;
        }

        
    }
    
}

int buy_present(int pid, int stock_cnt) {   i++;    // printf("keepo\n\n\n");
    
    if (stock_tree == NULL) { // If there are no presents the first one is created
        //printf("----> ΤΟ <%d> ΜΠΑΙΝΕΙ ΩΣ ΡΙΖΑ\n",pid);
        struct present* newSentinel = (struct present *)malloc(sizeof(struct present));
        struct present* newPresent = (struct present *)malloc(sizeof(struct present));
        
        newSentinel->pid = -1;
        newSentinel->stock_cnt = -1;
        newSentinel->request_cnt = -1;
        newSentinel->parent = newPresent; // sentinels father points at root
        
        newSentinel->rc = NULL; // rc of sentinel leaf is NULL
        newSentinel->lc = NULL; // lc of sentinel leaf is NULL
        
        newPresent->pid = pid;
        newPresent->stock_cnt = stock_cnt;
        newPresent->request_cnt = 0; // giving 0 just in case
        newPresent->parent = NULL; // has NULL as father because its first in tree
        
        newPresent->rc = newSentinel; // rc of first leaf is sentinel
        newPresent->lc = newSentinel; // lc of first leaf is sentinel
        
        stock_tree = newPresent; // points at head of tree
        stock_sentinel = newSentinel; // points at sentinel of tree which is end of tree
        
        
    }else{ // If presents already exist in list,
           // pushes current present to the end of the list
        //printf("---->");
        insertInTree(stock_tree, pid, stock_cnt);
        
    }
    
    printf("B <%d> <%d>\n\n   Presents = ",pid,stock_cnt);until_eight=0;
    printPresentsTree(stock_tree);
    printf("\n\n");
    
    return 1;
}