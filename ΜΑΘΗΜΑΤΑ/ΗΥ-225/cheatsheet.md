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

## MIPS Instructions (used in hy225)

```
add     $rd,  $rs,  $rt   
addi    $rd,  $rs,  $rt   
sub     $rd,  $rs,  $rt 

slti    $rd,  $rs,  $rt 

```
