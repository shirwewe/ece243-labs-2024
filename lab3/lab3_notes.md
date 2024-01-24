## LAB 3

Learning objectives: logic shift, using subroutines, how transfer of control works and parameter passing, memory-mapped IO, software delay loops

Submit: parts 1 - 4

Part 1: Counts the number of ones in binary number of a given 32 bit word
Part 2: Make the Part 1 code into a subroutine
Part 3: Calls the ONES subroutine twice in a loop
Part 4: Display Output on LEDs

A note on stack pointer and subroutines
    - the subroutine is in charge of pushing registers onto the stack that it uses. it  will always return the registers to the previous values after using it. (only valid for registers r8-r15)
    - for registers r4-r7 they are not guarenteed to stay the same, because they are used to pass by values between subroutines.
    - if we use nested subroutines, do not forget to add the return address of the previous subroutine onto the stack pointer.
