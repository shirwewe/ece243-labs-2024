### Lab 6

#### Summary
    - The goal of this lab is to become comfortable with using the C programming language to do embedded system io
    - focusing on sound io

##### Notes for future CPUlator sound generation, remember to dynamically allocate memory and set the cpu sampling rate to 8k instead of 48000

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

#### Part 2
    - can be struct based or just accessing pointer
    - takes sound from microphone and puts it onto the speaker

#### Part 3
    - generated a square wave using function square_wave_gen
    - takes in the frequency and a sample and sets high values to 0x0FFFFFFF and low values to 0
    - the sampling frequency is 8K
    - switched change the frequency it produces
    

#### Part 4
    - similar to part 2 but the sound has an echo
    - output = input + D * Input (t-N)
    - where D is the dampling constant
