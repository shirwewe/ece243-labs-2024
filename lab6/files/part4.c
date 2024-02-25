#define AUDIO_BASE			0xFF203040
#define BUF_SIZE 			1500
#define PAUSE_LEN			800


struct audio_t *const audiop = ((struct audio_t *) AUDIO_BASE);
	
int left_buffer[BUF_SIZE];
int right_buffer[BUF_SIZE];

int second_left_buffer[BUF_SIZE];
int second_right_buffer[BUF_SIZE];

int third_left_buffer[BUF_SIZE];
int third_right_buffer[BUF_SIZE];

int fourth_left_buffer[BUF_SIZE];
int fourth_right_buffer[BUF_SIZE];

int fifth_left_buffer[BUF_SIZE];
int fifth_right_buffer[BUF_SIZE];

int pause[PAUSE_LEN];

int buffer_index, pause_index, sample_length;

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

	sample_length = buffer_index;
}

void generate_echo(){
	buffer_index = 0;
	//for (int n = 20; n < 100; n += 20){
		while (buffer_index < BUF_SIZE) { 
			// copy what was in buffer_index original and put another copy right after it, make it quieter
			second_left_buffer[buffer_index]  = left_buffer[buffer_index] * (1 - (20 /100));
			second_right_buffer[buffer_index]  = right_buffer[buffer_index] * (1 - (20 /100)); 

			third_left_buffer[buffer_index]  = left_buffer[buffer_index] * (1 - (40 /100));
			third_right_buffer[buffer_index]  = right_buffer[buffer_index] * (1 - (40 /100)); 

			fourth_left_buffer[buffer_index]  = left_buffer[buffer_index] * (1 - (60 /100));
			fourth_right_buffer[buffer_index]  = right_buffer[buffer_index] * (1 - (60 /100)); 

			fifth_left_buffer[buffer_index]  = left_buffer[buffer_index] * (1 - (80 /100));
			fifth_right_buffer[buffer_index]  = right_buffer[buffer_index] * (1 - (80 /100)); 

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
	buffer_index = 0;
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	while (buffer_index < BUF_SIZE){
		// output data if there is space in the output FIFOs
		if (audiop->wsrc){
			audiop->ldata = second_left_buffer[buffer_index];
			audiop->rdata = second_right_buffer[buffer_index];
			buffer_index++;
		}
	}
}

void third_audio_playback(void){
	buffer_index = 0;
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	while (buffer_index < BUF_SIZE){
		// output data if there is space in the output FIFOs
		if (audiop->wsrc){
			audiop->ldata = third_left_buffer[buffer_index];
			audiop->rdata = third_right_buffer[buffer_index];
			buffer_index++;
		}
	}
}

void fourth_audio_playback(void){
	buffer_index = 0;
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	while (buffer_index < BUF_SIZE){
		// output data if there is space in the output FIFOs
		if (audiop->wsrc){
			audiop->ldata = fourth_left_buffer[buffer_index];
			audiop->rdata = fourth_right_buffer[buffer_index];
			buffer_index++;
		}
	}
}

void fifth_audio_playback(void){
	buffer_index = 0;
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	while (buffer_index <= BUF_SIZE){
		// output data if there is space in the output FIFOs
		if (audiop->wsrc){
			audiop->ldata = fifth_left_buffer[buffer_index];
			audiop->rdata = fifth_right_buffer[buffer_index];
			buffer_index++;
		}
	}
}

void generate_pause(void) {  
	int pause_index = 0;      
	while (pause_index < PAUSE_LEN) { 
		pause[pause_index] = 0;
		pause_index++;
	}
}

void pause_audio_playback(void){
	pause_index = 0;
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	while (pause_index < PAUSE_LEN){
		// output data if there is space in the output FIFOs
		if (audiop->wsrc){
			audiop->ldata = pause[pause_index];
			audiop->rdata = pause[pause_index];
			pause_index++;
		}
	}
}


int main(void) {
	// This is an infinite loop checking the RARC to see if there is at least a single
	// entry in the input fifos.   If there is, just copy it over to the output fifo.
	// The timing of the input fifo controls the timing of the output
	generate_pause();
    while (1) {
		
        int fifospace = audiop -> rarc; // read the audio port fifospace register
        if ((fifospace & 0x000000FF) > 0) // check RARC to see if there is data to read 
        {
			audio_record();
			generate_echo();
            // load both input microphone channels - just get one sample from each
            audio_playback();
			pause_audio_playback();
			second_audio_playback();
			pause_audio_playback();
			third_audio_playback();
			pause_audio_playback();
			fourth_audio_playback();
			pause_audio_playback();
			fifth_audio_playback();
			pause_audio_playback();
			
			
			
			

            // store both of those samples to output channels
			//second_audio_playback();
			

        }
    }
}
