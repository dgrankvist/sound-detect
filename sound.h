//#define DEBUG
/*
 * header file for processing sound (WAV) file
 * define the WAV header
 */

// constant definitions
#define SAMPLERATE 16000

// define the structure of the WAV header file
typedef struct{
	char chunkID[4];			// "RIFF"
	unsigned int chunkSize;		// 4 bytes
	char format[4];				// "WAVE"
	char subchunk1ID[4];		// "fmt "
	unsigned int subchunk1Size;
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned int sampleRate;
	unsigned int byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char subchunk2ID[4];		// "data"
	unsigned int subchunk2Size;
}WAVHeader;

// function prototypes
void displayWAVheader(char filename[]);
void displayBar(char filename[]);
void printID(char ID[]);
