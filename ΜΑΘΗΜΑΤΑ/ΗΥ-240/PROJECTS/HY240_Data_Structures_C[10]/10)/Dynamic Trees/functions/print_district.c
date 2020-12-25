/**********************************************************************
 * @file   print_district.c                                           *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>                      *
 *                                                                    *
 * @brief  Prints all districts list                                  *
 *                                                                    * 
 * for the needs of the Data Structures project by Ioannis Tsiakkas   *
 * Computer Science Department, University of Crete, Greece           *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int print_district(void) {
    
    struct district* DistrictsLR = DistrictsL;
    
    int k = 0, dis_cnt = 0;
    
    printf("I\n\n    DISTRICT:\n");
    while (DistrictsLR != NULL) {

        printf("\n\n    <%d>\n       ASSIGNMENT: ",DistrictsLR->did);

        if (DistrictsLR == NULL) { return 1;}
        
        if (DistrictsLR->assignHT != NULL) {

            dis_cnt = 0;
            k=0;
            while (k < DistrictsLR->children_cnt) {
                
                if (dis_cnt == 6) { printf("\n                   ");dis_cnt=0; }
                printf("<%d:%d:%d>, ",DistrictsLR->assignHT[k].cid,DistrictsLR->assignHT[k].pid,DistrictsLR->assignHT[k].s_degree);
                k++;
                dis_cnt++;
                
            }
        }
        dis_cnt=0;
        DistrictsLR = DistrictsLR->next;
    }
    printf("\n\nDONE\n\n");
    
    return 1;
}