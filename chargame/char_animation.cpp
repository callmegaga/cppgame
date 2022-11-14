#include <iostream>
#include <string.h>
#include <conio.h>
#include <windows.h>

void flashString() {
    using namespace std;
    cout << "String Flash" << endl;
    char str[] = "Welcome to Wuhan, my friends! Have a good time here!";
    int i, len = strlen(str);
    while (!kbhit()) {
        cout << "\r" << str;
        Sleep(250);
        cout << "\r";
        for (i = 0; i < len; i++) {
            cout << " ";
        }
        Sleep(250);
    }
    getch();
    cout << "\r" << str << endl;
}

void flashChar() {
    using namespace std;
    cout << "Char Flash" << endl;
    char str[] = "Welcome to Wuhan, my friends! Have a good time here!";
    int i, len = strlen(str);
    i = -1;
    while (!kbhit()) {
        i = (i + 1) % (len * 2);
        if (i == 0 || i == len) {
            cout << "\r";
        }
        if (i < len) {
            cout << str[i];
        } else {
            cout << " ";
        }
        Sleep(50);
    }
    getch();
    cout << "\r" << str << endl;
}

void moveString() {
    using namespace std;
    cout << "String move" << endl;
    int width = 75;
    char str[] = "Welcome to Wuhan, my friends! Have a good time here!";
    int len = strlen(str);
    int left = 0;
    int inc = 1;
    int i;
    while (!kbhit()) {
        left += inc;
        if (left == 0 || left == width - len)
            inc = -1 * inc;
        cout << "\r";
        for (i = 0; i < left; i++) {
            cout << " ";
        }
        cout << str;
        for (i = left + len; i < width; i++) {
            cout << " ";
        }
        Sleep(100);
    }
    getch();
    cout << endl;
}

void displayString() {
    using namespace std;
    cout << "String display from right to left" << endl;
    char str[] = "Welcome to Wuhan, my friends!     ";
    int len = strlen(str);
    int width = 60;
    int pos = 0;
    int i;
    while (!kbhit()) {
        pos = (pos + 1) % len;
        cout << "\r";
        for (i = 0; i < width; i++) {
            cout << str[(pos + i) % len];
        }
        Sleep(150);
    }
    getch();
    cout << endl;
}

int main() {
    int key;
    const int ESC_KEY = 27;
    while (key != ESC_KEY) {
        flashString();
        flashChar();
        moveString();
        displayString();
        key = getch();
    }
}