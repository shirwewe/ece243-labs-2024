.global _start
_start:

.equ LED_BASE, 0xFF200000
.equ KEY_BASE, 0xFF200050
movia r8, LED_BASE
movia r9, KEY_BASE
movi r14, 1 # used to see if key 3 has been pressed



POLL_ZERO:
	ldwio r10, (r9) # r10 will store the data register contents
	andi r10, r10, 1 # check if KEY0 is pressed
	beq r10, r0, POLL_ONE
	CALL KEY_ZERO
	
POLL_ONE:	
	ldwio r10, (r9) # r10 will store the data register contents
	andi r10, r10, 2 # check if KEY1 is pressed
	beq r10, r0, POLL_TWO
	CALL KEY_ONE
	
POLL_TWO:
	ldwio r10, (r9) # r10 will store the data register contents
	andi r10, r10, 4 # check if KEY2 is pressed
	beq r10, r0, POLL_THREE
	CALL KEY_TWO
	
POLL_THREE:
	ldwio r10, (r9) # r10 will store the data register contents
	andi r10, r10, 8 # check if KEY3 is pressed
	beq r10, r0, POLL_ZERO
	CALL KEY_THREE
	br POLL_ZERO
	
# subroutine 1
KEY_ZERO: # stores 1 into LED
	beq r13, r14, SET_ZERO
	movi r12, 1 # r12 will store the current binary number
	br STORE
		
KEY_ONE: # increments display number but dont go above 1111
	beq r13, r14, SET_ZERO
	movi r11, 0xF
	bge r12, r11, STORE
	
KEY_ONE_LOOP:
	ldwio r10, (r9)
	beq r10, r0, KEY_ONE_NEXT
	br KEY_ONE_LOOP
	
KEY_ONE_NEXT:
	addi r12, r12, 1
	br STORE
	
	
# subroutine 2
KEY_TWO: # decreases display number by 1 but don't go below 1
	beq r13, r14, SET_ZERO
	movi r11, 1
	ble r12, r11, STORE
	
KEY_TWO_LOOP:
	ldwio r10, (r9)
	beq r10, r0, KEY_TWO_NEXT
	br KEY_TWO_LOOP
	
KEY_TWO_NEXT:
	subi r12, r12, 1
	br STORE	
	
# subroutine 3	
KEY_THREE: # resets to zero and any other button pressed after sets the counter to 1
	beq r13, r14, SET_ZERO
	movi r13, 1 # r13 will keep track of if KEY3 has been pressed or now
	
KEY_THREE_LOOP:
	ldwio r10, (r9)
	beq r10, r0, KEY_THREE_NEXT
	br KEY_THREE_LOOP

KEY_THREE_NEXT:
	mov r12, r0
	br STORE

# branches that all subroutines can call 
STORE: # stores into leds and returns subroutine
	stwio r12, (r8)
	ret

# this branch allows any key to set number to 1 after KEY3 has been called
SET_ZERO:
	movi r13, 0 # reset r13 back to 0 because we have now called on another button adter r13
	
SET_ZERO_LOOP:
	ldwio r10, (r9)
	beq r10, r0, SET_ZERO_NEXT
	br SET_ZERO_LOOP
	
SET_ZERO_NEXT:
	call KEY_ZERO
	br POLL_ZERO

	
	

	
	
	