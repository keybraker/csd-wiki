#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int print_child(void) {
    
    struct child* reader_agec = NULL;

    printf("H\n\n");
    for (int i = 0 ; i < 4; i++) {
        
        if(i == 0){
            printf("    0-3:    ");
        }else if(i == 1){
            printf("    4-7:    ");
        }else if(i == 2){
            printf("    8-11:   ");
        }else if(i == 3){
            printf("    12-15:  ");
        }
        
        if (Age_categories[i] != NULL) {
            reader_agec = Age_categories[i];
            while(reader_agec != NULL){
                printf("<%d>, ",reader_agec->cid);
                reader_agec = reader_agec->next;
            }
        }
        printf("\n");
    }
    printf("\nDONE\n\n");
    
    return 1;
}