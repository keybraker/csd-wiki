//
//  main.c
//  dataStruct
//
//  Created by Ioannis Tsiakkas on 21/03/2017.
//  Copyright © 2017 Ioannis Tsiakkas. All rights reserved.
//

#include "../bison_libs/DataStruct.h"

#define TRUE 1
#define FALSE 0

const char* UnionTypeEnumStrings[]   = {"function","variable"};
const char* SymbolTableTypeStrings[] = {"GLOBAL", "LOCAL","FORMAL", "USERFUNC","LIBFUNC"};

ScopeStruct Scopelist = NULL;

void initializeArray(){
    int i;
    for(i = 0; i < HASH_SIZE; i++){
        
        BucketList[i] = NULL;
        ColisionList[i] = NULL;
        
    }
}

/**
*
*This function is called in parser for finding the number of global vars 
*in our proogram. We use this number for the BinaryFile so the stack in the VM 
*knows how much space should allocate for globals.
*
**/

unsigned int totalGlobals(){

    unsigned int total = 0;

     int i = 0;
    
    for(i = 0; i < HASH_SIZE ; i++){
        if(BucketList[i] != NULL){
            SymTableEntry reader = BucketList[i];
            while(reader != NULL){
                if(reader->space == programVar){
                    total++;
                }
                reader = reader->nextList;
            }
            
        }
    }

    return total;

}

/**
 *
 * input:  name, scope, decLine
 * work:   creates key from input
 * return: returns (int) key
 *
 **/
int hashFunction(char *name, int scope){ 
    int output = 0, i = 0;
    unsigned long length = strlen(name);
    
    for(i = 0; i<length; i++){
        output += ( name[i] + i ) * ( scope ) ;
    }
    
    if((output % HASH_SIZE) < 0 ){
        return (output % HASH_SIZE)*(MINUS);
    }else{
        return (output % HASH_SIZE);
    }    
}

/**
 *
 * input:  name
 * work:   checks whether, there is a function
 *         already defined with this name (doesn't throw error)
 * return: TRUE if there is
 *         FALSE if not
 *
 **/
int existsInLibFunc(char *name){

    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;

    while(reader != NULL && reader->scope != 0){ reader = reader->next; }

    if(reader != NULL){

        readerS = reader->firstScope;

        while(readerS != NULL){

            if(readerS->type == LIBFUNC ){

                if(readerS->union_t == variable && strcmp(readerS->value.varVal->name,name) == 0)
                {
                    return TRUE;
                }
                else if(readerS->union_t == function && strcmp(readerS->value.funcVal->name,name) == 0)
                {
                    return TRUE;
                }

            }
            readerS = readerS->nextScope;
        }
    }
    return FALSE;
}

/**
 *
 * input:  name, type, yylineno
 * work:   checks whether shadowing
 *         of libFuncs is about to 
 *         and prevents it  
 * return: TRUE on duplicate find
 *         FALSE else
 *
 **/
int redeclarationLibFunc(char * name,unionType type, int yylineno){ 
    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;

    while(reader != NULL && reader->scope != 0){ reader = reader->next; }

    if(reader != NULL){

        readerS = reader->firstScope;

        while(readerS != NULL){

            if(readerS->type == LIBFUNC ){

                if(readerS->union_t == variable && strcmp(readerS->value.varVal->name,name) == 0)
                {
                    codeIsCorrect = FALSE;
                    printf(a_c_r "Error: (l: %d) %s %s, tries to shadow library function.",yylineno,UnionTypeEnumStrings[type],name);
                    printf(a_c_re "\n");
                    return TRUE;
                }
                else if(readerS->union_t == function && strcmp(readerS->value.funcVal->name,name) == 0)
                {
                    codeIsCorrect = FALSE;
                    printf(a_c_r "Error: (l: %d) %s %s, tries to shadow library function.",yylineno,UnionTypeEnumStrings[type],name);
                    printf(a_c_re "\n");
                    return TRUE;
                }

            }
            readerS = readerS->nextScope;
        }
    }
    return FALSE;
}

/**
*
* input:  name, scope, yylineno
* work:   This function checks for redeclaration of function arguments. 
*         It checks the scope of the arguments and if we hit the same name
*         we check if the arg is active. If it's active we thow an error.
* return: TRUE on redeclaration
*         FALSE else
**/
int formalArgsRedeclaration(char *name, int scope, int yylineno){

    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;

    while(reader != NULL && reader->scope != scope) { reader = reader->next; }

    readerS = reader->firstScope;

    while(readerS != NULL){

        if(readerS->union_t == variable && strcmp(readerS->value.varVal->name,name) == 0){

            if(readerS->type == FORMAL && readerS->isActive == TRUE){

                codeIsCorrect = FALSE;
                printf(a_c_r " Error: (l: %d) Redeclaration of argument '%s' in line: %d ",yylineno,name,yylineno);
                printf(a_c_re "\n");
                return TRUE;

            }

        }

        readerS = readerS->nextScope;
    }

    return FALSE;
}

/**
 *
 * input:  name, type, scopename =, yylineno
 * work:   checks whether there is already a variable or function   
 *         with same name, decleared in the specified scope  
 * return: TRUE if there is
 *         FALSE if not      
 *tsikas
 **/
int notValidAccess(char *name, int scope, int yylineno){ 
    
    //printf("Mpaino gia %s me scope %d\n",name,scope);
    // printf("Arxiko scope = %d\n", scope);

    
    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;
    int currscope = scope;
    int foundFunc = FALSE;
    int foundEqual = FALSE;


    while(currscope > 0){
        while(reader != NULL && reader->scope != currscope){ 
            reader = reader->next; 
        }
        if(reader != NULL && reader->scope == currscope){break;}
        currscope--;
        reader = Scopelist;
    }

    //printf("prev scope of %s line %d is %d\n",name, yylineno, scope);

    while(reader != NULL && reader->scope >= 0){   
        int start = 0;
        readerS = reader->firstScope;

        SymTableEntry foundBucket = NULL;
        SymTableEntry prevBucket = NULL;
         
        while(readerS != NULL){ 
         

            if(readerS->type == USERFUNC && readerS->isActive == TRUE && readerS->value.varVal->scope != 0 && readerS->value.varVal->scope != scope){ foundFunc = TRUE; }

            if(strcmp(readerS->value.varVal->name,name) == 0 && readerS->isActive == TRUE && (readerS->type == LOCAL || readerS->type == FORMAL)){
                foundEqual = TRUE;
            }

            readerS = readerS->nextScope;

        }


        if(foundEqual == TRUE){
            if(foundFunc == FALSE){
                return FALSE; // IS VALID
            }else{

                codeIsCorrect = FALSE;
                printf(a_c_r "  Error: (l: %d) Name '%s', is used in a lesser scope , where there is no access.",yylineno,name);
                printf(a_c_re "\n");         
                printf(a_c_y italic "~ Hint: you can't access variables/functions from other" bold " functions in the same \n        scope");
                printf(bold_re a_c_y italic " declare it again with local or use '::'."); 
                printf(italic_re a_c_re "\n");

                return TRUE; // IS NOT VALID
            }
        }

        reader = reader->next; 

    }

    return FALSE;
}

/**
 *
 * input:  name, type, scopename =, yylineno
 * work:   checks whether there is already a variable or function   
 *         with same name, decleared in the specified scope  
 * return: TRUE if there is
 *         FALSE if not      
 *tsikas
 **/
int lookUpValidFuncCall(char *name, int scope, int yylineno){ 
    
    //printf("Mpaino gia %s lookUpAllScopes\n",name);
    // printf("Arxiko scope = %d\n", scope);
    
    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;
    int currscope = scope;

    while(currscope > 0){
        while(reader != NULL && reader->scope != currscope){ 
            reader = reader->next; 
        }
        if(reader != NULL && reader->scope == currscope){break;}
        currscope--;
        reader = Scopelist;
    }

    // Decreasing scope to get to an outter scope one at a time until scope == 0
    while(reader != NULL && reader->scope >= 0){//} && reader->scope != scope){ 
        
        //printf("reader->scope = %d\n", reader->scope);
        // When current scope is found the flag is set to 
        // TRUE and the search can begin
        


            readerS = reader->firstScope;

            while(readerS != NULL){ 
               // printf("PSAXNO SE SCOPE %d\n", readerS->value.varVal->scope); printf("| %s == %s\n",readerS->value.varVal->name,name );

                if((strcmp(readerS->value.varVal->name,name) == 0)){ 
                    if(readerS->value.varVal->scope < scope && readerS->isActive == 1 && (readerS->type == LOCAL || readerS->type == FORMAL )){
                        // Here the name is found in lesser scope which is false
                        codeIsCorrect = FALSE;
                        printf(a_c_r "  Error: (l: %d) Name '%s', is used in a lesser scope , where there is no access.",yylineno,name);
                        printf(a_c_re "\n");         
                        printf(a_c_y italic "~ Hint: you can't access variables/functions from other" bold " functions in the same \n        scope");
                        printf(bold_re a_c_y italic " declare it again with local or use '::'."); 
                        printf(italic_re a_c_re "\n");
                        return TRUE;
                    }

                }

                readerS = readerS->nextScope;

            }

        

        reader = reader->next; 

    }

    return FALSE;
}

SymTableEntry lookUpBucketDuplicateLocal(char *name, int scope){

    ScopeStruct   reader = Scopelist;
    SymTableEntry readerS;
    int foundFunc = FALSE;
    int foundEqual = FALSE;
    int currscope = scope;

    while(reader != NULL && reader->scope != currscope){
        reader = reader->next;
    }
    
    if(reader != NULL){

       

        readerS = reader->firstScope;

        while(readerS != NULL){
            if(strcmp(readerS->value.varVal->name,name) == 0 && readerS->isActive == TRUE){
                    return readerS;
            }
            readerS = readerS->nextScope;
        }
    }

    return NULL;

}

/**
 *
 * input:  name, BucketHash 
 * work:   checks whether there is already a variable or function   
 *         with same name, decleared in the specified hash of the
 *         BucketList
 * return: TRUE if there is
 *         FALSE if not      
 *
 **/
SymTableEntry lookUpBucketDuplicate(char *name, int scope){ // local rule is boolean , 1 is call from local rule 0 is not.

    ScopeStruct   reader = Scopelist;
    SymTableEntry readerS;
    int foundFunc = FALSE;
    int foundEqual = FALSE;
    int currscope = scope;
    SymTableEntry foundBucket = NULL;

    while(currscope >= 0){
        if(scope > 0) {
            while(reader != NULL && reader->scope != currscope){
                reader = reader->next;
            }
        }
        if(reader != NULL && reader->scope == currscope){break;}
        reader = Scopelist;
        currscope--;
    }

    // if(reader == NULL && localRule == 1) //diladi an exw local x; psaxnw mono sto trexon scope , an einai h prwti fora pou mpainei metabliti ekei epistrefw null amesws.
    //     return NULL;

    if(reader != NULL){
      
        readerS = reader->firstScope;


        if(scope == 0) { 

            return lookUpBucketDuplicateLocal(name,0);

        }else{

            SymTableEntry lookFirstInCurrScope = lookUpBucketDuplicateLocal(name,scope);
            if(lookFirstInCurrScope != NULL)
                return lookFirstInCurrScope;

            while(scope >= 0){

                reader = Scopelist;

                while(reader != NULL && reader->scope != scope){
                    reader = reader->next;
                }

                if(reader != NULL){

                    readerS = reader->firstScope;

                    while(readerS != NULL){

                        if(readerS->type == USERFUNC && readerS->isActive == TRUE)
                            foundFunc = TRUE;

                        if(strcmp(readerS->value.varVal->name,name) == 0 && readerS->isActive == TRUE){
                            if(reader->scope == 0){
                                return readerS;
                            }
                            foundBucket = readerS;
                            foundEqual = TRUE;
                        }

                       // printf("cur name %s\n",readerS->value.varVal->name );

                        readerS = readerS->nextScope;
                    }// end of while readerS != null

                    

                    if( foundFunc == TRUE && foundEqual == FALSE ){// we didnt find var with same name and we found a function. So we insert the var
                        return NULL;
                    } 
                    else if (foundFunc == FALSE && foundEqual == TRUE){ //we found a var with same name but not a function in between, so we dont insert
                        return foundBucket;
                    }
                    
                } // end of if reader != null

                scope--; 

            }//end of while scope > 0
        }


            

    }


    return NULL;
}

/**
 *
 * input:  name, BucketHash 
 * work:   checks whether there is already a variable or function   
 *         with same name, decleared in the specified hash of the
 *         BucketList
 * return: TRUE if there is
 *         FALSE if not      
 *
 **/
SymTableEntry lookUpTemp(char *name, int scope){

    ScopeStruct   reader = Scopelist;
    SymTableEntry readerS;
    int foundFunc = FALSE;
    int foundEqual = FALSE;
    int currscope = scope;
    SymTableEntry foundBucket = NULL;



    while(currscope >= 0){
        if(scope > 0) {
            while(reader != NULL && reader->scope != currscope){
                reader = reader->next;
            }
        }
        if(reader != NULL && reader->scope == currscope){break;}
        reader = Scopelist;
        currscope--;
    }

  

    // if(reader == NULL && localRule == 1) //diladi an exw local x; psaxnw mono sto trexon scope , an einai h prwti fora pou mpainei metabliti ekei epistrefw null amesws.
    //     return NULL;

    if(reader != NULL){
      
        readerS = reader->firstScope;

        if(scope == 0) { 

            return lookUpBucketDuplicateLocal(name,0);

        }else{

             SymTableEntry lookFirstInCurrScope = lookUpBucketDuplicateLocal(name,scope);

            if(lookFirstInCurrScope != NULL)
                return lookFirstInCurrScope;

            while(scope >= 0){

                reader = Scopelist;

                while(reader != NULL && reader->scope != scope){
                    reader = reader->next;
                }

                if(reader != NULL){

                    readerS = reader->firstScope;

                    while(readerS != NULL){

                        if(readerS->type == USERFUNC && readerS->isActive == TRUE)
                            foundFunc = TRUE;

                        if(strcmp(readerS->value.varVal->name,name) == 0 && readerS->isActive == TRUE){
                            if(reader->scope == 0){
                                return readerS;
                            }
                            foundBucket = readerS;
                            foundEqual = TRUE;
                        }

                       // printf("cur name %s\n",readerS->value.varVal->name );

                        readerS = readerS->nextScope;
                    }// end of while readerS != null

                    

                    if( foundFunc == TRUE && foundEqual == FALSE ){// we didnt find var with same name and we found a function. So we insert the var
                        return NULL;
                    } 
                    else if (foundFunc == FALSE && foundEqual == TRUE){ //we found a var with same name but not a function in between, so we dont insert
                        return foundBucket;
                    }
                    
                } // end of if reader != null

                scope--; 

            }//end of while scope > 0
        }


            

    }


    return NULL;
}

SymTableEntry lvalueIsFunction(char *name, int scope){
    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;
    int currscope = scope;


    while(currscope > 0){
        while(reader != NULL && reader->scope != currscope){ 
            reader = reader->next; 
        }
        if(reader != NULL && reader->scope == currscope){break;}
        currscope--;
        reader = Scopelist;
    }

    while(reader != NULL && reader->scope >= 0){   

        readerS = reader->firstScope;

        while(readerS != NULL){ 

            if(strcmp(readerS->value.varVal->name,name) == 0 && readerS->isActive == TRUE && (readerS->type == USERFUNC || readerS->type == LIBFUNC)){
                return readerS;
            }

            readerS = readerS->nextScope;

        }

        

        reader = reader->next; 

    }

    return NULL;
}

/**
 *
 * input:  name, type, scopename =, yylineno
 * work:   checks whether there is already a variable or function   
 *         with same name, decleared in the specified scope  
 * return: TRUE if there is
 *         FALSE if not      
 *tsikas
 **/
int lookUpValidAssignment(char *name, int scope,int yylineno){

    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;
    int currscope = scope;


    while(currscope > 0){
        while(reader != NULL && reader->scope != currscope){ 
            reader = reader->next; 
        }
        if(reader != NULL && reader->scope == currscope){break;}
        currscope--;
        reader = Scopelist;
    }



    while(reader != NULL && reader->scope >= 0){   

        readerS = reader->firstScope;

        while(readerS != NULL){ 

            if(strcmp(readerS->value.varVal->name,name) == 0 && readerS->isActive == TRUE && readerS->type == FORMAL){
                return FALSE;
            }

            if(strcmp(readerS->value.varVal->name,name) == 0 && readerS->isActive == TRUE && readerS->type == USERFUNC){
                codeIsCorrect = FALSE;
                printf(a_c_r "  Error: (l: %d) Assigning value to function '%s', which is in line %d, is forbidden.\n"\
                            ,yylineno,name,readerS->value.varVal->line);
                printf(a_c_re "\n");
                return TRUE;
            }

            readerS = readerS->nextScope;

        }

        

        reader = reader->next; 

    }

    return FALSE;
}



int callExists(char *name , int scope){

    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;

    while(reader != NULL && reader->scope != scope){ 
            reader = reader->next; 
    }

    if(reader != NULL){
        readerS = reader->firstScope;
        while(readerS != NULL){
            if(readerS->union_t == function && strcmp(readerS->value.funcVal->name,name) == 0 && readerS->isActive == TRUE){ return TRUE ; }
            if(readerS->union_t == variable && strcmp(readerS->value.varVal->name,name) == 0 && readerS->isActive == TRUE){ return TRUE ; }
            readerS = readerS->nextScope;
        }
    }
    return FALSE;
}

/**
 *
 * input:  name, type, scopename =, yylineno
 * work:   checks whether there is already a variable or function   
 *         with same name, decleared in the specified scope  
 * return: TRUE if there is
 *         FALSE if not      
 *
 **/
int lookUpScopeRedeclaration(char *name, unionType type, int scope, int yylineno, RuleEnum rule){

    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;

    while(reader != NULL && reader->scope != scope){ reader = reader->next; }

    if(reader == NULL && type != function && scope-1 >= 0){
        reader = Scopelist;
        while(reader != NULL && reader->scope != scope-1){ reader = reader->next; }    
    }

    if(reader != NULL){

        readerS = reader->firstScope;

        while(readerS != NULL){

            if(type == function){

                    if(strcmp(readerS->value.funcVal->name,name) == 0 && readerS->union_t == function){

                        codeIsCorrect = FALSE;
                        printf(a_c_r "  Error: (l: %d) Redeclaration of '%s' as %s, but it has already been\n         decleared as %s "\
                            ,yylineno,name,UnionTypeEnumStrings[type],UnionTypeEnumStrings[readerS->union_t]);
                        printf("at line %d.",readerS->value.funcVal->line);                    
                        printf(a_c_re "\n");
                        return TRUE ;

                    }else if(strcmp(readerS->value.funcVal->name,name) == 0 && readerS->union_t == variable){

                        codeIsCorrect = FALSE;
                        printf(a_c_r "  Error: (l: %d) Redeclaration of '%s' as %s, but it has already been\n         decleared as %s "\
                            ,yylineno,name,UnionTypeEnumStrings[type],UnionTypeEnumStrings[readerS->union_t]);
                        printf("at line %d.",readerS->value.funcVal->line);                    
                        printf(a_c_re "\n");
                        return TRUE ;
                    }

            }else if(type == variable){

                if(strcmp(readerS->value.varVal->name,name) == 0 && readerS->union_t == function){

                    if(rule == AssignExpr){

                        codeIsCorrect = FALSE;
                        printf(a_c_r "  Error: (l: %d) Assigning value to function '%s', which is in line %d, is forbidden.\n"\
                            ,yylineno,name,readerS->value.varVal->line);
                        printf(a_c_re "\n");

                    }else if(rule == Primary){

                        codeIsCorrect = FALSE;
                        printf(a_c_r "  Error: (l: %d) Redeclaration of '%s' as %s, but it has already been\n         decleared as %s "\
                            ,yylineno,name,UnionTypeEnumStrings[type],UnionTypeEnumStrings[readerS->union_t]);
                        printf("at line %d.",readerS->value.funcVal->line);                    
                        printf(a_c_re "\n");

                    }
                    return TRUE;
                }

            }
            readerS = readerS->nextScope;
        }
    }
    return FALSE;
}

/**
 *
 * input:  name, yylineno
 * work:   checks whether, there is a variable or function, already
 *         defined on global (a.k.a scope 0)
 * return: TRUE if there is
 *         FALSE if not
 *
 **/
int LookUpGlobalScope(char *name){ 

    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;

    while(reader != NULL && reader->scope != 0){ reader = reader->next; }

    if(reader != NULL){

        readerS = reader->firstScope;

        while(readerS != NULL){

            if(readerS->union_t == variable && strcmp(readerS->value.varVal->name,name) == 0) { return TRUE;  }
            else if(readerS->union_t == function && strcmp(readerS->value.funcVal->name,name) == 0) { return TRUE; }
            
            readerS = readerS->nextScope;
        }
    }

    return FALSE;
}

/**
 *
 * input:  name, yylineno
 * work:   checks whether, there is a variable or function, already
 *         defined on global (a.k.a scope 0)
 * return: TRUE if there is
 *         FALSE if not
 *
 **/
SymTableEntry LookUpGlobal(char *name, int yylineno){ 

    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;

    while(reader != NULL && reader->scope != 0){ reader = reader->next; }

    if(reader != NULL){

        readerS = reader->firstScope;

        while(readerS != NULL){

            if(readerS->union_t == variable && strcmp(readerS->value.varVal->name,name) == 0) { return readerS;  }
            else if(readerS->union_t == function && strcmp(readerS->value.funcVal->name,name) == 0) { return readerS; }
            
            readerS = readerS->nextScope;
        }
    }

    codeIsCorrect = FALSE;
    printf(a_c_r "  Error: (l: %d) Variable %s, undefined in global Scope.\n", yylineno,name);
    printf(a_c_y italic "~ Hint: if using \'::\', only " bold "global" bold_re a_c_y italic" variables or functions can be accessed.");
    printf(italic_re a_c_re "\n");
    return NULL;
}


int formalArgsLibFuncShadow(char *name, int yylineno){

    ScopeStruct reader = Scopelist;
    SymTableEntry readerS;

    while(reader != NULL && reader->scope != 0){ reader = reader->next; }

    if(reader != NULL){

        readerS = reader->firstScope;

        while(readerS != NULL){

            if(readerS->type == LIBFUNC ){

                if(readerS->union_t == variable && strcmp(readerS->value.varVal->name,name) == 0) { 
                    
                    codeIsCorrect = FALSE;
                    printf(a_c_r "  Error: (l: %d) formal argument %s, tries to shadow LIBFUNC.",yylineno,name);
                        printf(a_c_re "\n");
                    return TRUE;  
                }
                else if(readerS->union_t == function && strcmp(readerS->value.funcVal->name,name) == 0) {
                    
                    codeIsCorrect = FALSE;
                    printf(a_c_r "  Error: (l: %d) formal argument %s, tries to shadow LIBFUNC.",yylineno,name);
                        printf(a_c_re "\n");
                 return TRUE; 
                }
            }
            readerS = readerS->nextScope;
        }
    }

    return FALSE;
}

/**
 *
 * input:  scope
 * work:   changes the activity of the whole scope 
 *         from 0 to 1 and 
 *         from 1 to 0 
 * return: TRUE on success
 *         FALSE on failure
 *
 **/
int changeActivity(int Scope){

    if(Scope == 0)
        return TRUE ;


    ScopeStruct readerS = Scopelist;
    SymTableEntry readerSS = NULL;

    while(readerS != NULL && readerS->scope != Scope){ readerS = readerS->next; }

    if(readerS != NULL)
        readerSS = readerS->firstScope ;

    while(readerSS != NULL){
        
        //if(readerSS->isActive == 0){readerSS->isActive = 1;}
        //else{readerSS->isActive = 0;}

        readerSS->isActive = FALSE;

        readerSS = readerSS->nextScope;

    }

    return FALSE;
}

//*****************************************

/**
 *
 * input:  placement, value
 * work:   creates a new bucket
 * return: the new struct
 *
 **/
SymTableEntry newBucket(char *name, enum UnionTypeEnum union_t,  SymbolTableType type, int scope, int decLine, scopespace_t scopespace, unsigned int offset){
    
    SymTableEntry node = (SymTableEntry)malloc(sizeof (struct SymbolTableEntry));
    
    node->isActive = 1;
    node->type = type;
    node->union_t = union_t;

    node->space = scopespace;
    node->offset = offset;
    
    if(union_t == variable){
        
        node->value.varVal = (Variable*)malloc(sizeof(struct Variable));
        
        node->value.varVal->name = name;
        node->value.varVal->scope = scope;
        node->value.varVal->line = decLine;
    
        
    }else{
        
        node->value.funcVal = (Function*)malloc(sizeof(struct Function));
        
        node->value.funcVal->name = name;
        node->value.funcVal->scope = scope;
        node->value.funcVal->line = decLine;
        
        node->value.funcVal->returnList = NULL;
    }
    
    node->nextList = NULL;
    node->nextScope = NULL;

    return node;
}

/**
 *
 * input:  int & struct
 * work:   connects the new node to scopeList
 * return: 1 on success, 0 on failure
 *
 **/
int scopeConnect(int isFirst, int scope, SymTableEntry newEntry){

    if(isFirst == 1){
        
        if(Scopelist == NULL){

            //otan o scopelist einai kenos kai to proto stoixeio tou possition sto bucketlist
            
            ScopeStruct newnode = (ScopeStruct)malloc(sizeof(struct ScopeStruct));
            newnode->scope = scope;
            newnode->firstScope=newEntry;
            newnode->lastScope=newEntry;
            newnode->next=NULL;
            Scopelist = newnode;
        
        }else{

            //diatrexoume mexri na broume to scope an uparxei
            ScopeStruct reader = Scopelist;
            while(reader != NULL && reader->scope != scope){
                
                reader = reader -> next;
            
            }
            
            if(reader != NULL){
                
                // uparxei to scope
                
                reader->lastScope->nextScope = newEntry;
                reader->lastScope = newEntry;
                
            }else{
                
                //otan to scope auto den uparxei
                
                ScopeStruct newnode = (ScopeStruct)malloc(sizeof(struct ScopeStruct));
                newnode->scope = scope;
                newnode->next = Scopelist;
                newnode->firstScope = newEntry;
                newnode->lastScope = newEntry;
                Scopelist = newnode;
                
            }
            
        }
        
    }else{
        
        if(Scopelist == NULL){
            
            codeIsCorrect = FALSE;
            return 0; //error giati upoti8etai oti o scopelist exei arxikopoii8ei idi
       
        }else{

            ScopeStruct reader = Scopelist;
            while(reader != NULL && reader->scope != scope){
                
                reader = reader -> next;
                
            }
            
            if(reader != NULL){
                
                // uparxei to scope
                
                reader->lastScope->nextScope = newEntry;
                reader->lastScope = newEntry;
                
            }else{
                
                //otan to scope auto den uparxei
                
                ScopeStruct newnode = (ScopeStruct)malloc(sizeof(struct ScopeStruct));
                newnode->scope = scope;
                newnode->next = Scopelist;
                newnode->firstScope = newEntry;
                newnode->lastScope = newEntry;
                Scopelist = newnode;
                
            }
            
            
        }
        
    }
    
    return 1;
}

/**
 *
 * input:  name, 
 * work:   Does hash the name to the struct
 * return: 1 on success, 0 on failure
 *
 **/
SymTableEntry insert(char *name, enum UnionTypeEnum union_t, SymbolTableType type, int scope, int decLine, int fromLocalRule, scopespace_t scopespace, unsigned int offset){
    
    int hash = hashFunction(name, scope);
    SymTableEntry sym = NULL;

         
    
    if(BucketList[hash] == NULL){
        

       /* printf("(1) The hash for %d is empty\n", hash);
        printf("    Creating bucket and inserting %s.\n\n", name);*/

        if(fromLocalRule == 1){
            sym = lookUpBucketDuplicateLocal( name, scope );
        }else{
            sym = lookUpBucketDuplicate( name, scope );
        }

        if(sym == NULL){ 

            sym = newBucket(name, union_t,  type, scope , decLine, scopespace, offset);
        	BucketList[hash] = sym;
        	scopeConnect(1, scope, BucketList[hash]);

        }
        
        
    }else{
        
        SymTableEntry reader = BucketList[hash];
        SymTableEntry readerPrev = NULL;
        
        while(reader != NULL){
            readerPrev = reader;
            reader = reader->nextList;
        }

        if(fromLocalRule == 1){
            sym = lookUpBucketDuplicateLocal( name, scope );
        }else{
            sym = lookUpBucketDuplicate( name, scope );
        }
        
        if(sym == NULL){
            //printf("%s with line %d\n",name,decLine );
            sym =  newBucket(name, union_t,  type, scope , decLine, scopespace, offset);
        	readerPrev->nextList = sym;
            ColisionList[hash] = readerPrev->nextList;  // collision list is always up-to-date
                                                        // with the latest collision occured
        	scopeConnect(0, scope, readerPrev->nextList);

        }


    }
    
    return sym; 
}

/**
 *
 * input:  -
 * work:   prints the whole struct
 * return: -
 *
 **/
void printWholeStruct(){
    
    int i = 1;
    
    for(i = 0; i < HASH_SIZE ; i++){
        if(BucketList[i] != NULL){
            SymTableEntry reader = BucketList[i];
            while(reader != NULL){
                if(reader->union_t == variable){
                    printScopeVar(reader)
                }else{
                    printScopeFunc(reader) //define
                }
                reader = reader->nextList;
            }
            
        }
    }
    
    printf("--------------------------------------------\n\n");
    
    ScopeStruct readerS = Scopelist;
    SymTableEntry readerSS;
    
    while(readerS != NULL){
        printf("\nSCOPE: %d\n",readerS->scope);
        
        readerSS = readerS->firstScope;
        
        while(readerSS != NULL){
            
            if(readerSS->union_t == variable){
                printVar(readerSS)
            }else{
                printFunc(readerSS)
            }
            readerSS = readerSS->nextScope;
            
        }
        readerS = readerS->next;
        
    }
    
    printf("========================================\n\n");
}


 
