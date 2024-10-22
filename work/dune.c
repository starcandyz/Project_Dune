#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#define TICK 10
int sys_clock = 0;
bool exiting = false;

int exit_count = 0;
int main(void) {
    while (1) {
        if (exiting) {
            exit_count -= TICK;
        }

        if (_kbhit()) {
            int key = _getch();
            if (key == 'q') {
                exiting = true;
                exit_count = 3000;
            }

        }
        Sleep(TICK);
        sys_clock += TICK;
        return 0;
    }
}