#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

void printAge(struct child* age){
    printf("Age = ");
    if (age == NULL) {
        printf(" NULL");
    }else{
        while (age != NULL) {
            printf("<%d>, ",age->cid);
            age = age->next;
        }
    }
    printf("\n");
}

int new_season(void) {
    
    struct child* reader_agec = NULL;
    struct child* reader_agec_prev = NULL;
    
    //increases all ages by one year
    for (int i = 0 ; i < 4; i++) {
        if (Age_categories[i] != NULL) {
            reader_agec = Age_categories[i];
            while (reader_agec != NULL) {
                reader_agec->age++;
                reader_agec = reader_agec->next;
            }
        }
    }
    
    // goes up age_category for grown children
    // also deletes children with age > 15
    for (int i = 0 ; i < 4; i++) {
        if (Age_categories[i] != NULL) {
            reader_agec = Age_categories[i];
            reader_agec_prev = NULL;
            if (i==0) {
                while (reader_agec != NULL) {
                    if (reader_agec->age > 3) { // Child with age > 3 found
                        
                        if (reader_agec_prev == NULL) {
                            Age_categories[i] = reader_agec->next;
                        }else{
                            reader_agec_prev->next = reader_agec->next;
                        }
                        
                        check(1, reader_agec->cid, reader_agec->age, reader_agec->did, reader_agec->present_choices[0], reader_agec->present_choices[1], reader_agec->present_choices[2]);
                    
                    }
                    if (reader_agec->next == NULL) {break;}
                    reader_agec_prev = reader_agec;
                    reader_agec = reader_agec->next;
                }
            }else if (i==1) {
                while (reader_agec != NULL) {
                    if (reader_agec->age > 7) {
                        
                        if (reader_agec_prev == NULL) {
                            Age_categories[i] = reader_agec->next;
                        }else{
                            reader_agec_prev->next = reader_agec->next;
                        }
                        
                        check(2, reader_agec->cid, reader_agec->age, reader_agec->did, reader_agec->present_choices[0], reader_agec->present_choices[1], reader_agec->present_choices[2]);
                    }
                    if (reader_agec->next == NULL) {break;}
                    reader_agec_prev = reader_agec;
                    reader_agec = reader_agec->next;
                }
            }else if (i==2) {
                while (reader_agec != NULL) {
                    if (reader_agec->age > 11) {
                        
                        if (reader_agec_prev == NULL) {
                            Age_categories[i] = reader_agec->next;
                        }else{
                            reader_agec_prev->next = reader_agec->next;
                        }
                        
                        check(3, reader_agec->cid, reader_agec->age, reader_agec->did, reader_agec->present_choices[0], reader_agec->present_choices[1], reader_agec->present_choices[2]);
                        
                    }
                    if (reader_agec->next == NULL) {break;}
                    reader_agec_prev = reader_agec;
                    reader_agec = reader_agec->next;
                }
            }else if (i==3) {
                while (reader_agec != NULL) {
                    if (reader_agec->age > 15) {
                        
                        // child with age > 15 is deleted from list
                        if (reader_agec_prev == NULL) {
                           
                            Age_categories[i] = reader_agec->next;
                            
                        }else{
                           
                            reader_agec_prev->next = reader_agec->next;
            
                        }
                        
                    }
                    
                    if (reader_agec->next == NULL) {break;}
                    reader_agec_prev = reader_agec;
                    reader_agec = reader_agec->next;
                    
                }
            }
        }
    }

    // Clears all districts
    struct district* districts = district_head;

    while (districts != NULL) {
        districts->assignL = NULL;
        districts = districts->next;
    }
    
    // Clears present_list
    if (stock_list != NULL) {
        struct present *reader_present = stock_list;
        
        while (reader_present->pid != -1) {
            
            if (reader_present->stock_cnt == 0) {
                
                if (reader_present->next->pid != -1 && reader_present->prev->pid != -1) {
                    
                    reader_present->prev->next = reader_present->next;
                    reader_present->next->prev = reader_present->prev;
                    
                }else if(reader_present->prev->pid == -1 && reader_present->next->pid != -1){
                    
                    stock_sentinel->prev = reader_present->next;
                    reader_present->next->prev = stock_sentinel;
                    stock_list = reader_present->next;
                    
                }else if(reader_present->next->pid != -1 && reader_present->prev->pid == -1){
                    
                    stock_sentinel->next = reader_present->prev;
                    reader_present->prev->next = stock_sentinel;
                    stock_list = reader_present->prev;
                    
                }else if(reader_present->next->pid == -1 && reader_present->prev->pid == -1){
                    
                    stock_sentinel->next = NULL;
                    stock_sentinel->prev = NULL;
                    stock_list = NULL;
                    
                }
                
            }else{
                
                reader_present->stock_cnt = 0 ;
                
            }
            reader_present = reader_present->next;
        }
    }else{
        printf("Present_list already empty\n");
    }
    
    ///////////////////////////
    for (int i = 0 ; i < 4; i++) {
        if (Age_categories[i] != NULL) {
            reader_agec = Age_categories[i];
            while (reader_agec != NULL) {
                
                reader_agec->present_choices[0]=0;
                reader_agec->present_choices[1]=0;
                reader_agec->present_choices[2]=0;
                
                reader_agec = reader_agec->next;
            }
        }
    }
    
    printf("N\n\nDONE\n\n");

    return 1;
}


/*///////////////////////////////
 reader->present_choices[0] = 0;
 reader->present_choices[1] = 0;
 reader->present_choices[2] = 0;
 
 ///////////////////////////////////////////
 struct district* districts = district_head;
 struct present_assign* ass  = NULL;
 struct present_assign* ass_prev = NULL;
 
 while (districts != NULL) {
 if (districts->did == reader->did) {
    ass = districts->assignL;
    while (ass != NULL) {
        if (ass->cid == reader->cid) {
            if (ass_prev == NULL) {
                districts->assignL = ass->next;
            }else{
                ass_prev = ass->next;
            }
        }
        ass_prev = ass;
        ass = ass->next;
    }
 }
 districts = districts->next;
 }
 
 ////////////////////////////////////
 struct present *present_reader = stock_list;
 
 while (present_reader->pid != -1) {
 if (present_reader->pid == reader->) {
 
 }
 present_reader = present_reader->next;
 }
 
 
 ////////////////////////////////////*/