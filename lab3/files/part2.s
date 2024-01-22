/* Program to Count the number of 1's in a 32-bit word,
located at InputWord using a subroutine*/

.global _start
_start:
	movia r8, InputWord #r8 will store the address of the inputword
	ldw r4, (r8) #r4 has the contents of the inputword
	movi r11, 1
	movi r2, 0 #keeps track on the number of 1's
	call ONES
	stw r2, 4(r8)
	br endiloop
	
ONES:
	beq r4, r0, DONE
	andi r10, r4, 1
	srli r4, r4, 1
	beq r10, r11, add_one
	br ONES
	
add_one:
	addi r2, r2, 1
	br ONES  
	
DONE: ret
	
endiloop: br endiloop

InputWord: .word 0x4a01fead

Answer: .word 0
	
	