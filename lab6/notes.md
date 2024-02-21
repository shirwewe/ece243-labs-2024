### Lab 6

#### Summary
    - The goal of this lab is to become comfortable with using the C programming language to do embedded system io
    - focusing on sound io

#### Part 1
    - Know the various C  bit-level logical operators
    - AND (&)
    - OR (|)
    - XOR (^)
    - NOT (~)
    - shift left (<<)
    - shift right (>>)
    - Also, note that the pointer arithmetic in C takes into account the byte-addressability of the item being pointed to in **BYTES**

    - The main task: 
        - write a C-language program that turns on all ten red LEDS when button KEY0 is pressed and released
        - and turns them off when KEY1 is pressed
        - program should run continuously
        - should use the edge capture register of the key pushbuttons parallel port
        - DO NOT use interrupts, just poll the register

