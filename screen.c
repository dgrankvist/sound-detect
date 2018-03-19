/*
 * contains screen manipulation functions such as clearScreen(), gotoxy(),
 * setColor(), etc.
 */

#include <stdio.h>
#include "screen.h"

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
		printf("%c", '*');
	}
}
