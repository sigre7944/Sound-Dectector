#include <stdio.h>  
#include "screen.h"
//the vertical bars are displayed from x and y coordinates to the bottom
void dispBar(short x, short y, short bottom)
{
	int i;
	for(i=y; i<bottom; i++){
		gotoxy(x, i); 

		printf("%s", BAR);
	}
	fflush(stdout);
}
//clear the screen
void clearScreen(void)
{
	printf("\033[2J");
	fflush(stdout);
}
//the cursor is moved to the x and y coordinates
void gotoxy(short x, short y)
{
	printf("\033[%d;%dH", y, x);
	fflush(stdout);
}
//using Ansi Escape Sequence and change the background and foreground color
void setColors(short fg, short bg)
{
	printf("\033[%d;%dm", fg, bg);
	fflush(stdout);
}
//reset the color of the background and foreground to default value 
void resetColors(void){
	printf("\033[m");
	fflush(stdout);
}

