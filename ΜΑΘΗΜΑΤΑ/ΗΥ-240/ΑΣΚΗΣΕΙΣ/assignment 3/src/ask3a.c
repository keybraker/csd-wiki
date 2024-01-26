#include <stdio.h>
#include <stdlib.h>

struct box {
    int x;
    struct box *next;
};

struct box boxMerge(struct box* a,struct box* b){
    
    struct box *currentnode,*temp;
    a = malloc( sizeof(struct box) );
    b = malloc( sizeof(struct box) );
    currentnode = malloc( sizeof(struct box) );
    
    printf("a->x = %d\n",a->x);
    
    if(a==NULL){
        a=b;
        currentnode=a;
    }else{
        temp = a;
        while(temp->next!=NULL)
        {
            temp = temp->next;
        }
        temp->next = b;
    }
    
    printf("a->x = %d\n",a->x);
    
    int i=0;
    while (a!=NULL) {
        
        printf("a->x = %d\n",a->x);
        a=a->next;
        i++;
        
    }
    
    
    return *a;
    
}


int main() {
    
    int i=0;
    char answer;
    struct box *pointer;
    struct box *heada;
    struct box *headb;
    
    struct box *boxa;
    boxa = malloc( sizeof(struct box) );//printf("%d \n",boxa->x);
    boxa->next=NULL;
    heada = boxa;
    
    struct box *boxb;
    boxb = malloc( sizeof(struct box) );//printf("%d \n",boxb->x);
    boxb->next=NULL;
    headb = boxb;
    
    
    printf("Αdd a node to the first struct (y/n) :");
    scanf("%c",&answer);
    
    while (answer!='n') {
        
        struct box *newBoxa,*currentBoxa,*temp;
        newBoxa = (struct box *)malloc(sizeof(struct box));
        if(newBoxa == NULL){printf("nFailed to Allocate Memory");}
        
        newBoxa->next=NULL;
        printf("Enter data : ");
        scanf("%d",&newBoxa->x);
        
        if(boxa==NULL){
            boxa=newBoxa;
            currentBoxa=newBoxa;
        }else{
            temp = boxa;
            while(temp->next!=NULL)
            {
                temp = temp->next;
            }
            temp->next = newBoxa;
        }
        
        printf("Αdd a node to the first struct (y/n) :");
        scanf("%c",&answer);
        scanf("%c",&answer);
        
        
    }
    
    printf("Αdd a node to the second struct (y/n) :");
    scanf("%c",&answer);
    scanf("%c",&answer);
    
    while (answer!='n') {
        
        struct box *newBoxb,*currentBoxb,*temp2;
        newBoxb = (struct box *)malloc(sizeof(struct box));
        if(newBoxb == NULL){printf("nFailed to Allocate Memory");}
        
        newBoxb->next=NULL;
        printf("Enter data : ");
        scanf("%d",&newBoxb->x);
        
        if(boxb==NULL){
            boxb=newBoxb;
            currentBoxb=newBoxb;
        }else{
            temp2 = boxb;
            while(temp2->next!=NULL)
            {
                temp2 = temp2->next;
            }
            temp2->next = newBoxb;
        }
        
        printf("Αdd a node to the first struct (y/n) :");
        scanf("%c",&answer);
        scanf("%c",&answer);
        
        
    }
    
    
    i=0;
    while (boxa!=NULL || boxb!=NULL) {
        
        printf("boxa is: %d,boxb is: %d\n",boxa->x,boxb->x);
        boxa=boxa->next;
        boxb=boxb->next;
        i++;
        
    }
    
    *pointer = boxMerge(boxa,boxb);
    
    //
    while (pointer!=NULL) {
        printf("Pointer is: %d\n",pointer->x);
        pointer=pointer->next;
    }
    //
    
    return 0;
    
}

