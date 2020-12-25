/**********************************************************************
 * @file   clear_list_of_children.c                                   *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>                      *
 *                                                                    *
 * @brief  Clears all children with present_choices[3] == {0,0,0}     *
 *                                                                    * 
 * for the needs of the Data Structures project by Ioannis Tsiakkas   *
 * Computer Science Department, University of Crete, Greece           *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int ce = 0;

void printChildTreeCid(struct child* R){ 
    
    if ( R == NULL ) { return; }

    printChildTreeCid(R->lc);
    printChildTreeCid(R->rc);

    ce++;

    printf("<%d>, ",R->cid);
    if (ce == 8) { printf("\n           "); ce=0; }

}

struct child* right_left_most_three(struct child* AgeF,struct child* AgeR, int i){
    
    if (AgeR == NULL) { return NULL; }
    
    int k = 0;
    while (k == 0) {
        if (AgeR->lc == NULL && AgeR->rc == NULL) {
            if (i == 1) {
                AgeF->lc = NULL;
                return AgeR; //
            }else{
                AgeF->rc = NULL;
                return AgeR; //
            }
        }else if(AgeR->lc != NULL && AgeR->rc != NULL) {
            AgeF = AgeR;
            AgeR = AgeR->lc;
            i=1;
        }else if(AgeR->rc != NULL) {
            if (i == 1) {
                AgeF->lc = AgeR->rc;
                return AgeR;
            }else{
                AgeF->rc = AgeR->rc;
                return AgeR;
            }
        }else if(AgeR->lc != NULL) {
            AgeF = AgeR;
            AgeR = AgeR->lc;
            i=1;
        }
    }
    printf("\n\n\nMUSTNT HAPPEN\n\n\n");
    return AgeR;
}

void deleteChild(int masterAC, struct child*  father, struct child* AgeR, int i){
    
    if ( AgeR == NULL) { return; }
    
    
    deleteChild(masterAC, AgeR, AgeR->lc, 1);
    deleteChild(masterAC, AgeR, AgeR->rc, 2);

    
    // check if left child needs deletion
    if (AgeR->present_choices[0] == -1 && AgeR->present_choices[1] == -1 && AgeR->present_choices[2] == -1) {
        
        // if both children of node that as to be deleted are NULL
        if (AgeR->lc == NULL && AgeR->rc == NULL) { //printf("\nBOTH NULL ->\n");
            
            if (i == 1) {
                father->lc = NULL;
            }else if (i == 2){
                father->rc = NULL;
            }else{ //  if (i == 0)
                Age_categories[masterAC] = NULL;
            }
        
        // if none of the childrens node that has to be deleted are NULL
        }else if (AgeR->lc != NULL && AgeR->rc != NULL) { //printf("\nBOTH !NULL -> NEEDS FIXIND -> ");
                                                                            // NEEDS FIXIND
            struct child* left_most = right_left_most_three(AgeR,AgeR->rc,0);
     
            if (left_most != NULL){
                
                if (i == 1) {
                    father->lc = left_most;
                }else if (i == 2){
                    father->rc = left_most;
                }else{ //  if (i == 0)
                    Age_categories[masterAC] = left_most;
                }
                
                left_most->lc = AgeR->lc;
                left_most->rc = AgeR->rc;
                
            }
            
        // if left child is not NULL but right is
        }else if (AgeR->lc != NULL){ //printf("\nlLC NULL ->\n");
            
            if (i == 1) {
                father->lc = AgeR->lc;
            }else if (i == 2){
                father->rc = AgeR->lc;
            }else{ //  if (i == 0)
                
                Age_categories[masterAC] = AgeR->lc;

            }
            
        // if right child is not NULL but left is
        }else if (AgeR->rc != NULL){ //printf("\nrRC NULL ->\n");
            
            if (i == 1) {
                father->lc = AgeR->rc;
            }else if (i == 2){
                father->rc = AgeR->rc;
            }else{ //  if (i == 0)
                
                Age_categories[masterAC] = AgeR->rc;

            }
            
        }

    }
   
}

int clear_list_of_children(void) {
        
    int i=0;
    for (i = 0 ; i < 4; i++) {
        
        if (Age_categories[i] != NULL) {
            deleteChild(i, NULL, Age_categories[i], 0);
        }
    }

    printf("C\n");
    for (int i = 0 ; i < 4; i++) {
        
        if(i == 0){
            printf("      0-3: ");
        }else if(i == 1){
            printf("\n      4-7: ");
        }else if(i == 2){
            printf("\n     8-11: ");
        }else if(i == 3){
            printf("\n    12-15: ");
        }
        
        if (Age_categories[i] != NULL) { printChildTreeCid(Age_categories[i]); ce=0; }
        // printChildTreeCid(Age_categories[i]);
        printf("\n");
        
    }
    printf("\nDONE\n\n");
    return 1;
}




