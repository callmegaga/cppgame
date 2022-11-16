#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

const short int WD = 30, HT = 20;
short int map[HT][WD] = {0};

short int sx, sy, len;
short int x[(WD - 2) * (HT - 2)], y[(WD - 2) * (HT - 2)];
short int foodx, foody;

void initGame() {
    for (int i = 0; i < HT; i++) {
        for (int j = 0; j < WD; j++) {
            if (i == 0 || i == HT - 1 || j == 0 || j == WD - 1) {
                map[i][j] = -2;
            }
        }
    }

    sx = WD / 3;
    sy = HT / 2;
    len = 4;

    for (int i = 0; i <= len; i++) {
        x[i] = sx;
        y[i] = sy;
        map[sx][sy] = 1;
    }

    srand(time(0));
    foodx = rand() % (WD - 2) + 1;
    foody = rand() % (HT - 2) + 1;
    map[foody][foodx] = -1;
}

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
    cout << "Snake Game" << endl;
    for (int i = 0; i < HT; i++) {
        for (int j = 0; j < WD; j++) {
            gotoxy(j, i + 1);
            cout << (map[i][j] == -2 ? "#" : " ");
        }
    }
}

void drawSnake() {
    gotoxy(x[0], y[0] + 1);
    cout << " ";
    gotoxy(x[len - 1], y[len - 1] + 1);
    cout << "*";
    gotoxy(x[len], y[len] + 1);
    cout << "O";
}

void drawFoodLen() {
    gotoxy(foodx, foody + 1);
    cout << "☆";
    gotoxy(0, HT + 1);
    cout << "length: " << len;
}

void gameOver(const char msg[]) {
    gotoxy(0, HT + 2);
    cout << msg;
}

bool wantExit() {
    showCursor(true);
    gotoxy(0, HT + 2);
    cout << "结束游戏(y/n)?";
    int key;
    if ((key = getch()) == 'y' || key == 'Y') return true;
    showCursor(false);
    gotoxy(0, HT + 2);
    cout << "                   ";
    return false;
}

int main() {
    const short int ESC = 27, LEFT = 75, UP = 72, RIGHT = 77, DOWN = 80;
    short int move_aspect = RIGHT, key = RIGHT;

    initGame();
    showCursor(false);
    drawMap();
    drawFoodLen();

    while (true) {
        drawSnake();
        Sleep(200);

        if (kbhit()) {
            key = getch();
            if (key <= 0 || key > 127) {
                key = getch();
            }

            if (key == ESC && wantExit()) {
                gameOver("谢谢使用！再见！");
                break;
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
                foodx = rand() % (WD - 2) + 1;
                foody = rand() % (HT - 2) + 1;
            } while (map[foody][foodx] != 0);
            map[foody][foodx] = -1;
            drawFoodLen();
        } else {
            map[y[0]][x[0]] = 0;
            for (int i = 0; i < len; i++) {
                x[i] = x[i + 1];
                y[i] = y[i + 1];
            }
        }
        x[len] = sx;
        y[len] = sy;
        map[sy][sx] = 1;
    }
    showCursor(true);
    getch();
    return 0;
}