/**********************************************************************
 * @file   print_child.c                                              *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>                      *
 *                                                                    *
 * @brief  Prints all children by age                                 *
 *                                                                    * 
 * for the needs of the Data Structures project by Ioannis Tsiakkas   *
 * Computer Science Department, University of Crete, Greece           *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int child_cnt=0;

void print_age_category(struct child* AgeR){
    
    if (AgeR == NULL) { return; }
    
    print_age_category(AgeR->lc);
    print_age_category(AgeR->rc);
    
    child_cnt++;
    printf("<%d:{%d, %d, %d}>,  ",AgeR->cid,AgeR->present_choices[0], AgeR->present_choices[1], AgeR->present_choices[2]);
    if (child_cnt == 3) {
        printf("\n            ");
        child_cnt = 0;
    }
}

int print_child(void) {

    printf("H\n\n");
    int i=0;
    for (i = 0 ; i < 4; i++) {
        
        if(i == 0){
            printf("    0-3:    ");
        }else if(i == 1){
            printf("\n    4-7:    ");
        }else if(i == 2){
            printf("\n    8-11:   ");
        }else if(i == 3){
            printf("\n    12-15:  ");
        }
        
        child_cnt=0;
        print_age_category(Age_categories[i]);
        
        printf("\n");
    }
    printf("\nDONE\n\n");
    
    return 1;
}