/*
 * contains screen manipulation functions such as clearScreen(), gotoxy(),
 * setColor(), etc.
 */

#include <stdio.h>
#include "screen.h"


/* Function definition of setColor(). Uses VT100 escape sequence "\ESC[1;colorm"
 * where color is given in the enumerated type in screen.h 
 * Input argument: int color: color, values of the constants defined in screen.h
 * Output argument: none
 */
void setColor(int color){
	printf("%c[1;%dm", ESC, color);
	fflush(stdout);
}

/*
 * Function definition of clearScreen(). Uses VT100 escape sequence "\ESC[2J" to
 * erase the entire terminal screen. 
 * Input argument: none
 * Return argument: none
 */
void clearScreen(void){
	printf("%c[2J", ESC);
	fflush(stdout);
}

/* Function definition of gotoxy(). Uses VT100 escape sequence "\ESC[row,colH"
 * to set cursor to the specific location of the terminal screen.
 * Input argument:
 * 		int row: row number (1 is top)
 * 		int col: column number (1 is left)
 * Return argument: none
 */
void gotoxy(int row, int col){
	printf("%c[%d;%dH", ESC, row, col);
	fflush(stdout);
}

/* Function definition of bar(). Draws a bar in the terminal to visualize the sound
 * level. The decibel value is divided by 4 to limit the number of rows used in the
 * terminal window.
 * Input arguments:
 * 		int col: column number
 *		double dB: calculated decibel value of the sound level
 * Return argument: none
 */
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
