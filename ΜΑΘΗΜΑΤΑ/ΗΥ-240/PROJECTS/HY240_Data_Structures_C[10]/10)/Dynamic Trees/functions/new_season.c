/**********************************************************************
 * @file   new_season.c                                               *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>                      *
 *                                                                    *
 * @brief  New season means all ages increase by one year             *
 *         all children >15 get deleted and children that grew        *
 *         and need to change Age_Categories                          *
 *         get pushed on Age_Categories up                            *
 *         All presents of all children get value 0                   *
 *                                                                    * 
 * for the needs of the Data Structures project by Ioannis Tsiakkas   *
 * Computer Science Department, University of Crete, Greece           *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

void printPresentsFour(struct present* R){
    
    if ( R != NULL) {
        if (R != stock_sentinel) {
            
            printPresentsFour(R->lc);
            printPresentsFour(R->rc);
            
            printf("<%d:%d>, ",R->pid,R->stock_cnt);
        }
    }
    
}


/********************************
 * @brief Increases all ages of *
 * Age_category by one year     *
 ********************************/
void increase_age(struct child* AgeR){
    
    if ( AgeR == NULL) { return; }
    
    increase_age(AgeR->lc);
    increase_age(AgeR->rc);
    
    AgeR->age ++;
    
}

////////////////////////////////////////////////////
/***************************************************
 * @brief helps insert_child_in_Age_categories_two *
 ***************************************************/
void putchild_two(struct child* nd, int cid, int age, int did, int pid1, int pid2, int pid3, int destination){
    
    if (destination == 1) {
        
        struct child* newChild = (struct child *)malloc(sizeof(struct child));
        
        newChild->cid = cid;
        newChild->age = age;
        newChild->did = did;
        
        newChild->lc = NULL;
        newChild->rc = NULL;
        
        newChild->present_choices[0] = pid1;
        newChild->present_choices[1] = pid2;
        newChild->present_choices[2] = pid3;
        
        nd->lc = newChild;
        
    }else{
        
        struct child* newChild = (struct child *)malloc(sizeof(struct child));
        
        newChild->cid = cid;
        newChild->age = age;
        newChild->did = did;
        
        newChild->lc = NULL;
        newChild->rc = NULL;
        
        newChild->present_choices[0] = pid1;
        newChild->present_choices[1] = pid2;
        newChild->present_choices[2] = pid3;
        
        nd->rc = newChild;
        
    }
    
    return;
    
}

/********************************************
 * @brief finds node with largest cid       *
 *        that is smaller than cid given    *
 ********************************************/
struct child* findLargerestSmaller_two( struct child* Age_categories, int cid ){//printf(" IN_LS ");if (cid == 135) { printf("IS 135\n"); }
    
    if (Age_categories == NULL) { return Age_categories; }
    
    struct child* returner = NULL;
    
    if (Age_categories->lc != NULL && Age_categories->rc != NULL) {//printf(" IN_ONE ");if (cid == 135) { printf("        IS 135\n"); }
        
        if (cid > Age_categories->lc->cid && cid > Age_categories->rc->cid) { // larger than both
            
            if (Age_categories->lc->cid > Age_categories->rc->cid) {
                
                returner = findLargerestSmaller_two( Age_categories->lc,  cid );
                // this if checks if it didnt find something smaller than
                 // current lc so it returns the current nd
                 if (returner == Age_categories->lc) {returner = Age_categories;}
            }else{
                
                returner = findLargerestSmaller_two( Age_categories->rc,  cid );
                // this if checks if it didnt find something smaller than
                 // current rc so it returns the current nd
                 if (returner == Age_categories->rc) {returner = Age_categories;}
            }
            
        }else if(cid > Age_categories->lc->cid && cid < Age_categories->rc->cid){ // larger than lc
            returner = findLargerestSmaller_two( Age_categories->lc,  cid );
        }else if(cid < Age_categories->lc->cid && cid > Age_categories->rc->cid){ // larger than rc
            returner = findLargerestSmaller_two( Age_categories->rc,  cid );
        }else{ //smaller than both
            
            // if both are bigger than cid we go to the smaller one so that
            // in the end it will go to the smaller of the whole tree
            if (Age_categories->lc->cid < Age_categories->rc->cid) {
                returner = findLargerestSmaller_two( Age_categories->lc,  cid );
            }else{
                returner = findLargerestSmaller_two( Age_categories->rc,  cid );
            }
            
        }
        
    }else if (Age_categories->lc == NULL && Age_categories->rc == NULL) {  //printf(" IN_TWO ");if (cid == 135) { printf("        IS 135->"); }
        
        return Age_categories;
        
    }else if (Age_categories->lc == NULL) {  //printf(" IN_THREE ");if (cid == 135) { printf("        IS 135 ->"); }
        
        if (cid > Age_categories->rc->cid) { //if (cid == 135) { printf("        KISS 135\n"); }
            returner = findLargerestSmaller_two( Age_categories->rc,  cid );
        }else{//if (cid == 135) { printf("        PISS 135\n"); }
            return Age_categories;
        }
        
    }else if (Age_categories->rc == NULL) {  //printf(" IN_FOUR ");if (cid == 135) { printf("        IS 135\n"); }
        
        if (cid > Age_categories->lc->cid) {
            returner = findLargerestSmaller_two( Age_categories->lc,  cid );
        }else{
            return Age_categories;
        }
        
    }
    
    return returner;
    
}

/********************************************
 * @brief finds node that is left most      *
 *        of the given tree                 *
 ********************************************/
struct child* right_left_most_two(struct child* AgeF,struct child* AgeR, int i){
    int k = 0;
    while (k == 0) {
        if (AgeR->lc == NULL && AgeR->rc == NULL) {
            if (i == 1) {
                AgeF->lc = NULL;
                return AgeR;
            }else{
                AgeF->rc = NULL;
                return AgeR;
            }
        }else if(AgeR->lc != NULL && AgeR->rc != NULL) {
            AgeF = AgeR;
            AgeR = AgeR->lc;
            i=0;
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
            i=0;
        }
    }
    printf("\n\n\nMUSTNT HAPPEN\n\n\n");
    return AgeR;
}

/*****************************
 * @brief helps check_two    *
 *****************************/
void insert_child_in_Age_categories_two(struct child* Age_categories, int cid, int age, int did, int pid1, int pid2, int pid3){
    
    // nd is the node we are looking for
    struct child* nd = NULL;
    nd = findLargerestSmaller_two( Age_categories,  cid);
    
    if(nd == NULL){ return; }

    if (nd->lc != NULL && nd->rc == NULL) { //printf(" ---------------------------> ONE ");
        
        putchild_two(nd, cid, age, did, pid1, pid2, pid3, 2);
        
    }else if (nd->lc == NULL && nd->rc != NULL) { //printf(" ---------------------------> TWO ");
        
        putchild_two(nd, cid, age, did, pid1, pid2, pid3, 1);
        
    }else if (nd->lc == NULL && nd->rc == NULL) { //printf(" ---------------------------> THREE ");
        
        if (cid % 2 == 1) { //printf("(1)\n");
            putchild_two(nd, cid, age, did, pid1, pid2, pid3, 1);
        }else{ //printf("(2)\n");
            putchild_two(nd, cid, age, did, pid1, pid2, pid3, 2);
        }
        
    }else{ //printf(" ---------------------------> FOUR ");// if (nd->lc != NULL && nd->rc != NULL)
        
        nd = right_left_most_two(Age_categories, Age_categories->rc, 0);
        putchild_two(nd, cid, age, did, pid1, pid2, pid3, 1);
        insert_child_in_Age_categories_two(Age_categories->lc, cid, age, did, pid1, pid2, pid3);
        
    }
    
}

struct child* right_left_most_three_new(struct child* AgeF,struct child* AgeR, int i){

    int k = 0;

    while (k == 0) {
        if (AgeR->lc == NULL && AgeR->rc == NULL) {
            if (i == 1) {
                AgeF->lc = NULL;
                return AgeR;
            }else{
                AgeF->rc = NULL;
                return AgeR;
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

void deleteChild_new(int masterAC, struct child*  father, struct child* AgeR, int i){
    
    if ( AgeR == NULL) { return; }
    

    // if both children of node that as to be deleted are NULL
    if (AgeR->lc == NULL && AgeR->rc == NULL) { //printf("\nBOTH NULL (%d)->\n",i);
        
        if (i == 1) {
            father->lc = NULL;
        }else if (i == 2){
            father->rc = NULL;
        }else{ //  if (i == 0)
            Age_categories[masterAC] = NULL;
        }
        
        // if none of the childrens node that has to be deleted are NULL
    }else if (AgeR->lc != NULL && AgeR->rc != NULL) { //printf("\nBOTH !NULL -> NEEDS FIXIND -> ");

        struct child* left_most = right_left_most_three_new(AgeR,AgeR->rc,0);
        
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


/********************************************
 * @brief inserts chiild in Age_category    *
 ********************************************/
void check_two(int i, int cid, int age, int did, int pid1, int pid2, int pid3) {
    
    if (Age_categories[i] == NULL) {
        
        struct child* newChild = (struct child *)malloc(sizeof(struct child));
        
        newChild->cid = cid;
        newChild->age = age;
        newChild->did = did;
        
        newChild->lc = NULL;
        newChild->rc = NULL;
        
        newChild->present_choices[0] = pid1;
        newChild->present_choices[1] = pid2;
        newChild->present_choices[2] = pid3;
        
        Age_categories[i] = newChild;
        
    }else{
        
        insert_child_in_Age_categories_two( Age_categories[i],  cid,  age,  did,  pid1,  pid2,  pid3);
        
    }
    
}

/*******************************
 * @brief moves grown children *
 * to the next Age_category    *
 *******************************/
void move_grown_children(int i,struct child* AgeF, struct child* AgeR, int lc_or_rc){
    
    if ( AgeR == NULL) { return; }
    
    move_grown_children(i, AgeR, AgeR->lc, 1);
    move_grown_children(i, AgeR, AgeR->rc, 2);
    
    AgeR->present_choices[0] = -1;
    AgeR->present_choices[1] = -1;
    AgeR->present_choices[2] = -1;
    
    if (i==0) { //printf("\nAgeR->cid = <%d>, AgeR->age = <%d> > 3 ",AgeR->cid,AgeR->age);

        if (AgeR->age > 3) { //printf(" <-- ΣΒΗΝΩ ");
            
            check_two(1, AgeR->cid, AgeR->age, AgeR->did, -1, -1, -1);
            deleteChild_new(i, AgeF, AgeR, lc_or_rc);

        }
        
    }else if (i==1){ //printf("\nAgeR->cid = <%d>, AgeR->age = <%d> > 7 ",AgeR->cid,AgeR->age);

        if (AgeR->age > 7) { //printf(" <-- ΣΒΗΝΩ ");

            check_two(2, AgeR->cid, AgeR->age, AgeR->did, -1, -1, -1);
            deleteChild_new(i, AgeF, AgeR, lc_or_rc);

        }

    }else if (i==2){ //printf("\nAgeR->cid = <%d>, AgeR->age = <%d> > 11 ",AgeR->cid,AgeR->age);
        
        if (AgeR->age > 11) { //printf(" <-- ΣΒΗΝΩ ");

            check_two(3, AgeR->cid, AgeR->age, AgeR->did, -1, -1, -1);
            deleteChild_new(i, AgeF, AgeR, lc_or_rc);

        }

    }else if (i==3){ //printf("\nAgeR->cid = <%d>, AgeR->age = <%d> > 15 ",AgeR->cid,AgeR->age);
        
        if (AgeR->age > 15) { //printf(" <-- ΣΒΗΝΩ ");
            deleteChild_new(i, AgeF, AgeR, lc_or_rc);
        }
        
    }
    //printf("\n");
}
////////////////////////////////////////////////////////


/*******************************
 * @brief unshackles all Hash  *
 * Tables from every district *
 *******************************/
void unshackle_HT(struct district* DistrictR){
    
    while (DistrictR != NULL) {
        
        DistrictR->assignHT = NULL;
        DistrictR->children_cnt = 0;
        
        DistrictR = DistrictR->next;
    }
    
}

struct present* right_left_most_new(struct present* AgeF,struct present* AgeR, int i){
    
    if (AgeR == stock_sentinel) { return stock_sentinel; }
    
    int k = 0;
    while (k == 0) {
        if (AgeR->lc == stock_sentinel && AgeR->rc == stock_sentinel) { //printf(" <-One ");
            if (i == 1) { //printf(" <-one ");
                AgeF->lc = stock_sentinel;
                return AgeR; //
            }else{
                AgeF->rc = stock_sentinel;
                return AgeR; //
            }
        }else if(AgeR->lc != stock_sentinel && AgeR->rc != stock_sentinel) { // printf(" <-Two ");
            AgeF = AgeR;
            AgeR = AgeR->lc;
            i=1;
        }else if(AgeR->rc != stock_sentinel) { // printf(" <-Three ");
            if (i == 1) { // printf(" <-one ");
                AgeF->lc = AgeR->rc;
                return AgeR;
            }else{
                AgeF->rc = AgeR->rc;
                return AgeR;
            }
        }else if(AgeR->lc != stock_sentinel) { // printf(" <-Four ");
            AgeF = AgeR;
            AgeR = AgeR->lc;
            i=1;
        }
    }
    printf("\n\n\nMUSTNT HAPPEN\n\n\n");
    return AgeR;
}

void delete_presents_with_stock_cnt_zero(struct present* Present){
    
    //printf("pid<%d> ",Present->pid);
    //if (Present->parent != NULL) {
     //   printf("p-pid <%d>\n",Present->parent->pid);
    //}else{        printf("p-pid <NULL> :\n"); }
    //printf("<%d> ",Present->pid); printf("ΤΕΛΟΣ\n");

    struct present* left_most;
    
    if (Present->parent == NULL) { //printf("Parent NULL - ");
        
        if (Present->lc == stock_sentinel && Present->rc == stock_sentinel) { //printf("one ");
            
            stock_tree = NULL;
            
        }else if(Present->lc != stock_sentinel && Present->rc != stock_sentinel) { //printf("two ");
            
            left_most = right_left_most_new(Present, Present->rc, 0);
            
            left_most->lc = Present->lc;
            left_most->rc = Present->rc;
            
            stock_tree = left_most;
            
        }else if(Present->rc != stock_sentinel) { //printf("three ");
            
            Present->rc->parent = stock_sentinel;
            stock_tree = Present->rc;
            
        }else if(Present->lc != stock_sentinel) { //printf("four ");
            
            Present->lc->parent = stock_sentinel;
            stock_tree = Present->lc;
            
        }
        //printf("<%d> ",Present->pid); printf("ΤΕΛΟΣ\n");

    }else{  //printf(" ! Parent NULL - ");
        
        if (Present->lc == stock_sentinel && Present->rc == stock_sentinel) {  //printf(" 2x stock_sentinel - ");
        
            if (Present->parent->lc != stock_sentinel) {
                if (Present->parent->lc == Present) {
                    Present->parent->lc = NULL;
                }else{
                    Present->parent->rc = NULL;
                }
            }else{
                Present->parent->rc = NULL;
            }
            //printf("<%d> ",Present->pid); printf("ΤΕΛΟΣ\n");

         
        }else if(Present->lc != stock_sentinel && Present->rc != stock_sentinel) { //printf(" 2x ! stock_sentinel - ");
        
            left_most = right_left_most_new(Present, Present->rc, 0);
            
            //printf(" left_most->pid = %d ",left_most->pid);
            //printf(" left_most->parent->pid = %d ",left_most->parent->pid);
            //printf(" Present->parent->pid = %d ",Present->parent->pid);

            left_most->lc = Present->lc;
            left_most->rc = Present->rc;
            //printf(" checking ... ");
            if (Present->parent->lc != stock_sentinel) {
                if (Present->parent->lc == Present) { //printf("one ");
                    Present->parent->lc = left_most;
                }else{ //printf("two ");
                    Present->parent->rc = left_most;
                }
            }else{ //printf("three ");
                Present->parent->rc = left_most;
            }
            //printf("<%d> ",Present->pid); printf("ΤΕΛΟΣ\n");

        }else if(Present->rc != stock_sentinel) { //printf("rc ! stock_sentinel - ");
            
            if (Present->parent->lc != stock_sentinel) {
                if (Present->parent->lc == Present) { //printf("one ");
                    Present->parent->lc = Present->rc;
                }else{ //printf("two ");
                    Present->parent->rc = Present->rc;
                }
            }else{ //printf("three ");
                Present->parent->rc = Present->rc;
            }
            //printf("<%d> ",Present->pid); printf("inside ");

        }else if(Present->lc != stock_sentinel) { //printf("lc ! stock_sentinel - ");
            
            if (Present->parent->lc != stock_sentinel) {
                if (Present->parent->lc == Present) {
                    Present->parent->lc = Present->lc;
                }else{
                    Present->parent->rc = Present->lc;
                }
            }else{
                Present->parent->rc = Present->lc;
            }
            //printf("<%d> ",Present->pid); printf("ΤΕΛΟΣ\n");

        }
        
    }
    //printf("<%d> ",Present->pid); printf("ΤΕΛΟΣ\n");
}

/*******************************
 * @brief Deletes all presents *
 * with stock_cnt zero         *
 *******************************/
void present_operations(struct present* Present){
    
    if ( Present == stock_sentinel) { return; }
    
    if (Present->stock_cnt == 0) { //printf("\n<%d> ",Present->pid); printf("ΜΠΑΙΝΕΙ ΕΞΩ - ");
        delete_presents_with_stock_cnt_zero(Present);
    }else{
        Present->request_cnt = 0;
    }
    
    present_operations(Present->lc);
    present_operations(Present->rc);
}

int new_season(void) {
    
    /*****************************************
     * @brief Increases all ages by one year *
     *****************************************/
    int i=0;
    for (i = 0 ; i < 4; i++) {
        if (Age_categories[i] != NULL) {
            increase_age(Age_categories[i]);
        }
    }


   /**************************************************
    * @brief Goes up age_category for grown children *
    *        also deletes children with age > 15     *
    **************************************************/
    for (i = 0 ; i < 4; i++) {
        if (Age_categories[i] != NULL) {
            move_grown_children(i, NULL, Age_categories[i], 0);
        }
    }
    
    
    /*****************************************
     * @brief Clears all HT of all districts *
     *****************************************/
    unshackle_HT(DistrictsL);
    
    
    /*******************************************
     * @brief Deletes presents with stock = 0  *
     *        Makes request_cnt = 0 else       *
     *******************************************/
    //printf("\n\nPRESENTS_B: "); printPresentsFour(stock_tree);printf("\n\n");
    present_operations(stock_tree);
    //printf("\n\nPRESENTS_A: "); printPresentsFour(stock_tree);printf("\n");
    printf("\nN\n\nDONE\n\n");

    return 1;
}