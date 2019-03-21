/**********************************************************************
 * @file   prepare_presents.c                                         *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>                      *
 *                                                                    *
 * @brief  Gives presents to children                                 *
 *                                                                    *
 * for the needs of the Data Structures project by Ioannis Tsiakkas   *
 * Computer Science Department, University of Crete, Greece           *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

struct district* DistrictsL = NULL;
int maxCid;

int primes_g[160] = {
    5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
    41, 43, 47, 53, 59, 61, 67, 71, 73, 79,
    83, 89, 97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
    191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
    241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
    307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409, 419, 421,
    431, 433, 439, 443, 449, 457, 461, 463, 467, 479,
    487, 491, 499, 503, 509, 521, 523, 541, 547, 557,
    563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
    617, 619, 631, 641, 643, 647, 653, 659, 661, 673,
    677, 683, 691, 701, 709, 719, 727, 733, 739, 743,
    751, 757, 761, 769, 773, 787, 797, 809, 811, 821,
    823, 827, 829, 839, 853, 857, 859, 863, 877, 881,
    883, 887, 907, 911, 919, 929, 937, 941, 947, 953
};

void printPresentsTree3(struct present* R){
    
    if ( R != NULL) {
        if (R != stock_sentinel) {
            
            printPresentsTree3(R->lc);
            printPresentsTree3(R->rc);
            
            printf("<%d:%d>, ",R->pid,R->stock_cnt);
        }
    }
    
}

void PrinDistricts(){
    
    struct district* DistrictsLR = DistrictsL;
    
    int k = 0, dis_cnt = 0;
    
    printf("P\n\n    DISTRICT:\n");
    while (DistrictsLR != NULL) {
        
        printf("\n\n    <%d>\n       ASSIGNMENT: ",DistrictsLR->did);
        
        if (DistrictsLR == NULL) { return;}
        
        if (DistrictsLR->assignHT != NULL) {
            
            dis_cnt = 0;
            k=0;
            while (k < DistrictsLR->children_cnt) {
                
                if (dis_cnt == 6) { printf("\n                   ");dis_cnt=0; }
                printf("<%d:%d:%d>, ",DistrictsLR->assignHT[k].cid,
                       DistrictsLR->assignHT[k].pid,DistrictsLR->assignHT[k].s_degree);
                k++;
                dis_cnt++;
                
            }
        }
        dis_cnt=0;
        DistrictsLR = DistrictsLR->next;
    }
    printf("\n\nDONE\n\n");
    
    return;
}

int givePresent(struct present* R, int present_choices){
    
    if ( R == NULL) { return -2; }
    
    if (R->pid == present_choices) { //printf("Vrika to pid = %d",R->pid);
        
        if (R->stock_cnt > 0) { //printf("<stock: %d>\n",R->stock_cnt);
            if ( R->stock_cnt != 0 ){ R->stock_cnt--; }
            return R->pid;
        }else{ //printf(" -> den exo stock <stock: %d>\n",R->stock_cnt);
            return -2;
        }
        
    }
    
    int one = givePresent(R->lc,present_choices);
    int two = givePresent(R->rc,present_choices);
    
    if (one == present_choices || two == present_choices) {
        return present_choices;
    }
    
    //printf("\n");
    return (-2);
}



void coalesced_chaining(struct child* AgeR, struct district* DistrictR,int pid, int prev_index){
    
    int cellar = (0.14*DistrictR->children_cnt);
    if (cellar == 0) { cellar = 1; }
    
    // checks cellar if empty
    int i = 0,f = 0;
    while (i < cellar) {
        
        if (DistrictR->assignHT[i].cid == 0) {
            
            DistrictR->assignHT[i].cid = AgeR->cid;
            DistrictR->assignHT[i].s_degree = 0;
            DistrictR->assignHT[i].next = NULL;
            DistrictR->assignHT[i].pid = pid;
            
            DistrictR->assignHT[prev_index].next = &DistrictR->assignHT[i];
            
            f = 1;
            break;
        }
        
        i++;
        
    }
    if ( f == 0 ) {
        
        i = cellar;
        while (i < DistrictR->children_cnt) {
            
            if (DistrictR->assignHT[i].cid == 0) {
                
                DistrictR->assignHT[i].cid = AgeR->cid;
                DistrictR->assignHT[i].s_degree = 0;
                DistrictR->assignHT[i].next = NULL;
                DistrictR->assignHT[i].pid = pid;

                DistrictR->assignHT[prev_index].next = &DistrictR->assignHT[i];
                
                break;
            }
            
            i++;
            
        }
    }
    
}

void double_hashing(struct child* AgeR, struct district* DistrictR,int pid, int prev_index){

    int k = 0;
    while (k < DistrictR->children_cnt ) {

        if (DistrictR->assignHT[k].cid == 0) {
            
            DistrictR->assignHT[k].cid = AgeR->cid;
            DistrictR->assignHT[k].s_degree = 0;
            DistrictR->assignHT[k].next = NULL;
            DistrictR->assignHT[k].pid = pid;

            DistrictR->assignHT[prev_index].next = &DistrictR->assignHT[k];

            return;
        }
        
        k+= 2;
    }
    k = 1;
    while (k < DistrictR->children_cnt ) {

        if (DistrictR->assignHT[k].cid == 0) {
            
            DistrictR->assignHT[k].cid = AgeR->cid;
            DistrictR->assignHT[k].s_degree = 0;
            DistrictR->assignHT[k].next = NULL;
            DistrictR->assignHT[k].pid = pid;
            
            DistrictR->assignHT[prev_index].next = &DistrictR->assignHT[k];

            return;
        }
        
        k+= 2;
    }

}

void sorted_double_hashing(struct child* AgeR, struct district* DistrictR, int pid, int prev_index){
    
    //printf("   sorted_double_hashing AgeR->cid = %d, AgeR->did = %d\n",AgeR->cid,AgeR->did);
    
    /*
     if (k > DistrictR->children_cnt){ printf(" FINATE ->");
        k = 0;
        while (k < DistrictR->children_cnt) {
            if (DistrictR->assignHT[k].cid == 0) {
     
                DistrictR->assignHT[k].cid = AgeR->cid;
                DistrictR->assignHT[k].s_degree = 0;
                DistrictR->assignHT[k].next = NULL;
                DistrictR->assignHT[k].pid = pid;
     
                DistrictR->assignHT[prev_index].next = &DistrictR->assignHT[k];
                printf(" \n");
                return;
            }
        }
     }
     */
    
    int k;
    for (k=0; k<1; k++) {
        
        while (k < DistrictR->children_cnt ) {
            
            if (DistrictR->assignHT[k].cid == 0) {
                
                DistrictR->assignHT[k].cid = AgeR->cid;
                DistrictR->assignHT[k].s_degree = 0;
                DistrictR->assignHT[k].next = NULL;
                DistrictR->assignHT[k].pid = pid;
                
                DistrictR->assignHT[prev_index].next = &DistrictR->assignHT[k];
                
                return;
                
            }else{
                
                if (DistrictR->assignHT[k].cid > AgeR->cid) {
                    
                    int tmp_cid = DistrictR->assignHT[k].cid;
                    int tmp_s_degree = DistrictR->assignHT[k].s_degree;
                    //next
                    int tmp_pid = DistrictR->assignHT[k].pid;
                
                    DistrictR->assignHT[k].cid = AgeR->cid;
                    DistrictR->assignHT[k].s_degree = 0;
                    DistrictR->assignHT[k].next = NULL;
                    DistrictR->assignHT[k].pid = pid;
                    
                    DistrictR->assignHT[prev_index].next = &DistrictR->assignHT[k];
                    
                    ///////////////////////////////////////
                    int l = 0;
                    while (l < DistrictR->children_cnt ) { //printf("l1 = %d\n",l);
                        
                        if (DistrictR->assignHT[l].cid == 0) { //printf("->l1 = %d\n",l);
                            
                            DistrictR->assignHT[l].cid = tmp_cid;
                            DistrictR->assignHT[l].s_degree = tmp_s_degree;
                            DistrictR->assignHT[l].next = NULL;
                            DistrictR->assignHT[l].pid = tmp_pid;
                            
                            break;
                            return;
                         
                        }
                        l += 2;
                    }
                    l = 1;
                    //printf("\n");
                    while (l < DistrictR->children_cnt ) { //printf("l2 = %d\n",l);
                        
                        if (DistrictR->assignHT[l].cid == 0) { //printf("->l2 = %d\n",l);
                            
                            DistrictR->assignHT[l].cid = tmp_cid;
                            DistrictR->assignHT[l].s_degree = tmp_s_degree;
                            DistrictR->assignHT[l].next = NULL;
                            DistrictR->assignHT[l].pid = tmp_pid;
                             
                            break;
                            return;
                            
                        }
                        l += 2;
                    }
                    ///////////////////////////////////////
                }
                
            }
            k += 1;
        }
        k = 0;
    }
}



int hash_function(int max_cid, int next_prime, int cid, int size){
    
    if (size != 0) {
        return (((max_cid + next_prime) + cid) % size);
    }else{
        return 0;
    }
    
}



void max_cid(struct child* R, int did){

    if ( R == NULL) { return ; }
    
    max_cid(R->lc, did);
    max_cid(R->rc, did);
    
    if (R->did == did) {
        if (R->cid > maxCid) {
            maxCid = R->cid;
        }
    }
    
}

int next_prime(){
    int i=0;
    while (primes_g[i] < maxCid) {
        i++;
    }
    return primes_g[i];
}
    
    

void readAge(struct child* AgeR, struct district* DistrictsLR){
    
    // input given is AgeR = Age_categories[...],DistrictsL
    // function puts children presente in present list
    // must go through the whole of Age_categories tree and function on every node
    
    if (AgeR == NULL) {return;}
    
    while (DistrictsLR != NULL) {
        
        if (DistrictsLR->did == AgeR->did) {

            if (DistrictsLR->assignHT == NULL) {
                // creation of hash table
                
                struct present_assign* HashTable = (struct present_assign *)malloc((DistrictsLR->children_cnt)*sizeof(struct present_assign));
                int i;
                for (i = 0; i < DistrictsLR->children_cnt; i++) {
                
                    HashTable[i].cid = 0;
                    HashTable[i].pid = 0;
                    HashTable[i].s_degree = 0;
                
                }
                
                DistrictsLR->assignHT = HashTable;
            }
            /////////////////////////////
            int pid = givePresent(stock_tree, AgeR->present_choices[0]);
            if ( pid == -2){
                pid = givePresent(stock_tree, AgeR->present_choices[1]);
                if ( pid == -2){
                    pid = givePresent(stock_tree, AgeR->present_choices[2]);
                }
            }

            int i;
            for (i=0; i<4; i++) { max_cid(Age_categories[i],DistrictsLR->did); }

            int k = hash_function(maxCid, next_prime(), AgeR->cid, DistrictsLR->children_cnt);
            maxCid = 0;

            //printf("\n\nHF = <%d> < CC = <%d>\n\n",k,DistrictsLR->children_cnt);
            
            if (DistrictsLR->assignHT[k].cid == 0) {

                DistrictsLR->assignHT[k].cid = AgeR->cid;
                DistrictsLR->assignHT[k].s_degree = 0;
                //DistrictsLR->assignHT[k].next = NULL;
                DistrictsLR->assignHT[k].pid = pid;
                
            }else{
                
                if ( (DistrictsLR->did % 3) == 0 ) { //printf("0 ->");
                    
                    coalesced_chaining(AgeR, DistrictsLR, pid, k);
                    
                }else if ( (DistrictsLR->did % 3) == 1 ) { //printf("1 ->");
                    
                    double_hashing(AgeR, DistrictsLR,pid, k);
                    
                }else if ( (DistrictsLR->did % 3) == 2 ) { //printf("2 ->");
                    
                    sorted_double_hashing(AgeR, DistrictsLR,pid, k);
                    
                }
 
            }
            /////////////////////////////

        }

        DistrictsLR = DistrictsLR->next;
        
    }

    readAge(AgeR->lc,DistrictsL);
    readAge(AgeR->rc,DistrictsL);
    
}

int prepare_presents(void) { //printf("prepare_presents -> ");// return 1;
    
    struct child* AgeR;
    
    // Creates all districts
    int i=0;
    for (i = 0 ; i < 4; i++) {
        if (Age_categories[i] != NULL) { // if not NULL we want to look for all the childern
            AgeR = Age_categories[i];    // helper *node AgeR that gets value of front of struct
            readAge(AgeR, DistrictsL);
        }
    }
    PrinDistricts();
    return 1;
}

/*if (DistrictsL != NULL) { printf(" NOT-> ");
 printf("DistrictsL <%d> <%d>",DistrictsL->assignHT->cid,DistrictsL->assignHT->pid);
 if (DistrictsL->next != NULL) { printf(" NOT ONE");
 printf("DistrictsLN <%d> <%d>",DistrictsL->next->assignHT->cid,DistrictsL->next->assignHT->pid);
 if (DistrictsL->next->next != NULL) { printf(" NOT TWO");
 printf("DistrictsLNN <%d> <%d>",DistrictsL->next->next->assignHT->cid,DistrictsL->next->next->assignHT->pid);
 if (DistrictsL->next->next->next != NULL) { printf(" NOT THREE");
 printf("DistrictsLNNN <%d> <%d>",DistrictsL->next->next->next->assignHT->cid,DistrictsL->next->next->next->assignHT->pid);
 }
 }
 }
 }*/
