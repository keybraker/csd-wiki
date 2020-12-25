//insert in ST anonymous function with 
//two formal arguments (x, AnonymousOne). scope: 0, line: 5
//insert in ST formal argument x. scope: 1, line: 5
//insert in ST formal argument AnonymousOne. scope: 1, line: 5
function (x, AnonymousOne){
	
	//insert in ST anonymous function with 
	//one formal argument (AnonymousTwo). scope: 1, line: 10
	//insert in ST formal argument AnonymousTwo. scope: 2, line: 10
	function (AnonymousTwo){
		
		//insert in ST anonymous function with 
		//one formal argument (AnonymousThree). scope: 2, line: 15
		//insert in ST formal argument AnonymousThree. scope: 3, line: 15
		function (AnonymousThree){}
		
		//insert in ST anonymous function with 
		//one formal argument (AnonymousFour). scope: 2, line: 20
		//insert in ST formal argument AnonymousFour. scope: 3, line: 20
		function (AnonymousFour){}
	}
}

//insert in ST anonymous function with 
//two formal arguments (x, AnonymousFive). scope: 0, line: 28
//insert in ST formal argument x. scope: 1, line: 28
//insert in ST formal argument AnonymousFive. scope: 1, line: 28
function (x, AnonymousFive){}
