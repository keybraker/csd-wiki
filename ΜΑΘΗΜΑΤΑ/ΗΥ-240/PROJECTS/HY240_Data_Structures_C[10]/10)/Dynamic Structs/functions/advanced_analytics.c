#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

void Sorter(struct district* head){

    while (head != NULL) {

        //if (head->assignL != NULL) {
        //    if (head->assignL->next != NULL) {
                
                struct present_assign* readerM = head->assignL;
                struct present_assign* readerC = NULL;
                struct present_assign* readerC_prev = NULL;
                struct present_assign* help = NULL;
                
                while (readerM != NULL) {
                    readerC = head->assignL;
                    readerC_prev = NULL;
                    while (readerC->next != NULL) {
                        if (readerC->pid > readerC->next->pid) {
                            
                            help = readerC->next;
                            if (readerC_prev != NULL) {
                                readerC_prev->next = help;
                                readerC->next = help->next;
                                help->next = readerC;
                            }else{
                                readerC->next = help->next;
                                help->next = readerC;
                                head->assignL = help;
                                break;
                            }
                            
                        }
                        readerC_prev = readerC;
                        readerC = readerC->next;
                        if (readerC == NULL) {break;}
                    }
                    readerM = readerM->next;
                }
           //}
        //}
        
        head = head->next;
    }
}

int most_famous (struct present_assign* head){
    
    int counterMOST = 0;
    int counterCMP = 0;
    
    int pidMOST = 0;
    int pidCMP = 0;
    
    // count the times of the first present
    pidMOST = head->pid;
    counterMOST++;
    
    if (head->next !=NULL) {
        head = head->next;
    }else{
        return pidMOST;
    }
    while (head->pid == pidMOST) {
        counterMOST++;
        if (head->next != NULL) {
            head = head->next;
        }else{
            return pidMOST;
        }
    }
    // count the rest and compare to pidMOST
    while (head != NULL) {
        ///////////////////////////////////////////
        pidCMP = head->pid;
        counterCMP = 1;
        
        if (head->next != NULL) {
            head = head->next;
        }else{
            if (counterMOST > counterCMP) {
                return pidMOST;
            }else{
                return pidCMP;
            }
        }
        
        while (head->pid == pidCMP) {
            counterCMP++;
            if (head->next != NULL) {
                head = head->next;
            }else{
                if (counterMOST > counterCMP) {
                    return pidMOST;
                }else{
                    return pidCMP;
                }
            }
        }
        if (counterMOST < counterCMP) {
            pidMOST = pidCMP;
        }
        if (head->next != NULL) {
            head = head->next;
        }else{
            return pidMOST;
        }
        ///////////////////////////////////////////
    }
    
    return 1;
}

int advanced_analytics(void) {
    
    struct district* districts = district_head;
    struct present_assign* ass = district_head->assignL;
    
    // Sort is called
    districts = district_head;
    Sorter(districts);
    
    // Super fast search-return-print
    districts = district_head;
    ass = district_head->assignL;
    printf("D\n\n        Districts:\n");
    while (districts != NULL) {
        
        printf("    <%d> : <%d>\n",districts->did,most_famous(districts->assignL));
        districts = districts->next;
    }
    printf("\n\nDONE\n\n");

    return 1;
}

