# TwoPassAssembler

---> Opcode and Operands 
1. CLA , STP take no arguments or operands. 
2. An operand should take a label which is valid. For example: BRZ, BRN, BRP take one operand which should be a valid label. 

--->General 
1. First step should be to clear the accumulator. Clear accumulator (CLA) resets the accumulator. 
2. The execution stops after the end statement in our case which is the STP. The code written after the end statement does not get executed. 
3. The total instruction length is 12 bit including 8 bit instruction address and 4 bit opcode. 
 
 
---> Designing of the code 
1. Label Table : 
The Label table contains all the Labels defined in the main code . 
->Label name : is the name of the label that is defined in the code. 
-> Address : address allotted to the label during the first pass.

2.Symbol Table : 
The Symbol table contains all the variables defined in the main code. 
-> Name : Variable name defined in the main code. 
-> Address : address allotted to the symbol during the first pass. 

---> Error Reporting and handling 
1)Opcode should be valid .
2)A label should be defined before using the branching opcodes. 
3)The program should end with STP .
