/*
* raw(?) I/O
*/
#include "io.h"

void gotoxy(POSITION pos) {
	COORD coord = { pos.column, pos.row }; // ��, �� �ݴ�� ����
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
	gotoxy((POSITION) { 0, pos.row + 1 }); // ����â �Ʒ��� ��ġ
	printf("����: %s", info);
}

void clear_info_line(POSITION pos) {
	// ����â�� ����� ����
	gotoxy((POSITION) { 0, pos.row + 1 });
	printf("                    ");  // ���� ������ �������� ���� ���ϴ�.
}


KEY get_key(void) {
	if (!_kbhit()) {  // �Էµ� Ű�� �ִ��� Ȯ��
		return k_none;
	}

	int byte = _getch();    // �Էµ� Ű�� ���� �ޱ�
	switch (byte) {
	case 'q': return k_quit;  // 'q'�� ������ ����
	case 224:
		byte = _getch();  // MSB 224�� �Է� �Ǹ� 1����Ʈ �� ���� �ޱ�
		switch (byte) {
		case 72: return k_up;
		case 75: return k_left;
		case 77: return k_right;
		case 80: return k_down;
		default: return k_undef;
		}
	case 27: return k_escape; // ESC Ű
	case 32: return k_space;
	default: return k_undef;
	}
}
