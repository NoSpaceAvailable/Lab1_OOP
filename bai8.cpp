#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <iomanip>
#define TYPE_LENGTH 10
#define MAX_NAME_LENGTH 30
#define MAX_ID_LENGTH 5
#define NGAN_HAN "Ngắn hạn"
#define DAI_HAN "Dài hạn"
#define CURRENT_DATETIME "10/11/2024"

using namespace std;

enum toCheck { 
    maSo, loaiTietKiem, hoVaTen, CMND, ngayMoSo, soTienGui
};

enum months {
    Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

struct Date {
    int day, month, year;
    bool isLeap = false;
};

struct SoTietKiem {
    string maSo;
    string loaiTietKiem;
    string hoVaTen;
    string CMND;
    Date ngayMoSo;
    double soTienGui;
};

bool dateExist(string date);
bool isValidDate(string date);
bool hasValidID(string toCheck);
bool hasValidCMND(string CMND);
string toDateString(Date &d);
bool checkName(string &name);
int cmp(Date &l, Date &r);
Date parse(string datetime);
bool isSTKValid(string toCheck, int flag, double optional = 0);
int countDaysBetween(Date &start, Date &end);
double tinhTienLai(SoTietKiem &stk, double laiSuat, Date start);
string phanLoaiTienGui(string ngaymoso);
int search(vector<SoTietKiem> &stk, string id, int flag);
void search(vector<SoTietKiem> &stk);
void rutTien(vector<SoTietKiem> &stk);
void tinhLai(vector<SoTietKiem> &stk, double laiSuatNganHan, double laiSuatDaiHan);
void capNhatLaiSuat(double &laisuatnganhan, double &laisuatdaihan);
void _sort(vector<SoTietKiem> &stk);
void enumerate(vector<SoTietKiem> &stk);
void nhap(vector<SoTietKiem> &dsstk);
void printBanner();
void xuat(SoTietKiem &stk);
void clear();

/**
 * Hàm dùng để kiểm tra xem ngày có tồn tại theo lịch không.
 * @param date ngày cần kiểm tra.
 * @return `true` nếu ngày tồn tại, ngược lại trả về `false`.
 */
bool dateExist(string date) {
    int day = (date[0] - '0')*10 + (date[1] - '0');
    int month = (date[3] - '0')*10 + (date[4] - '0');
    int year = (date[6] - '0')*1000 + (date[7] - '0')*100 + (date[8] - '0')*10 + (date[9] - '0');
    bool leap = false;
    if (year < 0 || year > 2024) {
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
 * Hàm dùng để kiểm tra xem format ngày có hợp lệ không.
 * @param date ngày cần kiểm tra.
 * @return `true` nếu ngày hợp lệ, ngược lại trả về `false`.
 * @note Format ngày hợp lệ: dd/mm/yyyy
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
 * Hàm dùng để kiểm tra xem mã số có hợp lệ không.
 * @param toCheck mã số cần kiểm tra.
 * @return `true` nếu mã số hợp lệ, ngược lại trả về `false`.
 * @note Mã số hợp lệ khi không chứa kí tự đặc biệt và có độ dài không quá 5 kí tự.
 */
bool hasValidID(string toCheck) {
    if (toCheck.length() > MAX_ID_LENGTH) return false;
    for (int i = 0; i < toCheck.length(); i++) {
        if (!isalnum(toCheck[i])) {
            return false;
        }
    }
    return true;
}

/**
 * Hàm dùng để kiểm tra xem CMND có hợp lệ không.
 * @param CMND số CMND cần kiểm tra.
 * @return `true` nếu CMND hợp lệ, ngược lại trả về `false`.
 * @note CMND hợp lệ khi có độ dài 9 hoặc 12 kí tự và chỉ chứa kí tự số.
 */
bool hasValidCMND(string CMND) {
    regex pattern("^[0-9]{9}$|^[0-9]{12}$");
    return regex_match(CMND, pattern);
}

/**
 * Hàm chuyển đổi struct ngày thành chuỗi.
 * @param d struct ngày cần chuyển đổi.
 * @return chuỗi ngày dạng dd/mm/yyyy.
 */
string toDateString(Date &d) {
    return (d.day < 10 ? "0" + to_string(d.day) : to_string(d.day)) + "/" + (d.month < 10 ? "0" + to_string(d.month) : to_string(d.month)) + "/" + to_string(d.year);
}

/**
 * Hàm kiểm tra xem tên có hợp lệ không.
 * @param name tên cần kiểm tra.
 * @return `true` nếu tên hợp lệ, ngược lại trả về `false`.
 * @note Tên hợp lệ khi bắt đầu bằng kí tự in hoa và không chứa kí tự đặc biệt.
 */
bool checkName(string &name) {
    if (name.length() > MAX_NAME_LENGTH) {
        return false;
    }
    regex pattern("^[A-Z][a-z]*( [A-Z][a-z]*)+$");
    return regex_match(name, pattern);
}

/**
 * Hàm so sánh 2 struct `Date`.
 * @param l struct `Date` thứ nhất.
 * @param r struct `Date` thứ hai.
 * @return 1 nếu l > r, -1 nếu l < r, 0 nếu l = r.
 */
int cmp(Date &l, Date &r) {
    if (l.year > r.year) return 1;
    if (l.year < r.year) return -1;
    else {
        if (l.month > r.month) return 1;
        if (l.month < r.month) return -1;
        else {
            if (l.day > r.day) return 1;
            if (l.day < r.day) return -1;
            else return 0;
        }
    }
}

/**
 * Hàm chuyển đổi chuỗi ngày thành struct `Date`.
 * @param datetime chuỗi ngày cần chuyển đổi.
 * @return struct `Date` sau khi chuyển đổi.
 */
Date parse(string datetime) {
    // ex: 11/01/2024
    // format: dd/mm/yyyy

    Date _date;
    if (isValidDate(datetime)) {
        _date = { (datetime[0] - '0')*10 + (datetime[1] - '0'), 
                  (datetime[3] - '0')*10 + (datetime[4] - '0'), 
                  (datetime[6] - '0')*1000 + (datetime[7] - '0')*100 + (datetime[8] - '0')*10 + (datetime[9] - '0') };
    }
    if (_date.year % 4 == 0 && _date.year % 100 != 0) {
        _date.isLeap = true;
    }
    return _date;
}

/**
 * Hàm kiểm tra tính hợp lệ của thông tin.
 * @param toCheck thông tin cần kiểm tra.
 * @param flag cờ xác định loại thông tin cần kiểm tra.
 * @param optional thông tin phụ thuộc vào loại thông tin cần kiểm tra.
 * @return `true` nếu thông tin hợp lệ, ngược lại trả về `false`.
 */
bool isSTKValid(string toCheck, int flag, double optional) {
    switch (flag) {
        case maSo: {
            if (toCheck.length() > MAX_ID_LENGTH) return false;
            for (int i = 0; i < toCheck.length(); i++) {
                if (!isalnum(toCheck[i])) {
                    return false;
                }
            }
            return true;
        }
        case loaiTietKiem: {
            if (toCheck != NGAN_HAN && toCheck != DAI_HAN) {
                return false;
            }
            return true;
        }
        case hoVaTen: {
            return checkName(toCheck);
        }
        case CMND: {
            return hasValidCMND(toCheck);
        }
        case ngayMoSo: {
            return isValidDate(toCheck);
        }
        case soTienGui: {
            return optional > 0;
        }
        default: return false;
    }
}

/**
 * Hàm đếm số ngày giữa 2 ngày.
 * @param start ngày bắt đầu.
 * @param end ngày kết thúc.
 * @return số ngày giữa 2 ngày.
 */
int countDaysBetween(Date &start, Date &end) {
    auto isLeapYear = [](int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    };

    auto daysInMonth = [&](int month, bool isLeap) {
        switch (month) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                return 31;
            case 4: case 6: case 9: case 11:
                return 30;
            case 2:
                return isLeap ? 29 : 28;
            default:
                return 0;
        }
    };

    auto daysFromStartOfYear = [&](Date date) {
        int days = 0;
        for (int month = 1; month < date.month; ++month) {
            days += daysInMonth(month, date.isLeap);
        }
        return days + date.day;
    };

    int totalDays = 0;

    for (int year = start.year; year < end.year; ++year) {
        totalDays += isLeapYear(year) ? 366 : 365;
    }

    totalDays -= daysFromStartOfYear(start);
    totalDays += daysFromStartOfYear(end);

    return totalDays;
}

/**
 * Hàm tính tiền lãi. Công thức: Số tiền lãi = (Số tiền gửi x lãi suất (%/năm) x số ngày thực gửi) / 360 ngày. Tính theo lãi đơn
 * @param stk thông tin sổ tiết kiệm.
 * @param laiSuat lãi suất.
 * @param start ngày mở sổ.
 * @return số tiền lãi.
 */
double tinhTienLai(SoTietKiem &stk, double laiSuat, Date start) {
    Date currentDate = parse(CURRENT_DATETIME);
    return (stk.soTienGui * laiSuat * countDaysBetween(start, currentDate) / 360);
}

/**
 * Hàm phân loại tiền gửi.
 * @param ngaymoso ngày mở sổ.
 * @return loại tiền gửi.
 */
string phanLoaiTienGui(string ngaymoso) {
    Date currentTime = parse(CURRENT_DATETIME);
    Date d = parse(ngaymoso);
    if ((double)countDaysBetween(d, currentTime) / 30 <= 6) {
        return NGAN_HAN;
    }
    return DAI_HAN;
}

/**
 * Hàm tìm kiếm thông tin sổ tiết kiệm.
 * @param stk danh sách sổ tiết kiệm.
 * @param id mã sổ hoặc CMND cần tìm.
 * @param flag cờ xác định loại tìm kiếm. Có thể là mã sổ hoặc CMND.
 * @return vị trí sổ tiết kiệm trong danh sách.
 */
int search(vector<SoTietKiem> &stk, string id, int flag) {
    switch (flag) {
        case maSo: {
            for (int i = 0; i < stk.size(); i++) {
                if (stk[i].maSo == id) {
                    return i;
                }
            }
            return -1;
        }
        case CMND: {
            for (int i = 0; i < stk.size(); i++) {
                if (stk[i].CMND == id) {
                    return i;
                }
            }
            return -1;
        }
        default: return -1;
    }
}

/**
 * Hàm tìm kiếm thông tin sổ tiết kiệm và xuất thông tin.
 * @param stk danh sách sổ tiết kiệm.
 */
void search(vector<SoTietKiem> &stk) {
    while (true) {
        cout << "Tìm theo?\n1. Mã sổ\n2. CMND\n3. Quay lại\n";
        cout << ">> "; int choice; cin >> choice;
        cin.ignore();
        if (choice == 1) {
            cout << "Nhập mã sổ cần tìm: \n";
            string stkID; cout << ">> "; getline(cin, stkID);
            int idx = search(stk, stkID, maSo);
            if (idx == -1) {
                cout << "Không tìm thấy sổ tiết kiệm!\n";
            } else {
                xuat(stk[idx]);
            }
        } else if (choice == 2) {
            cout << "Nhập CMND cần tìm: \n";
            string stkID; cout << ">> "; getline(cin, stkID);
            int idx = search(stk, stkID, CMND);
            if (idx == -1) {
                cout << "Không tìm thấy sổ tiết kiệm!\n";
            } else {
                xuat(stk[idx]);
            }
        } else if (choice == 3) {
            clear();
            break;
        } else {
            cout << "Lựa chọn không hợp lệ!\n";
        }
    }
}

/**
 * Hàm rút tiền từ sổ tiết kiệm.
 * @param stk danh sách sổ tiết kiệm.
 */
void rutTien(vector<SoTietKiem> &stk) {
    cout << "Nhập mã sổ tiết kiệm cần rút tiền: \n";
    string ID; cout << ">> "; getline(cin, ID);
    int idx = search(stk, ID, maSo);
    if (idx == -1) {
        cout << "Không tìm thấy sổ tiết kiệm!\n";
        return;
    }
    double tienRut = 0;
    cout << "Nhập số tiền cần rút: \n";
    cout << ">> "; cin >> tienRut;
    while (tienRut > stk[idx].soTienGui || tienRut <= 0) {
        cout << "Số tiền rút không hợp lệ hoặc lớn hơn số tiền hiện có!\n";
        cout << "Nhập lại: \n>> "; cin >> tienRut;
    }
    stk[idx].soTienGui -= tienRut;
    cout << "Rút tiền thành công!\nTài khoản còn lại: " << stk[idx].soTienGui << '\n';
}

/**
 * Hàm tính lãi cho sổ tiết kiệm.
 * @param stk danh sách sổ tiết kiệm.
 * @param laiSuatNganHan lãi suất ngắn hạn.
 * @param laiSuatDaiHan lãi suất dài hạn.
 */
void tinhLai(vector<SoTietKiem> &stk, double laiSuatNganHan, double laiSuatDaiHan) {
    cout << "Nhập mã sổ cần tính lãi: \n";
    string stkID; cout << ">> "; getline(cin, stkID);
    int idx = search(stk, stkID, maSo);
    if (idx == -1) {
        cout << "Không tìm thấy sổ tiết kiệm!\n";
        return;
    }
    double tienLai = 0;
    if (stk[idx].loaiTietKiem == NGAN_HAN) {
        tienLai = tinhTienLai(stk[idx], laiSuatNganHan, stk[idx].ngayMoSo);
    } else {
        tienLai = tinhTienLai(stk[idx], laiSuatDaiHan, stk[idx].ngayMoSo);
    }
    cout << "Tiền lãi: " << tienLai << '\n';
}

/**
 * Hàm cập nhật lãi suất.
 * @param laisuatnganhan lãi suất ngắn hạn.
 * @param laisuatdaihan lãi suất dài hạn.
 */
void capNhatLaiSuat(double &laisuatnganhan, double &laisuatdaihan) {
    while (true) {
        cout << "Cập nhật lãi suất: \n1. Ngắn hạn\n2. Dài hạn\n3. Quay lại\n";
        cout << ">> "; int choice; cin >> choice;
        cin.ignore();
        if (choice == 1) {
            cout << "Nhập lãi suất ngắn hạn: \n";
            cout << ">> "; cin >> laisuatnganhan;
            while (laisuatnganhan < 0) {
                cout << "Lãi suất không hợp lệ! Nhập lại: \n";
                cout << ">> "; cin >> laisuatnganhan;
            }
            cout << "Cập nhật lãi suất thành công!\n";
        } else if (choice == 2) {
            cout << "Nhập lãi suất dài hạn: \n";
            cout << ">> "; cin >> laisuatdaihan;
            while (laisuatdaihan < 0) {
                cout << "Lãi suất không hợp lệ! Nhập lại: \n";
                cout << ">> "; cin >> laisuatdaihan;
            }
            cout << "Cập nhật lãi suất thành công!\n";
        } else if (choice == 3) {
            clear();
            break;
        } else {
            cout << "Lựa chọn không hợp lệ!\n";
        }
    }
}

/**
 * Hàm sắp xếp danh sách sổ tiết kiệm. Có thể sắp xếp theo ngày mở sổ hoặc số tiền gửi.
 * @param stk danh sách sổ tiết kiệm.
 */
void _sort(vector<SoTietKiem> &stk) {
    while (true) {
        cout << "Sắp xếp theo?\n1. Ngày mở sổ (tăng dần)\n2. Số tiền gửi (giảm dần)\n3. Quay lại\n";
        cout << ">> "; int choice; cin >> choice;
        cin.ignore();
        if (choice == 1) {
            sort(stk.begin(), stk.end(), [](SoTietKiem &l, SoTietKiem &r) {
                return cmp(l.ngayMoSo, r.ngayMoSo) < 0;
            });
            cout << "Sắp xếp thành công!\n";
            return;
        } else if (choice == 2) {
            sort(stk.begin(), stk.end(), [](SoTietKiem &l, SoTietKiem &r) {
                return l.soTienGui > r.soTienGui;
            });
            cout << "Sắp xếp thành công!\n";
            return;
        } else if (choice == 3) {
            clear();
            return;
        } else {
            cout << "Lựa chọn không hợp lệ!\n";
        }
    }
}

/**
 * Hàm liệt kê các sổ mở trong khoảng thời gian cho trước. Tương tác với người dùng để nhập ngày bắt đầu và kết thúc.
 * @param stk danh sách sổ tiết kiệm.
 */
void enumerate(vector<SoTietKiem> &stk) {
    string start, end;
    cout << "Nhập ngày bắt đầu: \n";
    cout << ">> "; getline(cin, start);
    while (!isValidDate(start)) {
        cout << "Ngày không hợp lệ! Nhập lại: \n";
        cout << ">> "; getline(cin, start);
    }
    cout << "Nhập ngày kết thúc: \n";
    cout << ">> "; getline(cin, end);
    while (!isValidDate(end)) {
        cout << "Ngày không hợp lệ! Nhập lại: \n";
        cout << ">> "; getline(cin, end);
    }
    Date startDate = parse(start);
    Date endDate = parse(end);
    bool found = false;
    for (SoTietKiem s : stk) {
        if (cmp(s.ngayMoSo, startDate) >= 0 && cmp(s.ngayMoSo, endDate) <= 0) {
            found = true;
            xuat(s);
        }
    }
    if (!found) {
        cout << "Không tìm thấy sổ nào trong khoảng thời gian đã nhập!\n";
    }
}

/**
 * Hàm nhập thông tin sổ tiết kiệm.
 * @param dsstk danh sách sổ tiết kiệm.
 */
void nhap(vector<SoTietKiem> &dsstk) {
    string ms, hoten, cmnd, ngaymoso, phanloaiso;
    double sotiengui;
    cout << "Nhập mã sổ: \n";
    cout << ">> "; getline(cin, ms);
    while (!isSTKValid(ms, maSo)) {
        cout << "Mã sổ không hợp lệ! Nhập lại: \n";
        cout << ">> "; getline(cin, ms);
    }
    cout << "Họ và tên chủ sổ (VD: Le Quoc Cuong): \n";
    cout << ">> "; getline(cin, hoten);
    while (!isSTKValid(hoten, hoVaTen)) {
        cout << "Họ và tên không hợp lệ! Nhập lại: \n";
        cout << ">> "; getline(cin, hoten);
    }
    cout << "Nhập CMND: \n";
    cout << ">> "; getline(cin, cmnd);
    while (!isSTKValid(cmnd, CMND)) {
        cout << "CMND không hợp lệ! Nhập lại: \n";
        cout << ">> "; getline(cin, cmnd);
    }
    cout << "Nhập ngày mở sổ (dd/mm/yyyy): \n";
    cout << ">> "; getline(cin, ngaymoso);
    while (!isSTKValid(ngaymoso, ngayMoSo)) {
        cout << "Ngày mở sổ không hợp lệ! Nhập lại: \n";
        cout << ">> "; getline(cin, ngaymoso);
    }
    phanloaiso = phanLoaiTienGui(ngaymoso);
    cout << "Nhập số tiền gửi: \n";
    cout << ">> "; cin >> sotiengui;
    while (!isSTKValid("", soTienGui, sotiengui)) {
        cout << "Số tiền gửi không hợp lệ! Nhập lại: \n";
        cout << ">> "; cin >> sotiengui;
    }
    SoTietKiem stk = { ms, phanloaiso, hoten, cmnd, parse(ngaymoso), sotiengui };
    dsstk.push_back(stk);
    cout << "Nhập sổ thành công!\n";
    return;
}

/**
 * Hàm in menu chương trình.
 */
void printBanner() {
    cout << "========================================================================\n";
    cout << "1. Nhập dữ liệu sổ\n";
    cout << "2. Xuất dữ liệu toàn bộ sổ\n";
    cout << "3. Cập nhật lãi suất\n";
    cout << "4. Tính toán tiền lãi\n";
    cout << "5. Rút tiền\n";
    cout << "6. Tìm kiếm sổ theo CMND hoặc mã sổ\n";
    cout << "7. Liệt kê các sổ mở trong khoảng thời gian\n";
    cout << "8. Sắp xếp danh sách sổ tiết kiệm\n";
    cout << "9. Clear screen\n";
    cout << "10. Thoát\n";
    cout << "========================================================================\n";
}

/**
 * Hàm xuất thông tin sổ tiết kiệm.
 * @param stk thông tin sổ tiết kiệm.
 */
void xuat(SoTietKiem &stk) {
    cout << "----------------------------------------\n";
    cout << "--- Mã sổ: " << stk.maSo << '\n';
    cout << "--- Loại tiết kiệm: " << stk.loaiTietKiem << '\n';
    cout << "--- Họ và tên chủ sổ: " << stk.hoVaTen << '\n';
    cout << "--- CMND: " << stk.CMND << '\n';
    cout << "--- Ngày mở sổ: " << toDateString(stk.ngayMoSo) << '\n';
    cout << "--- Số tiền gửi: " << fixed << setprecision(3) << stk.soTienGui << '\n';
    cout << "----------------------------------------\n";
}

// Clear console cho dễ nhìn
void clear() {
    system("clear");
}

/**
 * Hàm main làm các nhiệm vụ sau:
 * - Khởi tạo vector sổ tiết kiệm
 * - Khởi tạo lãi suất ngắn hạn và dài hạn
 * - Hiển thị menu chương trình
 * - Cho phép người dùng nhập và lựa chọn chức năng
 */
int main() {
    vector<SoTietKiem> stk;
    double laiSuatNganHan = 0.029;
    double laiSuatDaiHan = 0.047;
    while (true) {
        printBanner();
        int choice; cout << ">> "; cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                clear();
                nhap(stk);
                break;
            }
            case 2: {
                if (stk.size() == 0) {
                    cout << "Danh sách sổ trống!\n";
                    break;
                }
                for (SoTietKiem s : stk) {
                    xuat(s);
                }
                break;
            }
            case 3: {
                clear();
                capNhatLaiSuat(laiSuatNganHan, laiSuatDaiHan);
                break;
            }
            case 4: {
                clear();
                if (stk.size() == 0) {
                    cout << "Danh sách sổ trống!\n";
                    break;
                }
                tinhLai(stk, laiSuatNganHan, laiSuatDaiHan);
                break;
            }
            case 5: {
                clear();
                if (stk.size() == 0) {
                    cout << "Danh sách sổ trống!\n";
                    break;
                }
                rutTien(stk);
                break;
            }
            case 6: {
                clear();
                if (stk.size() == 0) {
                    cout << "Danh sách sổ trống!\n";
                    break;
                }
                search(stk);
                break;
            }
            case 7: {
                clear();
                if (stk.size() == 0) {
                    cout << "Danh sách sổ trống!\n";
                    break;
                }
                enumerate(stk);
                break;
            }
            case 8: {
                clear();
                if (stk.size() == 0) {
                    cout << "Danh sách sổ trống!\n";
                    break;
                }
                _sort(stk);
                break;
            }
            case 9: {
                clear();
                break;
            }
            case 10: {
                cout << "Bye!\n";
                return 0;
            }
            default: {
                clear();
                cout << "Lựa chọn không hợp lệ!\n";
                break;
            }
        }
    }
}