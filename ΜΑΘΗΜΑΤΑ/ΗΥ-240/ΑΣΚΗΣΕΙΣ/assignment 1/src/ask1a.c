#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int top=0;

//Pushes chars in to the stack
void Push(char stack[],char s){
    
    stack[top]=s;
    top++;
    
}

//Pop chars from stack
char Pop(char stack[50]){
    
    int c=0;
    stack[top]='\0';
    top--;
    return c;
    
}

//Empty stack check
int IsEmptyStack(char stack[50]){
    
    if (stack[top]=='\0') {
        return 1;
    }
    return 0;
}

//Returns what is in the upper box
char Top(char stack[50]) {
    
    return stack[top];
    
}



int main() {
    
    unsigned long helper;
    int i,MasterControl = 0;
    char stackHelper[50],stack[50];
    
    for (i=0; i<50; i++) {
        stackHelper[i]= '\0';
        stack[i]='\0';
    }
    
    printf("Enter an Expression:");
    scanf("%s",stackHelper);
    
    //Tester Output
    printf("string length is:%lu\n",strlen(stackHelper));
    helper=strlen(stackHelper);
    for (i=0; i<helper; i++) {
        if (i!=helper-1) {
            printf("%c-",stackHelper[i]);
        }else{
            printf("%c",stackHelper[i]);
        }
    }
    printf("\n");
    
    
    //Checking wether it is valid or not
    
    for (i=0; i<helper; i++) {
        
        if (stackHelper[i]=='(') {
            
            Push(&stack[50],'('); /**/printf("Push at %d time\n",i);
            
            printf("%d) With word=%c and stack[%d]=%c  .\n\n",i,stackHelper[i],top,Top(&stack[50]));
            
        }
        
        if (stackHelper[i]==')') {
            
            if(Top(&stack[50])=='[') {
                MasterControl = 1;
                printf("1MasterControl=1 the %d time\n",i);
                printf("%d) With word=%c and top=%c \n",i,stackHelper[i],Top(&stack[50]));
            }else if(Top(&stack[50])=='('){
                
                Pop(&stack[50]);/**/printf("Pop at %d time\n",i);
                
                printf("%d) With word=%c and stack[%d]=%c  .\n\n",i,stackHelper[i],top,Top(&stack[50]));
                
            }else{
                
                Push(&stack[50],']');/**/printf("Push at %d time\n",i);
                
                printf("%d) With word=%c and stack[%d]=%c  .\n\n",i,stackHelper[i],top,Top(&stack[50]));
            }
            
        }
        
        if (stackHelper[i]=='[') {
            
            Push(&stack[50],'[');/**/printf("Push at %d time\n",i);
            
            printf("%d) With word=%c and stack[%d]=%c  .\n\n",i,stackHelper[i],top,Top(&stack[50]));
            
        }
        
        if (stackHelper[i]==']') {
            
            if(Top(&stack[50])=='(') {
                MasterControl = 1;
                printf("2MasterControl=1 the %d time\n",i);
                printf("%d) With word=%c and top=%c \n",i,stackHelper[i],Top(&stack[50]));
            }else if(Top(&stack[50])=='['){
                
                Pop(&stack[50]);/**/printf("Pop at %d time\n",i);
                
                printf("%d) With word=%c and stack[%d]=%c  .\n\n",i,stackHelper[i],top,Top(&stack[50]));
                
            }else{
                
                Push(&stack[50],']');/**/printf("Push at %d time\n",i);
                
                printf("%d) With word=%c and stack[%d]=%c  .\n\n",i,stackHelper[i],top,Top(&stack[50]));
            }
            
        }
        
    }
    

    helper=strlen(stackHelper);
    
    for (i=0; i<50; i++) {
        if (i!=50-1) {
            printf("%c-",stack[i]);
        }else{
            printf("%c",stack[i]);
        }
    }
    printf("\n\n");
    //
    
    if (MasterControl==1) {
        printf("The Expression %s is invalid\n",stackHelper);
    }else{
        printf("IsEmptyStack=%d\n",IsEmptyStack(&stack[helper]));
        if (IsEmptyStack(&stack[helper])==1) {
            printf("The Expression %s is valid\n",stackHelper);
        }else{
            printf("The Expression %s is invalid\n",stackHelper);
        }
    }
    return 0;
}