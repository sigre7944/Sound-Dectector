#ifndef __WAVE_H_ 
#define __WAVE_H__ //to prevent defining the struct and declaring the functions more than once
#define SAMPLE_PER_SEC 16000 //number of samples in 1 second
#define FASTSIZE 8	//define constant
//#define DEBUG_INFO

typedef struct{
	char chunkID[4];
	unsigned int chunkSize;
	char format[4];
	char subchunk1ID[4];
	unsigned int subchunk1Size;
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned int sampleRate;
	unsigned int byteRate;
	unsigned short blockAllign;
	unsigned short bitsPerSample;
	unsigned char subchunk2ID[4];
	unsigned int subchunk2Size;
}waveHDR; //struct containing information which will be read from the file

void dispWaveHDR(waveHDR w);
void dispSoundWave(short int [], double []);
void send_dBfast(double df[]);
#endif
