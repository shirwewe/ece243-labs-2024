.global _start
_start:

.equ LED_BASE, 0xFF200000
.equ KEY_BASE, 0xFF200050
movia sp, 0x20000
movia r8, LED_BASE
movia r9, KEY_BASE
movi r10, 0x1
movi r11, 0x2
movi r12, 0x4
movi r13, 0x8

MAIN_LOOP:
	ldwio r4, (r9)
	call POLL_KEY
	br MAIN_LOOP
	
POLL_KEY:
	subi sp, sp, 4
	stw r16, (sp)
	subi sp, sp, 4
	stw r17, (sp)
	subi sp, sp, 4
	stw r18, (sp)
	mov r16, r4
	beq r16, r10, KEY_ZERO
	beq r16, r11, KEY_ONE
	beq r16, r12, KEY_TWO
	beq r16, r13, KEY_THREE
	br NEXT
	
KEY_ZERO: # stores 1 into LED
	movi r2, 0
	movi r17, 1
	stwio r17, (r8)
	br NEXT

	
KEY_ONE: # increments display number but dont go above 1111
	beq r2, r10, KEY_ZERO
	movi r18, 0xF
	bge r17, r18, NEXT
	addi r17, r17, 1
	stwio r17, (r8)
	br NEXT
	
KEY_TWO:
	beq r2, r10, KEY_ZERO
	movi r18, 1
	ble r17, r18, NEXT
	subi r17, r17, 1
	stwio r17, (r9)
	br NEXT

KEY_THREE:
	beq r2, r10, KEY_ZERO
	movi r17, 0
	stwio r17, (r9)
	movi r2, 1
	br NEXT

NEXT: 
	ldw r18, (sp)
	addi sp, sp, 4
	ldw r17, (sp)
	addi sp, sp, 4
	ldw r16, (sp)
	addi sp, sp, 4
	ret

	
	
	