/*
* raw(?) I/O
*/
#ifndef _IO_H_
#define _IO_H_

#include "common.h"

KEY get_key(void);
void printc(POSITION pos, char ch, int color);
void gotoxy(POSITION pos);
void set_color(int color);

enum ColorType {
	BLACK,  	//0
	darkBLUE,	//1
	DarkGreen,	//2
	darkSkyBlue,//3
	DarkRed,  	//4
	DarkPurple,	//5
	DarkYellow,	//6
	GRAY,		//7
	DarkGray,	//8
	BLUE,		//9
	GREEN,		//10
	SkyBlue,	//11
	RED,		//12
	PURPLE,		//13
	YELLOW,		//14
	WHITE		//15
} COLOR;

#endif

