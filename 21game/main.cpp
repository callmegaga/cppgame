#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    using namespace std;
    cout << "��4���˿��Ƽ���24��" << endl;
    cout << "�淨���򣺵���ÿ��������4������[1, 13]������" << endl;
    cout << "�û�����������Ӽ��˳���ʽ��������Զ�������������" << endl;
    cout << "����4�����ּ����������ʹ��һ�Σ�������ս��Ϊ24" << endl;

    int a, b, c, d;
    int i, j;
    char op;

    srand(time(0));
    do {
        a = rand() % 12 + 1;
        b = rand() % 12 + 1;
        c = rand() % 12 + 1;
        d = rand() % 12 + 1;

        cout << "4�����õ����֣�" << endl;
        cout << a << " " << b << " " << c << " " << d << " ";

        cout << "�������һ����ʽ��" << endl;
        cin >> i >> op >> j;
        if (i == a) {
            a = d;
            d = 0;
        } else if (i == b) {
            b = d;
            d = 0;
        } else if (i == c) {
            c = d;
            d = 0;
        } else if (i == d) {
            d = 0;
        }

        if (j == a) {
            a = c;
            c = 0;
        } else if (j == b) {
            b = c;
            c = 0;
        } else if (j == c) {
            c = 0;
        }

        if (c != 0 || d != 0) {
            cout << "������������������ֲ������ṩ�����֣�" << endl;
            break;
        }

        if (op == '+') {
            c = i + j;
        } else if (op == '-') {
            c = i - j;
        } else if (op == '*') {
            c = i * j;
        } else if (op == '/') {
            c = i / j;
            if (i % j) {
                cout << "����" << i << "��������" << j << " ��" << endl;
                break;
            }
        } else {
            cout << "��������������㷨���ǼӼ��˳���" << endl;
            break;
        }

        cout << "\t" << i << " " << op << " " << j << " = " << c << endl;
        cout << "���õ��������֣� ";
        cout << a << " " << b << " " << c << endl;

        cout << "����ڶ�����ʽ��" << endl;
        cin >> i >> op >> j;

        if (i == a) {
            a = c;
            c = 0;
        } else if (i == b) {
            b = c;
            c = 0;
        } else if (i == c) {
            c = 0;
        }


        if (j == a) {
            a = b;
            b = 0;
        } else if (j == b) {
            b = 0;
        }

        if (b != 0 || c != 0) {
            cout << "������������������ֲ����ǿ��õ����֣�" << endl;
            break;
        }

        if (op == '+') {
            b = i + j;
        } else if (op == '-') {
            b = i - j;
        } else if (op == '*') {
            b = i * j;
        } else if (op == '/') {
            b = i / j;
            if (i % j) {
                cout << "����" << i << "��������" << j << " ��" << endl;
                break;
            }
        } else {
            cout << "��������������㷨���ǼӼ��˳���" << endl;
            break;
        }

        cout << "\t" << i << " " << op << " " << j << " = " << b << endl;
        cout << "���õ��������֣� ";
        cout << a << " " << b << endl;

        if (a < b) {
            c = b;
            b = a;
            a = c;
        }

        if ((c = a + b) == 24) {
            cout << "\t" << a << "+" << b << " = " << c << endl;
        } else if ((c = a - b) == 24) {
            cout << "\t" << a << "-" << b << " = " << c << endl;
        } else if ((c = a * b) == 24) {
            cout << "\t" << a << "*" << b << " = " << c << endl;
        } else if ((c = a / b) == 24 && a % b == 0) {
            cout << "\t" << a << "/" << b << " = " << c << endl;
        }

        if (c == 24) {
            cout << "����õ���24����Ӯ�ˣ�" << endl << endl;
        } else {
            cout << "�����������޷�����õ�24����һ����ʧ���ˡ�" << endl;
        }

        cout << "��Ϸ������" << endl;
        cout << "����һ����(y/n)?";
        cin >> op;
    } while (op == 'y' || op == 'Y');
}