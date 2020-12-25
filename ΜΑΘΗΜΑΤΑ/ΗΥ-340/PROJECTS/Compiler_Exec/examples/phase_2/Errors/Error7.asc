function foo(){
   x=0;
}
foo = 4;	//Using ProgramFunc as an lvalue
print = foo;	//Using LibFunc as an lvalue
++print;	//Using LibFunc as an lvalue
foo--;		//Using ProgramFunc as an lvalue
