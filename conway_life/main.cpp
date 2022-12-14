#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <windows.h>

void gotoxy(short x, short y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

const int WIDTH = 38;
const int HEIGHT = 20;
bool map[HEIGHT][WIDTH] = {false};
bool periodic = true;

bool initMap() {
    using namespace std;
    system("cls");
    cout << "** ??????Ϸ **" << endl;
    cout << "\r????ֵ??ʼ?趨         \n"
         << " 1: ????\n"
         << " 2: ??̬????:Block, Beehive, load, Boat\n"
         << " 3: ??????:blinker, toad, beacon\n"
         << " 4: ??????:oscillator 2\n"
         << " 5: ?????ɴ?:glider\n"
         << " 6: ?????ɴ?:spacecraft\n"
         << " 7: ?????ɴ?:slipper\n"
         << " 8: ?????ɴ?:copper head\n"
         << " 9: ??˹????????:Gosper glider gun\n"
         << " 0: ?˳???Ϸ\n"
         << "??ѡ??: ";
    int x, y, select = 0;
    cin >> select;

    if (select == 0) {
        return false;
    }

    char st[HEIGHT][WIDTH + 1] = {""};
    switch (select) {
        case 1:
            cout << "??ʼ״̬: 30% ????" << endl;
            for (y = 0; y < HEIGHT; y++)  //??ѭ??
                for (x = 0; x < WIDTH; x++)  //??ѭ??
                    st[y][x] = ((rand() % 10) < 3) ? '@' : '+';
            break;
        case 2:
            strcpy(st[0], "++++++++++++++++++++++++++++++++++");
            strcpy(st[1], "++@@++++@@+++++@@++++@@+++");
            strcpy(st[2], "++@@+++@++@+++@++@+++@+@++");
            strcpy(st[3], "++++++++@@+++++@+@++++@+++");
            strcpy(st[4], "++++++++++++++++@+++++++++");
            strcpy(st[5], "++++++++++++++++++++++++++");
            //?ִ?(ship)??ԡ??(Tub)?ͳ???(pond)
            strcpy(st[6], "++++++++++++++++++++++++++");
            strcpy(st[7], "++@@+++++@+++++@@+++++++++");
            strcpy(st[8], "++@+@+++@+@+++@++@++++++++");
            strcpy(st[9], "+++@@++++@++++@++@++++++++");
            strcpy(st[10], "+++++++++++++++@@+++++++++");
            strcpy(st[11], "++++++++++++++++++++++++++");
            break;
        case 3:
            strcpy(st[0], "++++++++++++++++++++++++++++++++++");
            strcpy(st[1], "++++++++++++++++++++++++++++++++++");
            strcpy(st[2], "++++++++++++@@++++++@@++++++++++++");
            strcpy(st[3], "+++@@@+++++@++++++++@@++++++++++++");
            strcpy(st[4], "++++++++++++++@+++++++@@++++++++++");
            strcpy(st[5], "++++++++++++@@++++++++@@++++++++++");
            strcpy(st[6], "++++++++++++++++++++++++++++++++++");
            strcpy(st[7], "++++++++++++++++++++++++++++++++++");
            strcpy(st[8], "++++++++++++++++++++++++++++++++++");
            strcpy(st[9], "++++++++++++++@+++++++++++++++++++");
            strcpy(st[10], "++++++++++++@+@+++++++++++++++++++");
            strcpy(st[11], "+++++++++++@+@++++++++++++++++++++");
            strcpy(st[12], "+++++@@+++@++@+++++++++++@@+++++++");
            strcpy(st[13], "+++++@@++++@+@+++++++++++@@+++++++");
            strcpy(st[14], "++++++++++++@+@+++++++++++++++++++");
            strcpy(st[15], "++++++++++++++@+++++++++++++++++++");
            strcpy(st[16], "++++++++++++++++++++++++++++++++++");
            break;
        case 4:
            strcpy(st[0], "++++++++++++++++++++++++++++++++++");
            strcpy(st[1], "++++++++++++++++++++++++++++++++++");
            strcpy(st[2], "++++++++++++++@@@+++@@@+++++++++++");
            strcpy(st[3], "++++++++++++++++++++++++++++++++++");
            strcpy(st[4], "++++++++++++@++++@+@++++@+++++++++");
            strcpy(st[5], "++++++++++++@++++@+@++++@+++++++++");
            strcpy(st[6], "++++++++++++@++++@+@++++@+++++++++");
            strcpy(st[7], "++++++++++++++@@@+++@@@+++++++++++");
            strcpy(st[8], "++++++++++++++++++++++++++++++++++");
            strcpy(st[9], "++++++++++++++@@@+++@@@+++++++++++");
            strcpy(st[10], "++++++++++++@++++@+@++++@+++++++++");
            strcpy(st[11], "++++++++++++@++++@+@++++@+++++++++");
            strcpy(st[12], "++++++++++++@++++@+@++++@+++++++++");
            strcpy(st[13], "++++++++++++++++++++++++++++++++++");
            strcpy(st[14], "++++++++++++++@@@+++@@@+++++++++++");
            strcpy(st[15], "++++++++++++++++++++++++++++++++++");
            strcpy(st[16], "++++++++++++++++++++++++++++++++++");
            break;
        case 5:
            strcpy(st[0], "++++++++++++++++++++++++++++++++++");
            strcpy(st[1], "++++++++++++++++++++++++++++++++++");
            strcpy(st[2], "+++++@++++++++++++++++++++++++++++");
            strcpy(st[3], "++++++@+++++++++++++++++++++++++++");
            strcpy(st[4], "++++@@@+++++++++++++++++++++++++++");
            break;
        case 6:
            strcpy(st[0], "++++++++++++++++++++++++++++++++++");
            strcpy(st[1], "+++++++++++++++@++++++++++++");
            strcpy(st[2], "+++++++++++++@+++@++++++++");
            strcpy(st[3], "++++++++++++@++++++++++++");
            strcpy(st[4], "++++++++++++@++++@+++++++");
            strcpy(st[5], "++++++++++++@@@@@++++++++");
            strcpy(st[6], "++++++++++++++++++++++++++++++++++");
            strcpy(st[7], "++++++++++++++++++++++++++++++++++");
            break;
        case 7:
            strcpy(st[8], "++++++++++++++++++++++++++++++++++");
            strcpy(st[9], "+++++++++@@++@+@@+++++++++++++++++");
            strcpy(st[10], "++++++++@++@++@@++++++++++++++++++");
            strcpy(st[11], "+++++++++@+@++++++++++++++++++++++");
            strcpy(st[12], "++++++++++@+++++++++++++++++++++++");
            strcpy(st[13], "++++++++++++++++@+++++++++++++++++");
            strcpy(st[14], "++++++++++++++@@@+++++++++++++++++");
            strcpy(st[15], "+++++++++++++@++++++++++++++++++++");
            strcpy(st[16], "++++++++++++++@+++++++++++++++++++");
            strcpy(st[17], "+++++++++++++++@@+++++++++++++++++");
            strcpy(st[18], "++++++++++++++++++++++++++++++++++");
            break;
        case 8:
            strcpy(st[0], "++++++++++++++++++++++++++++++++++");
            strcpy(st[1], "++++++++++++++++++++++++++++++++++");
            strcpy(st[2], "++++++++++++++++++++++++++++++++++");
            strcpy(st[3], "++++++++++++++++++++++++++++++++++");
            strcpy(st[4], "+++++++++++++@@++@@+++++++++++++++");
            strcpy(st[5], "+++++++++++++++@@+++++++++++++++++");
            strcpy(st[6], "+++++++++++++++@@+++++++++++++++++");
            strcpy(st[7], "++++++++++++@+@++@+@++++++++++++++");
            strcpy(st[8], "++++++++++++@++++++@++++++++++++++");
            strcpy(st[9], "++++++++++++++++++++++++++++++++++");
            strcpy(st[10], "++++++++++++@++++++@++++++++++++++");
            strcpy(st[11], "+++++++++++++@@++@@+++++++++++++++");
            strcpy(st[12], "++++++++++++++@@@@++++++++++++++++");
            strcpy(st[13], "++++++++++++++++++++++++++++++++++");
            strcpy(st[14], "+++++++++++++++@@+++++++++++++++++");
            strcpy(st[15], "+++++++++++++++@@+++++++++++++++++");
            strcpy(st[16], "++++++++++++++++++++++++++++++++++");
            break;
        case 9:
            strcpy(st[0], "+++++++++++++++++++++++++++++++++++++");
            strcpy(st[1], "+++++++++++++++++++++++++++++++++++++");
            strcpy(st[2], "+++++++++++++++++++++++++@+++++++++++");
            strcpy(st[3], "+++++++++++++++++++++++@+@+++++++++++");
            strcpy(st[4], "+++++++++++++@@++++++@@++++++++++++@@");
            strcpy(st[5], "++++++++++++@+++@++++@@++++++++++++@@");
            strcpy(st[6], "+@@++++++++@+++++@+++@@++++++++++++++");
            strcpy(st[7], "+@@++++++++@+++@+@@++++@+@+++++++++++");
            strcpy(st[8], "+++++++++++@+++++@+++++++@+++++++++++");
            strcpy(st[9], "++++++++++++@+++@++++++++++++++++++++");
            strcpy(st[10], "+++++++++++++@@++++++++++++++++++++++");
            strcpy(st[11], "+++++++++++++++++++++++++++++++++++++");
            periodic = false;  //???????Ա߽?????
            break;
        default:
            cout << "error, quit game" << endl;
            return false;
    }

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            map[y][x] = st[y][x] == '@';
        }
    }
    return true;
}

void drawMap() {
    using namespace std;

    int x, y;
    gotoxy(0, 0);
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            cout << (map[y][x] ? "??" : "??");
        }
        cout << endl;
    }
}

void updateMap() {
    static bool bak[HEIGHT + 1][WIDTH + 1] = {false};
    int x, y, up, down, left, right, count;

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            bak[y][x] = map[y][x];
        }
    }

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            left = (x + WIDTH - 1) % WIDTH;
            right = (x + WIDTH + 1) % WIDTH;
            up = (y + HEIGHT - 1) % HEIGHT;
            down = (y + HEIGHT + 1) % HEIGHT;

            if (!periodic) {
                left = (left == WIDTH - 1 ? WIDTH : left);
                right = (right == 0 ? WIDTH : right);
                up = (up == HEIGHT - 1 ? HEIGHT : up);
                down = (down = 0 ? HEIGHT : down);
            }

            count = bak[up][left] + bak[up][x] + bak[up][right]
                    + bak[y][left] + bak[y][right] + bak[down][left]
                    + bak[down][x] + bak[down][right];

            if (!map[y][x]) {
                map[y][x] = (count == 3 ? true : false);
            } else if (count == 2 || count == 3) {
                map[y][x] = true;
            } else {
                map[y][x] = false;
            }
        }
    }
}

int main() {
    using namespace std;
    char key;


    initMap();

    int round = 0;
    while (true) {
        drawMap();
        cout << "????????Ԥϰ. ?Ѹ??´???: " << ++round << endl;
        cout << "???ո?????ͣ, ??ESC???˳?" << endl;
        cout << "                                  \r";
        Sleep(800);

        if (kbhit()) {
            key = getch();
            if (key == ' ') {
                cout << "????ͣ????????????????Ϸ";
                getch();
                continue;
            }
            if (key == 27) {
                if (!initMap()) {
                    break;
                }
                round = 0;
            }
        }

        updateMap();
    }
    cout << "\n??Ϸ????????л??ʹ??" << endl;
    return 0;
}