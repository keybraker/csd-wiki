#include <stdio.h>

int main() {
    int i=0,A[10],this = 0;
    for (i=0; i<10; i++) {
        if (i>5) {
            A[i]=INT16_MAX;
        }else{
            A[i]=i;
        }
    }
    /*
     for (i=0; i<10; i++) {
     printf("%d,",A[i]);
     }
     printf("\n");
     */
    for (i=0; i<50; i++) {
        if(A[i+1]==INT16_MAX){
            this = (i+1);
            break;
        }
        i++;
    }
    printf("The last block with a valid number is A[%d].\n", this);
    
    return 0;
}
