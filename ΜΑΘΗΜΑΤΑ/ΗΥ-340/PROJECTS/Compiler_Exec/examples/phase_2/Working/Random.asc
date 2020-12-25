//insert in ST global variable (nl). scope: 0, line: 2
nl = "\n";

//insert in ST user function Assert with 
//one formal argument (con). scope: 0, line: 7
//insert in ST formal argument con. scope: 1, line: 7
function Assert(con){
	if (not con)
		print("Assertion", nl);
}

//insert in ST user function Assert with 
//one formal argument (num). scope: 0, line: 15
//insert in ST formal argument num. scope: 1, line: 15
function IsEven(num) {
	return num % 2 == 0;
}

//insert in ST user function Assert with 
//one formal argument (num). scope: 0, line: 22
//insert in ST formal argument num. scope: 1, line: 22
function IsOdd(num) {
	return not IsEven(num);
}

//insert in ST user function Assert with 
//one formal argument (num). scope: 0, line: 29
//insert in ST formal argument num. scope: 1, line: 29
function CanDivideByTen(num) {
	return num % 10;
}

//insert in ST user function Assert with 
//one formal argument (MAX). scope: 0, line: 36
//insert in ST formal argument MAX. scope: 1, line: 36
function PrintParityOfNumbers(MAX) {
	local exit = true;	//insert in ST local variable (x). scope 1, line 37
	
	for(local i = 0; i < MAX + 1; ++i){	//insert in ST local cariable (i). scope 1, line 39
		if (IsEven(i))
			print(i, " is evan", nl);
		else if (IsOdd(i))
			print(i, " is odd", nl);
		else {
			exit = false;
			break;
		}
	}

	return exit;
}

//insert in ST global variable (even). scope: 0, line: 56
//insert in ST global variable (odd). scope: 0, line: 56
//insert in ST global variable (cnt). scope: 0, line: 56
for (local even = 0, local odd = 1, local cnt = 0; (IsEven(even) and IsOdd(odd)) or (CanDivideByTen(10)); ) {
	if (cnt == 10)
		break;
	if (cnt == 0) {
		even = 1;
		odd	 = 0;
		cnt  = 10;
	}		
}

//insert in ST user function Print with 
//no formal arguments. scope: 0, line: 68
function Print() {
	print("cnt: ", cnt, nl);	//must print 10
	print("even: ", even, nl);	//must print 1
	print("odd: ", odd, nl);	//must print 0
}

Print();
Assert(PrintParityOfNumbers(10));






