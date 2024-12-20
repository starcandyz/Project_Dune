/*
*  display.c:
* 화면에 게임 정보를 출력
* 맵, 커서, 시스템 메시지, 정보창, 자원 상태 등등
* io.c에 있는 함수들을 사용함
*/

#include "display.h"
#include "io.h"

// 출력할 내용들의 좌상단(topleft) 좌표
const POSITION resource_pos = { 0, 0 };
const POSITION map_pos = { 1, 0 };


char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };

char backmessage[SYSTEM_MESSAGE_H][SYSTEM_MESSAGE_W] = { 0 };
char frontmessage[SYSTEM_MESSAGE_H][SYSTEM_MESSAGE_W] = { 0 };

char backinfo[OBJECT_INFO_H][OBJECT_INFO_W] = { 0 };
char frontinfo[OBJECT_INFO_H][OBJECT_INFO_W] = { 0 };

char backcommands[COMMANDS_H][COMMANDS_W] = { 0 };
char frontcommands[COMMANDS_H][COMMANDS_W] = { 0 };

void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]);
void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]);
void display_cursor(CURSOR cursor);
void display_system_message(char message[SYSTEM_MESSAGE_H][SYSTEM_MESSAGE_W]);
void display_object_info(char info[OBJECT_INFO_H][OBJECT_INFO_W]);
void display_commands(char commands[COMMANDS_H][COMMANDS_W]);


void display(
	RESOURCE resource,
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	char message[SYSTEM_MESSAGE_H][SYSTEM_MESSAGE_W],
	char info[OBJECT_INFO_H][OBJECT_INFO_W],
	char commands[COMMANDS_H][COMMANDS_W],
	CURSOR cursor)
{
	display_resource(resource);
	display_map(map);
	display_cursor(cursor);
	display_system_message(message);
	display_object_info(info);
	display_commands(commands);
	// ...
}

void display_resource(RESOURCE resource) {
	set_color(COLOR_RESOURCE);
	gotoxy(resource_pos);
	printf("spice = %d/%d, population=%d/%d\n",
		resource.spice, resource.spice_max,
		resource.population, resource.population_max
	);
}

void display_initial_state(RESOURCE resource, char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) {
	CURSOR cursor = { {0, 0}, {0, 0} };
	char message[SYSTEM_MESSAGE_H][SYSTEM_MESSAGE_W] = { 0 };
	char info[OBJECT_INFO_H][OBJECT_INFO_W] = { 0 };
	char commands[COMMANDS_H][COMMANDS_W] = { 0 };

	display(resource, map, message, info, commands, cursor);
}

// 맵
void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			for (int k = 0; k < N_LAYER; k++) {
				if (src[k][i][j] >= 0) {
					dest[i][j] = src[k][i][j];
				}
			}
		}
	}
}

void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) {
	project(map, backbuf);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (frontbuf[i][j] != backbuf[i][j]) {
				POSITION pos = { i, j };
				printc(padd(map_pos, pos), backbuf[i][j], COLOR_DEFAULT);
			}
			frontbuf[i][j] = backbuf[i][j];

		}
	}
	POSITION pos_r1 = { 10, 20 };
	printc(padd(map_pos, pos_r1), 'R', 7);
	POSITION pos_r2 = { 6,50 };
	printc(padd(map_pos, pos_r2), 'R', 7);
	POSITION pos_r3 = { 15, 50 };
	printc(padd(map_pos, pos_r3), 'R', 7);
	POSITION pos_r4 = { 15, 55 };
	printc(padd(map_pos, pos_r4), 'R', 7);
	POSITION pos1_5 = { 12, 1 };
	printc(padd(map_pos, pos1_5), '5', 1);
	POSITION pos2_5 = { 6, 58 };
	printc(padd(map_pos, pos2_5), '5', 1);
	POSITION pos1_w = { 4, 5 };
	printc(padd(map_pos, pos1_w), 'W', 14);
	POSITION pos2_w = { 13, 52 };
	printc(padd(map_pos, pos2_w), 'W', 14);
	POSITION pos1_h = { 14, 1 };
	printc(padd(map_pos, pos1_h), 'H', 9);
	POSITION pos2_h = { 3, 58 };
	printc(padd(map_pos, pos2_h), 'H', 12);
	for (int h_b = 1; h_b < 3; h_b++) {
		for (int w_b = 1; w_b < 3; w_b++) {
			POSITION pos1_b = { 17 - h_b, w_b };
			printc(padd(map_pos, pos1_b), 'B', 9);
			POSITION pos2_b = { h_b, 59 - w_b };
			printc(padd(map_pos, pos2_b), 'B', 12);
			POSITION pos1_p = { 17 - h_b, w_b + 2 };
			printc(padd(map_pos, pos1_p), 'P', 0);
			POSITION pos2_p = { h_b, 57 - w_b };
			printc(padd(map_pos, pos2_p), 'P', 0);
			POSITION pos1_r = { 9 - h_b, 30 - w_b };
			printc(padd(map_pos, pos1_r), 'R', 7);
			POSITION pos2_r = { 9 + h_b, 30 + w_b };
			printc(padd(map_pos, pos2_r), 'R', 7);

		}
	}
}


//시스탬 메시지
void project_message(char src[SYSTEM_MESSAGE_H][SYSTEM_MESSAGE_W], char dest[SYSTEM_MESSAGE_H][SYSTEM_MESSAGE_W]) {
	for (int i = 0; i < SYSTEM_MESSAGE_H; i++) {
		for (int j = 0; j < SYSTEM_MESSAGE_W; j++) {
			if (src[i][j] >= 0) {
				dest[i][j] = src[i][j];
			}
		}
	}
}

void display_system_message(char message[SYSTEM_MESSAGE_H][SYSTEM_MESSAGE_W]) {
	project_message(message, backmessage);

	for (int i = 0; i < SYSTEM_MESSAGE_H; i++) {
		for (int j = 0; j < SYSTEM_MESSAGE_W; j++) {
			if (frontmessage[i][j] != backmessage[i][j]) {
				POSITION pos = { i + MAP_HEIGHT, j };
				printc(padd(map_pos, pos), backmessage[i][j], COLOR_DEFAULT);
			}
			frontmessage[i][j] = backmessage[i][j];
		}
	}
}
// 상태창
void project_info(char src[OBJECT_INFO_H][OBJECT_INFO_W], char dest[OBJECT_INFO_H][OBJECT_INFO_W]) {
	for (int i = 0; i < OBJECT_INFO_H; i++) {
		for (int j = 0; j < OBJECT_INFO_W; j++) {
			if (src[i][j] >= 0) {
				dest[i][j] = src[i][j];
			}
		}
	}
}

void display_object_info(char info[OBJECT_INFO_H][OBJECT_INFO_W]) {
	project_info(info, backinfo);

	for (int i = 0; i < OBJECT_INFO_H; i++) {
		for (int j = 0; j < OBJECT_INFO_W; j++) {
			if (frontinfo[i][j] != backinfo[i][j]) {
				POSITION pos = { i, j + MAP_WIDTH };
				printc(padd(map_pos, pos), backinfo[i][j], COLOR_DEFAULT);
			}
			frontinfo[i][j] = backinfo[i][j];
		}
	}
}
// 명령창
void project_commands(char src[COMMANDS_H][COMMANDS_W], char dest[COMMANDS_H][COMMANDS_W]) {
	for (int i = 0; i < COMMANDS_H; i++) {
		for (int j = 0; j < COMMANDS_W; j++) {
			if (src[i][j] >= 0) {
				dest[i][j] = src[i][j];
			}
		}
	}
}

void display_commands(char commands[COMMANDS_H][COMMANDS_W]) {
	project_commands(commands, backcommands);

	for (int i = 0; i < COMMANDS_H; i++) {
		for (int j = 0; j < COMMANDS_W; j++) {
			if (frontcommands[i][j] != backcommands[i][j]) {
				POSITION pos = { i + MAP_HEIGHT, j + MAP_WIDTH };
				printc(padd(map_pos, pos), backcommands[i][j], COLOR_DEFAULT);
			}
			frontcommands[i][j] = backcommands[i][j];
		}
	}
}


// frontbuf[][]에서 커서 위치의 문자를 색만 바꿔서 그대로 다시 출력
void display_cursor(CURSOR cursor) {
	POSITION prev = cursor.previous;
	POSITION curr = cursor.current;

	char ch = frontbuf[prev.row][prev.column];
	printc(padd(map_pos, prev), ch, COLOR_DEFAULT);

	ch = frontbuf[curr.row][curr.column];
	printc(padd(map_pos, curr), ch, COLOR_CURSOR);
}