#include <iostream>
#include <windows.h>

int main() {
    int i, j, num = 50;
    using namespace std;
    cout << "|-----------------------------------------------| 0%";
    for (i = 1; i <= num; i++) {
        cout << "\r" << "|";
        for (j = 0; j < i; j++) {
            cout << "=";
        }

        for (j = 0; j < 6; j++) {
            cout << "\b";
            cout << (j % 3 == 0 ? "-" : (j % 3 == 1 ? "\\" : "/"));
            Sleep(50);
        }
        cout << "\b" << "=";
        for (j = i + 1; j <= num; j++) {
            cout << "-";
        }
        cout << "| ";
        cout << 100.0 * i / num << "%";
    }
    cout << endl;
    cin >> i;
    return 0;
}