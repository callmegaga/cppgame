#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

const short int WD = 30, HT = 20;
short int map[HT][WD] = {0};
short int sx = WD / 3, sy = HT / 2, len = 4, i, j;
const short int ESC = 27, LEFT = 75, UP = 72, RIGHT = 77, DOWN = 80;
short int move_aspect = RIGHT, key = RIGHT;

void gotoxy(short x, short y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showCursor(bool visible) {
    CONSOLE_CURSOR_INFO cursor_info = {20, visible};
    //CONSOLE_CURSOR_INFO结构体包含控制台光标信息，成员分别表示光标百分比厚度和是否可见
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    //SetConsoleCursorInfo设定控制台窗口的光标大小和是否可见
}

void drawMap() {
    gotoxy(WD / 2, 0);
    cout << "          Snake Game" << endl;
    for (int i = 0; i < HT; i++) {
        for (int j = 0; j < WD; j++) {
            cout << (map[i][j] == len ? "@" : (map[i][j]) > 0 ? "◎" : (map[i][j] == 0 ? " " : (map[i][j]) == -1 ? "☆"
                                                                                                                : "█"));
        }
        cout << "\n";
    }
    cout << "length: " << len;
    Sleep(500);
}

int main() {
    for (int i = 0; i < HT; i++) {
        for (int j = 0; j < WD; j++) {
            if (i == 0 || i == HT - 1 || j == 0 || j == WD - 1) {
                map[i][j] = -2;
            }
        }
    }
    srand(time(0));
    map[rand() % (HT - 2) + 1][rand() % (WD - 2) + 1] = -1;

    showCursor(false);
    while (true) {
        drawMap();
        if (kbhit()) {
            key = getch();
            if (key <= 0 || key > 127) {
                key = getch();
            }

            if (key == ESC) {
                showCursor(true);
                gotoxy(0, HT + 2);
                cout << "End game(y/n)?";
                if ((key = getch()) == 'y' || key == 'Y') {
                    break;
                }
            }

            if ((key == LEFT && move_aspect != RIGHT) || (key == RIGHT && move_aspect != LEFT) ||
                (key == UP && move_aspect != DOWN) || (key == DOWN && move_aspect != UP)) {
                move_aspect = key;
            }
        }

        if ((move_aspect == LEFT && --sx <= 0) || (move_aspect == RIGHT && ++sx == WD - 1) ||
            (move_aspect == UP && --sy <= 0) || (move_aspect == DOWN && ++sy == HT - 1)) {
            cout << "\n蛇头撞墙，游戏结束。";
            break;
        }

        if (map[sy][sx] > 0) {
            cout << "\n蛇头撞到自身，游戏结束。";
            break;
        } else if (map[sy][sx] == -1) {
            len++;
            do {
                i = rand() % (HT - 2) + 1;
                j = rand() % (WD - 2) + 1;
            } while (map[i][j] != 0);
            map[i][j] = -1;
        } else {
            for (i = 0; i < HT; i++) {
                for (j = 0; j < WD; j++) {
                    if (map[i][j] > 0) {
                        map[i][j] -= 1;
                    }
                }
            }
        }
        map[sy][sx] = len;
    }
}