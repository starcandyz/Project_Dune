/*
* raw(?) I/O
*/
#include "io.h"

void gotoxy(POSITION pos) {
	COORD coord = { pos.column, pos.row }; // 행, 열 반대로 전달
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printc(POSITION pos, char ch, int color) {
	if (color >= 0) {
		set_color(color);
	}
	gotoxy(pos);
	printf("%c", ch);
}

void display_info(POSITION pos, const char* info) {
	gotoxy((POSITION) { 0, pos.row + 1 }); // 상태창 아래에 위치
	printf("상태: %s", info);
}

void clear_info_line(POSITION pos) {
	// 상태창을 지우는 로직
	gotoxy((POSITION) { 0, pos.row + 1 });
	printf("                    ");  // 지울 공간을 공백으로 덮어 씁니다.
}


KEY get_key(void) {
	if (!_kbhit()) {  // 입력된 키가 있는지 확인
		return k_none;
	}

	int byte = _getch();    // 입력된 키를 전달 받기
	switch (byte) {
	case 'q': return k_quit;  // 'q'를 누르면 종료
	case 224:
		byte = _getch();  // MSB 224가 입력 되면 1바이트 더 전달 받기
		switch (byte) {
		case 72: return k_up;
		case 75: return k_left;
		case 77: return k_right;
		case 80: return k_down;
		default: return k_undef;
		}
	case 27: return k_escape; // ESC 키
	case 32: return k_space;
	default: return k_undef;
	}
}
