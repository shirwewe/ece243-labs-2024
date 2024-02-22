#include <stdio.h>
#include <stdlib.h>





int samples_n =  240000; // audio will run for 30s
void square_wave_gen(int *samples, double frequency){
int low = 1;
int multiplier = 1;
double fund_period = 1 / frequency;
double sample_per_period = fund_period / 0.000125;
for (int i = 0; i < samples_n; i++){
	if(i < multiplier * sample_per_period/2 && low){
		samples[i] = 0;
	}
	else if (i == multiplier * sample_per_period/2 && low){
		multiplier++;
		low = 0;
		samples[i] = 0xFFFFF000;
	}
	else if (i == multiplier * sample_per_period/2 && !(low)){
		multiplier++;
		low = 1;
		samples[i] = 0;
	}
	else{
		samples[i] = 0xFFFFF000;
	}
	
	}
}


// int samples[];


// int samples_n =  240000; // audio will run for 30s


// void square_wave_gen(int *samples, double frequency){
// 	double fund_period = 1 / frequency;
// 	double sample_per_period = fund_period / 0.000125;
// 	for (int i = 0; i < sample_per_period; i++){
// 		if(i > sample_per_period / 2){
// 			samples[i] = 0;
// 			continue;
// 		}
// 		samples[i] = 0xFFFFF000;
// 	}
// }

int main(){
    // Write C code here
	int samples_n =  240000; // audio will run for 30s
	int* samples; 
	samples = (int*)calloc(240000, sizeof(int));
	square_wave_gen(samples, 100);
    for (int i = 0; i < 1000; i++){
        printf("%d", samples[i]);
    }
}