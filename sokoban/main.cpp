#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <fstream>

// #---墙
// $---箱子
// .---目标点
// @---小人
// +---小人在目标点
// *---箱子在目标点
// (-/-)---空地

using namespace std;

void drawMap(int, int, int);

void gotoxy(short, short);

void showCursor(bool visible) {
    CONSOLE_CURSOR_INFO cursor_info = {20, visible};
    //CONSOLE_CURSOR_INFO结构体包含控制台光标信息，成员分别表示光标百分比厚度和是否可见
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    //SetConsoleCursorInfo设定控制台窗口的光标大小和是否可见
}

bool initMap(int, int &, int &);

bool isWin();

const int WD = 35;
const int HT = 20;
char map[HT][WD] = {""};
char xsbfile[50] = "";

int main() {
    int x, y;
    int dx = 1, dy = 1;
    int x2, y2, x3, y3;
    char key;

    int level = 0;
    int step = 0, total = 0;
    char track[500] = "";
    int play = 1;

    if (!initMap(++level, x, y)) {
        cout << "\n\t\t读取第 " << level << " 关地图出错。" << endl;
        return 0;
    }

    showCursor(false);
    while (true) {
        if (dx != 0 || dy != 0) {
            drawMap(level, step, total);
        }
        if (isWin()) {
            cout << "\n\n\t\t恭喜你过了第 " << level << " 关！" << endl;
            getch();
            if (!initMap(++level, x, y)) {
                cout << "\n\t\t读取第 " << level << " 关地图出错。" << endl;
                break;
            }
            total = step = 0;
            continue;
        }

        play = 1;
        key = getch();
        if (key <= 0 || key > 127)
            key = getch();
        if (key == 75 || key == 'a' || key == 'A') {
            key = 'l';
        } else if (key == 77 || key == 'd' || key == 'D') {
            key = 'r';
        } else if (key == 72 || key == 'w' || key == 'W') {
            key = 'u';
        } else if (key == 80 || key == 's' || key == 'S') {
            key = 'd';
        } else if (key == 'z' || key == 'Z') {
            if (step <= 0) continue;
            key = track[step - 1];
            play = -1;
        } else if (key == 'r' || key == 'R') {
            if (step >= total) continue;
            key = track[step];
            play = 2;
        } else if (key == 27) {
            gotoxy(0, HT);
            showCursor(true);
            cout << "\t\t结束游戏(y/n)?";
            if ((key = getch()) == 'y' || key == 'Y') {
                break;
            } else {
                cout << "\r";
                showCursor(false);
            }
        }


        dx = dy = 0;
        if (key == 'l' || key == 'L') {
            dx = (play > 0 ? -1 : 1);
        } else if (key == 'r' || key == 'R') {
            dx = (play > 0 ? 1 : -1);
        } else if (key == 'u' || key == 'U') {
            dy = (play > 0 ? -1 : 1);
        } else if (key == 'd' || key == 'D') {
            dy = (play > 0 ? 1 : -1);
        }

        if (dx == 0 && dy == 0) continue;

        x2 = x + dx;
        y2 = y + dy;

        if (play > 0) {
            x3 = x2 + dx;
            y3 = y2 + dy;
        } else {
            x3 = x - dx;
            y3 = y - dy;
        }

        if (play > 0 && (map[y2][x2] == '$' || map[y2][x2] == '*') && (map[y3][x3] == '_' || map[y3][x3] == '.')) {
            map[y3][x3] = (map[y3][x3] == '_' ? '$' : '*');
            map[y2][x2] = (map[y2][x2] == '$' ? '_' : '.');
            key = toupper(key);
        }

        if (map[y2][x2] == '_' || map[y2][x2] == '.') {
            map[y2][x2] = (map[y2][x2] == '_' ? '@' : '+');
            map[y][x] = (map[y][x] == '@' ? '_' : '.');
            if (play == -1 && key == toupper(key)) {
                map[y3][x3] = (map[y3][x3] == '$' ? '_' : '.');
                map[y][x] = (map[y][x] == '_' ? '$' : '*');
            }
            y = y + dy;
            x = x + dx;
            if (play == 1) {
                track[++step - 1] = key;
                total = step;
            } else if (play == 2) {
                step++;
            } else {
                step--;
            }
        }
    }

    cout << "\n\t\t游戏结束，谢谢使用";
    getchar();
    return 0;
}

bool initMap(int level, int &x, int &y) {
    char st[HT][WD + 1] = {""};    //在本函数内部存储地图信息的二维数组

    // @ 人  + 人在目标点   $ 箱子  * 箱子在目标点  # 墙  . 目标点   _ 空地
    if (level == 1) {
        strcpy(st[0], "__###___");//snail 1
        strcpy(st[1], "__#.#___");
        strcpy(st[2], "__#_####");
        strcpy(st[3], "###$_$.#");
        strcpy(st[4], "#._$@###");
        strcpy(st[5], "####$#__");
        strcpy(st[6], "___#.#__");
        strcpy(st[7], "___###__");
    } else if (level == 2) {
        strcpy(st[0], "#####____");//snail 2
        strcpy(st[1], "#@__#____");
        strcpy(st[2], "#_$$#_###");
        strcpy(st[3], "#_$_#_#.#");
        strcpy(st[4], "###_###.#");
        strcpy(st[5], "_##____.#");
        strcpy(st[6], "_#___#__#");
        strcpy(st[7], "_#___####");
        strcpy(st[8], "_#####___");
    } else if (level == 3) {
        strcpy(st[0], "_####_");//snail 3
        strcpy(st[1], "##__#_");
        strcpy(st[2], "#_@$#_");
        strcpy(st[3], "##$_##");
        strcpy(st[4], "##_$_#");
        strcpy(st[5], "#.$__#");
        strcpy(st[6], "#..*.#");
        strcpy(st[7], "######");
    } else if (level == 4) {
        strcpy(st[0], "_####___");//snail 4
        strcpy(st[1], "_#__###_");
        strcpy(st[2], "_#@$__#_");
        strcpy(st[3], "###_#_##");
        strcpy(st[4], "#.#_#__#");
        strcpy(st[5], "#.$__#_#");
        strcpy(st[6], "#.___$_#");
        strcpy(st[7], "########");
    } else if (level == 5) {
        strcpy(st[0], "_#######__");//
        strcpy(st[1], "_#_____###");
        strcpy(st[2], "##$###___#");
        strcpy(st[3], "#_@_$__$_#");
        strcpy(st[4], "#_..#_$_##");
        strcpy(st[5], "##..#___#_");
        strcpy(st[6], "_########_");
    } else {
        return false;
    }

    int ix, iy;
    //找出新地图的高度和宽度（非空格点的二维最大下标值+1）
    int hgt = 0, wid = 0;
    for (iy = 0; iy < HT; iy++)
        for (ix = 0; ix < WD; ix++) {
            if (st[iy][ix] == '-' || st[iy][ix] == ' ' )
                st[iy][ix] == '_';  //把'-'和' '替换为'_'
            if (st[iy][ix] > 0 && st[iy][ix] != '_') {
                hgt = (hgt > iy + 1 ? hgt : iy + 1);
                wid = (wid > ix + 1 ? wid : ix + 1);
            }
        }
    //原地图全部清空
    for (iy = 0; iy < HT; iy++)
        for (ix = 0; ix < WD; ix++)
            map[iy][ix] = '_';
    //把新地图的信息复制到数组的中央部分
    int yup = (HT - hgt) / 2;
    int xleft = (WD - wid) / 2;
    for (iy = 0; iy < hgt; iy++)
        for (ix = 0; ix < wid; ix++) {
            map[iy + yup][ix + xleft] = st[iy][ix];
            if (map[iy + yup][ix + xleft] == '@') {
                x = ix + xleft;
                y = iy + yup;
            }
        }
    return true;
}

void drawMap(int level, int step, int total) {
    gotoxy(0, 0);
    cout << "\n\t\t推箱子, 第【" << level << "】关" << endl;
    cout << "            第 " << step << " 步 共 " << total << "步                  " << endl;
    int ix, iy;
    for (iy = 0; iy < HT; iy++) {
        for (ix = 0; ix < WD; ix++) {
            switch (map[iy][ix]) {
                case '#':
                    cout << "█";
                    break;
                case '$':
                    cout << "□";
                    break;
                case '.':
                    cout << "☆";
                    break;
                case '@':
                    cout << "＠";
                    break;
                case '+':
                    cout << "◎";
                    break;
                case '*':
                    cout << "★";
                    break;
                case ' ':
                case '-':
                case '_':
                    cout << " ";
                    break;
            }
        }
        cout << endl;
    }
    gotoxy(0, 0);
}

void gotoxy(short x, short y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool isWin() {
    int ix, iy;
    for (iy = 0; iy < HT; iy++) {
        for (ix = 0; ix < WD; ix++) {
            if (map[iy][ix] == '$') {
                return false;
            }
        }
    }
    return true;
}
