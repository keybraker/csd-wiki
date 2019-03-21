#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

struct child *Age_categories[4] = {NULL,NULL,NULL,NULL};

void Insert(int pid){
    
    struct present* newNode = (struct present *)malloc(sizeof(struct present));
    
    newNode->pid = pid;
    newNode->stock_cnt = 10;
    newNode->request_cnt = 0;
    
    newNode->next = stock_list;
    newNode->prev = stock_sentinel;
    
    stock_sentinel->prev = newNode;
    stock_list->prev = newNode;
    
    stock_list = newNode;
    
}

void check_correct(int i, int cid, int age, int did, int pid1, int pid2, int pid3) {

    if (Age_categories[i] == NULL) {

        struct child* newChild = (struct child *)malloc(sizeof(struct child));
        
        newChild->cid = cid;
        newChild->age = age;
        newChild->did = did;
        newChild->next = NULL;
        newChild->present_choices[0] = pid1;
        newChild->present_choices[1] = pid2;
        newChild->present_choices[2] = pid3;
        
        Age_categories[i] = newChild;
        
    }else{ //// ΘΕΛΕΙ ΔΟΥΛΕΙΑ ΕΝΑ ΚΟΠΙ ΠΑΣΤΑ ΕΙΝΑΙ
        
        //helper *node reader that gets value of front o struct
        struct child* reader = Age_categories[i];
        struct child* readerprev = NULL;
        
        while (reader != NULL) {
        
            if (reader->cid == cid) { // if present's id is found in the list than there is no reason to continue searching

                reader = NULL;
                
            }else{
                
                if (reader->cid < cid) { // cid is bigger so we go to the next block of the list

                    readerprev = reader;
                    reader = reader->next;
                    
                    if (reader == NULL){ // All presents in list have smaller ids than current
                        // checking imidiatelly after going to next block to
                        // keep the O(1) speed

                        struct child* newChild = (struct child *)malloc(sizeof(struct child));
                        
                        newChild->cid = cid;
                        newChild->age = age;
                        newChild->did = did;
                        newChild->next = NULL;
                        newChild->present_choices[0] = pid1;
                        newChild->present_choices[1] = pid2;
                        newChild->present_choices[2] = pid3;
                        
                        readerprev->next = newChild;
                        
                        reader = NULL;
                    }
                    
                }else if(reader->cid > cid) { // current id is smaller than the one in the list

                    struct child* newChild = (struct child *)malloc(sizeof(struct child));
                    
                    newChild->cid = cid;
                    newChild->age = age;
                    newChild->did = did;
                    newChild->next = reader->next;
                    newChild->present_choices[0] = pid1;
                    newChild->present_choices[1] = pid2;
                    newChild->present_choices[2] = pid3;
                    
                    if (readerprev == NULL) { // if there is only one present and its id is bigger than current
                        newChild->next = Age_categories[i];
                        Age_categories[i] = newChild;
                    }else{ // if the current cid is in the middle of two ids
                        newChild->next = readerprev->next;
                        readerprev->next = newChild;
                    }
                    
                    reader = NULL;
                    
                }
            }
        }
    }
}

void check(int i, int cid, int age, int did, int pid1, int pid2, int pid3) {
    
    if (Age_categories[i] == NULL) {
        
        struct child* newChild = (struct child *)malloc(sizeof(struct child));
        
        newChild->cid = cid;
        newChild->age = age;
        newChild->did = did;
        newChild->next = NULL;
        newChild->present_choices[0] = pid1;
        newChild->present_choices[1] = pid2;
        newChild->present_choices[2] = pid3;
        
        Age_categories[i] = newChild;
        
    }else{//printf("KAPPA : ");
        
        struct child* reader = Age_categories[i];
        
        while (reader->next != NULL) {
            if (reader->next->cid > cid) {
                
                struct child* newChild = (struct child *)malloc(sizeof(struct child));
                
                newChild->cid = cid;
                newChild->age = age;
                newChild->did = did;
                
                newChild->present_choices[0] = pid1;
                newChild->present_choices[1] = pid2;
                newChild->present_choices[2] = pid3;
                
                newChild->next = reader->next;
                reader->next = newChild;
                
                break;
                
            }//printf("IN, ");
            reader = reader->next;
        }
        
        if (reader->next == NULL) {
            
            struct child* newChild = (struct child *)malloc(sizeof(struct child));
            
            newChild->cid = cid;
            newChild->age = age;
            newChild->did = did;
            
            newChild->present_choices[0] = pid1;
            newChild->present_choices[1] = pid2;
            newChild->present_choices[2] = pid3;
            
            newChild->next = NULL;
            reader->next = newChild;
            
        }
        
    }
}

int letter_received(int cid, int age, int did, int pid1, int pid2, int pid3) {
    
    if (age>=0 && age <= 3) {
        
        check(0, cid, age, did, pid1, pid2, pid3);
        
    }else if ( age >= 4 && age <= 7){
        
        check(1, cid, age, did, pid1, pid2, pid3);
        
    }else if ( age >= 8 && age <= 11){
        
        check(2, cid, age, did, pid1, pid2, pid3);
        
    }else if ( age >= 12 && age <= 15){
        
        check(3, cid, age, did, pid1, pid2, pid3);

    }else{
        
        if (age<0) {
            printf("Error : Age bellow 0\n");
        }else{
            printf("Error : Age over 15, is not child.\n");
        }
        
    }

    if (stock_list != NULL) {
        int times1 = 0,times2 = 0,times3 = 0;
        //helper *node reader that gets value of front o struct
        struct present *reader = stock_list;
        
        while (reader->pid != -1) {
            
            if (reader->pid == pid1 || reader->pid == pid2 || reader->pid == pid3){
                
                reader->request_cnt++;

                if (reader->pid != 0) {
                    if(reader->pid == pid1){
                        times1 = 1;
                    }else if (reader->pid == pid2){
                        times2 = 1;
                    }else if (reader->pid == pid3){
                        times3 = 1;
                    }
                }
                
            }
            reader = reader->next;
        }
        
        if (times1 == 0) {
            if (pid1 != 0) {
                Insert(pid1);
            }
        }if (times2 == 0){
            if (pid2 != 0) {
                Insert(pid2);
            }
        } if (times3 == 0){
            if (pid3 != 0) {
                Insert(pid3);
            }
        }
        
    }    
    
    printf("L <%d> <%d> <%d> <%d> <%d> <%d>\n\nDONE\n\n",cid,age,did,pid1,pid2,pid3);
    
    return 1;
}











