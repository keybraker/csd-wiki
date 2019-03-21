#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

struct present *stock_sentinel = NULL;
struct present *stock_list = NULL;

void printPresentsList(){
    struct present *reader = stock_list;

    printf("B <%d> <%d>\n\n   Presents = ",reader->pid,reader->stock_cnt);
    while (reader->pid != -1) {
        
        printf("<%d>, ",reader->pid);
        reader = reader->next;
    }
    printf("\n\nDONE\n\n");
}

int buy_present(int pid, int stock_cnt) {
    
    //if there are no presents I create the first
   if (stock_list == NULL) {
        
       struct present* newSentinel = (struct present *)malloc(sizeof(struct present));
       struct present* newNode = (struct present *)malloc(sizeof(struct present));

       newSentinel->pid = -1;
       newSentinel->stock_cnt = -1;
       newSentinel->request_cnt = -1;
        
       newSentinel->next = newNode;
       newSentinel->prev = newNode;
        
       newNode->pid = pid;
       newNode->stock_cnt = stock_cnt;
       newNode->request_cnt = 0;
    
       newNode->next = newSentinel;
       newNode->prev = newSentinel;
        
       stock_list = newNode;
       stock_sentinel = newSentinel;
       

  }else{

      struct present* newNode = (struct present *)malloc(sizeof(struct present));
      
      newNode->pid = pid;
      newNode->stock_cnt = stock_cnt;
      newNode->request_cnt = 0;
      
      // pushed presents to back
      newNode->next = stock_sentinel;
      newNode->prev = stock_sentinel->next;
      
      stock_sentinel->next->next = newNode;
      stock_sentinel->next = newNode;
      
      /*
      // pushes new presents to front
      newNode->next = stock_list;
      newNode->prev = stock_sentinel;
      
      stock_sentinel->prev = newNode;
      stock_list->prev = newNode;
      stock_list = newNode;
      */
   }
    
    printPresentsList();
   
    return 1;
}