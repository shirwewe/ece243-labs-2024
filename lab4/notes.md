#### Lab 4

**The goal of this lab is to explore the use of devices that provide input and output capabilities for a processor, and to see how a processor connects to those inputs and outputs, through the Memory Mapped method. You’ll also
be introduced to a device that has a special purpose in computer systems, the Timer, which is used for precise
measurement and allocation of time within the computer.**

Calling convention review

- r0 is zero
- r8 to r15 is taken care of by the caller
- r16 to r23 is taken care of by the callee (the subroutine)
- r4 to r7 is used to pass to a subroutine
- r2 to r3 is used to return results from the subroutine (if more than 2 result needs to be returned used the stack)
