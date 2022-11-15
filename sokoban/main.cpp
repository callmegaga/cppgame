#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

// #---墙
// $---箱子
// .---目标点
// @---小人
// +---小人在目标点
// *---箱子在目标点
// (-/-)---空地

using namespace std;

void drawMap(int);

void gotoxy(short, short);

bool initMap(int, int &, int &);

bool isWin();

const int WD = 35;
const int HT = 20;
char map[HT][WD] = {""};

int main() {
    int x, y;
    int dx = 1, dy = 1;
    int x2, y2, x3, y3;
    char key;

    int level = 0;
    if (!initMap(++level, x, y)) {
        cout << "\n\t\t读取第 " << level << " 关地图出错。" << endl;
        return 0;
    }

    while (true) {
        if (dx != 0 || dy != 0) {
            drawMap(level);
        }
        if (isWin()) {
            cout << "\n\n\t\t恭喜你过了第 " << level << " 关！";
            getch();
            if (!initMap(++level, x, y)) {
                cout << "\n\t\t读取第 " << level << " 关地图出错。" << endl;
                break;
            }
            continue;
        }

        dx = dy = 0;
        key = getch();
        if (key <= 0 || key > 127)
            key = getch();
        if (key == 75 || key == 'a' || key == 'A')
            dx = -1;
        else if (key == 77 || key == 'd' || key == 'D')
            dx = 1;
        else if (key == 72 || key == 'w' || key == 'W')
            dy = -1;
        else if (key == 80 || key == 's' || key == 'S')
            dy = 1;
        else if (key == 'z' || key == 'Z');
        else if (key == 27) {
            gotoxy(0, HT);
            cout << "\t\t结束游戏(y/n)?";
            if ((key = getch()) == 'y' || key == 'Y') {
                break;
            } else
                cout << "\r";
            break;
        }

        if (dx == 0 && dy == 0) continue;

        x2 = x + dx;
        y2 = y + dy;
        x3 = x2 + dx;
        y3 = y2 + dy;

        if ((map[y2][x2] == '$' || map[y2][x2] == '*') && (map[y3][x3] == '_' || map[y3][x3] == '.')) {
            map[y3][x3] = (map[y3][x3] == '_' ? '$' : '*');
            map[y2][x2] = (map[y2][x2] == '$' ? '_' : '.');
        }

        if (map[y2][x2] == '_' || map[y2][x2] == '.') {
            map[y2][x2] = (map[y2][x2] == '_' ? '@' : '+');
            map[y][x] = (map[y][x] == '@' ? '_' : '.');
            y = y + dy;
            x = x + dx;
        }
    }

    cout << "\n\t\t游戏结束，谢谢使用";
    getchar();
    return 0;
}

bool initMap(int level, int &x, int &y) {
    char st[HT][WD + 1] = {""};
    switch (level) {
        case 1:
            strcpy(st[0], "__###___");//地图一(8*8)
            strcpy(st[1], "__#.#___");
            strcpy(st[2], "__#_####");
            strcpy(st[3], "###$_$.#");
            strcpy(st[4], "#._$@###");
            strcpy(st[5], "####$#__");
            strcpy(st[6], "___#.#__");
            strcpy(st[7], "___###__");
            break;
        case 2:
            strcpy(st[0], "#####____");//snail 2
            strcpy(st[1], "#@__#____");
            strcpy(st[2], "#_$$#_###");
            strcpy(st[3], "#_$_#_#.#");
            strcpy(st[4], "###_###.#");
            strcpy(st[5], "_##____.#");
            strcpy(st[6], "_#___#__#");
            strcpy(st[7], "_#___####");
            strcpy(st[8], "_#####___");
            break;
        case 3:
            strcpy(st[0], "_####_");//snail 3
            strcpy(st[1], "##__#_");
            strcpy(st[2], "#_@$#_");
            strcpy(st[3], "##$_##");
            strcpy(st[4], "##_$_#");
            strcpy(st[5], "#.$__#");
            strcpy(st[6], "#..*.#");
            strcpy(st[7], "######");
            break;
        case 4:
            strcpy(st[0], "_####___");//snail 4
            strcpy(st[1], "_#__###_");
            strcpy(st[2], "_#@$__#_");
            strcpy(st[3], "###_#_##");
            strcpy(st[4], "#.#_#__#");
            strcpy(st[5], "#.$__#_#");
            strcpy(st[6], "#.___$_#");
            strcpy(st[7], "########");
            break;
        case 5:
            strcpy(st[0], "_#######__");//boxxle 1 5
            strcpy(st[1], "_#_____###");
            strcpy(st[2], "##$###___#");
            strcpy(st[3], "#_@_$__$_#");
            strcpy(st[4], "#_..#_$_##");
            strcpy(st[5], "##..#___#_");
            strcpy(st[6], "_########_");
            break;
        default:
            return false;
    }

    int ix, iy;
    int hgt = 0, wid = 0;
    for (iy = 0; iy < HT; iy++) {
        for (ix = 0; ix < WD; ix++) {
            if (st[iy][ix] == '-' || st[iy][ix] == ' ')
                st[iy][ix] = '_';
            if (st[iy][ix] > 0 && st[iy][ix] != '_') {
                hgt = (hgt > iy + 1 ? hgt : iy + 1);
                wid = (wid > ix + 1 ? wid : ix + 1);
            }
        }
    }

    for (iy = 0; iy < HT; iy++) {
        for (ix = 0; ix < WD; ix++) {
            map[iy][ix] = '_';
        }
    }

    int yup = (HT - hgt) / 2;
    int xleft = (WD - wid) / 2;

    for (iy = 0; iy < hgt; iy++) {
        for (ix = 0; ix < wid; ix++) {
            map[iy + yup][ix + xleft] = st[iy][ix];
            if (map[iy + yup][ix + xleft] == '@') {
                x = ix + xleft;
                y = iy + yup;
            }
        }
    }
    return true;
}

void drawMap(int level) {
    gotoxy(0, 0);
    cout << "\n\t\t推箱子, 第【" << level << "】关" << endl;
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
