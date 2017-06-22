#include "appdevwave.h"
#include <stdio.h>
#include "screen.h"
#include <math.h>
#include <curl/curl.h>

//display information about the wave file
void dispWaveHDR(waveHDR w){
	int i;
	clearScreen();
//if the debug mode is on, print the following details
#ifdef DEBUG_INFO
	printf("ChunkID: ");
	for(i=0; i<4; i++)
	{
		printf("%c", w.chunkID[i]);
	}
	puts("");
	printf("Chunk size: %d\n", w.chunkSize);
	printf("Format: ");
	for (i=0; i<4; i++){
		printf("%c", w.format[i]);
	}
	puts("");
	for(i=0; i<4; i++) printf("%c", w.subchunk1ID[i]);
	puts("");
	printf("Subchunk1 Size: %d\n", w.subchunk1Size);
	printf("Audio Format: %d\n", w.audioFormat);
	printf("Number of channels: %d\n", w.numChannels);
	printf("Sample rate: %d\n", w.sampleRate);
	printf("Byte rate: %d\n", w.byteRate);
	printf("Block align: %d\n", w.blockAllign);
	printf("Bits per sample: %d\n", w.bitsPerSample);
	for(i=0;i<4;i++) printf("%c", w.subchunk2ID[i]);
	puts("");
	printf("Subchunk2 size: %d\n", w.subchunk2Size);
	printf("Duration of this sound track: %.2f\n", (double)w.subchunk2Size/w.byteRate);
//if debug mode is off, print the following information with the set colors
#else
	gotoxy(1,1);
	setColors(CYAN, bg(BLACK));
	printf("sample.wave"); fflush(stdout);
	gotoxy(15,1);
	setColors(YELLOW, bg(BLUE));
	printf("N.Ch.:%1d", w.numChannels); fflush(stdout);
	gotoxy(25,1);
	setColors(WHITE, bg(GREEN));
	printf("Bs/Sp:%2d", w.bitsPerSample); fflush(stdout);
	gotoxy(35,1);
	setColors(RED, bg(BLACK));
	printf("DUR:%6.2f", (double)w.subchunk2Size/w.byteRate);
	fflush(stdout);
#endif
}
//calculate the db value and display the wave
void dispSoundWave(short int s[], double df[]){
	int i,j;    
	double sumRMS, rms, rmsdB, sumdf;
#ifdef DEBUG_INFO //if debug mode is on, print the dB value in a list
	for(i=0; i<80; i++){
		for(j=0, sumRMS = 0.0; j<200; j++){
			sumRMS += s[i*200+j]*s[i*200+j];
		}
	rms = sqrt(sumRMS)/200;	//RMS value 
	rmsdB = 20*log10(rms);	//dB value
	printf("chunk %d: %10.2f, in dB =  %10.2f\n", i, rms, rmsdB);
	}
#else //if debug mode is off, display the wave
	for(i=0; i<80; i++){
		for(j=0, sumRMS = 0.0; j<200; j++){
			sumRMS += s[i*200+j]*s[i*200+j];
		}
		rms = sqrt(sumRMS)/200;	//RMS value
		rmsdB = 20*log10(rms);	//dB value
		if(rmsdB > 50) setColors(YELLOW, bg(RED)); //change the colors if dB value is more than 50
		else setColors(WHITE, bg(BLACK));
		dispBar(i+1, 30-round(rmsdB/2.5), 30); //display the bar
		fflush(stdout);	
		resetColors();
	}

#endif
// calculate and store 8 pieces of dB data into an array
	for(i=0; i<FASTSIZE; i++){
		for(j=0, sumdf=0.0; j<SAMPLE_PER_SEC/FASTSIZE; j++){
			sumdf += s[i*2000+j]*s[i*2000+j];
		}
		rms = sqrt(sumdf)/2000;
		df[i] = 20*log10(rms);
	}

}
//sending the dB data
void send_dBfast(double df[]){
	int i;
#ifdef DEBUG_INFO //if debug mode is on, just print out the dB array
	printf("----------------------------------------------------------------\n");
	for(i=0; i<FASTSIZE; i++)
		printf("dB(%d)-%5.2f\n", i+1, df[i]);
	printf("-----------------------------------------------------------------\n");
#else //if debug mode is off, send the data to the website
	CURL *curl;
	CURLcode res;
	char postdata[200];
	sprintf(postdata, "df%d=%6.2f&df%d=%6.2f&df%d=%6.2f&df%d=%6.2f&df%d=%6.2f&df%d=%6.2f&df%d=%6.2f&df%d=%6.2f",
	 1, df[0], 2, df[1], 3, df[2], 4, df[3], 5, df[4], 6, df[5], 7, df[6], 8, df[7]);  
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl){
		printf("sending %s\n", postdata);	
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.cc.puv.fi/~e1500968/php/input.php");  //URL for receiving the data
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);	
		res = curl_easy_perform(curl);
		if(res != CURLE_OK) printf("Cannot send!\n");	//notify if there's any error
		curl_easy_cleanup(curl);	//close the connection
	}
	curl_global_cleanup();
#endif
}
