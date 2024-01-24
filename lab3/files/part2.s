/* Program to Count the number of 1's in a 32-bit word,
located at InputWord using a subroutine*/


.global _start
_start:
	movia r8, InputWord # r8 will store the address of the inputword
	ldw r4, (r8) # r4 has the contents of the inputword
	call ONES
	stw r2, 4(r8)
	br endiloop
	
ONES:
	movi r2, 0 # keeps track on the number of 1s
ONES_LOOP:
	beq r4, r0, ONES_END
	andi r10, r4, 1
	srli r4, r4, 1
	add r2, r2, r10 # we can use r10 to add straight onto r2
	br ONES_LOOP
	
ONES_END: ret
	
endiloop: br endiloop

InputWord: .word 0x4a01fead

Answer: .word 0
	
	