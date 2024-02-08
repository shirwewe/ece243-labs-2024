.global _start
_start:

/*Part III*/
	.equ LEDs, 0xFF200000	
		movi r12, 0 /*moves 0 into r12*/
		movi r9, 1 /* moves 1 into r9*/
		movi r8, 31 /*moves 30 into r8 */
	
	loop:	
		add r12, r12, r9 /* adds r9 to r12*/
		addi r9, r9, 1 /*increases r9 by 1 */
		beq r9, r8, done 
		br loop
	
	done: 
		movia r25, LEDs
		stwio r12, (r25)
		br done
	
	
	
	