/*
 * contains screen manipulation functions such as clearScreen(), gotoxy(),
 * setColor(), etc.
 */

#include <stdio.h>
#include "screen.h"

void setColor(int color){
	printf("%c[1;%dm", ESC, color);
	fflush(stdout);
}

void clearScreen(void){
	printf("%c[2J", ESC);
	fflush(stdout);
}

void gotoxy(int row, int col){
	printf("%c[%d;%dH", ESC, row, col);
	fflush(stdout);
}

void bar(int col, double dB){
	int i;
	for(i=0;i<dB/4; i++){
		gotoxy(25-i, col+1);	// the first bar starts from col=1
		if(i<(60/4))
			setColor(WHITE);
		else if(i<(80/4))
			setColor(YELLOW);
		else
			setColor(RED);
			
#ifndef UNICODE
		printf("%c", '*');		// if UNICODE is not defined
#else
		printf("%s", BAR);
#endif
	}
	gotoxy(27, 1);
	setColor(WHITE);
}
