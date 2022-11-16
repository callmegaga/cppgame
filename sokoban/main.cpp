#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <fstream>

// #---ǽ
// $---����
// .---Ŀ���
// @---С��
// +---С����Ŀ���
// *---������Ŀ���
// (-/-)---�յ�

using namespace std;

void drawMap(int, int, int);

void gotoxy(short, short);

void showCursor(bool visible) {
    CONSOLE_CURSOR_INFO cursor_info = {20, visible};
    //CONSOLE_CURSOR_INFO�ṹ���������̨�����Ϣ����Ա�ֱ��ʾ���ٷֱȺ�Ⱥ��Ƿ�ɼ�
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    //SetConsoleCursorInfo�趨����̨���ڵĹ���С���Ƿ�ɼ�
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
        cout << "\n\t\t��ȡ�� " << level << " �ص�ͼ����" << endl;
        return 0;
    }

    showCursor(false);
    while (true) {
        if (dx != 0 || dy != 0) {
            drawMap(level, step, total);
        }
        if (isWin()) {
            cout << "\n\n\t\t��ϲ����˵� " << level << " �أ�" << endl;
            getch();
            if (!initMap(++level, x, y)) {
                cout << "\n\t\t��ȡ�� " << level << " �ص�ͼ����" << endl;
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
            cout << "\t\t������Ϸ(y/n)?";
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

    cout << "\n\t\t��Ϸ������ллʹ��";
    getchar();
    return 0;
}

bool initMap(int level, int &x, int &y) {
    char st[HT][WD + 1] = {""};    //�ڱ������ڲ��洢��ͼ��Ϣ�Ķ�ά����

    // @ ��  + ����Ŀ���   $ ����  * ������Ŀ���  # ǽ  . Ŀ���   _ �յ�
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
    //�ҳ��µ�ͼ�ĸ߶ȺͿ�ȣ��ǿո��Ķ�ά����±�ֵ+1��
    int hgt = 0, wid = 0;
    for (iy = 0; iy < HT; iy++)
        for (ix = 0; ix < WD; ix++) {
            if (st[iy][ix] == '-' || st[iy][ix] == ' ' )
                st[iy][ix] == '_';  //��'-'��' '�滻Ϊ'_'
            if (st[iy][ix] > 0 && st[iy][ix] != '_') {
                hgt = (hgt > iy + 1 ? hgt : iy + 1);
                wid = (wid > ix + 1 ? wid : ix + 1);
            }
        }
    //ԭ��ͼȫ�����
    for (iy = 0; iy < HT; iy++)
        for (ix = 0; ix < WD; ix++)
            map[iy][ix] = '_';
    //���µ�ͼ����Ϣ���Ƶ���������벿��
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
    cout << "\n\t\t������, �ڡ�" << level << "����" << endl;
    cout << "            �� " << step << " �� �� " << total << "��                  " << endl;
    int ix, iy;
    for (iy = 0; iy < HT; iy++) {
        for (ix = 0; ix < WD; ix++) {
            switch (map[iy][ix]) {
                case '#':
                    cout << "��";
                    break;
                case '$':
                    cout << "��";
                    break;
                case '.':
                    cout << "��";
                    break;
                case '@':
                    cout << "��";
                    break;
                case '+':
                    cout << "��";
                    break;
                case '*':
                    cout << "��";
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
