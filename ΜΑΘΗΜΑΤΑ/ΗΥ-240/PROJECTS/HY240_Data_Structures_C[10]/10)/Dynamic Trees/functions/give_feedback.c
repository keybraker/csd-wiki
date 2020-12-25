/**********************************************************************
 * @file   give_feedback.c                                            *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>                      *
 *                                                                    *
 * @brief  Gives satisfaction value to children                       *
 *                                                                    *σ
 * for the needs of the Data Structures project by Ioannis Tsiakkas   *
 * Computer Science Department, University of Crete, Greece           *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int give_feedback(int cid, int did, int s_degree) {
    
    struct district* DistrictsLR = DistrictsL;
    
    if (DistrictsLR == NULL) { printf("Districts list is empty\n"); return 1; }
    
    while (DistrictsLR->did != did) { //printf(" . ");
        DistrictsLR = DistrictsLR->next;
    }
    
    int i=0;
    while (i < DistrictsLR->children_cnt) {
        
        if (DistrictsLR->assignHT[i].cid == cid) {
            
            if (DistrictsLR->assignHT[i].pid == -2) {
                DistrictsLR->assignHT[i].s_degree = 1;
            }else{
                DistrictsLR->assignHT[i].s_degree = s_degree;
            }
            printf("F <%d>, <%d>, <%d>\n\nDONE\n\n",DistrictsLR->assignHT[i].cid,DistrictsLR->assignHT[i].s_degree,DistrictsLR->assignHT[i].pid);

        }
        
        i++;
    
    }

    return 1;
}
