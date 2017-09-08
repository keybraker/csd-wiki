#include <stdio.h>

struct list{
    int x;
    struct list *next;
};

int insertionSort(struct list *list){
    
    struct list *help;
    help = malloc( sizeof(struct list) );
    struct list *help2;
    help2 = malloc( sizeof(struct list) );
 
    int i,j,key;
    help=list->next;
    for (j = 2; j <= size; j=j+1) {
        key = help->x;
        help2=help;
        help=help->next;
        
        i=j-1;
        while(i>0 && help2>key){
            help->next->x=help->x;
            i=i-1;
        }
        help->x=key;
    }
    return 0;
}



int main() {

    int i,A[50],*pointer;
    pointer = &A[0];
    
    for(i=0;i<50;i++){
        if (i % 2 == 0) {
            A[i]=((i+(i*i))-2);
        }else{
            A[i]=i;
        }
    }
    
    
    
    //
    printf("[");
    for(i=0;i<50;i++){
        if (i==49) {
            printf("%d",A[i]);
        }else{
            printf("%d,",A[i]);
        }
    }
    printf("]\n\n");
    //
    insertionSort(pointer, 50);
    //
    printf("[");
    for(i=0;i<50;i++){
        if (i==49) {
            printf("%d",A[i]);
        }else{
            printf("%d,",A[i]);
        }
    }
    printf("]\n\n");
    //
    
    return 0;
}
