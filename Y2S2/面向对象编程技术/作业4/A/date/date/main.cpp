#include <iostream>
#include <ctime>
using namespace std;

class Date {
private:
    int year, month, day;

    // ����Ƿ�Ϊ����
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // ���㲢���õ�ǰ���ڵ�����
    void updateDaysMonth() {
        static int daysInMonth[12] = { 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 };
        if (isLeapYear(year)) {
            daysInMonth[2] = 29;
        }
        while (month <= 0) {
            year--;
            month += 12;
        }
        while (day > daysInMonth[month%12]) {
            day -= daysInMonth[month%12];
            month++;
        }
        while (day <= 0) {
            month--;
            if (month == 0) {
                month = 12;
                year--;
            }
            day += daysInMonth[month % 12];
        }
        while (month > 12) {
            month -= 12;
            year++;
        }
    }

public:
    // ���캯��
    Date(int y, int m, int d) : year(y), month(m), day(d) {
        updateDaysMonth();
    }

    // ��������أ��ӷ�
    Date operator+(int days) {
        Date newDate = *this;
        newDate.day += days;
        newDate.updateDaysMonth();
        return newDate;
    }

    // ��������أ�����
    Date operator-(int days) {
        Date newDate = *this;
        newDate.day -= days;
        newDate.updateDaysMonth();
        return newDate;
    }

    // ��������أ�С�ڣ��������ڱȽ�
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    // ��ӡ����
    void print() const {
        cout << year << "-" << month << "-" << day << endl;
    }
};

int main() {
    time_t now = time(nullptr);
    struct tm now_tm;
    localtime_s(&now_tm, &now);

    int year = now_tm.tm_year + 1900;
    int month = now_tm.tm_mon + 1;
    int day = now_tm.tm_mday;

    Date today(year, month, day);
    cout << "Today's date: ";
    today.print();

    Date date2 = today + 62;
    cout << "date2's date: ";
    date2.print();

    Date date3 = today - 31;
    cout << "date3's date: ";
    date3.print();

    if (date2 < today) {
        cout << "date2 is before today!" << endl;
    }
    else {
        cout << "date2 is after today!" << endl;
    }

    if (date3 < today) {
        cout << "date3 is before today!" << endl;
    }
    else {
        cout << "date3 is after today!" << endl;
    }

    return 0;
}