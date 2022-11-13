#include <iostream>
#include <ctime>
#include <cmath>

void isLeapYear() {
    int year = 0;
    bool leap_year;

    std::cout << "please input a year: " << std::endl;
    std::cout << "input a year >= 1583" << std::endl;

    while (!(std::cin >> year) || year < 1583) {
        std::cin.clear();
        std::cin.sync();
        std::cout << "get year: " << year << std::endl;
        if (year < 1583) {
            std::cout << "bad year,input again." << std::endl;
            std::cout << "input a year(>= 1583)" << std::endl;
        }
    }

    if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0) {
        leap_year = 1;
    } else {
        leap_year = 0;
    }

    if (leap_year) {
        std::cout << "year" << " is leap year" << std::endl;
    } else {
        std::cout << year << " is not leap year" << std::endl;
    }
}

void dayNumber() {
    int year, month, day, num;
    int mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 31, 30};

    bool valid = false;
    while (!valid) {
        std::cout << "Please input year, month, day: " << std::endl;
        if (!(std::cin >> year >> month >> day)) {
            std::cin.clear();
            std::cin.sync();
            continue;
        }

        if (year < 1583) {
            std::cerr << "year should later than 1583." << std::endl;
            continue;
        }

        if (month < 1 || month > 12) {
            std::cerr << "month should be 1-12." << std::endl;
            continue;
        }

        mdays[1] = (((year % 100 != 0 && year % 4 == 0) || year % 400 == 0)) ? 29 : 28;

        if (day < 1 || day > 31) {
            std::cerr << "day should be 1-31." << std::endl;
        } else {
            if (month == 4 || month == 6 || month == 9 || month == 11) {
                if (day > 30) {
                    std::cerr << "day should not bigger than 30." << std::endl;
                    continue;
                }
            }

            if (month == 2 && ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0)) {
                if (day > 29) {
                    std::cerr << "day should not bigger than 29." << std::endl;
                    continue;
                }
            }

            if (month == 2 && !((year % 100 != 0 && year % 4 == 0) || year % 400 == 0)) {
                if (day > 28) {
                    std::cerr << "day should not bigger than 28." << std::endl;
                    continue;
                }
            }

        }

        valid = true;
    }

    num = day;
    for (int i = 0; i < month - 1; i++) {
        num += mdays[i];
    }

    std::cout << "that day is " << num << "th day in " << year;
}

void toDayYearMonthAndDay() {
    int second = time(NULL);
    int day = ceil(1.0 * second / (60 * 60 * 24));

    int year = 1970;
    int num = ((year % 4 == 0 && year % 100 || year % 400 == 0) ? 366 : 365);
    while (day > num) {
        day = day - num;
        year++;
        num = ((year % 4 == 0 && year % 100 || year % 400 == 0) ? 366 : 365);
    }

    int mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    mdays[1] = (((year % 100 != 0 && year % 4 == 0) || year % 400 == 0)) ? 29 : 28;

    int month = 1;
    while (day > mdays[month - 1]) {
        day = day - mdays[month - 1];
        month++;
    }

    std::cout << "today is : " << " year: " << year << " month: " << month << " day: " << day << std::endl;

}

int main() {
//    isLeapYear();
//    dayNumber();
    toDayYearMonthAndDay();
    return 0;
}