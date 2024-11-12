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


#define	BLACK  	//0
#define	darkBLUE	//1
#define	DarkGreen	//2
#define	darkSkyBlue //3
#define	DarkRed  	//4
#define	DarkPurple	//5
#define	DarkYellow	//6
#define	GRAY		//7
#define	DarkGray	//8
#define	BLUE		//9
#define	GREEN		//10
#define	SkyBlue		//11
#define	RED			//12
#define	PURPLE		//13
#define	YELLOW		//14
#define	WHITE		//15


#endif

