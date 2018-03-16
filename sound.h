/* header file for processing sound (WAV) file
 * define the WAV header
 */

typedef struct{
	char chunkID[4];		// "RIFF"
	unsigned int chunkSize; // 4 bytes
	char format[4];			// "WAVE"
	char subchunkID[4];		// "fmt "
	unsigned int subchunk1Size;
	unsigned short audioFormat;
}
