
// Sampled at 8Khz, mono, 32b int per sample


int samples[];

int samples_n =  240000; // audio will run for 30s


void square_wave_gen(int *samples, int frequency){
	float fund_period = 1 / frequency;
	float sample_per_period = fund_period / 0.000125;
	for (int i = 0; i < sample_per_period; i++){
		if(i > sample_per_period / 2){
			samples[i] = 0;
		}
		samples[i] = 0xFFFFF000;
	}
}

void square_wave_gen_30(int frequency){
	for (int i = 0; i < samples_n / 80; i++){
		square_wave_gen(samples, frequency);
	}
	return 0;
}


struct audio_t {
	volatile unsigned int control;
	volatile unsigned char rarc;
	volatile unsigned char ralc;
	volatile unsigned char warc;
	volatile unsigned char walc;
    volatile unsigned int ldata;
	volatile unsigned int rdata;
};

struct audio_t *const audiop = ((struct audio_t *)0xff203040);


void play_audio(int *samples, int n) {
    int i;
    audiop->control = 0x8; // clear the output FIFOs
    audiop->control = 0x0; // resume input conversion
    for (i = 0; i < n; i++) {
        // output data if there is space in the output FIFOs
        if (audiop->warc) {
            audiop->ldata = samples[i];
            audiop->rdata = samples[i];
        }
    }
}	


int main(void) {
	square_wave_gen_30(100);
  	play_audio(samples, samples_n);
  	while (1);
}

