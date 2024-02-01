.global _start
_start:
	.equ COUNTER_DELAY, 500000
	.equ LED_BASE, 0xFF200000
	.equ KEY_BASE, 0xFF200050
	movia r8, LED_BASE
	movia r9, KEY_BASE
	movi r10, 0 # r10 has the counter number
	movi r12, 0 # r12 is 1, counter is going; r12 is 0, counter is paused
	movi r13, 0xFF # for resetting edge capture and comparing with 255

POLL_KEY:
	ldwio r11, 0xc(r9) # load the edge capture register into r11
	andi r11, r11, 15
	beq r11, r0, CHECK_START_STOP
	bne r12, r0, POLL_KEY
	

CHECK_START_STOP:
	bne r12, r0, ADD_COUNT
	br POLL_KEY
	

ADD_COUNT:
	stwio r13, 0xC(r9)
	movi r12, 1 # indicates that the counter has started
	addi r10, r10, 1 #increases the counter
	call DO_DELAY
	stwio r10, (r8)
	br POLL_KEY
	
DO_DELAY: 
	movia r16, COUNTER_DELAY
	
SUB_LOOP:
	subi r16, r16, 1
	bne r16, r0, SUB_LOOP
	ret




	
	
	