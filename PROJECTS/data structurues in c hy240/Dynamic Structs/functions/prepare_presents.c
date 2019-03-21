#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

struct district* district_head = NULL;

void PrinDistricts(){
    
    struct district* districts = district_head;
    struct present_assign* ass;
    
    printf("P\n\n    DISTRICT:\n");
    while (districts != NULL) {
        printf("\n    <%d>\n       ASSIGNMENT: ",districts->did);
        ass = districts->assignL;
        while (ass != NULL) {
            printf("<%d, %d>, ",ass->cid,ass->pid);
            ass = ass->next;
        }
        districts = districts->next;
    }
    printf("\n\nDONE\n\n");
}

int givePresent(struct child *kids){

    if (stock_list != NULL) {
        struct present *reader = stock_list;
        
        while (reader->pid != -1) { // runs until end of list
            
            if (kids->present_choices[0] == reader->pid){
                // if present is found
                if (reader->stock_cnt > 0) { // and stock is
                    reader->stock_cnt--;
                    return reader->pid;
                }
            }
            reader = reader->next;
        }
        while (reader->pid != -1) { // runs until end of list
            if (kids->present_choices[1] == reader->pid){
                // if present is found
                if (reader->stock_cnt > 0) { // and stock is
                    reader->stock_cnt--;
                    return reader->pid;
                }
            }
            reader = reader->next;
        }
        while (reader->pid != -1) { // runs until end of list
            if (kids->present_choices[2] == reader->pid){
                // if present is found
                if (reader->stock_cnt > 0) { // and stock is
                    reader->stock_cnt--;
                    return reader->pid;
                }
            }
            reader = reader->next;
        }
    }else{
        printf("P   No presents in stock, will get (-2)\n");
    }
    return (-2);
}

int prepare_presents(void) {

    int found = 0;
    
    struct district* district_list = district_head;
    struct district* district_prev = NULL;
    struct child* reader;
    
    for (int i = 0 ; i < 4; i++) {
        if (Age_categories[i] != NULL) {
            
            reader = Age_categories[i]; // helper *node reader that gets value of front o struct
            
            found = 0;
            
            while (reader != NULL) {

                if (district_head == NULL) {
                    
                    struct district* newDistrict = (struct district *)malloc(sizeof(struct district));
                    
                    newDistrict->did = reader->did;
                    newDistrict->next = NULL;
                    
                    struct present_assign* assignLnew = (struct present_assign *)malloc(sizeof(struct present_assign));
                    
                    assignLnew->cid = reader->cid;
                    if (givePresent(reader) != -2) {
                        assignLnew->pid = givePresent(reader);
                    }
                    assignLnew->next = NULL;
                    
                    newDistrict->assignL = assignLnew;
                    
                    district_head = newDistrict;
                    district_list = district_head;
                    
                }else{
                
                    found = 0;
                    while (district_list != NULL) {
                        
                        if (district_list->did == reader->did) {
                            
                            struct present_assign* assignLnew = (struct present_assign *)malloc(sizeof(struct present_assign));

                            assignLnew->cid = reader->cid;
                            if (givePresent(reader) != -2) {
                                assignLnew->pid = givePresent(reader);
                            }

                            assignLnew->next = district_list->assignL;
                            district_list->assignL = assignLnew;

                            found = 1; // dont know if good programming technique
                        }
                        
                        district_prev = district_list;
                        district_list = district_list->next;
                        
                    }
                    if (found == 0) {
                        
                        struct district* newDistrict = (struct district *)malloc(sizeof(struct district));
                        
                        newDistrict->did = reader->did;
                        newDistrict->next = NULL;
                        
                        struct present_assign* assignLnew = (struct present_assign *)malloc(sizeof(struct present_assign));
                        
                        assignLnew->cid = reader->cid;
                        if (givePresent(reader) != -2) {
                            assignLnew->pid = givePresent(reader);
                        }
                        assignLnew->next = NULL;

                        newDistrict->assignL = assignLnew;
                        district_prev->next = newDistrict;

                    }
                    
                }
                reader = reader->next;
                district_list = district_head;
                district_prev = NULL;
            }
        }
    }
    PrinDistricts();
    return 1;
}
