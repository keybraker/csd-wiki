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
Type	    31-26        25-21	 20-16	 15-11    10-06   05-00
R-Type	    opcode  	  $rs	  $rt	  $rd     shamt   funct
I-Type	    opcode  	  $rs	  $rt	  imm
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


