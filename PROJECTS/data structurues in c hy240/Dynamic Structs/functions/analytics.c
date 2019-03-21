#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

void insertionSort(struct present* head){
    
    if (head != NULL) { // overcautiouse
        if (head->next != NULL) { // ultra overcautiouse
            struct present *key = NULL;
            struct present *i = NULL;
            struct present *j = NULL;
            j = head;
            key = head;
            
            if (j->request_cnt != -1) {
                /////////////////////
                while(j->next->request_cnt != -1){
                    
                    key = j;
                    i = j->next;
                    while(key->request_cnt != -1 && i->request_cnt > key->request_cnt){
                        key->next = i->next;
                        i->next->prev = key;
                        
                        if(key->prev == NULL){
                            i->prev = NULL;
                        }else{
                            i->prev = key->prev;
                            key->prev->next = i;
                        }
                        
                        i->next = key;
                        key->prev = i;
                        
                        if(i->prev != NULL){
                            key = i->prev;
                        }else{
                            break;
                        }
                        j = key;
                    }
                    j = j->next;
                }
                stock_list = stock_sentinel->next;
                stock_sentinel->next = stock_sentinel->prev;
                stock_sentinel->prev = stock_list;
            }
        }
    }
}

int analytics(void) {
    
    insertionSort(stock_list);

    struct present* reader = stock_list;

    printf("A\n\n");
    if (reader != NULL) {
        while (reader->request_cnt != -1) {
            printf("    <%d> : <%d>\n",reader->pid,reader->request_cnt);
            reader = reader->next;
        }
    }else{
        printf("<NULL>\n");
    }
    
    printf("\nDONE\n\n");
    
    return 1;
    
}