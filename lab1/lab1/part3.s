.global _start
_start:

/*Part III*/	
		movi r12, 0 /*moves 0 into r12*/
		movi r9, 1 /* moves 1 into r9*/
		movi r8, 31 /*moves 30 into r8 */
	
	loop:	
		add r12, r12, r9 /* does r8+r9 and puts the sum into r10*/
		addi r9, r9, 1
		beq r9, r8, done
		br loop
	
	done: br done
	
	.equ LEDs, 0xFF200000
	movia r25, LEDs
	stwio r12, (r25)
	