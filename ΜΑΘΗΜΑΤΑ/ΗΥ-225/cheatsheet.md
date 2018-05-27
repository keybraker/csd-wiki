# MIPS Cheat Sheet
The essential knowledge for MIPS (hy225)

## 32 MIPS Registers

```
$0	=	0       Immediate 0					                               
$1	=	$at     assembler temporary			                             
$2	=	$v0 \	Procedure					                         
$3	=	$v1 /	Return Values				                          
$4	=	$a0 \								                          
$5	=	$a1 |	Procedure					                             
$6	=	$a2 |	Arguments					                             
$7	=	$a3 /								                             
$8	=	$t0 \								                           
$9	=	$t1 |								                          
$10	=	$t2 |								                          
$11	=	$t3 |	Temporary					                           
$12	=	$t4 |	Registers					                          
$13	=	$t5 |								                          
$14	=	$t6 |								                           
$15	=	$t7 /								
$16	=	$s0 \
$17	=	$s1 | 
$18	=	$s2 |     
$19	=	$s3 |	Saved    
$20	=	$s4 |   Registers 
$21	=	$s5 | 
$22	=	$s6 |  
$23	=	$s7 /  
$24	=	$t8 \   Temporary 
$25	=	$t9 /   Registers 
$26	=	$k0 \   Kernel   
$27	=	$k1 /   Reserved 
$28	=	$gp     Global Pointer 
$29	=	$sp     Stack Pointer 
$30	=	$fp     Stack Frame
$31	=	$ra    	Return Address        
```

## Instruction Formats
```
Type	    31-26(6)    25-21(5)  20-16(5)  15-11(5)  10-06(5)   05-00(6)
R-Type      opcode        $rs       $rt	      $rd      shamt      funct
I-Type	    opcode  	  $rs	    $rt	      imm
J-Type	    opcode  	 target
```

## MIPS Instructions (used in hy225)

```
add     $rd,  $rs,  $rt   // $rd = $rs + $rt | R-format
addi    $rd,  $rs,  Imm   // add Immediate (can take negative values, no need for subi) | I-format   
sub     $rd,  $rs,  $rt   // $rd = $rs - $rt  | R-format

sll     $rd,  $rs,  Imm   // shift less logical (shift 2 means adding x2 zeros in the end
                             resulting in multiplying the number by 2^2=4) | R-format  

beq     $rd,  $rs,  label // branch if equal | I-format  
bne     $rd,  $rs,  label // branch if not equal | I-format  

lw      $rd,  Imm($rx)    // $rd,  $rx,  Imm -> $rd = $rx[Imm] | I-format  
sw      $rs,  Imm($rx)    // $rs,  $rx,  Imm -> $rx[Imm] = $rs | I-format  

slt     $rd,  $rs,  $rt   // set less than | R-format
slti    $rd,  $rs,  Imm   // set less than Immediate | I-format   

j       target            // jump target | I-format
jr      $rs               // jump register | R-format
jal     target            // jump and link (essential instruction of MIPS, core 
                             of calling procedures and returning back to caller)
                             | I-format
                             
lui     $t,   Imm         // load upper immediate, immediate value is shifted left 16
                             bits and stored in the register. The lower 16 bits are zeroes
                             | I-format
```

## MIPS code

instructions starting with "." are directives to the compiler:
```
.asciiz declares that what follows, is an ASCII string
```
```
.data   declares that what follows, is data and not commands
```
```
.text   declares that what follows, are commands and not data
```
```
.globl  declares that what follows, are labels that should
            be stored in the global array
```
```
.align  declares that what follows, is the power to which
        2 must be raised in order to find the alignment 
        (e.g .align 2 means 2^2 = 4 bytes, which means that
        every address must be a multiple of 4, so it must 
        end with two zeros 00)
```
```
.space  declares that what follows, is the number of bytes we
        want the Assembler to give to our program to store data
```

## MIPS Memory alignments

Addresses on MIPS, are **Byte Addressable**, which means that addresses
are referring to **Bytes** in memory.

## Big-Endian και Little-Endian Machines

Big-Endian and Little-Endian Machines have both (left) MS -> LS (right), they also store number in this fashion (left to right) but Big saves strings in that manner, whereas Little in the opposite direction. 

### This is the byte order of Big and Little endian
word | BIG | LITTLE 
--- | --- | --- 
0 | *0-1-2-3* | *3-2-1-0*  
4 | *4-5-6-7* | *7-6-5-4* 
8 | *8-9-10-11* | *11-10-9-8* 
12 | *k-a-t-e* | *e-t-a-k* 
16 | *v-e-n-i* | *i-n-e-v* 
20 | *s-\0- -*    | *- -\0-s* 

## How do jump and branch instructions work ?

Jump and Branch instructions are I-format and the basic execution is as follows:<br>
**PC_new := (PC_br + 4) + 4 * ImmOffset (signed)**

**PC_new:** *is the new address the proccessor will execute next*<br>
**PC_br:** *is the address same as the address of the jump/branch instruction*<br>
**ImmOffset:** *is the the standart 16 bits of the I-format*<br>

## Procedure calls

The **caller** function and the **callee** function are connected as one calls the other.<br>
Who's responsibility is it to save variables before and after procedure calls ?<br>

There are two types of variables:<br>
**Temporary registers:** $t0-$t9 ($8-$15 και $24-$25), *it's the caller's responsibility to save the useful value before calling the new procedure ("callersaved")*<br>
**Saved registers:** $s0 - $s7 ($16-$23), *it's the callee's responsibility to save the old value each of all the saved registers before it changes them ("callee-saved")*<br>

## Register File (RF) Πολύπορτο Αρχείο Καταχωρητών
Although called a "file", a register file is not related to disk files. 
A register file is a small set of high-speed storage cells inside the CPU.
With a 32 registers of 32 bit size each.

# Pipeline
There are 5 states of MIPS's pipeline:
1. **IF:** **I**nstruction **F**etch
2. **ID:** **I**nstruction **D**ecode
3. **EX:** **Ex**ecute or address calculation
4. **MEM:** Data **Mem**ory
5. **WB:** **W**rite **B**ack

Although the flow is going from left to right, there are two exceptions:
1. **Write Back** which writes data back to the Register File (RF) mid flow
2. **Next PC calculation** which is decided between the increased PC or the branch address from the Data Memory stage.

For a pipeline to be implemented in a processor architecture, state memories have to be added, so that every state of the five above, can work individually. 
1. **IF/ID** 
2. **ID/EX** 
3. **EX/MEM** 
4. **MEM/WB**
These memories, work as checkpoints of the pipeline, for every single state to a percentile of the work, of one instruction.

## [Pipeline Hazards](https://en.wikipedia.org/wiki/Hazard_(computer_architecture) "Hazard (computer architecture)")
1. **Structural** hazard is the impotence of the hardware to support a certain combination of istructions.
2. **Data** hazard is when the pipeline has to wait, a certain amount of cycles, because it's waiting for another instruction to finish.
3. **Control** hazard is when the pipeline has to take a decision upon the outcome of an instructions whilst it is being executed.

## [Dependencies](https://en.wikipedia.org/wiki/Hazard_(computer_architecture)#Read_after_write_(RAW) "wiki examples")
1. **RAW:** **R**ead **A**fter **W**rite *(or write and then read)*.<br>
   **R2** <- R1 + R3<br>
   R4 <- **R2** + R3<br>
2. **WAW:** **W**rite **A**fter **W**rite *(or write and then write)*.<br>
   **R2** <- R1 + R3<br>
   **R2** <- R1 + R3<br>
3. **WAR:** **W**rite **A**fter **R**ead *(or read and then write)*.<br>
   R4 <- R1 + **R5**<br>
   **R5** <- R1 + R2<br>

1. **RAW:**<br>
   *in this **dependency you have to wait and there is no way to speed it up***
2. **WAW:**<br>
   *to solve this dependency you have to **cancel the first write in order to only keep the lader one***
3. **WAR:**<br>
   *to solve this dependency you have to **keep a copy of the old value in order to give it to the one will come later***

## Pipeline Jumps and Branches
Our pipeline will execute instructions although having fetched a branch or jump instruction. Given the probability of correctly executing the instruction on PC+4, although unaware if it has to get executed, saves us 2 clock cycles, while executing them wrongfully as the same effect as doing nothing at all (the only downside to not doing anything at all is the increase in power consumption).

If the branch is true and we have to jump (something that will be determined on the third part of our pipeline after the ALU has given its output), our pipeline will cancel the last two instructions by making all the control bits to null (0) in order to skip everything they made (this is possible because the instruction or not on the store phase of the pipeline so they have not stored nor altered any register or memory values).

## Pipeline cost per false prediction
instruction | execution<br>time (cc*)
--- | --- 
general | 1~
load that is followed by<br>dependent instruction | 2~
failed branches (1/3) | 1~
successfull branches (2/3)** | 3~
jump*** | 2~
```
*  clock cycles
** success means that our prefetched PC+4 instructions are wrongfully executed
** as jump instructions are basically true branches you will always lose one cycle.
   Knowing that it is a jump withought the use of the ALU to determine it we can 
   know it one cycle prior to a successfull branch so one less cycle is lost
```
