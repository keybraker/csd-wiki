//
i = 8;
x = 10;
y = 30;

function foo(x,y){
    x = i;     
    ::y = x;  

    function g() {
		::x = x;   //Error Cannot access x inside g
		::y = y;   //Error Cannot access x inside g
    }
}
