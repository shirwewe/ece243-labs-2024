/* Program to Count the number of 1's in a 32-bit word,
located at InputWord */

.global _start
_start:
	movia r8, InputWord #r8 will store the address of the inputword
	ldw r9, (r8) #r9 has the contents of the inputword
	movi r11, 1
	movi r12, 0 #keeps track on the number of 1's
	
iloop: 
	beq r9, r0, store
	andi r10, r9, 1
	srli r9, r9, 1
	beq r10, r11, add_one
	br iloop
	
add_one:
	addi r12, r12, 1
	br iloop
		
store: stw r12, 4(r8)
	
endiloop: br endiloop

InputWord: .word 0x4a01fead

Answer: .word 0
	
	