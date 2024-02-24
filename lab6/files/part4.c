#define AUDIO_BASE			0xFF203040
#define BUF_SIZE 			128


struct audio_t *const audiop = ((struct audio_t *) AUDIO_BASE);
	
int left_buffer[BUF_SIZE];
int right_buffer[BUF_SIZE];

int second_left_buffer[BUF_SIZE];
int second_right_buffer[BUF_SIZE];

int buffer_index, second_buffer_index, sound_length;

struct audio_t {
	volatile unsigned int control;  // The control/status register
	volatile unsigned char rarc;	// the 8 bit RARC register
	volatile unsigned char ralc;	// the 8 bit RALC register
	volatile unsigned char wsrc;	// the 8 bit WSRC register
	volatile unsigned char wslc;	// the 8 bit WSLC register
    volatile unsigned int ldata;	// the 32 bit (really 24) left data register
	volatile unsigned int rdata;	// the 32 bit (really 24) right data register
};


void audio_record(void) {        
	audiop->control = 0x4; // clear the input FIFOs
	audiop->control = 0x0; // resume input conversion
	buffer_index = 0;
	while (buffer_index < BUF_SIZE) { 
		// read samples if there are any in the input FIFOs
		if (audiop->rarc) {
			left_buffer[buffer_index] = audiop->ldata;
			right_buffer[buffer_index] = audiop->rdata;
			++buffer_index;
		}
	}
	sound_length = buffer_index;
}

void generate_echo(){
	second_buffer_index = 0;
	buffer_index = 0;
	//for (int n = 20; n < 100; n += 20){
		while (buffer_index < BUF_SIZE) { 
			// copy what was in buffer_index original and put another copy right after it, make it quieter
			second_left_buffer[second_buffer_index]  = left_buffer[buffer_index] * (1 - 50 /100);
			second_right_buffer[second_buffer_index]  = right_buffer[buffer_index] * (1 - 50 /100); 
			buffer_index++;
		}
		
	//}
}

void audio_playback(void){
	int buffer_index = 0;
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	while (buffer_index < BUF_SIZE){
		// output data if there is space in the output FIFOs
		if (audiop->wsrc){
			audiop->ldata = left_buffer[buffer_index];
			audiop->rdata = right_buffer[buffer_index];
			++buffer_index;
		}
	}
}

void second_audio_playback(void){
	int second_buffer_index = 0;
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	while (buffer_index < BUF_SIZE){
		// output data if there is space in the output FIFOs
		if (audiop->wsrc){
			audiop->ldata = second_left_buffer[second_buffer_index];
			audiop->rdata = second_right_buffer[second_buffer_index];
			++buffer_index;
		}
	}
}

void delay(){
	for(int i = 0; i < 100000000; i++){
		for (int n = 0; n < 100000000; n++){}
	}
	return ;
}



int main(void) {
	// This is an infinite loop checking the RARC to see if there is at least a single
	// entry in the input fifos.   If there is, just copy it over to the output fifo.
	// The timing of the input fifo controls the timing of the output
	
    while (1) {
        int fifospace = audiop -> rarc; // read the audio port fifospace register
        if ((fifospace & 0x000000FF) > 0) // check RARC to see if there is data to read 
        {
            // load both input microphone channels - just get one sample from each
            audio_record();
			generate_echo();
			audio_playback();
			delay();
            // store both of those samples to output channels
			second_audio_playback();
			

        }
    }
}
