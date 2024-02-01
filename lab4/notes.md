#### Lab 4

**The goal of this lab is to explore the use of devices that provide input and output capabilities for a processor, and to see how a processor connects to those inputs and outputs, through the Memory Mapped method. You’ll also
be introduced to a device that has a special purpose in computer systems, the Timer, which is used for precise
measurement and allocation of time within the computer.**

##### Calling convention review

- r0 is zero
- r8 to r15 is taken care of by the caller
- r16 to r23 is taken care of by the callee (the subroutine)
- r4 to r7 is used to pass to a subroutine
- r2 to r3 is used to return results from the subroutine (if more than 2 result needs to be returned used the stack)

##### Part 1 Notes:
    - when I press key 0 -> data register bit 0 turns into 1 -> when key 0 is released -> data register bit 0 turns into 0
    - I want to detect if key 0 is pressed and act accordingly until the key is released, then I'll poll again
    - If we do not use the edge capture register then we need a method to keep track of when the button is released and when the button is pressed. Because we want to increment the counter only when the button is pressed and released. The CPU can detect when the button is pressed, and branch to an instruction but it also needs to know when to stop executing that instruction, so we need to poll for it again (aka poll for when it's zero again), then we can say that by pressing and releasing a certain key -> something happens accordingly. 
    - In part 2 this will be handled by the edge capture register

##### Part 2 Notes:
    - This part want us to make a binary counter that increments every 0.25 seconds and counts until 255(base 10) which is 0b11111111 (binary) or 0xFF (hex). and restarts from zero. pressing any button will start/stop the counter.
    - the delay loop is a software delay loop 
    - Use 10,000,000 for hardware delay loop for 0.25s and on CPUlator use 500,000 for 0.25 seconds
    - first i need something to tell me if the counter is going or not so i can start/pause it
    - second i need a delay loop so that the counter doesn't increment that fast
    - third, i need a branch that will reset the number when it hits 0xFF

##### Part 3 Notes:
    - Same as part 2 but just replace the delay loop with a hardware timer
    
