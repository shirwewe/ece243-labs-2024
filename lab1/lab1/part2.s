.global _start
_start:

/*Part II*/	
	movi r8, 2 /*moves 2 into r8*/
	movi r9, 3 /* moves 3 into r9*/
	
	add r10, r8, r9 /* does r8+r9 and puts the sum into r10*/
	
	done: br done
	