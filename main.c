#include <stdio.h>
#include <stdlib.h>	// system()
#include "sound.h"

int main(void){
	while(1){
		// record 1 sec of sound into test.wav
		system("arecord -q -r16000 -c1 -f S16_LE -d1 test.wav");
		// open the wav file and read samples
		displayWAVheader();
		// display necessary information (duration, wav header etc)
		// calculate fast dBs
		// send fast dBs to web (php program on www.cc.puv.fi)
	}
}
