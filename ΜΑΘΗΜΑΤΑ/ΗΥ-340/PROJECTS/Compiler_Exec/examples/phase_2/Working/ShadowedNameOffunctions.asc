//insert in ST global variable (nl). scope: 0, line: 2
nl = "\n";

//insert in ST user function F with 
//no formal arguments. scope: 0, line: 6
function F(){
	print("(zero)");
	
	//insert in ST user function F with 
	//no formal arguments. scope: 1, line: 11
	function F(){
		print("(one)");
		
		//insert in ST user function F with 
		//no formal arguments. scope: 2, line: 16
		function F(){
			print("(two)");
			
			//insert in ST user function F with 
			//no formal arguments. scope: 3, line: 21
			function F(){
				print("(Three)");
				return ::F;			//call gloabl F;
			}
			return F;
		}
		return F;
	}
	return F;
}

F();		//print -> (zero)
print(nl);
F()();		//print -> (zero)(one)
print(nl);
F()()();	//print -> (zero)(one)(two)
print(nl);
F()()()();	//print -> (zero)(one)(two)(Three)
