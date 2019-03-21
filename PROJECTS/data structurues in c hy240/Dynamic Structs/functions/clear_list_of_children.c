#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int clear_list_of_children(void) {
   
    struct child* reader_agec = NULL;
    struct child* reader_agec_prev = NULL;
    
    for (int i = 0 ; i < 4; i++) {
        
        if (Age_categories[i] != NULL) {
            
            reader_agec = Age_categories[i];
            reader_agec_prev = NULL;

            while (reader_agec != NULL) {
                //printf("{%d, %d, %d}, ",reader_agec->present_choices[0],reader_agec->present_choices[1],reader_agec->present_choices[2]);
                if (reader_agec->present_choices[0] == 0 && reader_agec->present_choices[1]
                    == 0 && reader_agec->present_choices[2] == 0) {
                    
                    if (reader_agec_prev == NULL) {

                        Age_categories[i] = reader_agec->next;

                        if (reader_agec->next == NULL) {break;}
                        reader_agec_prev = NULL;

                    }else{
                        
                        reader_agec_prev->next = reader_agec->next;
                       
                        if (reader_agec->next == NULL) {break;}
                        reader_agec_prev = reader_agec;

                    }
                    
                }
                reader_agec = reader_agec->next;
            }
            
        }
        
    }
    
    printf("C\n\n");
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