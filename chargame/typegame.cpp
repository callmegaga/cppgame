#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

int main() {
    using namespace std;

    const int ESC_KEY = 27;
    int pos , pos_max = 72;
    int win = 0, loss = 0;

    cout << "Type Game(press Enter to start, in game press ESC quit game)" << endl;
    getchar();
    int ch = 0, key = 0;
    srand(time(0));

    while (key != ESC_KEY) {
        ch = rand() % ('z' + 1 - 'a') + 'a';
        for (pos = 0; pos < pos_max && key != ESC_KEY; pos++) {
            cout << "\b--" << (char) ch;
            pos++;
            Sleep(150);
            if (kbhit() && (key = getch()) == ch) {
                win++;
                cout << "*\a";
                break;
            }
        }

        if (key == ESC_KEY) {
            cout << "\nDo you want finish the Game?(y/n)";
            while ((key = tolower(getchar())) != 'y' && ch != 'n');
            key = (key == 'y' ? ESC_KEY : 0);
        }

        if (pos >= pos_max) {
            loss++;
        }
        cout << endl;
    }

    cout << "Char practise number: " << win + loss << ", right number: " << win << endl;
    cout << "Game Over, Thank you for use" << endl;
    return 0;
}