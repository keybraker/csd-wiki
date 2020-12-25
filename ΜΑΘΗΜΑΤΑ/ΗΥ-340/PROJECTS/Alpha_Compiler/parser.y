%{
    #include "../Alpha_Compiler/bison/bison_libs/DataStruct.h"
    #include "../Alpha_Compiler/TargetCode/phase4.h"

    #define ANSI_COLOR_RED     "\x1b[31m"
    #define ANSI_COLOR_GREEN   "\x1b[32m"
    #define ANSI_COLOR_RESET   "\x1b[0m"

    typedef enum{ INCREASE , DECREASE }scopeAction;
    typedef enum State State;

    enum State{ S_IF, S_LOOP, S_FUNCTION, S_BLOCK};

    char* getStringValueQuad(expr* e,int isResult);

    char* opcodeToString[] = {
                                "ASSIGN",         "ADD",            "SUB",
                                "MUL",            "DIV",            "MOD", 
                                "jump",           "if_eq",          "if_noteq",
                                "if_lesseq",      "if_greatereq",   "if_less",
                                "if_greater",     "call",           "param",
                                "funcstart",      "funcend",        "tablecreate",    
                                "tablegetelem",   "tablesetelem",   "getretval",
                                "no_op",          "ret"
                            };

    char* vmopcodeToString[] = {
                                    "assign_v",       "add_v",              "sub_v",
                                    "mul_v",          "div_v",              "mod_v",
                                    "jump_v",         "jeq_v",              "jne_v",
                                    "jle_v",          "jge_v",              "jlt_v",
                                    "jgt_v",          "call_v",             "pusharg_v",  
                                    "funcenter_v",    "funcexit_v",         "newtable_v",
                                    "tablegetelem_v", "tablesetelem_v",     "nop_v"
                               };

    char* vmarg_tToString[] = {

        "label",      
        "global",    
        "formal",    
        "local",     
        "number",    
        "string",    
        "bool",      
        "nil",       
        "userfunc",  
        "libfunc",   
        "retval"    

    };

    int yylex(void);
    int yyerror(char* yaccProvidedMessage);
    void ScopeOperations(scopeAction action);
    int numberDigits(int num);
    
    char* getEnumString(int id);
    char* giveName();
    int getCurrentLine();
    void myprint(char* msg,int line);
    void printAllQuads();
    
    int codeIsCorrect = 1;
    int mustDecrease = 0;
    int mustIncrease = 0;

    int funcdefStart = 0 ;
    int Scope = 0 ;

    int namelessFunctionNumber = 0;

    int openedFunctions = 0;
    int openedLoops = 0;

    State prevState;

    int GlobalRuleManage = 0;
    int LocalRuleManage = 0;
    int GlobalBeforeEqual = 0;
    int LocalBeforeEqual = 0;
    int PrimaryRuleManage = 0;
    int MemberManageRule = 0;
    int MemberBeforeEqual = 0;
    int EqualFound = 0;

    int accessIsValid = 0;

    int notRulePassed = 0;

    int totalFuncArgs = 0;


    extern FILE* yyin;
    extern FILE* yyout;
    extern char* yytext;
    extern int yylineno;
%}

%union{
    int intVal;
    struct SymbolTableEntry *symbol;
    char* strVal;
    double numVal;
    struct expr *exprVal; // struct needed with no reason
    struct method_call *method_call ;
    struct forLoopStruct *forLoopVal;
    struct loopStack* loopStack;
}

%start program

%token<numVal> NUMBER
%token<strVal> IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR local TRUE FALSE NIL STRING ID
%token<strVal> equal plus minus mul divide percent equalequal notequal plusplus minusminus greater lesser 
%token<strVal> greaterequal lesserequal openblock closeblock openbracket closebracket openpar closepar semicolon comma 
%token<strVal> colon coloncolon dot dotdot UMINUS 

%type<strVal>  funcName
%type<strVal> block whilestmt forstmt   

%type<method_call> callsuffix normcall  methodcall
%type<forLoopVal> forprefix
%type<symbol> FuncPrefix funcdef funcPefixAndArgs
%type<intVal> ifprefix funcBody elseprefix ifstmt whilestart whilecond N M idlist
%type<exprVal>  expr const primary term assignexpr lvalue member indexedelem indexed objectdef elist call returnstmt stmt
%type<loopStack>  loopstmt


%right      equal
%left       OR
%left       AND
%nonassoc   equalequal notequal
%nonassoc   greater greaterequal lesser lesserequal
%left       plus minus
%left       mul divide percent
%right      NOT plusplus minusminus UMINUS
%left       dot dotdot
%left       openbracket closebracket
%left       openpar closepar

%%

program:        stmtlist                    {myprint("program",-1);}
                ;

stmtlist:       stmtlist stmt               {myprint("stmtlist stmt",getCurrentLine());}
                |
                ;

stmt:           expr semicolon              {
                                                $$ = $1;

                                                if($1->type == boolexpr_e || $1->cameFromNot == 1){

                                                    $1->sym = newTemp(Scope);
                                                    backPatchList($1->truelist,nextQuadLabel());
                                                    emit(ASSIGN,newexpr_constBool('1'),NULL,$1,nextQuadLabel(),getCurrentLine());
                                                    emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                                    backPatchList($1->falselist,nextQuadLabel());
                                                    emit(ASSIGN,newexpr_constBool('0'),NULL,$1,nextQuadLabel(),getCurrentLine());

                                                } 
                                                resetTemp(); 
                                                myprint("expr;",-1);
                                            }
                |ifstmt                     {$$ = $<exprVal>1; myprint("ifstmt",-1); resetTemp();}
                |whilestmt                  {$$ = $<exprVal>1; myprint("whilestmt",-1); resetTemp();}
                |forstmt                    {$$ = $<exprVal>1; myprint("forstmt",-1); resetTemp();}
                |returnstmt                 {$$ = $1; myprint("returnstmt",-1); resetTemp();}
                |BREAK semicolon            {
                                                if(openedLoops == 0){
                                                    codeIsCorrect = FALSE;
                                                    printf(a_c_r "  Error: (l: %d) Use of break outside of loop.\n" a_c_re ,getCurrentLine()); 
                                                }
                                                else{
                                                    breakPush(nextQuadLabel());
                                                    emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
                                                }
                                                resetTemp();
                                                myprint("BREAK semicolon",-1);
                                            }
                |CONTINUE semicolon         {
                                                if(openedLoops == 0){
                                                    codeIsCorrect = FALSE;
                                                    printf(a_c_r "  Error: (l: %d) Use of continue outside of loop.\n" a_c_re ,getCurrentLine()); 
                                                }
                                                else{
                                                    contPush(nextQuadLabel());
                                                    emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
                                                }
                                                resetTemp();
                                                myprint("CONTINUE semicolon",-1);
                                            }
                |block                      {$$ = $<exprVal>1; myprint("block",-1); resetTemp();}
                |funcdef                    {$$ = $<exprVal>1; myprint("funcdef",-1); resetTemp();}
                |semicolon                  {myprint("semicolon",-1); resetTemp();}
                ; 

expr:           assignexpr                  {$<exprVal>$ = $1; myprint("assign expression",-1);}
                |expr plus expr             {
                                                SymTableEntry sym = newTemp(Scope);
                                                $<exprVal>$ = lvalue_expr(sym);
                                                emit(ADD,$1,$3,$$,nextQuadLabel(),getCurrentLine());
                                                myprint("expr + expr",getCurrentLine());

                                            }
                |expr minus expr            {
                                                SymTableEntry sym = newTemp(Scope);

                                                $<exprVal>$ = lvalue_expr(sym);
                                                emit(SUB,$1,$3,$$,nextQuadLabel(),getCurrentLine());
                                                myprint("expr - expr",getCurrentLine());
                                            }   
                |expr mul expr              {
                                                SymTableEntry sym = newTemp(Scope);

                                                $<exprVal>$ = lvalue_expr(sym);
                                                emit(MUL,$1,$3,$$,nextQuadLabel(),getCurrentLine());
                                                myprint("expr * expr",getCurrentLine());
                                            }
                |expr divide expr           {
                                                SymTableEntry sym = newTemp(Scope);

                                                $<exprVal>$ = lvalue_expr(sym);
                                                emit(DIV,$1,$3,$$,nextQuadLabel(),getCurrentLine());
                                                myprint("expr / expr",getCurrentLine());
                                            }
                
                |expr percent expr          {
                                                SymTableEntry sym = newTemp(Scope);

                                                $<exprVal>$ = lvalue_expr(sym);
                                                emit(MOD,$1,$3,$$,nextQuadLabel(),getCurrentLine());
                                                myprint("expr % expr",getCurrentLine());
                                            } 

                // apo edo kai pera meriki apotimisi



                |expr greater expr          {
                                                $<exprVal>$ = newexpr(boolexpr_e);
                                                $$->truelist = makelist(nextQuadLabel());
                                                $$->falselist = makelist(nextQuadLabel()+1);
                                                emit(if_greater,$1,$3,NULL,nextQuadLabel(),getCurrentLine());
                                                emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
                                                myprint("expr > expr",getCurrentLine());
                                            }
                |expr greaterequal expr     {
                                                $<exprVal>$ = newexpr(boolexpr_e);
                                                $$->truelist = makelist(nextQuadLabel());
                                                $$->falselist = makelist(nextQuadLabel()+1);
                                                emit(if_greatereq,$1,$3,NULL,nextQuadLabel(),getCurrentLine());
                                                emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
                                                myprint("expr >= expr",getCurrentLine());
                                            }
                |expr lesser expr           { 
                                                $<exprVal>$ = newexpr(boolexpr_e);
                                                $$->truelist = makelist(nextQuadLabel());
                                                $$->falselist = makelist(nextQuadLabel()+1);
                                                emit(if_less,$1,$3,NULL,nextQuadLabel(),getCurrentLine());
                                                emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
                                                myprint("expr < expr",getCurrentLine());
                                            }   
                |expr lesserequal expr      {
                                                $<exprVal>$ = newexpr(boolexpr_e);
                                                $$->truelist = makelist(nextQuadLabel());
                                                $$->falselist = makelist(nextQuadLabel()+1);
                                                emit(if_lesseq,$1,$3,NULL,nextQuadLabel(),getCurrentLine());
                                                emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
                                                myprint("expr <= expr",getCurrentLine());
                                            }
                |expr equalequal { checkForEmitEqEq($1,getCurrentLine(),Scope); } expr  {

                                                                        if($4->type == boolexpr_e && $4->cameFromNot == 1){

                                                                            $4->sym = newTemp(Scope);
                                                                            backPatchList($4->truelist,nextQuadLabel());
                                                                            emit(ASSIGN,newexpr_constBool('1'),NULL,$4,nextQuadLabel(),getCurrentLine());
                                                                            emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                                                            backPatchList($4->falselist,nextQuadLabel());
                                                                            emit(ASSIGN,newexpr_constBool('0'),NULL,$4,nextQuadLabel(),getCurrentLine());

                                                                        }

                                                                        $<exprVal>$ = newexpr(boolexpr_e);
                                                                        $$->truelist = makelist(nextQuadLabel());
                                                                        $$->falselist = makelist(nextQuadLabel()+1);
                                                                        emit(if_eq,$1,$4,NULL,nextQuadLabel(),getCurrentLine());
                                                                        emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
                                                                        
                                                                        myprint("expr == expr",getCurrentLine());

                                                                    }
                |expr notequal { checkForEmitNotEq($1,getCurrentLine(),Scope); } expr  {

                                                
                                                                        if($4->type == boolexpr_e && $4->cameFromNot == 1){

                                                                            $4->sym = newTemp(Scope);
                                                                            backPatchList($4->truelist,nextQuadLabel());
                                                                            emit(ASSIGN,newexpr_constBool('1'),NULL,$4,nextQuadLabel(),getCurrentLine());
                                                                            emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                                                            backPatchList($4->falselist,nextQuadLabel());
                                                                            emit(ASSIGN,newexpr_constBool('0'),NULL,$4,nextQuadLabel(),getCurrentLine());

                                                                        }

                                                                        $<exprVal>$ = newexpr(boolexpr_e);
                                                                        $$->truelist = makelist(nextQuadLabel());
                                                                        $$->falselist = makelist(nextQuadLabel()+1);
                                                                        emit(if_noteq,$1,$4,NULL,nextQuadLabel(),getCurrentLine());
                                                                        emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());

                                                                        myprint("expr != expr",getCurrentLine());

                                                                    }
                |expr AND { checkForEmitAND($1,getCurrentLine(),notRulePassed); } M expr  {

                                                                                notRulePassed = 0;
                                                                                $<exprVal>$ = newexpr(boolexpr_e);

                                                                                //typecheck for arguments that are not boolean and create logic lists for them 
                                                                                
                                                                                if($5->type != boolexpr_e){

                                                                                    $5->truelist   = makelist(nextQuadLabel());
                                                                                    $5->falselist  = makelist(nextQuadLabel()+1);
                                                                                    emit(if_eq,newexpr_constBool('1'),$5,NULL,nextQuadLabel(),getCurrentLine());
                                                                                    emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());

                                                                                }
                                                                                
                                                                                if($1->type == boolexpr_e){
                                                                                    backPatchList($1->truelist,$4);
                                                                                }

                                                                                $$->truelist = $5->truelist;
                                                                                $$->falselist = mergeLocicLists($1->falselist,$5->falselist);
                                                                                myprint("expr AND expr",getCurrentLine());
                                                                            }
                |expr OR { checkForEmitOR($1,getCurrentLine(),notRulePassed); } M expr    {   

                                                                                $<exprVal>$ = newexpr(boolexpr_e);

                                                                                //typecheck for arguments that are not boolean and create logic lists for them 

                                                                                if($5->type != boolexpr_e){

                                                                                    $5->truelist   = makelist(nextQuadLabel());
                                                                                    $5->falselist  = makelist(nextQuadLabel()+1);
                                                                                    emit(if_eq,newexpr_constBool('1'),$5,NULL,nextQuadLabel(),getCurrentLine());
                                                                                    emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());

                                                                                }

                                                                                if($1->type == boolexpr_e){

                                                                                    backPatchList($1->falselist,$4);

                                                                                }

                                                                                
                                                                                $$->truelist = mergeLocicLists($1->truelist,$5->truelist);
                                                                                $$->falselist = $5->falselist;
                                                                                notRulePassed = 0;
                                                                                myprint("expr OR expr",getCurrentLine());

                                                                            }
                |term                       {$<exprVal>$ = $1; myprint("term",-1);}
                ;

term:           openpar expr closepar       {
                                                $<exprVal>$ = $2; 
                                                myprint("( expression )",getCurrentLine());
                                            }
                |minus expr %prec UMINUS    {
                                                checkUminus($2);
                                                $<exprVal>$ = newexpr(arithexpr_e);
                                                $$->sym = newTemp(Scope);
                                                emit(MUL,newexpr_constNumber(-1),$2,$$,nextQuadLabel(),getCurrentLine());
                                                myprint("- expression",getCurrentLine());
                                            }
                |NOT expr                   {
                                                // MERIKI !!!!!!!!!!!!!!!!!!!!!

                                                $<exprVal>$ = newexpr(boolexpr_e);
                                                $$->sym = $2->sym;
                                                $$->cameFromNot = 1;

                                                if($2->type != boolexpr_e){
                                                    $$->truelist    =   makelist(nextQuadLabel()+1);
                                                    $$->falselist   =   makelist(nextQuadLabel());
                                                    emit(if_eq,newexpr_constBool('1'),$2,NULL,nextQuadLabel(),getCurrentLine());
                                                    emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
                                                }else{
                                                    $$->truelist = $2->falselist;
                                                    $$->falselist = $2->truelist;
                                                }
                                                myprint("! expression",getCurrentLine());
                                            }
                |plusplus lvalue            {   
                                                char* name = (char*) $2->sym->value.varVal->name;

                                                if(!redeclarationLibFunc(name,variable,getCurrentLine())){
                                                    if(!lookUpValidAssignment(name,Scope,getCurrentLine())){ 

                                                    }
                                                }

                                                if(EqualFound == 1)
                                                    PrimaryRuleManage = 1;
                                                else
                                                    PrimaryRuleManage = 0;

                                                if($2->type == tableitem_e){ 

                                                    $<exprVal>$ = emit_iftableitem($2,nextQuadLabel(),getCurrentLine(),Scope);
                                                    emit(ADD,$<exprVal>$ ,newexpr_constNumber(1),$<exprVal>$ ,nextQuadLabel(),getCurrentLine());
                                                    emit(tablesetelem,$2,$2->index,$<exprVal>$ ,nextQuadLabel(),getCurrentLine());

                                                }else{ 

                                                    emit(ADD,$2,newexpr_constNumber(1),$2,nextQuadLabel(),getCurrentLine());
                                                    $<exprVal>$ = newexpr(arithexpr_e);
                                                    $<exprVal>$->sym = newTemp(Scope);
                                                    emit(ASSIGN,$2,NULL,$$,nextQuadLabel(),getCurrentLine());

                                                }

                                                myprint("++ lvalue",getCurrentLine());
                                            }
                |lvalue plusplus            {
                                                char* name = (char*) $1->sym->value.varVal->name;
                                                
                                                if(!redeclarationLibFunc(name,variable,getCurrentLine())){
                                                    if(!lookUpValidAssignment(name,Scope,getCurrentLine())){ 

                                                    }
                                                }

                                                if(EqualFound == 1)
                                                    PrimaryRuleManage = 1;
                                                else
                                                    PrimaryRuleManage = 0;

                                                $<exprVal>$ = newexpr(var_e);
                                                $<exprVal>$->sym = newTemp(Scope);

                                                if($1->type == tableitem_e){ 

                                                    expr* value = emit_iftableitem($1,nextQuadLabel(),getCurrentLine(),Scope);
                                                    emit(ASSIGN,value,NULL,$$,nextQuadLabel(),getCurrentLine());
                                                    emit(ADD,value,newexpr_constNumber(1),value,nextQuadLabel(),getCurrentLine());
                                                    emit(tablesetelem,$1,$1->index,value,nextQuadLabel(),getCurrentLine());

                                                }else{ 

                                                    emit(ASSIGN,$1,NULL,$$,nextQuadLabel(),getCurrentLine());
                                                    emit(ADD,$1,newexpr_constNumber(1),$1,nextQuadLabel(),getCurrentLine());

                                                }


                                                myprint("lvalue ++",getCurrentLine());
                                            }        
                |minusminus lvalue          {
                                                char* name = (char*) $2->sym->value.varVal->name;

                                                if(!redeclarationLibFunc(name,variable,getCurrentLine())){
                                                    if(!lookUpValidAssignment(name,Scope,getCurrentLine())){ 

                                                    }
                                                }

                                                if(EqualFound == 1)
                                                    PrimaryRuleManage = 1;
                                                else
                                                    PrimaryRuleManage = 0;

                                                if($2->type == tableitem_e){ 

                                                    $<exprVal>$ = emit_iftableitem($2,nextQuadLabel(),getCurrentLine(),Scope);
                                                    emit(SUB,$<exprVal>$ ,newexpr_constNumber(1),$<exprVal>$ ,nextQuadLabel(),getCurrentLine());
                                                    emit(tablesetelem,$2,$2->index,$<exprVal>$ ,nextQuadLabel(),getCurrentLine());

                                                }else{ 

                                                    emit(SUB,$2,newexpr_constNumber(1),$2,nextQuadLabel(),getCurrentLine());
                                                    $<exprVal>$ = newexpr(arithexpr_e);
                                                    $<exprVal>$->sym = newTemp(Scope);
                                                    emit(ASSIGN,$2,NULL,$$,nextQuadLabel(),getCurrentLine());

                                                }


                                                myprint("-- lvalue",getCurrentLine());
                                            }
                |lvalue minusminus          {
                                                char* name = (char*) $1->sym->value.varVal->name;
                                                
                                                if(!redeclarationLibFunc(name,variable,getCurrentLine())){
                                                    if(!lookUpValidAssignment(name,Scope,getCurrentLine())){ 

                                                    }
                                                }

                                                if(EqualFound == 1)
                                                    PrimaryRuleManage = 1;
                                                else
                                                    PrimaryRuleManage = 0;

                                                $<exprVal>$ = newexpr(var_e);
                                                $<exprVal>$->sym = newTemp(Scope);

                                                if($1->type == tableitem_e){ 

                                                    expr* value = emit_iftableitem($1,nextQuadLabel(),getCurrentLine(),Scope);
                                                    emit(ASSIGN,value,NULL,$$,nextQuadLabel(),getCurrentLine());
                                                    emit(SUB,value,newexpr_constNumber(1),value,nextQuadLabel(),getCurrentLine());
                                                    emit(tablesetelem,$1,$1->index,value,nextQuadLabel(),getCurrentLine());

                                                }else{ 

                                                    emit(ASSIGN,$1,NULL,$$,nextQuadLabel(),getCurrentLine());
                                                    emit(SUB,$1,newexpr_constNumber(1),$1,nextQuadLabel(),getCurrentLine());

                                                }

                                                myprint("lvalue --",getCurrentLine());
                                            }
                |primary                    {$<exprVal>$ = $1;  myprint("primary",-1);}
                ;

              

assignexpr:     lvalue equal        {EqualFound = 1;}  expr          
                                    { 
                                        char *var = NULL;

                                        if($4->type == boolexpr_e){
                                            $4->sym = newTemp(Scope);
                                            
                                            backPatchList($4->truelist,nextQuadLabel());
                                            emit(ASSIGN,newexpr_constBool('1'),NULL,$4,nextQuadLabel(),getCurrentLine());
                                            emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                            backPatchList($4->falselist,nextQuadLabel());
                                            emit(ASSIGN,newexpr_constBool('0'),NULL,$4,nextQuadLabel(),getCurrentLine());
                                            

                                        }

                                        if($<exprVal>1->type == tableitem_e){

                                            emit(tablesetelem,$1,$1->index,$4,nextQuadLabel(),getCurrentLine());

                                            $<exprVal>$ = emit_iftableitem($1,nextQuadLabel(),getCurrentLine(),Scope);
                                            $<exprVal>$->type = assignexpr_e;
                                        
                                        }else{

                                            char* symName =  (char*) $1->sym->value.varVal->name;

                                            SymTableEntry sym = $1->sym;



                                            $1 = lvalue_expr(sym);
                                            emit(ASSIGN,$4,NULL,$1,nextQuadLabel(),getCurrentLine());

                                            $<exprVal>$ = newexpr(assignexpr_e);
                                            $<exprVal>$->sym = newTemp(Scope);
                                            emit(ASSIGN,$1,NULL,$<exprVal>$,nextQuadLabel(),getCurrentLine()); // NA MI VGEI AUTO ! 
                                        }

                                        

                                        if(PrimaryRuleManage == 1){

                                            if(GlobalBeforeEqual == 0 && LocalBeforeEqual == 0 && MemberBeforeEqual == 0){
                                                var = (char*) $1->sym->value.varVal->name ;
                                            }

                                        }else{ 

                                            if(GlobalBeforeEqual == 0 && LocalBeforeEqual == 0 && MemberManageRule == 0) 
                                                var = (char*) $1->sym->value.varVal->name ; 

                                        }
                                
                                        if(var != NULL){

                                            if(!redeclarationLibFunc(var,variable,getCurrentLine())){

                                                if(!lookUpScopeRedeclaration(var,variable,Scope,getCurrentLine(),AssignExpr)){

                                                   if(accessIsValid == 1 && !lookUpValidAssignment(var,Scope,getCurrentLine())){        


                                                    }
                                                }
                                            }
                                        }
                                        
                                        GlobalRuleManage = 0;
                                        LocalRuleManage = 0;
                                        GlobalBeforeEqual = 0;
                                        LocalBeforeEqual = 0;
                                        PrimaryRuleManage = 0;
                                        MemberManageRule = 0;
                                        EqualFound = 0;
                                        accessIsValid = 0;

                                        myprint("lvalue = expr",getCurrentLine());
                                    }
                                           

                                            
                ;

primary:        lvalue                       {  //printf("Prim gbe = %d, g = %d, l = %d, p = %d in line %d\n",GlobalBeforeEqual,GlobalRuleManage,LocalRuleManage,PrimaryRuleManage,getCurrentLine());

                                                if(MemberManageRule == 1 && $1->type == tableitem_e){
                                                    $<exprVal>$ = emit_iftableitem($1,nextQuadLabel(),getCurrentLine(),Scope);
                                                }

                                                char* name = (char*) $1->sym->value.varVal->name ;

                                                if ((GlobalRuleManage == 1 && GlobalBeforeEqual == 1 && EqualFound == 1) ||\
                                                 (LocalRuleManage == 1 && LocalBeforeEqual == 1 && EqualFound == 1) ||\
                                                 (MemberManageRule == 1 && MemberBeforeEqual == 1 && EqualFound == 1) ||\
                                                 (GlobalRuleManage == 0 && LocalRuleManage == 0 && MemberManageRule == 0)) { 

                                                    $<exprVal>$ = lvalue_expr($1->sym) ;

                                                } 

                                                if(EqualFound == 1){
                                                    PrimaryRuleManage = 1 ;
                                                }
                                                else{
                                                     /* 
                                                        eg local x; function f{ x = 2; } The local x makes primary = 1 ,
                                                        so assignment rule will see prim = 1 and won't check the x = 2.
                                                        So if we have not found '=' primary is stand alone. like the example
                                                    */
                                                    MemberManageRule = 0;
                                                    PrimaryRuleManage = 0; 
                                                    LocalRuleManage = 0;
                                                    GlobalRuleManage = 0;
                                                    GlobalBeforeEqual = 0;
                                                    LocalBeforeEqual = 0;

                                                }

                                                
                                                myprint("primary -> lvalue",getCurrentLine());
                                             }

                |call                       {myprint("call",-1);}
                |objectdef                  {$<exprVal>$ = $1; myprint("objectdef",-1);}
                |openpar funcdef closepar   {
                                                $<exprVal>$ = newexpr(programfunc_e);
                                                $$->sym     = $2 ;
                                                myprint("( funcdef )",-1);
                                            }
                |const                      {$<exprVal>$ = $1 ;  myprint("const",-1);}
                ;   

lvalue:         ID              {    

                                    SymTableEntry sym = NULL;
                                    int symbolExists = 1;
                                    int isFuncCall = 0;

                                    if(!notValidAccess($1,Scope,getCurrentLine())){


                                        accessIsValid = 1;

                                        if(lvalueIsFunction($1,Scope) == NULL){


                                            if(lookUpBucketDuplicate(yylval.strVal,Scope) == NULL)
                                                symbolExists = 0;

                                            if(Scope > 0) { 
                                                sym = insert(yylval.strVal,variable,LOCAL,Scope,getCurrentLine(),0,currScopeSpace(),currScopeOffset()); 
                                            }
                                            else if( Scope == 0 ){ 
                                                sym = insert(yylval.strVal,variable,GLOBAL,Scope,getCurrentLine(),0,currScopeSpace(),currScopeOffset()); 
                                            }

                   

                                            if(!symbolExists){
                                                inCurrScopeOffset();
                                            }

                                        }else{
                                            isFuncCall = 1 ;
                                        }

                                    }else{
                                        accessIsValid = 0;
                                    }
                                    
                                    if(sym == NULL){
                                        if(isFuncCall){
                                            sym = lvalueIsFunction($1,Scope);
                                            $<exprVal>$ = lvalue_expr(sym);
                                        }else{
                                            $<exprVal>$ = lvalue_expr(newBucket(yylval.strVal,variable,GLOBAL,Scope,getCurrentLine(),currScopeSpace(),currScopeOffset())) ; 
                                        }
                                    }
                                    else{

                                        switch(sym->type){
                                            case LOCAL      : $<exprVal>$ = lvalue_expr(sym); break;
                                            case GLOBAL     : $<exprVal>$ = lvalue_expr(sym); break;
                                            case LIBFUNC    : $<exprVal>$ = lvalue_expr(sym); break;
                                            case USERFUNC   : $<exprVal>$ = lvalue_expr(sym); break;
                                            case FORMAL     : $<exprVal>$ = lvalue_expr(sym); break;
                                            default         : assert(0);

                                        }
                                        
                                    }

                                    myprint("ID -> lvalue",getCurrentLine()); 
                                }

                |local ID       {  
                                    LocalRuleManage = 1;
                                    
                                    if(EqualFound == 0) 
                                        LocalBeforeEqual = 1;
                                    else
                                        LocalBeforeEqual = 0; 

                                    int symbolExists = 1;
                                    
                                    SymTableEntry sym = NULL;

                                    if(Scope > 0) {
                                        if (!redeclarationLibFunc(yylval.strVal,variable,getCurrentLine()) ){

                                            if(lookUpBucketDuplicateLocal(yylval.strVal,Scope) == NULL){
                                                symbolExists = 0;
                                            }


                                            if(Scope > 0) { 
                                                sym = insert(yylval.strVal,variable,LOCAL,Scope,getCurrentLine(),1,currScopeSpace(),currScopeOffset()); 
                                            }
                                            else if( Scope == 0 )
                                            { 
                                                sym = insert(yylval.strVal,variable,GLOBAL,Scope,getCurrentLine(),1,currScopeSpace(),currScopeOffset()); 
                                            }


                                            if(! symbolExists)
                                                inCurrScopeOffset();

                                            $<exprVal>$ = lvalue_expr(sym);
                                            

                                        }

                                    }else{ 

                                        if (!existsInLibFunc(yylval.strVal) )
                                            { 
                                                if(lookUpBucketDuplicate(yylval.strVal,Scope) == NULL){
                                                    symbolExists = 0;
                                                }

                                                sym = insert(yylval.strVal,variable,GLOBAL,Scope,getCurrentLine(),1,currScopeSpace(),currScopeOffset());

                                                if(!symbolExists)
                                                    inCurrScopeOffset();

                                                $<exprVal>$ = lvalue_expr(sym);
                                            }

                                    }

                                    if(sym == NULL){
                                        $<exprVal>$ = lvalue_expr(newBucket(yylval.strVal,variable,GLOBAL,Scope,getCurrentLine(),currScopeSpace(),currScopeOffset())) ; 
                                    }
                                    else{

                                        switch(sym->type){
                                            case LOCAL      : $<exprVal>$ = lvalue_expr(sym); break;
                                            case GLOBAL     : $<exprVal>$ = lvalue_expr(sym); break;
                                            case LIBFUNC    : $<exprVal>$ = lvalue_expr(sym); break;
                                            case USERFUNC   : $<exprVal>$ = lvalue_expr(sym); break;
                                            case FORMAL     : $<exprVal>$ = lvalue_expr(sym); break;
                                            default         : assert(0);

                                        }
                                        
                                    }
                               

                               
                                    myprint("LOCAL ID",getCurrentLine());
                                }
                |coloncolon ID              {   
                                                if(EqualFound == 0) 
                                                    GlobalBeforeEqual = 1;
                                                else
                                                    GlobalBeforeEqual = 0; 

                                                GlobalRuleManage = 1; 

                                                SymTableEntry entry = LookUpGlobal(yylval.strVal,getCurrentLine());
                                                if(entry == NULL){ 
                                                    $<exprVal>$ = lvalue_expr(newBucket(yylval.strVal,variable,GLOBAL,Scope,getCurrentLine(),currScopeSpace(),currScopeOffset()));
                                                }
                                                else{
                                                    $<exprVal>$ = lvalue_expr(entry);
                                                }
                                                myprint(":: ID",getCurrentLine());
                                            }
                |member                     {
                                                $<exprVal>$ = $1; 
                                                MemberManageRule = 1;
                                                if(EqualFound == 0){
                                                    MemberBeforeEqual = 1;
                                                }else{
                                                    MemberBeforeEqual = 0;
                                                }
                                                myprint("lvalue->member",-1);
                                            }
                ;

member:         lvalue dot ID                               {

                                                                SymTableEntry sym ;
                                                                char* name = (char*) $1->sym->value.varVal->name ;


                                                                $<exprVal>$ = member_item($1,nextQuadLabel(),getCurrentLine(),Scope,$3);

                                                                myprint("lvalue .",getCurrentLine());
                                                            }
                | lvalue openbracket expr closebracket      {
                                                                if($3->type == boolexpr_e){

                                                                    $3->sym = newTemp(Scope);
                                                                    
                                                                    backPatchList($3->truelist,nextQuadLabel());
                                                                    emit(ASSIGN,newexpr_constBool('1'),NULL,$3,nextQuadLabel(),getCurrentLine());
                                                                    emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                                                    backPatchList($3->falselist,nextQuadLabel());
                                                                    emit(ASSIGN,newexpr_constBool('0'),NULL,$3,nextQuadLabel(),getCurrentLine());
                                                                    
                                                                }
                                                                
                                                                SymTableEntry sym ;
                                                                char* name = (char*) $1->sym->value.varVal->name ;


                                                                $1 = emit_iftableitem($1,nextQuadLabel(),getCurrentLine(),Scope);

                                                               
                                                                $<exprVal>$ = newexpr(tableitem_e);
                                                                $<exprVal>$->sym = $1->sym;
                                                                $<exprVal>$->index = $3;

                                                                //printf("MPIKA EDW\n");

                                                                myprint("lvalue [ expr ]",getCurrentLine());
                                                            }
                | call dot ID                               {myprint("call . ID",getCurrentLine());}
                | call openbracket expr closebracket        {myprint("call [ expr ]",getCurrentLine());}
                ;

call:           call openpar elist closepar                         {
                                                                        $<exprVal>$ = make_call($$, $3,Scope,getCurrentLine());
                                                                        myprint("call ( elist )",getCurrentLine());}
                |lvalue callsuffix                                  {   

                                                                        expr* tmp = $2->elist;

                                                                        if(existsInLibFunc((char*) $1->sym->value.funcVal->name))
                                                                            $1->type = libraryfunc_e;
                                                                        
                                                                        if($2->method){
                                                                            expr* self = $1;
                                                                            expr* memberItem = member_item(self,nextQuadLabel(),getCurrentLine(),Scope,$2->name);
                                                                            $1 = emit_iftableitem(memberItem,nextQuadLabel(),getCurrentLine(),Scope);
                                                                            tmp->prev = self;
                                                                            self->next = tmp;
                                                                            $2->elist = self;
                                                                        }
                                                                        $<exprVal>$ = make_call($1,$2->elist,Scope,getCurrentLine());
                                                                        
                                                                        

                                                                       
                                                                    /*error: f() = 2;*/ 
                                                                    myprint("lvalue callsuffix",getCurrentLine()); }
                |openpar funcdef closepar openpar elist closepar    {
                                                                        expr* func  = newexpr(programfunc_e);
                                                                        func->sym   = $2;
                                                                        $<exprVal>$ = make_call(func,$5,Scope,getCurrentLine()); 
                                                                        myprint("( funcdef ) ( elist )",getCurrentLine());}
                ;

callsuffix:     normcall        {
                                    $<method_call>$ = $1;
                                    myprint("normcall",getCurrentLine());
                                }
                |methodcall     {   
                                    $<method_call>$ = $1;
                                    myprint("methodcall",getCurrentLine());
                                }
                ;

normcall:       openpar elist closepar      {
                                                method_call* mc = (method_call*)malloc(sizeof(struct method_call));
                                                memset(mc,0,sizeof(struct method_call));
                                                $<method_call>$ = mc;
                                                $<method_call>$->elist    = $2;
                                                $<method_call>$->method   = 0;
                                                $<method_call>$->name     = NULL;
                                                myprint("( elist )",getCurrentLine());
                                            }
                ;

methodcall:     dotdot ID openpar elist closepar    {
                                                        method_call* mc = (method_call*)malloc(sizeof(struct method_call));
                                                        memset(mc,0,sizeof(struct method_call));
                                                        $<method_call>$ = mc;
                                                        $<method_call>$->elist    = $4;
                                                        $<method_call>$->method   = 1;
                                                        $<method_call>$->name     = $<strVal>2;
                                                        myprint(".. ID ( elist ) ",getCurrentLine());
                                                    }
                ;

elist:          expr                {
                                        if($1->type == boolexpr_e){

                                            $1->sym = newTemp(Scope);
                                            
                                            backPatchList($1->truelist,nextQuadLabel());
                                            emit(ASSIGN,newexpr_constBool('1'),NULL,$1,nextQuadLabel(),getCurrentLine());
                                            emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                            backPatchList($1->falselist,nextQuadLabel());
                                            emit(ASSIGN,newexpr_constBool('0'),NULL,$1,nextQuadLabel(),getCurrentLine());
                                                
                                        }

                                        $<exprVal>$ = $1;
                                        $<exprVal>$->voidParam = 0;
                                       // printf("!!!! offset of elist is %d \n",$$->sym->offset);
                                        myprint("expr",getCurrentLine());
                                    }
                |elist comma expr   {
                                        if($3->type == boolexpr_e){

                                            $3->sym = newTemp(Scope);
                                            
                                            backPatchList($3->truelist,nextQuadLabel());
                                            emit(ASSIGN,newexpr_constBool('1'),NULL,$3,nextQuadLabel(),getCurrentLine());
                                            emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                            backPatchList($3->falselist,nextQuadLabel());
                                            emit(ASSIGN,newexpr_constBool('0'),NULL,$3,nextQuadLabel(),getCurrentLine());
                                                
                                        }

                                        expr* tmp = $1;
                                        while(tmp->next != NULL){
                                            tmp = tmp->next;
                                        }
                                        tmp->next   = $3;
                                        $3->prev    = tmp;
                                        $<exprVal>$ = $1;
                                        $<exprVal>$->voidParam = 0;
                                        myprint("elist , expr",getCurrentLine());
                                    }
                |{/*empty*/
                    $$ = newexpr_Nil();
                    $$->voidParam = 1;
                } 
                ;

objectdef:      openbracket elist closebracket              {
                                                                expr* t = newexpr(newtable_e);
                                                                t->sym  = newTemp(Scope);
                                                                emit(tablecreate,NULL,NULL,t,nextQuadLabel(),getCurrentLine());
                                                                expr* tmp = $2;
                                                                int i = 0;
                                                                while(tmp != NULL){
                                                                    emit(tablesetelem,t,newexpr_constNumber(i++),tmp,nextQuadLabel(),getCurrentLine());
                                                                    tmp = tmp->next;
                                                                }
                                                                $<exprVal>$ = t;
                                                                myprint("[ elist ]",getCurrentLine());
                                                            }       
                | openbracket indexed closebracket          {
                                                                expr* t = newexpr(newtable_e);
                                                                t->sym     = newTemp(Scope);
                                                                emit(tablecreate,NULL,NULL,t,nextQuadLabel(),getCurrentLine());
                                                                expr* tmp = $2;
                                                                while(tmp != NULL){
                                                                    emit(tablesetelem,t,tmp->index,tmp->indexedVal,nextQuadLabel(),getCurrentLine());
                                                                    tmp = tmp->next;
                                                                }
                                                                $<exprVal>$ = t;
                                                                myprint("[ indexed ]",getCurrentLine());
                                                            }
                ;

indexed:        indexedelem                     {   
                                                    $<exprVal>$ = $1;
                                                    myprint("indexedelem",getCurrentLine());
                                                }
                | indexed comma indexedelem     {
                                                    expr* tmp = $1;
                                                    while(tmp->next != NULL){
                                                        tmp = tmp->next;
                                                    }
                                                    tmp->next   = $3;
                                                    $<exprVal>$ = $1;
                                                    myprint("indexed , indexedelem",getCurrentLine());
                                                }
                ;

indexedelem:    openblock expr colon expr closeblock    {
                                                            if($4->type == boolexpr_e){

                                                                $4->sym = newTemp(Scope);
                                                                
                                                                backPatchList($4->truelist,nextQuadLabel());
                                                                emit(ASSIGN,newexpr_constBool('1'),NULL,$4,nextQuadLabel(),getCurrentLine());
                                                                emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                                                backPatchList($4->falselist,nextQuadLabel());
                                                                emit(ASSIGN,newexpr_constBool('0'),NULL,$4,nextQuadLabel(),getCurrentLine());
                                                                
                                                            }

                                                            $<exprVal>$     = newexpr(tableitem_e);
                                                            $$->index       = $2;
                                                            $$->indexedVal  = $4;
                                                            myprint("{ expr : expr }",getCurrentLine());
                                                        }
                ;

block:          openblock {ScopeOperations(INCREASE);} 
                stmtlist 
                closeblock       { changeActivity(Scope); ScopeOperations(DECREASE); myprint("{ stmtlist }",getCurrentLine()); }
                ;

funcBlockStart:     { pushLoopCounter(openedLoops); openedLoops = 0; }
                    ;

funcBlockEnd:       { openedLoops = popLoopCounter(); }
                    ;

funcName:       ID  {
                        openedFunctions++; 
                        if(!redeclarationLibFunc(yylval.strVal, function,getCurrentLine())){
                            if(!lookUpScopeRedeclaration(yylval.strVal,function,Scope,getCurrentLine(),Funcdef)){
                                
                            }
                        }
                        $<strVal>$ = $1;
                        myprint("FUNCTION ID ( idlist ) block",getCurrentLine());
                    }

                |   {
                         openedFunctions++;
                         $<strVal>$ = giveName();
                         myprint("FUNCTION ( idlist ) block",getCurrentLine());
                    }
                ;


FuncPrefix:    FUNCTION funcName {

                                    $<symbol>$ = insert($<strVal>2,function,USERFUNC,Scope,getCurrentLine(),1,-1,-1);
                                    
                                    $<symbol>$->value.funcVal->iaddress = nextQuadLabel();

                                    // jump before function so it doesnt run on declaration
                                    pushFuncJump(nextQuadLabel());
                                    emit(jump, NULL,NULL, NULL,nextQuadLabel(),getCurrentLine());

                                    emit(funcstart,NULL,NULL,lvalue_expr($<symbol>$),nextQuadLabel(),getCurrentLine());
                                    
                                    push(functionLocalOffset); 
                                    
                                    resetFormalArgOffset(); 
                                    enterScopeSpace();    

                                    ScopeOperations(INCREASE);
                                    funcdefStart = 1 ;   

                                 }
                        ;

funcArgs:       openpar idlist closepar {
                                            enterScopeSpace();
                                            resetFunctionLocalOffset();
                                        }
                ;


funcPefixAndArgs:   FuncPrefix funcArgs     {
                                                $1->value.funcVal->totalargs = totalFuncArgs;
                                                totalFuncArgs = 0;
                                            }
                ;

funcBody:       block {
                            exitScopeSpace();
                      }
                ;


funcdef:        funcPefixAndArgs funcBlockStart funcBody funcBlockEnd    

                {   // edo an den kano lathos prepei na valoume to default value gia mi-defined function

                    patchLabel(popFuncJump(),nextQuadLabel()+1);

                    openedFunctions--;
                    exitScopeSpace();
                    $<symbol>1->value.funcVal->totallocals = functionLocalOffset;

                    functionLocalOffset = pop();

                    $<symbol>$ = $<symbol>1;
                    emit(funcend,NULL,NULL,lvalue_expr($<symbol>$),nextQuadLabel(),getCurrentLine());
                    
                }

                ;

const:          NUMBER             { 
                                        $<exprVal>$ = newexpr_constNumber($1) ; 
                                        myprint("NUMBER",getCurrentLine());
                                    }
                | STRING            {
                                        char* strPure = strtok($1,"\"");
                                        $<exprVal>$ = newexpr_constString(strPure); 
                                        myprint("STRING",getCurrentLine());
                                    }
                | NIL               {
                                        $<exprVal>$ = newexpr_Nil(); //it is type nil_e with const num 0 
                                        myprint("NIL",getCurrentLine());
                                    }
                | TRUE              {
                                        $<exprVal>$ = newexpr_constBool('1'); 
                                        myprint("TRUE",getCurrentLine());
                                    }
                | FALSE             {
                                        $<exprVal>$ = newexpr_constBool('0'); 
                                        myprint("FALSE",getCurrentLine());
                                    }
                ;

idlist:         ID           {      
                                    
                                    if(!formalArgsLibFuncShadow(yylval.strVal,getCurrentLine()))
                                        insert(yylval.strVal,variable,FORMAL,Scope,getCurrentLine(),1,currScopeSpace(),currScopeOffset()); 
                                        
                                    inCurrScopeOffset();
                                    
                                    totalFuncArgs++;

                                    myprint("ID",getCurrentLine());
                             }

                | idlist comma ID       {   
                                            totalFuncArgs++;

                                            if(!formalArgsLibFuncShadow(yylval.strVal,getCurrentLine()) && \
                                              !formalArgsRedeclaration(yylval.strVal, Scope, getCurrentLine()) ) {

                                                insert(yylval.strVal,variable,FORMAL,Scope,getCurrentLine(),1,currScopeSpace(),currScopeOffset()); 
                                                
                                                inCurrScopeOffset();
                                                
                                                
                                            }
                                            myprint("idlist , ID",getCurrentLine());
                                        }

                | {}    /*empty*/
                ;

ifprefix:       IF openpar expr closepar {

                                            if($3->type == boolexpr_e){

                                                $3->sym = newTemp(Scope);
                                                
                                                backPatchList($3->truelist,nextQuadLabel());
                                                emit(ASSIGN,newexpr_constBool('1'),NULL,$3,nextQuadLabel(),getCurrentLine());
                                                emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                                backPatchList($3->falselist,nextQuadLabel());
                                                emit(ASSIGN,newexpr_constBool('0'),NULL,$3,nextQuadLabel(),getCurrentLine());
                                                
                                            }

                                            emit(if_eq,newexpr_constBool('1'),$3,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                            $<intVal>$ = nextQuadLabel();
                                            emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
                                         }

elseprefix:     ELSE    {
                            $<intVal>$ = nextQuadLabel();
                            emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
                        }

ifstmt:         ifprefix stmt       {
                                        prevState = S_IF;
                                        patchLabel($1,nextQuadLabel());
                                        $$ = $1 ;
                                        myprint("if ( expr ) stmt",getCurrentLine());
                                    }
                | ifstmt elseprefix stmt        {
                                                    prevState = S_IF;
                                                    patchLabel($1,$2+1);
                                                    patchLabel($2,nextQuadLabel());
                                                    myprint("if ( expr ) stmt else stmt",getCurrentLine());
                                                }
                ;

loopstart:      {  
                    ++openedLoops;//new bucket ston loop_stack
                    loopPush();
                } 
                ;

loopend:        {  
                    --openedLoops;//pop to bucket tou loop_stack                    
                }
                ;

loopstmt:       loopstart stmt loopend  {
                                            loopStack* tmp = loopPop();
                                            assert(tmp);
                                            $<loopStack>$ = tmp;
                                        }


whilestart:     WHILE   { 
                            $<intVal>$ = nextQuadLabel();
                        }
                ;

whilecond:      openpar expr closepar   {   
                                            if($2->type == boolexpr_e){

                                                $2->sym = newTemp(Scope);
                                                
                                                backPatchList($2->truelist,nextQuadLabel());
                                                emit(ASSIGN,newexpr_constBool('1'),NULL,$2,nextQuadLabel(),getCurrentLine());
                                                emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                                backPatchList($2->falselist,nextQuadLabel());
                                                emit(ASSIGN,newexpr_constBool('0'),NULL,$2,nextQuadLabel(),getCurrentLine());
                                                
                                            }

                                            emit(if_eq,$2,newexpr_constBool('1'),newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                            $<intVal>$ = nextQuadLabel();
                                            emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
                                        }
                ;


whilestmt:      whilestart  whilecond loopstmt  {
                                                    emit(jump,NULL,NULL,newexpr_constNumber($1),nextQuadLabel(),getCurrentLine());
                                                    patchLabel($2,nextQuadLabel());

                                                    BClist* blist = $3 -> breaklist;
                                                    BClist* clist = $3 -> contlist;
                                                    while(blist!=NULL){
                                                        patchLabel(blist->QuadNo,nextQuadLabel());
                                                        blist=blist->next;
                                                    }
                                                    while(clist!=NULL){
                                                        patchLabel(clist->QuadNo,$1);
                                                        clist=clist->next;
                                                    }                                                    
                                                    myprint("while ( expr ) stmt",getCurrentLine());
                                                }
                ;

N:              { $<intVal>$ = nextQuadLabel(); emit(jump,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine()); }
M:              { $<intVal>$ = nextQuadLabel(); }

forprefix:      FOR openpar elist M semicolon expr semicolon {  
                                                                if($6->type == boolexpr_e){

                                                                    $6->sym = newTemp(Scope);
                                                                    
                                                                    backPatchList($6->truelist,nextQuadLabel());
                                                                    emit(ASSIGN,newexpr_constBool('1'),NULL,$6,nextQuadLabel(),getCurrentLine());
                                                                    emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                                                    backPatchList($6->falselist,nextQuadLabel());
                                                                    emit(ASSIGN,newexpr_constBool('0'),NULL,$6,nextQuadLabel(),getCurrentLine());
                                                                    
                                                                }
                                                                struct forLoopStruct* flv = (struct forLoopStruct*) malloc(sizeof(struct forLoopStruct));
                                                                $<forLoopVal>$          = flv;
                                                                $<forLoopVal>$->test    = $4;
                                                                $<forLoopVal>$->enter   = nextQuadLabel();
                                                                emit(if_eq,$<exprVal>6,newexpr_constBool('1'),NULL,nextQuadLabel(),getCurrentLine());
                                                            }
                ;

forstmt:        forprefix N elist closepar N loopstmt N    {    
                                                                patchLabel($1->enter,$5+1);
                                                                patchLabel($2,nextQuadLabel());
                                                                patchLabel($5,$1->test);
                                                                patchLabel($7,$2+1);
                                                                BClist* blist = $6 -> breaklist;
                                                                BClist* clist = $6 -> contlist;
                                                                while(blist!=NULL){
                                                                    patchLabel(blist->QuadNo,nextQuadLabel());
                                                                    blist=blist->next;
                                                                }
                                                                while(clist!=NULL){
                                                                    patchLabel(clist->QuadNo,$2+1);
                                                                    clist=clist->next;
                                                                }
                                                                myprint("FOR ( elist ; expr ; elist ) stmt",getCurrentLine());
                                                           }
                ;

returnstmt:     RETURN semicolon   {
                                     if(openedFunctions == 0){
                                        printf(a_c_r "  Error: (l: %d) Use of return outside of function.\n" a_c_re ,getCurrentLine()); 
                                        codeIsCorrect = FALSE;
                                     }

                                    emit(ret,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());

                                    myprint("RETURN ;",getCurrentLine());

                                    }
                | RETURN expr semicolon     {
                                                if($2->type == boolexpr_e){

                                                    $2->sym = newTemp(Scope);
                                                    
                                                    backPatchList($2->truelist,nextQuadLabel());
                                                    emit(ASSIGN,newexpr_constBool('1'),NULL,$2,nextQuadLabel(),getCurrentLine());
                                                    emit(jump,NULL,NULL,newexpr_constNumber(nextQuadLabel()+2),nextQuadLabel(),getCurrentLine());
                                                    backPatchList($2->falselist,nextQuadLabel());
                                                    emit(ASSIGN,newexpr_constBool('0'),NULL,$2,nextQuadLabel(),getCurrentLine());
                                                
                                                }

                                                if(openedFunctions == 0){ 
                                                    printf(a_c_r "  Error: (l: %d) Use of return outside of function.\n"a_c_re ,getCurrentLine()); 
                                                    codeIsCorrect = FALSE;
                                                }

                                                emit(ret,NULL,NULL,$<exprVal>2,nextQuadLabel(),getCurrentLine());
                                                $<exprVal>$ = $2;
                                                myprint("RETURN expr ;",getCurrentLine());
                                            }
                ;
%%



char* giveName(){

    char *prefix = "$yydefault_";
    char *funcName = NULL;
    //const int prefix_size = strlen(prefix) + 1;
   // funcName = (char *) malloc(sizeof(prefix_size + numberDigits(namelessFunctionNumber)));
    //funcName =  asprintf("%s%d",prefix,namelessFunctionNumber);
    asprintf(&funcName, "%s%d", prefix,namelessFunctionNumber);
    namelessFunctionNumber++;
    return funcName;
   // return funcName;

}

void ScopeOperations(scopeAction action){

    if (action == INCREASE){
        
        if(!funcdefStart)
            Scope++;
        else
            funcdefStart = 0 ;
    }else{
        Scope--;
    }

}

int numberDigits(int num){

    int counter = 0;

    if(num == 0)
        return 1;

    while(num != 0){
        num /= 10;
        counter++;
    }

    return counter;

}

void printAllQuads(){

    FILE *quadTxt = fopen("quads.txt", "w");
    if(quadTxt == NULL){printf("Error while opening file.\n");}

    int i = 0;

    if(codeIsCorrect == 1){
        
        // printf(         "\n%-s%-16s%-15s%-15s%-s\n","#|\t", "OP|", "ARG1|", "ARG2|", "RES|");            
        // printf(         "----------------------------------------------------------\n");   
        fprintf(quadTxt,"\n%-s%-16s%-15s%-15s%-s\n","#|\t", "OP|", "ARG1|", "ARG2|", "RES|");            
        fprintf(quadTxt,"----------------------------------------------------------\n");            
        
        for (i = 0; i<nextQuadLabel(); i++){

            // printf("%-d%-s%-12s\t",quads[i].label,":\t",opcodeToString[quads[i].op]);
            // printf("%-15s%-15s%-15s\n\n",getStringValueQuad(quads[i].arg1,0), getStringValueQuad(quads[i].arg2,0),getStringValueQuad(quads[i].result,1)); 

            fprintf(quadTxt,"%-d%-s%-12s\t",quads[i].label,":\t",opcodeToString[quads[i].op]);
            fprintf(quadTxt,"%-15s%-15s%-15s\n\n",getStringValueQuad(quads[i].arg1,0), getStringValueQuad(quads[i].arg2,0),getStringValueQuad(quads[i].result,1)); 

        }
        
    }

    fclose(quadTxt);

}

char* getStringValueQuad(expr* e,int isResult){

    char* ret = NULL;
    int tmp = 0 ;

    if(e == NULL)
        return "";
    
    if(e->type == constnum_e){
        ret = (char*) malloc (sizeof(numberDigits(e->numConst)) + 1);
        if(isResult == 1){ //this check is for logical operation. The quad we gonna jump is better to be represented as integer in print.
            tmp = (int) e->numConst;
            sprintf(ret,"%d",tmp);
        }else{
            double decPart, zero = 0 ;
            decPart = modf(e->numConst,&decPart);

            if(zero == decPart){
                sprintf(ret,"%d",(int) e->numConst);
            }else{
                sprintf(ret,"%lf",e->numConst);
            }
        }
        return ret;
    }else if(e->type == conststring_e){
        ret = strdup(e->strConst);
        return ret;
    }else if(e->type == constbool_e){
        if(e->boolConst == '1')
            return "TRUE";
        else
            return "FALSE";
    }else if(e->type == nil_e){
        return "nil";
    }
    else{
        //printf("name of quad arg %s offset %d\n",e->sym->value.varVal->name,e->sym->offset );
        ret = strdup( e->sym->value.varVal->name);
        return ret;
    }

}








void createBinaryFile(char* customName){

    if(codeIsCorrect == 1){

    	FILE *fp;

    	if(customName){
    		fp = fopen(strcat(customName,".bin"),"wb");
        	if(fp == NULL){  puts("Cannot open file"); exit(0); }
    	}else{
    		fp = fopen("AlphaCode.bin","wb");
        	if(fp == NULL){  puts("Cannot open file"); exit(0); }
    	}

        int totalGlobalsNo = totalGlobals();
        // printf("Real total globals %d\n",totalGlobalsNo );
        instructionToBinary instr;

        char* value = NULL;
        int currStringSize = 0, i = 0, j =0, actualByteSize;

        unsigned int magicNumber    = 19955991;
        fwrite(&magicNumber,        sizeof(magicNumber),        1,fp);  // MagicNumber
        fwrite(&totalNumConsts,     sizeof(totalNumConsts),     1,fp);  // totalNumConsts
        fwrite(&totalStringConsts,  sizeof(totalStringConsts),  1,fp);  // totalStringConsts
        fwrite(&totalNamedLibFuncs, sizeof(totalNamedLibFuncs), 1,fp);  // totalNamedLibFuncs 
        fwrite(&totalUserFuncs,     sizeof(totalUserFuncs),     1,fp);  // totalUserFuncs
        fwrite(&totalInstructions,  sizeof(totalInstructions),  1,fp);  // totalInstructions
        fwrite(&totalGlobalsNo,     sizeof(totalGlobalsNo),     1,fp);  // totalGlobals

        // numConsts
        for(i = 0; i<totalNumConsts; i++){                              
            
            fwrite(&i,sizeof(int),1,fp);                  
            fwrite(&numConsts[i],sizeof(double),1,fp);

        }

        // stringConsts
        for(i = 0; i<totalStringConsts; i++){                           

            currStringSize = strlen(stringConsts[i])+1;

            fwrite(&currStringSize, sizeof(int), 1,fp);  

            value = calloc (currStringSize, sizeof(char)) ;
            strcpy(value, stringConsts[i]); 

            fwrite(&i, sizeof(int), 1,fp);                 
            fwrite(value, sizeof(char)*currStringSize, 1,fp);                 

            value = NULL;

        }

        // userFuncs
        for(i = 0; i<totalUserFuncs; i++){

            currStringSize = strlen(userFuncs[i].id)+1; 
            fwrite(&currStringSize, sizeof(int), 1,fp);            

            value = calloc (currStringSize, sizeof(char)) ;           
            strcpy(value, userFuncs[i].id);
            
            fwrite(&i, sizeof(int), 1,fp);            
            fwrite(&userFuncs[i].address, sizeof(int), 1,fp);            
            fwrite(&userFuncs[i].localSize, sizeof(int), 1,fp); 
            fwrite(&userFuncs[i].totalargs, sizeof(int), 1,fp);
            fwrite(value, sizeof(char)*currStringSize , 1,fp);            

            value = NULL;

        }

        // namedLibFuncs
        for(i = 0; i<totalNamedLibFuncs; i++){
            
            currStringSize = strlen(namedLibFuncs[i])+1;
            fwrite(&currStringSize,sizeof(int), 1,fp);  

            value = calloc (currStringSize, sizeof(char)) ;           
            strcpy(value, namedLibFuncs[i]);

            fwrite(&i, sizeof(int), 1,fp);              
            fwrite(value, sizeof(char)*currStringSize , 1,fp);              

            value  = NULL;
        }   

        for (i = 0; i < nextinstructionlabel() ; i++){ 

            instr.instrOpcode   = instructions[i].opcode;
            
            instr.resultType    = instructions[i].result.type;
            instr.resultOffset  = instructions[i].result.val;
            
            instr.arg1Type      = instructions[i].arg1.type;
            instr.arg1Offset    = instructions[i].arg1.val;

            instr.arg2Type      = instructions[i].arg2.type;
            instr.arg2Offset    = instructions[i].arg2.val;

            instr.instrLine     = instructions[i].srcLine;

            fwrite(&instr,sizeof(instr),1,fp);

        }
        
        fclose(fp);

    }


}




void myprint(char* msg, int line){
    
   // if(line == -1)
   //      printf("%s\n",msg);        
   //  else
   //      printf("%s in line %d\n",msg,line);
        
}

int yyerror(char* yaccProvidedMessage){
   
    fprintf(stderr, ANSI_COLOR_RED"%s: ", yaccProvidedMessage);
    fprintf(stderr, ANSI_COLOR_RESET "");
    fprintf(stderr, "at line %d,  before token: %s \n", yylineno, yytext);
    fprintf(stderr, "INPUT NOT VALID\n");
    codeIsCorrect = FALSE;
    return -1 ;

}

int main(int argc, char** argv){

	char* customName = NULL;

	if(argc > 3){

        if(!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr,"Cannot read file: %s\n",argv[1]);
            return 1;
        }
        if(strcmp(argv[2],"o")){
            customName = calloc(1, strlen(argv[2]));
            strcpy(customName, argv[3]);

        }else{printf("error: argument\"%s\" not aknowledged.",argv[2]);return 1;}
        stdout = yyout ;

    } else 

	if(argc > 2){
 
 		if(!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr,"Cannot read file: %s\n",argv[1]);
            return 1;
        }
        if(!(yyout = fopen(argv[2], "w"))){
            fprintf(stderr,"Cannot write file: %s\n",argv[1]);
            return 1;
        }
        stdout = yyout ;

    } else 

    if(argc > 1){

        if(!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr,"Cannot read file: %s\n",argv[1]);
            return 1;
        }

    }
    else{
        yyin = stdin;
    }

    initializePhaseThree();
    initializeArray();
    libFuncInit();
    yyparse(); 

    //printWholeStruct();
    emit(no_op,NULL,NULL,NULL,nextQuadLabel(),getCurrentLine());
    //printAllQuads();
    
    generateTcode(nextQuadLabel());
    createBinaryFile(customName);

    return 0;
}
