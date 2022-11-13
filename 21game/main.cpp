#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    using namespace std;
    cout << "用4张扑克牌计算24点" << endl;
    cout << "玩法规则：电脑每次随机输出4个介于[1, 13]的整数" << endl;
    cout << "用户分两次输入加减乘除算式，计算机自动计算最后的数字" << endl;
    cout << "把这4个数字及其计算结果仅使用一次，求出最终结果为24" << endl;

    int a, b, c, d;
    int i, j;
    char op;

    srand(time(0));
    do {
        a = rand() % 12 + 1;
        b = rand() % 12 + 1;
        c = rand() % 12 + 1;
        d = rand() % 12 + 1;

        cout << "4个可用的数字：" << endl;
        cout << a << " " << b << " " << c << " " << d << " ";

        cout << "请输入第一个算式：" << endl;
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
            cout << "错误：所输入的两个数字并不是提供的数字！" << endl;
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
                cout << "错误：" << i << "不能整除" << j << " ！" << endl;
                break;
            }
        } else {
            cout << "错误：所输入的运算法不是加减乘除！" << endl;
            break;
        }

        cout << "\t" << i << " " << op << " " << j << " = " << c << endl;
        cout << "可用的三个数字： ";
        cout << a << " " << b << " " << c << endl;

        cout << "输入第二个算式：" << endl;
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
            cout << "错误：所输入的两个数字并不是可用的数字！" << endl;
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
                cout << "错误：" << i << "不能整除" << j << " ！" << endl;
                break;
            }
        } else {
            cout << "错误：所输入的运算法不是加减乘除！" << endl;
            break;
        }

        cout << "\t" << i << " " << op << " " << j << " = " << b << endl;
        cout << "可用的两个数字： ";
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
            cout << "计算得到了24！你赢了！" << endl << endl;
        } else {
            cout << "这两个数字无法计算得到24。这一局你失败了。" << endl;
        }

        cout << "游戏结束。" << endl;
        cout << "再玩一局吗(y/n)?";
        cin >> op;
    } while (op == 'y' || op == 'Y');
}