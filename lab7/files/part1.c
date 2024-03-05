/* This files provides address values that exist in the system */

/* Cyclone V FPGA devices */
#define LEDR_BASE             0xFF200000
#define HEX3_HEX0_BASE        0xFF200020
#define HEX5_HEX4_BASE        0xFF200030
#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
#define TIMER_BASE            0xFF202000
#define PIXEL_BUF_CTRL_BASE   0xFF203020
#define CHAR_BUF_CTRL_BASE    0xFF203030

/* VGA colors */
#define WHITE 0xFFFF
#define YELLOW 0xFFE0
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define GREY 0xC618
#define PINK 0xFC18
#define ORANGE 0xFC00

#define ABS(x) (((x) > 0) ? (x) : -(x))

/* Screen size. */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240

/* Constants for animation */
#define BOX_LEN 2
#define NUM_BOXES 8

#define FALSE 0
#define TRUE 1

#include <stdlib.h>
#include <stdio.h>

/* This program implements a line drawing algorithm */
#define ABS(x) (((x) > 0) ? (x) : -(x))

int pixel_buffer_start;
int resolution_x, resolution_y; 	// VGA screen size
int sizeof_pixel;						// number of bytes per pixel
int video_m, video_n;				// number of bits in VGA y coord (m), x coord (n)

void get_screen_specs(void);
void wait_for_vsync(void);

void clear_screen(void);
void plot_pixel(int, int, short int);
void draw_line(int, int, int, int, int);

void clear_screen(){
	for (int x = 0; x < 320; x++){
		for(int y = 0; y < 240; y++){
			plot_pixel(x, y, 0);
		}
	}
}


void draw_line(int x0, int y0, int x1, int y1, int colour){
	int temp, y_step;
	int is_steep = ABS(y1 - y0) > ABS(x1 - x0);
	if(is_steep){
		temp = x0;
		x0 = y0;
		y0 = temp;
	
		temp = x1;
		x1 = y1;
		y1 = temp;
	}
	
	if(x0 > x1){
		temp = x0;
		x0 = x1;
		x1 = temp;
		
		temp = y0;
		y0 = y1;
		y1 = temp;
	}
	
	int delta_x = x1 - x0;
	int delta_y = ABS(y1 - y0);
	int error = -(delta_x/2);
	int y = y0;
	
	if (y < y1){
		y_step = 1;
	}
	
	else{
		y_step = -1;
	}
	
	for (int x = x0; x < x1; x++){
		if (is_steep){
			plot_pixel(y, x, colour);
		}
		else{
			plot_pixel(x, y, colour);	
		}
		error = error + delta_y;
		if(error > 0){
			y = y + y_step;
			error = error - delta_x;
		}
	}	
}



int main(void)
{

    volatile int * pixel_ctrl_ptr = (int *)PIXEL_BUF_CTRL_BASE; // pixel controller

    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    clear_screen();
    draw_line(0, 0, 150, 150, 0x001F);   // this line is blue
    draw_line(150, 150, 319, 0, 0x07E0); // this line is green
    draw_line(0, 239, 319, 239, 0xF800); // this line is red
    draw_line(319, 0, 0, 239, 0xF81F);   // this line is a pink color
}


void plot_pixel(int x, int y, short int line_color)
{
    *(volatile short int *)(pixel_buffer_start + (y<<10) + (x<<1)) = line_color;
}
