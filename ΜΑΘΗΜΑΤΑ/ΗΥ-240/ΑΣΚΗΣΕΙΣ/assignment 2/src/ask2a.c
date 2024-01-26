#include <stdio.h>

struct list {
    int x;
    struct list *next;
};

int main() {
    
    
    struct list *old,*new,*temp,*tzoker,*add;
    old = malloc( sizeof(struct list) );
    new = malloc( sizeof(struct list) );
    temp = malloc( sizeof(struct list) );
    tzoker = malloc( sizeof(struct list) );
    
    if(old!=NULL){
        temp=old;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        new->x=temp->x;
        tzoker=temp;
        temp=old;
        while(temp!=tzoker){
            while (temp->next!=tzoker) {
                temp=temp->next;
            }
            new->x=temp->x;
            tzoker=temp;
            temp=old;
        }
    }
    return 0;
}
