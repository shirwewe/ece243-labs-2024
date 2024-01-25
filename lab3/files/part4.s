.text
/* Program to Count the number of 1's and Zeroes in a sequence of 32-bit words,
and determines the largest of each */

.global _start
_start:
	movia sp, 0x20000 # initializes the stack pointer
	movia r8, TEST_NUM # r8 will store the address of the inputword
	movia r9, LargestOnes # r9 will store the address of LargestOnes
	movia r10, LargestZeroes # r10 will store the address of LargestZeroes
	movia r3, 0xFFFFFFFF
	
	ldw r11, (r9) # r11 will have the largest ones
	ldw r12, (r10) # r12 will have the largest zeroes
	
MAIN_LOOP:
	ldw r4, (r8) # r4 has the contents of the inputword
	beq r4, r0, STORE_TO_MEMORY
	addi r8, r8, 4 # loop to the next number
	call ONES # the return address will be bgt r2, r9, STORE_ONE
	bgt r2, r11, MOVE_ONES
	br CALL_ZEROES
	
MOVE_ONES: 
	mov r11, r2
	
CALL_ZEROES:
	call ZEROES
	bgt r2, r12, MOVE_ZEROES
	br MAIN_LOOP
	
MOVE_ZEROES:
	mov r12, r2
	br MAIN_LOOP 
	
STORE_TO_MEMORY:
	stw r11, (r9)
	stw r12, (r10)
	br endiloop
	
ZEROES:
	subi sp, sp, 4
	stw ra, (sp) # stores the ra onto the stack
	xor r4, r4, r3
	call ONES
	ldw ra, (sp) #store the value of r10 in the stack
	addi sp, sp, 4 # we will be using r10 in the ones subroutine
	ret 

ONES:
	subi sp, sp, 4
	stw ra, (sp) # stores the ra onto the stack
	subi sp, sp, 4 # we will be using r10 in the ones subroutine
	stw r12, (sp) #store the value of r10 in the stack
	subi sp, sp, 4 # we will be using r10 in the ones subroutine
	stw r11, (sp) #store the value of r10 in the stack
	subi sp, sp, 4 # we will be using r10 in the ones subroutine
	stw r10, (sp) #store the value of r10 in the stack
	subi sp, sp, 4 # we will be using r10 in the ones subroutine
	stw r9, (sp) #store the value of r10 in the stack
	subi sp, sp, 4 # we will be using r10 in the ones subroutine
	stw r8, (sp) #store the value of r10 in the stack
	
	movi r8, 0 # keeps track on the number of 1s
	mov r9, r4 # r9 will store the number to be compared
	
ONES_LOOP:
	beq r9, r0, ONES_DONE # if done looping through, then compare with previous word
	andi r10, r9, 1
	srli r9, r9, 1
	add r8, r8, r10 # we can use r10 to add straight onto r8
	br ONES_LOOP

ONES_DONE: 
	mov r2, r8
	ldw r8, (sp) #store the value of r10 in the stack
	addi sp, sp, 4 # we will be using r10 in the ones subroutine
	ldw r9, (sp) #store the value of r10 in the stack
	addi sp, sp, 4 # we will be using r10 in the ones subroutine
	ldw r10, (sp) #store the value of r10 in the stack
	addi sp, sp, 4 # we will be using r10 in the ones subroutine
	ldw r11, (sp) #store the value of r10 in the stack
	addi sp, sp, 4 # we will be using r10 in the ones subroutine
	ldw r12, (sp) #store the value of r10 in the stack
	addi sp, sp, 4 # we will be using r10 in the ones subroutine
	ldw ra, (sp) #store the value of r10 in the stack
	addi sp, sp, 4 # we will be using r10 in the ones subroutine
	ret

endiloop:
	.equ LEDs, 0xFF200000 
	movia r25, LEDs
	stwio r11, (r25)
	call delay
	stwio r12, (r25)
	call delay
    br endiloop
	
delay:
	movia r13, 9999999
delay_loop:
	subi r13, r13, 1
	beq r13, r0, TIMER_END
	br delay_loop
TIMER_END: ret
	

.data
TEST_NUM:  .word 0x4a01fead, 0xF677D671,0xDC9758D5,0xEBBD45D2,0x8059519D
            .word 0x76D8F0D2, 0xB98C9BB5, 0xD7EC3A9E, 0xD9BADC01, 0x89B377CD, 0x00000001
            .word 0  # end of list 

LargestOnes: .word 0
LargestZeroes: .word 0