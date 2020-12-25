#include "binaryDecoder.h"

char* opcodeToString[] = {
                                    "assign",       "add",              "sub",
                                    "mul",          "div",              "mod",
                                    "jump",         "jeq",              "jne",
                                    "jle",          "jge",              "jlt",
                                    "jgt",          "call",             "pusharg",  
                                    "funcenter",    "funcexit",         "newtable",
                                    "tablegetelem", "tablesetelem",     "nop"
                               };

char* typeToStringArray[] = {

    "0  (label), ",      
    "1  (global), ",    
    "2  (formal), ",    
    "3  (local), ",     
    "4  (number), ",    
    "5  (string), ",    
    "6  (bool), ",      
    "7  (nil), ",       
    "8  (userfunc), ",  
    "9  (libfunc), ",   
    "10 (retval), "

};

char* typeToString(int type){
	if(type > 10 || type < 0){
		return "";
	}else{
		return typeToStringArray[type];
	}
}

char* offsetPrinter(int offset){
	if(offset == -1){
		return "";
	}else{
		char* iTs = calloc (1,sizeof(char*));
		sprintf(iTs,"%d",offset);
		return iTs;
	}
}

DataTables* decoder(int printerino, char* customName){ 

	printf("customName: %s\n", customName);
	
	magicNumberBinary			= 0;
	numConstsBinary				= (double*) 0;
	totalNumConstsBinary		= 0;	
	stringConstsBinary			= (char**) 0;
	totalStringConstsBinary		= 0;	
	namedLibFuncsBinary			= (char**) 0;	
	totalNamedLibFuncsBinary	= 0; 
	userFuncsBinary				= (userfunc*) 0;
	totalUserFuncsBinary		= 0;
	codeTable					= (instruction*) 0;	
	codeTableSize				= 0; 
	totalGlobals				= 0; 

	FILE *fp = fopen(strcat(customName,".bin"),"rb"); 
	if(fp == NULL) 
		{ printf(a_c_r"\nFile did not open or was not found.\n\n"a_c_re);exit(0);}

	if(fread(&magicNumberBinary,sizeof(magicNumberBinary),1,fp) == 1) { 
		if(magicNumberBinary == 19955991)	{ 
			if(printerino) printf(a_c_g"\n> MagicNumber is correct\n"a_c_re);
		} else {
			exit(0);
		}
	}

	fread(&totalNumConstsBinary,		sizeof(totalNumConstsBinary),		1,fp);			
	fread(&totalStringConstsBinary,		sizeof(totalStringConstsBinary),	1,fp);		
	fread(&totalNamedLibFuncsBinary,	sizeof(totalNamedLibFuncsBinary),	1,fp);		
	fread(&totalUserFuncsBinary,		sizeof(totalUserFuncsBinary),		1,fp);			
	fread(&codeTableSize,				sizeof(codeTableSize),				1,fp);	
	fread(&totalGlobals,				sizeof(totalGlobals),				1,fp);	

	double			numConstsBinary		[totalNumConstsBinary]		;
	char*			stringConstsBinary	[totalStringConstsBinary] 	;
	char*			namedLibFuncsBinary	[totalNamedLibFuncsBinary]	;
	userfunc		userFuncsBinary		[totalUserFuncsBinary]		;
	instruction 	codeTable			[codeTableSize]				;

	int 			currStringSize 		= 0;
	int 			i 					= 0;
	int 			offset 				= 0;
	int 			address 			= 0;
	int 			localSize 			= 0;
	int 			totalargs			= 0;
	double 			num 				= 0;
	char* 			str  				= NULL;	

	if(printerino) printf(a_c_r bold under"PINAKAS ARITHMITIKON STATHERON\n"under_re bold_re a_c_re);

	for(i = 0; i<totalNumConstsBinary; i++){

		fread(&offset,sizeof(int),1,fp);
		fread(&numConstsBinary[offset],sizeof(double),1,fp);
		
		if(printerino) {		
			printf(a_c_b "|" a_c_re);
			printf(a_c_b italic "%d" italic_re a_c_re, offset);
			printf(a_c_b "| %f\n" a_c_re, numConstsBinary[offset]);
		}

	}
	if(printerino) printf("\n");

	if(printerino) printf(a_c_r bold under"PINAKAS STATHERON STRINGS\n"under_re bold_re a_c_re);

	for(i = 0; i<totalStringConstsBinary; i++){

		fread(&currStringSize,sizeof(int),1,fp); 
	    str = calloc ( currStringSize,  sizeof(char)) ;

		fread(&offset,sizeof(int),1,fp);
		fread(str, sizeof(char)*currStringSize ,1,fp);  

		stringConstsBinary[offset] = strdup (str);

		if(printerino){
			printf(a_c_b "|" a_c_re);
			printf(a_c_b italic "%d" italic_re a_c_re, offset);
			printf(a_c_b "| %s\n" a_c_re, stringConstsBinary[offset]);
		}
		str = NULL;
	}

	if(printerino) printf("\n");

	if(printerino) printf(a_c_r bold under"PINAKAS SUNARTISEON XRISTI\n"under_re bold_re a_c_re);

	for(i = 0; i<totalUserFuncsBinary; i++){

		fread(&currStringSize,sizeof(int),1,fp); 
	    str = calloc (currStringSize,  sizeof(char)) ;

		fread(&offset,		sizeof(int),1,fp);
		fread(&address,		sizeof(int),1,fp);
		fread(&localSize,	sizeof(int),1,fp);
		fread(&totalargs,	sizeof(int),1,fp);
		fread(str,			sizeof(char)*currStringSize,1,fp);

		userFuncsBinary[offset].id 			= (char*) strdup(str);
		userFuncsBinary[offset].address 	= address;
		userFuncsBinary[offset].localSize 	= localSize;
		userFuncsBinary[offset].totalargs	= totalargs;

		if(printerino){
			printf(a_c_b "|" a_c_re);
			printf(a_c_b italic "%d" italic_re a_c_re, offset);
			printf(a_c_b "| address %d, localSize %d, totalargs %d, id %s\n" a_c_re, userFuncsBinary[offset].address, userFuncsBinary[offset].localSize, userFuncsBinary[offset].totalargs, userFuncsBinary[offset].id);
		}
		str = NULL;
	}
	if(printerino) printf("\n");

	if(printerino) printf(a_c_r bold under"PINAKAS SUNARTISEON VIVLIOTHIKIS\n"under_re bold_re a_c_re);

	for(i = 0; i<totalNamedLibFuncsBinary; i++){

		fread(&currStringSize,sizeof(int),1,fp); 
	    str = calloc (currStringSize,  sizeof(char)) ;

		fread(&offset,sizeof(int),1,fp);
		fread(str, sizeof(char)*currStringSize ,1,fp);

		namedLibFuncsBinary[offset] = strdup (str);
		if(printerino){
			printf(a_c_b "|" a_c_re);
			printf(a_c_b italic "%d" italic_re a_c_re, offset);
			printf(a_c_b "| %s\n" a_c_re, namedLibFuncsBinary[offset]);
		}
		str = NULL;		
	}
	if(printerino) printf("\n");

	if(printerino) printf(             "\n%-s%-16s%-30s%-30s%-s\n","#|\t", "OP|", "RES|", "ARG1|", "ARG2|");            
	if(printerino) printf(             "-----------------------------------------------------------------------------------------\n");   

	for (i = 0; i < codeTableSize ; i++){ 

		fread(&instr,sizeof(instr),1,fp);

		codeTable[i].opcode 		= instr.instrOpcode;

		codeTable[i].result.type 	= instr.resultType;
		codeTable[i].result.val  	= instr.resultOffset;

		codeTable[i].arg1.type 		= instr.arg1Type;
		codeTable[i].arg1.val  		= instr.arg1Offset;

		codeTable[i].arg2.type 		= instr.arg2Type;
		codeTable[i].arg2.val 		= instr.arg2Offset;

		codeTable[i].srcLine		= instr.instrLine;

	    if(printerino) printf( 	"%-d%-s%-12s\t",instr.instrLine,":\t",opcodeToString[instr.instrOpcode]);
	    if(printerino) printf( 	"%-3s%-17s%-3s%-17s%-3s%-2s\n\n",\
						    	typeToString(instr.resultType),\
						    	offsetPrinter(instr.resultOffset),\
						    	typeToString(instr.arg1Type),\
						    	offsetPrinter(instr.arg1Offset),\
						    	typeToString(instr.arg2Type),\
								offsetPrinter(instr.arg2Offset));
	}

	fclose(fp);

	DataTables* tables;
	tables = (DataTables*) malloc(sizeof(DataTables));
	memset(tables,0,sizeof(DataTables));

	tables->numConstsTable = (double*) malloc(sizeof(double) * totalNumConstsBinary);
	memcpy(tables->numConstsTable,numConstsBinary,(sizeof(double) * totalNumConstsBinary));
	tables->totalNumConsts = totalNumConstsBinary;

	tables->strConstsTable = (char**) malloc(sizeof(char*) * totalStringConstsBinary);
	memcpy(tables->strConstsTable,stringConstsBinary,(sizeof(char*) * totalStringConstsBinary));
	tables->totalStrConsts = totalStringConstsBinary;

	tables->userFuncsTable = (userfunc*) malloc(sizeof(userfunc) * totalUserFuncsBinary);
	memcpy(tables->userFuncsTable,userFuncsBinary,(sizeof(userfunc) * totalUserFuncsBinary));
	tables->totalUserFuncs = totalUserFuncsBinary;

	tables->libFuncsTable = (char**) malloc(sizeof(char*) * totalNamedLibFuncsBinary);
	memcpy(tables->libFuncsTable,namedLibFuncsBinary,(sizeof(char*) * totalNamedLibFuncsBinary));
	tables->totalLibFuncs = totalNamedLibFuncsBinary;

	tables->code = (instruction*) malloc(sizeof(instruction) * codeTableSize);
	memcpy(tables->code,codeTable,sizeof(instruction)*codeTableSize);
	tables->codeSize = codeTableSize;

	return tables;
}


