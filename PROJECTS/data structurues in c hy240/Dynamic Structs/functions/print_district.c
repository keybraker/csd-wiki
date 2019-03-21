#include <stdio.h>
#include <stdlib.h>
#include "../libraries/santa_claus.h"

int print_district(void) {
    
    struct district* districts = district_head;
    struct present_assign* ass;
    
    printf("Ι\n\n    DISTRICT:\n");
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
    
    return 1;
}