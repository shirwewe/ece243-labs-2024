### LAB 5

Summary: Interrupt and Hex Displays 
Goal: To understand the use of interrupts fro the NIOS II processor and to get some practice with subroutines, modularity and learning how to use HEX displays

#### Part 1
- there is a subroutine that displays any 4 bit hexadecimal digit on any one of the six hex 7 segment displays hex0-hex5
- the subroutine takes in two parameters
    - the low-order 4 bits of register r4 give the 4-bit value to be display (turns on of the 16 hex digits) 
    - r5 says which of the six HEX digits to display that digit on
    - the display can be blanked by turning on bit 4 of r4 (aka the fifth bit counting from 0)

- **the main goal is this part is to write an assembly program that demonstrates the full functionality of the porivded hex_disp subroutine**. DO NOT USE interrupts, make it short


#### Part 2
- write a program  that will display specific numbers on HEX0 to HEX3 display in response to the press and release of the four KEY pushbuttons
- KEYi is pressed and released then display HEXi will be set to display the number i
- when KEYi is again pressed and released, then display HEXi will become blank

#### Part 3
- we need to build an interrupt-based program that control sthe LEDR lights
- displays a binary counter which will be incremented at a certain rate by our program
- We must enable the timer and key pushbutton interrupt
- configurate timer so that every 0.25 seconds the counter goes

#### Part 4 
- We need to vary the speed at which the counter displayed on the red lights is incremented
- when key0 is pressed, it stops start the incrementing of the COUNT variable
- key1 doubles the incrementation rate
- key2 halves the rate
- q 