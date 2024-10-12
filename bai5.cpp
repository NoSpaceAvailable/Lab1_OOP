#include <iostream>

using namespace std;

enum months {
    Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

struct Date {
    int day, month, year;
};

/**
 * Hàm trả về ngày tiếp theo của một ngày
 * @param _datetime ngày cần xét
 * @return ngày tiếp theo của _datetime
 */
Date nextDay(Date _datetime) {
    Date datetime = _datetime;
    if (1 <= datetime.day && datetime.day <= 27) {
        cout << datetime.day << '\n';
        datetime.day += 1;
    } else if (datetime.day == 28) {
        if (datetime.month == Feb) {
            // Check if it's a leap year
            if (datetime.year % 4 == 0 && datetime.year % 100 != 0) {
                datetime.day = 29;
            } else {
                datetime.day = 1;
                datetime.month = Mar;
            }
        } else {
            datetime.day = 29;
        }
    } else if (datetime.day == 29) {
        if (datetime.month == Feb) {
            datetime.day = 1;
            datetime.month = Mar;
        } else {
            datetime.day = 30;
        }
    } else if (datetime.day == 30) {
        if (datetime.month == Apr || datetime.month == Jun || datetime.month == Sep || datetime.month == Nov) {
            datetime.day = 1;
            datetime.month += 1;
        } else {
            datetime.day = 31;
        }
    } else if (datetime.day == 31) {
        if (datetime.month == Dec) {
            datetime.day = 1;
            datetime.month = Jan;
            datetime.year += 1;
        } else {
            datetime.day = 1;
            datetime.month += 1;
        }
    }
    return datetime;
}

/**
 * Hàm trả về ngày trước đó của một ngày
 * @param _datetime ngày cần xét
 * @return ngày trước đó của _datetime
 */
Date previousDay(Date datetime) {
    Date _datetime = datetime;
    if (_datetime.day == 1) {
        if (_datetime.month == Jan) {
            _datetime.day = 31;
            _datetime.month = Dec;
            _datetime.year -= 1;
        } else if (_datetime.month == Mar) {
            if (_datetime.year % 4 == 0 && _datetime.year % 100 != 0) {
                _datetime.day = 29;
                _datetime.month = Feb;
            } else {
                _datetime.day = 28;
                _datetime.month = Feb;
            }
        } else if (_datetime.month == May || _datetime.month == Jul || _datetime.month == Oct || _datetime.month == Dec) {
            _datetime.day = 30;
            _datetime.month -= 1;
        } else {
            _datetime.day = 31;
            _datetime.month -= 1;
        }
    } else {
        _datetime.day -= 1;
    }

    return _datetime;
}

/**
 * Hàm trả về số ngày trong năm
 * @param datetime ngày cần xét
 * @return số ngày trong năm của datetime
 */
int countDaysOfYear(Date datetime) {
    int res = 0;
    for (int i = 1; i < datetime.month; ++i) {
        if (i == Feb) {
            if (datetime.year % 4 == 0 && datetime.year % 100 != 0) {
                res += 29;
            } else {
                res += 28;
            }
        } else if (i == Jan || i == Mar || i == May || i == Jul || i == Aug || i == Oct || i == Dec) {
            res += 31;
        } else {
            res += 30;
        }
    }
    res += datetime.day;
    return res;
}

/**
 * Hàm xuất ngày tháng năm
 * @param datetime ngày cần xuất
 */
void xuat(Date datetime) {
    cout << datetime.day << '/' << datetime.month << '/' << datetime.year;
}

/**
 * Hàm kiểm tra ngày tháng năm có hợp lệ không
 * @param datetime ngày cần kiểm tra
 */
void checkValid(Date datetime) {
    if (datetime.day < 1 || datetime.day > 31) {
        cout << "Invalid day\n";
        exit(0);
    }
    if (datetime.month < 1 || datetime.month > 12) {
        cout << "Invalid month\n";
        exit(0);
    }
    if (datetime.year < 1 || datetime.year > 9999) {
        cout << "Invalid year\n";
        exit(0);
    }
}

int main() {
    Date datetime;
    cout << "Nhập ngày tháng năm (VD: 01 01 2001): ";
    cin >> datetime.day >> datetime.month >> datetime.year;
    checkValid(datetime);
    Date next = nextDay(datetime);
    cout << "Ngày tiếp theo: "; xuat(next); cout << '\n';
    Date prev = previousDay(datetime);
    cout << "Ngày trước đó: "; xuat(prev); cout << '\n';
    cout << "Ngày "; xuat(datetime); cout << " là ngày thứ " << countDaysOfYear(datetime) << " trong năm\n";
    return 0;
}