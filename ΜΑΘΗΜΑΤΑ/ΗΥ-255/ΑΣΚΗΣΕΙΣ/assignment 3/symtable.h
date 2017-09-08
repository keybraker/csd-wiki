#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
 typedef struct binding {
 char *Key;
 void *Value;
 struct binding *next;
 } binding;
 
 struct SymTable_T {
 struct binding *head;
 };*/

////////////////////////////

typedef struct SymTable_T {
    
    char *Key;
    void *Value;
    struct SymTable_T *next;
    
} SymTable_T;

//Creates new SymTable with no infromation and no bindings
SymTable_T SymTable_new(void){
    
    SymTable_T* new;
    new = (SymTable_T *) malloc (sizeof(SymTable_T));
    new->Key = NULL;
    new->Value = NULL;
    new->next = NULL;
    return *new;
    
}

//¯\_(⊙_ʖ⊙)_/¯
//Frees Symtable it has one node and but '\0' to the one
//that remains after the freeing proccess is over
void SymTable_free( SymTable_T oSymTable ){
    
    assert ( &oSymTable == NULL );
    
    SymTable_T* tmp;
    SymTable_T* in;
    
    in = oSymTable.next;
    
    while (in != NULL){
        
        tmp = in;
        in = in->next;
        free(tmp->Key);
        free(tmp->Value);
        free(tmp);
    }
    
}

//Returns the length of the struct aka the number of bindings
unsigned int SymTable_getLength( SymTable_T oSymTable ){
    
    assert ( &oSymTable == NULL );
    
    SymTable_T* in;
    unsigned int i=0;
    
    in = oSymTable.next;
    
    while (in != NULL){
        
        i++;
        in = in->next;
        
    }
    
    return i;
    
}

//Puts value in binding
int SymTable_put(SymTable_T oSymTable, const char *pcKey,const void *pvValue){
    
    assert(&oSymTable != NULL);
    assert(pcKey != NULL);
    
    /*long size = 0;
     size = strlen(pcKey);*/
    
    SymTable_T* copy;
    copy = oSymTable.next;
    
    while (copy != NULL){
        
        if (copy->Key == pcKey) {
            
            return 0;
            
        }
        
        if (copy->next != NULL) {
            
            copy = copy->next;
            
        }else{
            
            break;
            
        }
        
    }
    
    SymTable_T *newnode;
    newnode = (SymTable_T *) malloc (sizeof(SymTable_T));
    
    newnode->Key = (char*)pcKey;
    newnode->Value = (void*)pvValue;
    newnode->next = NULL ;//dunno if needed
    
    copy->next = newnode ;
    
    return 1;
    
}

//Removes a binding
//Frees one binding if found
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    
    assert(&oSymTable != NULL);
    assert(pcKey != NULL);
    
    SymTable_T* cut;
    cut = &oSymTable;
    
    while (cut != NULL){
        
        if (cut->Key == pcKey) {
            
            free(cut->Value);
            free(cut->Key);
            cut->next = cut->next->next;
            return 1;
            
        }
        
        cut = cut->next;
        
    }
    
    return 0;
    
}

//Returns if Key is found in bindings or not
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    
    assert(&oSymTable != NULL);
    assert(pcKey != NULL);
    
    SymTable_T* cut;
    cut = oSymTable.next;
    
    while (cut != NULL)
    {
        if (cut->Key == pcKey) {
            
            return 1;
            
        }
        
        cut = cut->next;
        
    }
    
    return 0;
    
}

//Returns value of binding with name Key, if found
void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    
    assert(&oSymTable != NULL);
    assert(pcKey != NULL);
    
    SymTable_T* cut;
    cut = oSymTable.next;
    
    while (cut != NULL)
    {
        if (cut->Key == pcKey) {
            
            return cut->Value;
            
        }
        
        cut = cut->next;
        
    }
    
    return NULL;
    
}

//Runs pfApply for all values in the binding
void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra){
    
    assert(&oSymTable != NULL);
    assert(pvExtra != NULL);
    assert(pfApply != NULL);
    
    SymTable_T* map;
    map = &oSymTable;
    
    while (map != NULL){
        
        pfApply((const char*)map->Key,map->Value,(void*)pvExtra);
        map = map->next;
        
    }
    
}





