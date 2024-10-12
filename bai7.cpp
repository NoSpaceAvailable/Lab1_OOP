#include <iostream>
#include <vector>
#include <string>
#include <regex>
#define VALID_LENGTH 20
#define VALID_TIME_LENGTH 16
#define CB_MAX_LENGTH 5
using namespace std;

enum neededToCheck {
    maChuyenBay, thoiGianBay, noiDi, noiDen
};

struct Date {
    int day, month, year;
    bool isLeap = false;
};

struct Time {
    int hour, minute;
};

struct Datetime {
    Date date;
    Time time;
};

struct ChuyenBay {
    string maChuyenBay;
    Datetime thoiGianBay;
    string noiDi;
    string noiDen;
};

/**
 * Hàm chia chuỗi thành các phần nhỏ dựa vào delimiter.
 * @param s chuỗi cần chia.
 * @param delim delimiter.
 * @return vector chứa các phần nhỏ.
 */
vector<string> split(string s, string delim = " ") {
    vector<string> res;
    int start, end = (-1) * delim.size();
    do {
        start = end + delim.size();
        end = s.find(delim, start);
        res.push_back(s.substr(start, end - start));
    } while (end != -1);
    return res;
}

/**
 * Hàm kiểm tra xem ngày có tồn tại không.
 * @param date ngày cần kiểm tra.
 * @return `true` nếu ngày tồn tại, ngược lại trả về `false`.
 */
bool dateExist(string date) {
    int day = (date[0] - '0')*10 + (date[1] - '0');
    int month = (date[3] - '0')*10 + (date[4] - '0');
    int year = (date[6] - '0')*1000 + (date[7] - '0')*100 + (date[8] - '0')*10 + (date[9] - '0');
    bool leap = false;
    if (year < 0 || year > 9999) {
        return false;
    }
    if (year % 4 == 0 && year % 100 != 0) {
        leap = true;
    }
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > 31) {
        return false;
    }
    if (month == 2) {
        if (leap) {
            if (day > 29) {
                return false;
            }
        } else {
            if (day > 28) {
                return false;
            }
        }
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return false;
        }
    }
    return true;
}

/**
 * Hàm kiểm tra xem format ngày và giờ có hợp lệ không.
 * @param date ngày cần kiểm tra.
 * @return `true` nếu hợp lệ, ngược lại trả về `false`.
 */
bool isValidDate(string date) {
    if (date.length() != 10) {
        return false;
    }
    if (date[2] != '/' || date[5] != '/') {
        return false;
    }
    int __idx_arr[] = {0, 1, 3, 4, 6, 7, 8, 9};
    for (int i : __idx_arr) {
        if (!isdigit(date[i])) {
            return false;
        }
    }
    return dateExist(date);
}

/**
 * Hàm kiểm tra xem format giờ có hợp lệ không.
 * @param time giờ cần kiểm tra.
 * @return `true` nếu hợp lệ, ngược lại trả về `false`.
 */
bool isValidTime(string time) {
    if (time.length() != 5) {
        return false;
    }
    if (time[2] != ':') {
        return false;
    }
    int __idx_arr[] = {0, 1, 3, 4};
    for (int i : __idx_arr) {
        if (!isdigit(time[i])) {
            return false;
        }
    }
    int hour = (time[0] - '0')*10 + (time[1] - '0');
    int minute = (time[3] - '0')*10 + (time[4] - '0');
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return false;
    }
    return true;
}

/**
 * Hàm chuyển thời gian thành phút.
 * @param t thời gian cần chuyển.
 * @return thời gian tính bằng phút.
 */
int timeSum(Time &t) {
    return (t.hour - 1)*60 + t.minute;
}

/**
 * Hàm chuyển struct ngày thành chuỗi.
 * @param d ngày cần chuyển, kiểu `Date`.
 * @return chuỗi ngày.
 */
string toDateString(Date &d) {
    return (d.day < 10 ? "0" + to_string(d.day) : to_string(d.day)) + "/" + (d.month < 10 ? "0" + to_string(d.month) : to_string(d.month)) + "/" + to_string(d.year);
}

/**
 * Hàm chuyển chuỗi thành struct ngày và giờ.
 * @param datetime chuỗi cần chuyển.
 * @return struct ngày và giờ.
 */
Datetime parse(string datetime) {
    // ex: 11/01/2024 23:59
    // format: dd/mm/yyyy hh:mm
    vector<string> dt = split(datetime);
    string _date = dt.at(0);
    string _time = dt.at(1);
    Datetime _datetime;
    
    if (isValidDate(_date) && isValidTime(_time)) {
        _datetime.date = { (_date[0] - '0')*10 + (_date[1] - '0'), (_date[3] - '0')*10 + (_date[4] - '0'), (_date[6] - '0')*1000 + (_date[7] - '0')*100 + (_date[8] - '0')*10 + (_date[9] - '0') };
        _datetime.time = { (_time[0] - '0')*10 + (_time[1] - '0'), (_time[3] - '0')*10 + (_time[4] - '0') };
    }
    if (_datetime.date.year % 4 == 0 && _datetime.date.year % 100 != 0) {
        _datetime.date.isLeap = true;
    }
    return _datetime;
}

/**
 * Hàm so sánh 2 struct ngày và giờ.
 * @param l struct ngày và giờ thứ nhất.
 * @param r struct ngày và giờ thứ hai.
 * @return 1 nếu l > r, -1 nếu l < r, 0 nếu l = r.
 */
int cmp(Datetime &l, Datetime &r) {
    if (l.date.year > r.date.year) return 1;
    if (l.date.year < r.date.year) return -1;
    else {
        if (l.date.month > r.date.month) return 1;
        if (l.date.month < r.date.month) return -1;
        else {
            if (l.date.day > r.date.day) return 1;
            if (l.date.day < r.date.day) return -1;
            else {
                int res = timeSum(l.time) - timeSum(r.time);
                if (res > 0) return 1;
                if (res < 0) return -1;
                else return 0;
            }
        }
    }
}

/**
 * Hàm kiểm tra xem chuỗi có hợp lệ không.
 * @param toCheck chuỗi cần kiểm tra.
 * @param flag cờ để kiểm tra. Các giá trị có thể có: `maChuyenBay`, `thoiGianBay`, `noiDi`, `noiDen`.
 * @return `true` nếu hợp lệ, ngược lại trả về `false`.
 */
bool checkValid(string toCheck, int flag) {
    switch (flag) {
        case maChuyenBay: {
            if (toCheck.length() > CB_MAX_LENGTH) return false;
            for (int i = 0; i < toCheck.length(); i++) {
                if (!isalnum(toCheck[i])) {
                    return false;
                }
            }
            return true;
        }
        case thoiGianBay: {
            if (toCheck.length() != VALID_TIME_LENGTH) return false;
            vector<string> dt = split(toCheck);
            return isValidDate(dt.at(0)) && isValidTime(dt.at(1));
        }
        case noiDi:
        case noiDen: {
            if (toCheck.length() > VALID_LENGTH) return false;
            regex pattern("^[A-Za-z ,]+$");
            return regex_match(toCheck, pattern);
        }
        default: return false;
    }
}

/**
 * Hàm in ra ngày và giờ.
 * @param dt struct ngày và giờ cần in.
 */
void printDatetime(Datetime dt) {
    cout << (dt.date.day < 10 ? "0" + to_string(dt.date.day) : to_string(dt.date.day)) << "/" << (dt.date.month < 10 ? "0" + to_string(dt.date.month) : to_string(dt.date.month)) << "/" << dt.date.year << " " << dt.time.hour << ":" << dt.time.minute << '\n';
}

/**
 * Hàm in ra banner.
 */
void printBanner() {
    cout << "========================================================================\n";
    cout << "1. Nhập dữ liệu\n";
    cout << "2. Xuất dữ liệu toàn bộ chuyến bay\n";
    cout << "3. Tìm chuyến bay theo mã chuyến bay, nơi đi hoặc nơi đến\n";
    cout << "4. Sắp xếp chuyến bay\n";
    cout << "5. Tìm chuyến bay theo thời gian và địa điểm khởi hành\n";
    cout << "6. Đếm số chuyến bay từ nơi A đến B\n";
    cout << "7. Clear screen\n";
    cout << "8. Thoát\n";
    cout << "========================================================================\n";
}

/**
 * Hàm in ra thông tin chuyến bay.
 * @param cb chuyến bay cần in.
 */
void xuat(ChuyenBay cb) {
    cout << "-----------------------------------\n";
    cout << "--- Mã chuyến bay: " << cb.maChuyenBay << '\n';
    cout << "--- Thời gian bay: "; printDatetime(cb.thoiGianBay);
    cout << "--- Nơi đi: " << cb.noiDi << '\n';
    cout << "--- Nơi đến: " << cb.noiDen << '\n';
    cout << "-----------------------------------\n";
}

/**
 * Clear console, để cho dễ nhìn nội dung trên màn hình
 */
void clear() {
    system("clear");
}

/**
 * Hàm nhập thông tin chuyến bay. Có áp dụng kiểm tra dữ liệu đầu vào.
 * @return struct chuyến bay.
 */
ChuyenBay nhap() {
    cout << "[1] Nhập mã chuyến bay (độ dài 5, không chứa khoảng trắng và kí tự đặc biệt): \n";
    cout << ">> ";
    string mcb;
    cin.ignore();
    getline(cin, mcb);
    while (!checkValid(mcb, maChuyenBay)) {
        cout << "[x] Mã chuyến bay không hợp lệ, vui lòng nhập lại: \n";
        cout << ">> ";
        getline(cin, mcb);
    }
    clear();
    cout << "[1] Nhập thời gian bay (dd/mm/yyyy hh:mm): \n";
    cout << ">> ";
    string tgb;
    getline(cin, tgb);
    while (!checkValid(tgb, thoiGianBay)) {
        cout << "[x] Thời gian bay không hợp lệ hoặc không tồn tại, vui lòng nhập lại: \n";
        cout << ">> ";
        getline(cin, tgb);
    }
    clear();
    cout << "[1] Nhập nơi đi (dài tối đa 20, có thể chứa dấu cách và phẩy): \n";
    cout << ">> ";
    string nd; getline(cin, nd);
    while (!checkValid(nd, noiDi)) {
        cout << "[x] Nơi đi không hợp lệ, vui lòng nhập lại: \n";
        cout << ">> ";
        getline(cin, nd);
    }
    clear();
    cout << "[1] Nhập nơi đến (dài tối đa 20, có thể chứa dấu cách và phẩy): \n";
    cout << ">> ";
    string nD; getline(cin, nD);
    while (!checkValid(nD, noiDen)) {
        cout << "[x] Nơi đến không hợp lệ, vui lòng nhập lại: \n";
        cout << ">> ";
        getline(cin, nD);
    }
    clear();
    return ChuyenBay {mcb, parse(tgb), nd, nD};
}

int main() {
    vector<ChuyenBay> dscb;
    while (true) {
        printBanner();
        int choice; cout << ">> "; cin >> choice;
        switch (choice) {
            case 1: {
                clear();
                dscb.push_back(nhap());
                break;
            }
            case 2: {
                if (dscb.size() == 0) {
                    cout << "Danh sách chuyến bay trống!\n";
                    break;
                }
                for (ChuyenBay cb : dscb) {
                    xuat(cb);
                }
                break;
            }
            case 3: {
                if (dscb.size() == 0) {
                    cout << "Danh sách chuyến bay trống!\n";
                    break;
                }
                clear();
                while (true) {
                    cout << "[3] Tìm kiếm theo?\n";
                    cout << "1. Mã chuyến bay\n";
                    cout << "2. Nơi đi\n";
                    cout << "3. Nơi đến\n";
                    cout << "4. Quay lại\n";
                    cout << ">> ";
                    int c; cin >> c;
                    if (c == 1) {
                        clear();
                        cout << "Nhập mã chuyến bay cần tìm: \n";
                        cout << ">> ";
                        string mcb; cin.ignore(); getline(cin, mcb);
                        bool found = false;
                        for (ChuyenBay cb : dscb) {
                            if (cb.maChuyenBay == mcb) {
                                found = true;
                                xuat(cb);
                            }
                        }
                        if (!found) {
                            cout << "Không tìm thấy chuyến bay!\n";
                        }
                    }
                    if (c == 2) {
                        clear();
                        cout << "Nhập nơi đi cần tìm: \n";
                        cout << ">> ";
                        string nd; cin.ignore(); getline(cin, nd);
                        bool found = false;
                        for (ChuyenBay cb : dscb) {
                            if (cb.noiDi == nd) {
                                found = true;
                                xuat(cb);
                            }
                        }
                        if (!found) {
                            cout << "Không tìm thấy chuyến bay!\n";
                        }
                    }
                    if (c == 3) {
                        clear();
                        cout << "Nhập nơi đến cần tìm: \n";
                        cout << ">> ";
                        string nD; cin.ignore(); getline(cin, nD);
                        bool found = false;
                        for (ChuyenBay cb : dscb) {
                            if (cb.noiDen == nD) {
                                found = true;
                                xuat(cb);
                            }
                        }
                        if (!found) {
                            cout << "Không tìm thấy chuyến bay!\n";
                        }
                    }
                    if (c == 4) {
                        clear();
                        break;
                    }
                    else {
                        cout << "Lựa chọn không hợp lệ!\n";
                    }
                }
                break;
            }
            case 4: {
                if (dscb.size() == 0) {
                    cout << "Danh sách chuyến bay trống!\n";
                    break;
                }
                sort(dscb.begin(), dscb.end(), [](ChuyenBay &l, ChuyenBay &r) {
                    return cmp(l.thoiGianBay, r.thoiGianBay) < 0;
                });
                cout << "Đã sắp xếp theo thời gian bay!\n";
                break;
            }
            case 5: {
                if (dscb.size() == 0) {
                    cout << "Danh sách chuyến bay trống!\n";
                    break;
                }
                clear();
                cout << "Nhập địa điểm khởi hành: \n";
                cout << ">> ";
                string dd; cin.ignore(); getline(cin, dd);
                cout << "Nhập thời gian khởi hành (dd/mm/yyyy): \n";
                cout << ">> ";
                string tgb; getline(cin, tgb);
                bool found = false;
                for (ChuyenBay cb : dscb) {
                    if (cb.noiDi == dd && toDateString(cb.thoiGianBay.date) == tgb) {
                        found = true;
                        xuat(cb);
                    }
                }
                if (!found) {
                    cout << "Không tìm thấy chuyến bay!\n";
                }
                break;
            }
            case 6: {
                if (dscb.size() == 0) {
                    cout << "Danh sách chuyến bay trống!\n";
                    break;
                }
                clear();
                cout << "Nhập địa điểm khởi hành: \n";
                cout << ">> ";
                string dd; cin.ignore(); getline(cin, dd);
                cout << "Nhập địa điểm đến: \n";
                cout << ">> ";
                string dD; getline(cin, dD);
                int count = 0;
                for (ChuyenBay cb : dscb) {
                    if (cb.noiDi == dd && cb.noiDen == dD) {
                        count++;
                    }
                }
                cout << "Số chuyến bay từ " << dd << " đến " << dD << " là: " << count << '\n';
                break;
            }
            case 7: {
                clear();
                break;
            }
            case 8: {
                cout << "Bye!\n";
                return 0;
            }
            default: {
                cout << "Lựa chọn không hợp lệ!\n";
                break;
            }
        }
    }
    return 0;
}