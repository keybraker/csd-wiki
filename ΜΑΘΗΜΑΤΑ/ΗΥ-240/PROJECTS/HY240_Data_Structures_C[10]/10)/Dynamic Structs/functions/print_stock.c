#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int print_stock(void) {
    
    printf("T\n\n    Stock = ");
    if (stock_list != NULL) {
        struct present *reader = stock_list;
        
        while (reader->pid != -1) { // runs until end of list
            //printf("<%d> == <%d>\n",reader->pid,pid);
            if (reader->stock_cnt != 0){
                // if present is not zero
                printf("<%d> ",reader->pid);
            }
            reader = reader->next;
        }
    }
    printf("\n\nDONE\n\n");
    
    return 1;
}