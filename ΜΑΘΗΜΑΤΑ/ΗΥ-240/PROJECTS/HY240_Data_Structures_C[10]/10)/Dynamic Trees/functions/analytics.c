/**********************************************************************
 * @file   analytics.c                                                *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>                      *
 *                                                                    *
 * @brief  Sorts presents list by request_cnt and than prints all     *
 *         presents in order                                          *
 * for the needs of the Data Structures project by Ioannis Tsiakkas   *
 * Computer Science Department, University of Crete, Greece           *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int i_uni = 0;
struct present ZERO_STRUCT_PRESENT = { 0, 0, 0, NULL, NULL, NULL};

struct HeapTable{

    int k;
    struct present* data;

};

void print_analytics(struct present* analytics_array, int k){
    
    int i = 0;
    while (i < k) {
        
        printf("<%d> : <%d>\n",analytics_array[i].pid,analytics_array[i].request_cnt);
        i++;
        
        //printf("%d) analytics_array[%d] = %p | analytics_array[i].pid = %d | analytics_array[i].request_cnt = %d\n",i+1,i,&analytics_array[i],analytics_array[i].pid,analytics_array[i].request_cnt);
        //printf("%d) analytics_array[%d].lc = %p\n",i+1,i,&analytics_array[i].lc);
        //printf("%d) analytics_array[%d].rc = %p\n",i+1,i,&analytics_array[i].rc);
        
    }
    return;
    
}

void initialization(struct present* analytics_array, struct present* PresentR, int k){
    
    if (PresentR == stock_sentinel) { return; }

    initialization(analytics_array,PresentR->lc, k);
    
    if (i_uni == k) { return; }
    analytics_array[i_uni] = *PresentR;
    i_uni++;

    initialization(analytics_array,PresentR->rc, k);
    
}

int present_cnt(struct present* PresentR){
    
    if (PresentR == stock_sentinel) { return 0; }

    int right = present_cnt(PresentR->lc);
    int left = present_cnt(PresentR->rc);
    
    return (right+left+1);

}

void heapInsert(struct present* analytics_array,int index, struct present insert, int k){
    
    if (index > k || index < 0 || k == 0) { return; }
    
    analytics_array[index] = insert;
    
}

void heapDelete(struct present* analytics_array,int index, int k){
    
    if (index > k || index < 0 || k == 0) { return; }
    
    analytics_array[index] = ZERO_STRUCT_PRESENT;
    
}

void heapify(struct present* analytics_array, int k){ //printf("heapify\n");
    
    if (k == 0 || k == 1) { return; }
    
    struct present tmp;
    
    int i = k-1,j = 0;
    //printf("i = %d\n\n",i);

    while (0 < i) {
        
        if ( analytics_array[i].request_cnt > analytics_array[i-1].request_cnt ){
            //printf("\nS1) analytics_array[%d].request_cnt [ %d > %d ] analytics_array[%d].request_cnt\n",i,analytics_array[i].request_cnt,i-1,analytics_array[i-1].request_cnt);
            
            tmp = analytics_array[i];
            
            heapDelete(analytics_array, i, k);
            heapInsert(analytics_array, i, analytics_array[i-1], k);
            heapDelete(analytics_array, i-1, k);
            heapInsert(analytics_array, i-1, tmp, k);

            //tmp = analytics_array[i];
            //analytics_array[i] = analytics_array[i-1];
            //analytics_array[i-1] = tmp;
            
            j = i;
            while (j < k-1) {
                if ( analytics_array[j].request_cnt < analytics_array[j+1].request_cnt ){
                    //printf("\nS2) analytics_array[%d].request_cnt [ %d < %d ] analytics_array[%d].request_cnt\n",j,analytics_array[j].request_cnt,j-1,analytics_array[j-1].request_cnt);

                    tmp = analytics_array[j];
                    
                    heapDelete(analytics_array, j, k);
                    heapInsert(analytics_array, j, analytics_array[j+1], k);
                    heapDelete(analytics_array, j+1, k);
                    heapInsert(analytics_array, j+1, tmp, k);
                    
                    //tmp = analytics_array[j];
                    //analytics_array[j] = analytics_array[j+1];
                    //analytics_array[j+1] = tmp;
                    
                }
                j++;
            }
        }
        i--;
    }
    
}

void heapFunction(struct present* analytics_array, struct present* PresentR, int k){
    
    if (PresentR == stock_sentinel) { return; }
    
    heapFunction(analytics_array, PresentR->lc, k);
    
    struct present tmp,inserter;
    int i = k-1;
    //printf("\n/-------------------------------PresentR->pid = %d-------------------------------/\n\n",PresentR->pid);
    
    if (k == 1) {
        
        if (analytics_array[0].pid == PresentR->pid) {
            //printf("EQUALS: analytics_array[%d].r_cnt = %d == %d = PresentR.r_cnt \n",0,analytics_array[i].request_cnt, PresentR->request_cnt);
            return;
        }
        //printf("analytics_array[0].pid = [%d].r_cnt = %d < PresentR->r_cnt = %d\n",analytics_array[0].pid,analytics_array[0].request_cnt,PresentR->request_cnt);

        if (analytics_array[0].request_cnt < PresentR->request_cnt) {
            //printf(" ^ mpainei mesa giati einai megalutero apo to analytics_array[%d].r_cnt\n",0);
            
            heapDelete(analytics_array, 0, k);
            heapInsert(analytics_array, 0, *PresentR, k);
            
        }
        
    }else{
    
        while (0 < i) { //printf("i = %d\n",i);
            
            if (analytics_array[i].pid == PresentR->pid) {
                //printf("EQUALS: analytics_array[%d].r_cnt = %d == %d = PresentR.r_cnt \n",i,analytics_array[i].request_cnt, PresentR->request_cnt);
                break;
            }
            
            //printf("analytics_array[%d].r_cnt = [ %d < %d ] = PresentR.r_cnt \n",i,analytics_array[i].request_cnt, PresentR->request_cnt);
            if (analytics_array[i].request_cnt < PresentR->request_cnt) {
                //printf(" ^ mpainei mesa giati einai megalutero apo to analytics_array[%d].r_cnt\n",i);
                
                if (analytics_array[i-1].pid == PresentR->pid) {
                    //printf("EQUALS: analytics_array[%d].r_cnt = %d == %d = PresentR.r_cnt \n",i,analytics_array[i].request_cnt, PresentR->request_cnt);
                    break;
                }
                
                if (i == 0) {
                    //printf("mpainei sti proti 8esi\n");/* ΜΠΑΙΝΩ // while // break; */
                    inserter = *PresentR;
                    while (i < k ){
                        
                        tmp = analytics_array[i];
                        heapDelete(analytics_array, i, k);
                        heapInsert(analytics_array, i, inserter, k);
                        inserter = tmp;
                        
                        i++;
                        
                    }
                    break;
                }
                //printf(" analytics_array[%d].request_cnt %d>=%d PresentR->request_cnt\n",i-1,analytics_array[i-1].request_cnt,PresentR->request_cnt);
                if (analytics_array[i-1].request_cnt >= PresentR->request_cnt) {
                    //printf(" meta8etei oles tis 8eseis apo edo kai piso epeidi einai mikrotero apo to analytics_array[%d].r_cnt\n",i-1);
                    inserter = *PresentR;
                    while (i < k ){
                        //printf("while -> ");
                        
                        tmp = analytics_array[i];
                        heapDelete(analytics_array, i, k);
                        heapInsert(analytics_array, i, inserter, k);
                        inserter = tmp;
                        
                        i++;
                        
                    }//printf("\n");
                }
                if (i-1 == 0) {
                    i=0;//printf("i = %d\n",i);
                    //printf("inserter = %d\n",inserter.pid);
                    
                    inserter = *PresentR;
                    //printf("inserter = %d\n",inserter.pid);
                    
                    while (i < k ){
                        //printf("while -> ");
                        
                        tmp = analytics_array[i];
                        heapDelete(analytics_array, i, k);
                        heapInsert(analytics_array, i, inserter, k);
                        inserter = tmp;
                        
                        i++;
                        
                    }
                    //printf("TELOS MPAINEI PROTO\n");
                    break;
                }
                //printf(" <-- proxora\n");
            }
            
            i-=1;
            
        }
        
    }
    
    heapFunction(analytics_array, PresentR->rc, k);

}

int analytics(int k) {
    
    if (k < 0) { k = 0; }
    
    struct present* analytics_array = (struct present*)malloc(k * sizeof(struct present*));
    
    int p_cnt = present_cnt(stock_tree);
    if (k > p_cnt) { k = p_cnt; }
    //printf("initialization for %d\n",k);
    i_uni = 0;
    initialization(analytics_array, stock_tree, k);
    //printf("heapify\n");
    heapify(analytics_array,k);
    //printf("heapFunction\n");
    heapFunction(analytics_array, stock_tree, k);
    
    printf("A\n\n");
    print_analytics(analytics_array, k);
    printf("\nDONE\n\n");

    return 1;

}

