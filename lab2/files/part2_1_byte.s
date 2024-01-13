.text  # The numbers that turn into executable instructions
.global _start # grade is stored in bytes
_start:

/* r13 should contain the grade of the person with the student number, -1 if not found */
/* r10 has the student number being searched */


	movia r10, 718293		# r10 is where you put the student number being searched for

/* Your code goes here  */

	movia r8, Snumbers # r8 contains the address of Snumbers
	movia r9, Grades # r9 contains the address of grades
	movi r14, 0 # r14 will tell us how many addresses was added onto r8
	movi r15, 4 # used to offset byte for grade
	
search: 
	ldw r11,(r8) # r11 containst the Snumber we are currently on
	beq r11, r0, noSnumber #if no matching student number is fount branch to noSnumber
	beq r11, r10, loadGrade # Snumber is found, find grade
	addi r14, r14, 4 #increase address of Snumber by 4
	addi r8, r8, 4 # go to the next Snumber
	br search

loadGrade:
	div r14, r14, r15
	add r9, r9, r14 #adds r14 to address of grades
	ldb r13, (r9) #loads grade into r13
	br iloop

noSnumber: movi r13, -1
	
iloop: br iloop


.data  	# the numbers that are the data 

/* result should hold the grade of the student number put into r10, or
-1 if the student number isn't found */ 

result: .word 0
		
/* Snumbers is the "array," terminated by a zero of the student numbers  */
Snumbers: 
		.word 10392584, 423195, 644370, 496059, 296800
        .word 265133, 68943, 718293, 315950, 785519
        .word 982966, 345018, 220809, 369328, 935042
        .word 467872, 887795, 681936, 0

/* Grades is the corresponding "array" with the grades, in the same order*/
Grades: .byte 99, 68, 90, 85, 91, 67, 80
        .byte 66, 95, 91, 91, 99, 76, 68  
        .byte 69, 93, 90, 72
	
	
