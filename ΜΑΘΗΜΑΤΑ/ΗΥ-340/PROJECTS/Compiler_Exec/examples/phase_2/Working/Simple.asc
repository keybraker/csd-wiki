//insert in ST global variable (globalVarFirst). scope: 0, line: 2
globalVarFirst = true;

//insert in ST user function GlobalFunction with 
//no formal arguments. scope: 0, line: 6
function GlobalFunction(){
        //insert in ST local variable (localVar). scope: 1, line: 8
        local localVar = 1;

		//insert in ST user function LocalFunction with 
		//two formal argument (x, y). scope: 1, line: 14
		//insert in ST formal argument x. scope: 2, line: 14
		//insert in ST formal argument y. scope: 2, line: 14
        function LocalFunction (x, y){
                //insert in ST local variable (globalVarFirst). scope: 2, line: 16
                local globalVarFirst = 1;
        }
}

if(globalVarFirst == true)
		//insert in ST global variable (globalVarSecond). scope: 0, line: 22
        globalVarSecond = false;

if (globalVarSecond != true) {
        globalVarSecond = true;  //refer to global variable: globalVarSecond
		//insert in ST local variable (localVar). scope: 1, line: 27
        localVar = 1; 
}

//mail from: karolos@csd.uoc.gr

//insert in ST user function F with 
//no formal arguments. scope: 0, line: 34
function F() {}

//insert in ST global variable (a). scope: 0, line: 40
//insert in ST global variable (b). scope: 0, line: 40
//insert in ST global variable (x). scope: 0, line: 40
//insert in ST global variable (y). scope: 0, line: 40
F(a, b)()(x, y)()().z = 5;

//mail from: russoyan@csd.uoc.g
//insert in ST global variable (G). scope: 0, line: 44
G();

//mail from: dstamat@csd.uoc.g
//insert in ST global variable (G). scope: 0, line: 48
lol = 5;
lol();

///////////////////////////
//insert in ST global variable (print_). scope: 0, line: 53
print_ = print;
print_();
