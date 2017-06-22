#include <stdio.h>
#include "appdevwave.h"
#include <stdlib.h>
#include "screen.h"
#include <curl/curl.h>>
int main(int argc, char *argv[])
{
	waveHDR mywaveHDR; //struct for header information
	double dBfast[FASTSIZE]; //array with 8 data pieces for sending
	short int samples[SAMPLE_PER_SEC];	//array with 16000 samples for each second
	FILE *fp;	
	while(1){
		system("arecord -r 16000 -c 1 -d 1 -f S16_LE -q sample.wav"); //command to record into a wave file in 1 second
		fp = fopen("sample.wav", "rb");	//open the file in binary mode
		if(fp==NULL) {
			printf("Cannot open the file.\n"); exit(1);}
			//if the file doesn't exist, notify of the error
		fread(&mywaveHDR, sizeof(mywaveHDR), 1, fp);	//read the file's information
		dispWaveHDR(mywaveHDR);	//display file specification
		fread(&samples, sizeof(short int), SAMPLE_PER_SEC, fp); //read all samples 
		dispSoundWave(samples, dBfast);	 //display the soundwave
		send_dBfast(dBfast); //send the information to the webpage
		fclose(fp);
	}
}
