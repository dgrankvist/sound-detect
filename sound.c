#include "sound.h"
#include <stdio.h>
#include <math.h>

// function definition of displayBar()
// this function opens the "test.wav" file and reads the second part (data)
// of the file, and the samples should be in S16_LE format, and there are
// 16000 of them. The function processes every 200 samples and calculates
// their RMS value and renders this value as a bar on terminal screen.
void displayBar(char filename[]){
	FILE *fp;
	short int samples[SAMPLERATE];
	double sum_200, rms_80[80], dB;
	int i, j;
	WAVHeader myhdr;			// dummy header to skip over reading from file
	fp = fopen(filename, "r");
	if(fp == NULL){
		printf("ERROR opening file!\n");
		return;
	}
	fread(&myhdr, sizeof(WAVHeader), 1, fp);
	fread(&samples, sizeof(short), SAMPLERATE, fp);
	fclose(fp);
	// all the samples of 1 sec are read to the array samples[], we need to run
	// a loop 80 times for 80 bars on the screen, and each iteration of this loop
	// will calculate a RMS value of 200 samples.
	clearScreen();
	for(i=0; i<80; i++){
		for(j=0, sum_200=0.0; j<200; j++){
			sum_200 += samples[j+i*200]*samples[j+i*200];	
		} // for
		rms_80[i] = sqrt(sum_200/200);
		//in order to display sound value in a screen, we need to use decibel
		dB = 20*log10(rms_80[i]);
#ifdef DEBUG
		printf("RMS[%d] = %10.4f = %10.4fdB\n", i, rms_80[i], dB);
#else
		bar(dB, i);
#endif
	} // for
} // function

// function definition of displayWAVheader()
void displayWAVheader(char filename[]){
	WAVHeader myhdr;			// an instance of defined struct
	FILE *fp;
	fp = fopen(filename, "r");	// open the file for reading
	if(fp == NULL){				// if fopen is failed
		printf("ERROR opening file!\n");
		return;
	}
	fread(&myhdr, sizeof(WAVHeader), 1, fp);
	fclose(fp);
	printID(myhdr.chunkID);
	printf("chunk size: %d\n", myhdr.chunkSize);
	printID(myhdr.format);
	printID(myhdr.subchunk1ID);
	printf("subchunk 1 size: %d\n", myhdr.subchunk1Size);
	printf("audio format: %d\n", myhdr.audioFormat);
	printf("number of channels: %d\n", myhdr.numChannels);
	printf("sample rate: %d\n", myhdr.sampleRate);
	printf("byte rate: %d\n", myhdr.byteRate);
	printf("block align: %d\n", myhdr.blockAlign);
	printf("bits per sample: %d\n", myhdr.bitsPerSample);
	printID(myhdr.subchunk2ID);
	printf("subchunk 2 size: %d\n", myhdr.subchunk2Size);
}

void printID(char id[]){
	int i;
	for(i=0; i<4; i++)
		printf("%c", id[i]);
	printf("\n");
}
