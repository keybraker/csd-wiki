#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int search_present(int pid) {
    
    if (stock_list != NULL) {
        struct present *reader = stock_list;
        
        while (reader->pid != -1) { // runs until end of list
            //printf("<%d> == <%d>\n",reader->pid,pid);
            if (reader->pid == pid){
                // if present is found
                printf("S <%d>\n\n",pid);
                printf("    <%d>, <%d>",reader->stock_cnt,reader->request_cnt);
                printf("\n\nDONE\n\n");
                return 1;
            }
            reader = reader->next;
        }
    }
    printf("S <%d>\n\n",pid);
    printf("    DID NOT FIND");
    printf("\n\nDONE\n\n");
    return 1;
}