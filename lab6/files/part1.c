// this is a program that turns on all the LEDs when KEY0 is pressed and turns all the LEDs off when KEY1 is pressed

#include <stdlib.h>

int main()
{
    volatile int *LEDR_ptr = 0xFF200000;
    volatile int *KEY_ptr = 0xFF200050;


    while (1){
        int edgecapture_bit = *(KEY_ptr + 3) & 0b11;
		// if key0 is pressed
        if (edgecapture_bit == 1){ 
			*(LEDR_ptr) = 0x3FF;
			*(KEY_ptr + 3) = 0xFF;
		}
		if (edgecapture_bit == 2){
			*(LEDR_ptr) = 0;
			*(KEY_ptr + 3) = 0xFF;
		}
		else{
			continue;
		}
    }
}