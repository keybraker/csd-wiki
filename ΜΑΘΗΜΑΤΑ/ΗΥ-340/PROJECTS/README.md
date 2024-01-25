# Alpha Compiler
A fully fledged compiler for Alpha.

## How does it work ( simple representation )
```text
make     |---------------| alphac your.txt  |---------------| alpha your.bin  |-----------|
-------> |  alphac (cmp) |----------------> | AlphaCode.bin |---------------> |  program  |
compiler |  alpha  (vm)  | alpha executable |---------------|                 |  output   |
& VM     |---------------| created                                            |-----------|
```

## Structure of example
```text
.
|-- Alpha_Compiler
|   |
|   |-- bison
|   |   |
|   |   |-- bison_functions
|   |   |   |-- LibFuncsInitialize.c
|   |   |   '-- SymbolTable.c
|   |   |
|   |   '-- bison_libs
|   |	    '-- DataStruct.h
|   |
|   |-- flex
|   |   |
|   |   |-- flex_functions
|   |   |   |-- check_strings.l
|   |   |   '-- multiline_comment.l
|   |   |
|   |   '-- flex_libs
|   |	    '-- token_struct.h
|   |
|   |-- Intermidiate
|   |   |
|   |   |-- funcJumpStack.c
|   |   |-- LoopCounterStack.c
|   |   |-- loopStack.c
|   |   |-- phase3.c
|   |   |-- phase3.h
|   |   '-- phase3.h
|   |
|   |-- parser.y
|   |-- scanner.l
|  	|
|   '-- TargetCode
|       |
|       |-- constTables.h
|       |-- constTablesCreator.c
|       |-- funcStackTarget.c
|       |-- operands.h
|       |-- phase4.h
|       '-- targetCode.h
|
|-- Virtual_Machine_Alpha
|   |
|   |-- exec_Funcs
|   |   |
|   |   |-- Dispatcher.c
|   |   |-- Dispatcher.h
|   |   |-- execAssign.c
|   |   |-- execCallsv.c
|   |   |-- execJumps.h
|   |   |-- execNop.h
|   |   '-- execTables.h
|   |
|   |-- vm_Tools
|   |   |
|   |   |-- binaryDecoder.c
|   |   |-- binaryDecoder.h
|   |   |-- ConstTablesLinker.h
|   |   |-- memManager.c
|   |   |-- memManager.h
|   |   |-- phase5.c
|   |   '-- phase5.h
|   |
|   '-- Makefile
|
|-- CompilerExec
|   |
|   '-- examples
|       |
|       '-- ...
|
|-- Makefile
'-- README.md


```
## Folder explanation
* Alpha_Compiler holds all the necessary files to create the compiler.
* Virtual_Machine_Alpha has all the files to create the virtual machine.
* Compiler_Exec has example files that you can run, and is a folder,
    that stores all data created by the compilations of the compiler
    and of the virtual machine.


## Prerequisites
Most Linux distros and Mac OS come preinstalled with all of the following compilers
but if you find any trouble, these are the links to follow:

* [gcc](https://gcc.gnu.org) - to compile the compiler
* [flex](https://www.gnu.org/software/flex/) - to create the alpha compiler
* [bison](https://www.gnu.org/software/bison/) - to create the alpha compiler

## Installation Guide
Clone this repository with ( or download zip ):
```
git clone https://github.com/keybraker/Alpha-Compiler.git
```

## Usage Guide
Open a terminal window and cd to cloned project
```
cd .../Alpha-Compiler
```

##### 1. COMPILER AND VIRTUAL MACHINE CREATION
By typing, ``` make ``` the compiler ``` alphac ``` and vm ``` alpha ``` will be automatically created.

##### 2. EXECUTABLE GENERATION
To create an executable program you will have to simply type:
```
./alphac YOUR_CODE.txt
```
This will create a new AlphaCode.bin, if you want to give it a custom name , simply add:
```
./alphac YOUR_CODE.txt -o YOUR_CUSTOM_NAME
```

##### 3. RUN EXECUTABLE
To execute the compiled program with default name, type:
```
./alpha
```
if you want to execute a specific executable, type:
```
./alpha -n YOUR_CUSTOM_NAME
```
##### ( This will be fixed in an upcomming update and executables will have to be given to be executed. No Execs will be run by default )

## Execution flags for the VM

* -p ~ You can see in a visualized way all the data stored in the executable when the VM is running it.
* -i ~ Creators Info
* -n ~ followed by a "name" of executable without .bin, will execute the specific (needs fixing)
* -s ~ Easter Egg
