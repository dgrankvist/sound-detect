#include "sound.h"
#include "screen.h"
#include "comm.h"
#include <stdio.h>
#include <math.h>

// function definition of displayBar()
// this function opens the "test.wav" file and reads the second part (data)
// of the file, and the samples should be in S16_LE format, and there are
// 16000 of them. The function processes every 200 samples and calculates
// their RMS value and renders this value as a bar on terminal screen.
// Input argument: char filename[]: String containing the filename given called in main.c
// Output argument: none
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
	
	// clearScreen();
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
		bar(i, dB);
#endif
	} // for
#ifdef COMM		// conditional compilation
	sendToServer(rms_80);
#endif
} // function

// function definition of displayWAVheader(). Displays wavefile header information on screen
// (hidden unless conditional compitiling with DEBUG is used).
// Input argument: char filename[]: String containing the filename given called in main.c
// Output argument: none
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
#ifdef DEBUG	
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
#else
	// display at top of screen
	gotoxy(1, 3);
	setColor(WHITE);
	printf("%s", filename);
	gotoxy(1, 15);
	setColor(GREEN);
	printf("Channels: %d", myhdr.numChannels);
	gotoxy(1, 30);
	setColor(CYAN);
	printf("Sample rate: %d Hz", myhdr.sampleRate);
	gotoxy(1, 55);
	setColor(MAGENTA);
	printf("Dur: %ds", myhdr.subchunk2Size/myhdr.byteRate);
	setColor(0);

#endif
}

// function definition of printID(). Prints text information from
// the wave header to display in the header information.
// Input argument: char id[]: string containing the header field name
// Output argument: none
void printID(char id[]){
	int i;
	for(i=0; i<4; i++)
		printf("%c", id[i]);
	printf("\n");
}
