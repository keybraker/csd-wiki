/**********************************************************************
 * @file   letter_recieved.c                                          *
 * @author Ioannis Tsiakkas <csd3213@csd.uoc.gr>                      *
 *                                                                    *
 * @brief  creates a all lists of children based on age               *
 *                                                                    *
 * for the needs of the Data Structures project by Ioannis Tsiakkas   *
 * Computer Science Department, University of Crete, Greece           *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

struct child *Age_categories[4] = {NULL,NULL,NULL,NULL};

void findPidInTree(struct present* R, int pid){
    
    if ( R == NULL) { return ; }
    if ( R == stock_sentinel) { return ; }

    
    if (pid == R->pid) {
        //check
        R->request_cnt ++;
        
        return ;
        
    }else if (pid < R->pid){ //printf("left->");
        
        if (R->lc == stock_sentinel) {
            
            struct present* newPresent = (struct present *)malloc(sizeof(struct present));
            
            newPresent->pid = pid;
            newPresent->stock_cnt = 10;
            newPresent->request_cnt = 0; // giving 0 just in case
            newPresent->parent = R; // set father
            
            newPresent->rc = stock_sentinel; // rc of first leaf is sentinel
            newPresent->lc = stock_sentinel; // lc of first leaf is sentinel
            
            R->lc = newPresent;
            
            return ;
            
        }else{
            
            findPidInTree(R->lc, pid);
            
        }
        
    }else if (pid > R->pid){ //printf("right->");
        
        if (R->rc == stock_sentinel) {
            
            struct present* newPresent = (struct present *)malloc(sizeof(struct present));
            
            newPresent->pid = pid;
            newPresent->stock_cnt = 10;
            newPresent->request_cnt = 0; // giving 0 just in case
            newPresent->parent = R; // set father
            
            newPresent->rc = stock_sentinel; // rc of first leaf is sentinel
            newPresent->lc = stock_sentinel; // lc of first leaf is sentinel
            
            R->rc = newPresent;
            
            return;
            
        }else{
            
            findPidInTree(R->rc, pid);
            
        }
        
    }
    
}



void putchild(struct child* nd, int cid, int age, int did, int pid1, int pid2, int pid3, int destination){
    
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
struct child* findLargerestSmaller( struct child* Age_categories, int cid ){//printf(" IN_LS ");if (cid == 135) { printf("IS 135\n"); }

    if (Age_categories == NULL) { return Age_categories; }

    struct child* returner = NULL;

    if (Age_categories->lc != NULL && Age_categories->rc != NULL) {//printf(" IN_ONE ");if (cid == 135) { printf("        IS 135\n"); }

        if (cid > Age_categories->lc->cid && cid > Age_categories->rc->cid) { // larger than both
            
            if (Age_categories->lc->cid > Age_categories->rc->cid) {
                
                returner = findLargerestSmaller( Age_categories->lc,  cid );
                /*// this if checks if it didnt find something smaller than
                // current lc so it returns the current nd
                if (returner == Age_categories->lc) {
                    returner = Age_categories;
                }*/
            }else{
                
                returner = findLargerestSmaller( Age_categories->rc,  cid );
                /*// this if checks if it didnt find something smaller than
                // current rc so it returns the current nd
                if (returner == Age_categories->rc) {
                    returner = Age_categories;
                }*/
            }
            
        }else if(cid > Age_categories->lc->cid && cid < Age_categories->rc->cid){ // larger than lc
            returner = findLargerestSmaller( Age_categories->lc,  cid );
        }else if(cid < Age_categories->lc->cid && cid > Age_categories->rc->cid){ // larger than rc
            returner = findLargerestSmaller( Age_categories->rc,  cid );
        }else{ //smaller than both
            
            // if both are bigger than cid we go to the smaller one so that
            // in the end it will go to the smaller of the whole tree
            if (Age_categories->lc->cid < Age_categories->rc->cid) {
                returner = findLargerestSmaller( Age_categories->lc,  cid );
            }else{
                returner = findLargerestSmaller( Age_categories->rc,  cid );
            }
            
        }
        
    }else if (Age_categories->lc == NULL && Age_categories->rc == NULL) {  //printf(" IN_TWO ");if (cid == 135) { printf("        IS 135->"); }
        
        return Age_categories;
        
    }else if (Age_categories->lc == NULL) {  //printf(" IN_THREE ");if (cid == 135) { printf("        IS 135 ->"); }
        
        if (cid > Age_categories->rc->cid) { //if (cid == 135) { printf("        KISS 135\n"); }
            returner = findLargerestSmaller( Age_categories->rc,  cid );
        }else{//if (cid == 135) { printf("        PISS 135\n"); }
            return Age_categories;
        }
        
    }else if (Age_categories->rc == NULL) {  //printf(" IN_FOUR ");if (cid == 135) { printf("        IS 135\n"); }
        
        if (cid > Age_categories->lc->cid) {
            returner = findLargerestSmaller( Age_categories->lc,  cid );
        }else{
            return Age_categories;
        }
    
    }
    
    return returner; 
    
}

struct child* right_left_most(struct child* AgeF,struct child* AgeR, int i){
    
    if (AgeR == NULL) { return NULL; }
    
    int k = 0;
    while (k == 0) {
        if (AgeR->lc == NULL && AgeR->rc == NULL) {
            if (i == 1) {
                //AgeF->lc = NULL;
                return AgeR;
            }else{
                //AgeF->rc = NULL;
                return AgeR;
            }
        }else if(AgeR->lc != NULL && AgeR->rc != NULL) {
            AgeF = AgeR;
            AgeR = AgeR->lc;
            i=0;
        }else if(AgeR->rc != NULL) {
            if (i == 1) {
                //AgeF->lc = AgeR->rc;
                return AgeR;
            }else{
                //AgeF->rc = AgeR->rc;
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

void insert_child_in_Age_categories(struct child* Age_categories, int cid, int age, int did, int pid1, int pid2, int pid3){

    // nd is the largest smaller or smallest
    struct child* nd = findLargerestSmaller( Age_categories,  cid);
    
    if (nd->lc != NULL && nd->rc == NULL) { //printf(" ---------------------------> ONE ");
        
        putchild(nd, cid, age, did, pid1, pid2, pid3, 2);
        
    }else if (nd->lc == NULL && nd->rc != NULL) { //printf(" ---------------------------> TWO ");
        
        putchild(nd, cid, age, did, pid1, pid2, pid3, 1);
        
    }else if (nd->lc == NULL && nd->rc == NULL) { //printf(" ---------------------------> THREE ");
        
        if (cid % 2 == 1) { //printf("(1)\n");
            putchild(nd, cid, age, did, pid1, pid2, pid3, 1);
        }else{ //printf("(2)\n");
            putchild(nd, cid, age, did, pid1, pid2, pid3, 2);
        }
        
    }else{ //printf(" ---------------------------> FOUR ");// if (nd->lc != NULL && nd->rc != NULL)

        nd = right_left_most(Age_categories, Age_categories->rc, 0);
        putchild(nd, cid, age, did, pid1, pid2, pid3, 1);
        
        //insert_child_in_Age_categories(Age_categories->lc, cid, age, did, pid1, pid2, pid3);
        
    }
    
}

void check(int i, int cid, int age, int did, int pid1, int pid2, int pid3) {
    
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

        insert_child_in_Age_categories( Age_categories[i],  cid,  age,  did,  pid1,  pid2,  pid3);
        
    }
}



int checkForChild(struct child* Age_categories,int cid, int pid1, int pid2, int pid3){

    if (Age_categories == NULL) { return 0; }
    
    int one = checkForChild(Age_categories->lc,cid,pid1,pid2,pid3);
    int two = checkForChild(Age_categories->rc,cid,pid1,pid2,pid3);
    
    if (Age_categories->cid == cid) { //printf(" ΤΟ ΠΑΙΔΙ ΥΠΑΡΧΕΙ ΑΡΑ ΤΟΥ ΒΑΖΩ ΤΑ ΝΕΑ ΔΩΡΑ\n");
        
        Age_categories->present_choices[0] = pid1;
        Age_categories->present_choices[1] = pid2;
        Age_categories->present_choices[2] = pid3;
        
        return 1;
    }
    
    if(one > two){
        return one;
    }else{
        return two;
    }
    
}



int letter_received(int cid, int age, int did, int pid1, int pid2, int pid3) {//printf("BEGINS");

    int i=0, F=0;
    
    // if child is found than F = 1
    for (i = 0 ; i < 4; i++) {
        
        if (Age_categories[i] != NULL) {
            // checks for child in Age_categories[i]
            // F gets 1/0 : 1 for found 0 else
            F = checkForChild(Age_categories[i],cid,pid1,pid2,pid3);
        }
        
    }
    if (F == 0){ //only do when not F
        
        // Finds out in which age catecory the child is
        if (age>=0 && age <= 3) { //printf(" ΜΠΑΙΝΕΙ ΣΤΟ <= 3\n");
            
            check(0, cid, age, did, pid1, pid2, pid3);
            
        }else if ( age >= 4 && age <= 7){ //printf(" ΜΠΑΙΝΕΙ ΣΤΟ <= 7\n");
            
            check(1, cid, age, did, pid1, pid2, pid3);
            
        }else if ( age >= 8 && age <= 11){ //printf(" ΜΠΑΙΝΕΙ ΣΤΟ <= 11\n");
            
            check(2, cid, age, did, pid1, pid2, pid3);
            
        }else if ( age >= 12 && age <= 15){ //printf(" ΜΠΑΙΝΕΙ ΣΤΟ <= 15\n");
            
            check(3, cid, age, did, pid1, pid2, pid3);
            
        }else{
            
            if (age<0) {
                printf("Error : Age below 0\n");
            }else{
                printf("Error : Age over 15, is not child.\n");
            }
            
        }
        
    }
    F = 0;
    struct district* DistrictsLR = DistrictsL;
    struct district* DistrictsLRprev = NULL;

    if (DistrictsLR == NULL) {
        
        struct district* newDistrict = (struct district *)malloc(sizeof(struct district));
        
        newDistrict->children_cnt ++;
        newDistrict->did = did;
        newDistrict->next = NULL;
        
        DistrictsLR = newDistrict;
        DistrictsL = DistrictsLR;
        
    }else{

        //printf("1) DistrictsLR->did = <%d> , <%d> = did  -->  ",DistrictsLR->did,did);
        while (DistrictsLR != NULL) { //printf(" != ");

            if (DistrictsLR->did == did) { //printf(" == ");
                
                DistrictsLR->children_cnt ++;
                
                F = 1;
                break;
                
            }
            
            if (DistrictsLR->did > did) {
                
                struct district* newDistrict = (struct district *)malloc(sizeof(struct district));
                
                newDistrict->children_cnt = 1;
                newDistrict->did = did;
                
                if (DistrictsLRprev == NULL) { // is first node in list
                    newDistrict->next = DistrictsLR;
                    DistrictsL = newDistrict;
                }else{
                    newDistrict->next = DistrictsLRprev->next;
                    DistrictsLRprev->next = newDistrict;
                }
                
                F = 1;
                break;
                
            }
            
            if (DistrictsLR->next == NULL) {
                
                struct district* newDistrict = (struct district *)malloc(sizeof(struct district));
                
                newDistrict->children_cnt = 1;
                newDistrict->did = did;
                
                if (DistrictsLRprev == NULL) { // is first node in list
                    newDistrict->next = NULL;
                    DistrictsLR->next = newDistrict;
                }else{
                    newDistrict->next = NULL;
                    DistrictsLR->next = newDistrict;
                }
                
                break;
                
            }

            DistrictsLRprev = DistrictsLR;
            DistrictsLR = DistrictsLR->next;
            
        }
        
    }
    // Check for presence of present in present list
    findPidInTree ( stock_tree , pid1 );
    findPidInTree ( stock_tree , pid2 );
    findPidInTree ( stock_tree , pid3 );
    
    printf("L <%d> <%d> <%d> <%d> <%d> <%d>\n\nDONE\n\n",cid,age,did,pid1,pid2,pid3);

    return 1;
}



/* old insert_child
 void insert_child_in_Age_categories(struct child* Age_categories, int cid, int age, int did, int pid1, int pid2, int pid3){
 
 if (cid > Age_categories->cid){ //printf("left->");
 
    if (Age_categories->lc == NULL) {
 
        struct child* newChild = (struct child *)malloc(sizeof(struct child));
 
        newChild->cid = cid;
        newChild->age = age;
        newChild->did = did;
 
        newChild->lc = NULL;
        newChild->rc = NULL;
 
        newChild->present_choices[0] = pid1;
        newChild->present_choices[1] = pid2;
        newChild->present_choices[2] = pid3;
 
        Age_categories->lc = newChild;
 
        return;
 
 }else{
 
    insert_child_in_Age_categories( Age_categories->lc,  cid,  age,  did,  pid1,  pid2,  pid3);
 
 }
 
 }else if (cid < Age_categories->cid){ //printf("right->");
 
 if (Age_categories->rc == NULL) {
 
 struct child* newChild = (struct child *)malloc(sizeof(struct child));
 
 newChild->cid = cid;
 newChild->age = age;
 newChild->did = did;
 
 newChild->lc = NULL;
 newChild->rc = NULL;
 
 newChild->present_choices[0] = pid1;
 newChild->present_choices[1] = pid2;
 newChild->present_choices[2] = pid3;
 
 Age_categories->rc = newChild;
 
 return;
 
 }else{
 
 insert_child_in_Age_categories( Age_categories->rc,  cid,  age,  did,  pid1,  pid2,  pid3);
 
 }
 
 }
 
 }*/

/*if (DistrictsLR == NULL) {
 
 struct district* newDistrict = (struct district *)malloc(sizeof(struct district));
 
 newDistrict->children_cnt ++;
 newDistrict->did = did;
 newDistrict->next = NULL;
 
 DistrictsLR = newDistrict;
 DistrictsL = DistrictsLR;
 
 }else{
 
 while (DistrictsLR != NULL) {
 
 if (DistrictsLR->did == did) {
 
 DistrictsLR->children_cnt ++;
 
 F = 1;
 
 }
 
 DistrictsLRprev = DistrictsLR;
 DistrictsLR = DistrictsLR->next;
 
 }
 if (F == 0) {
 
 struct district* newDistrict = (struct district *)malloc(sizeof(struct district));
 
 newDistrict->children_cnt = 1;
 newDistrict->did = did;
 newDistrict->next = NULL;
 
 if (DistrictsLRprev != NULL) { DistrictsLRprev->next = newDistrict; }
 
 }
 
 }*/


