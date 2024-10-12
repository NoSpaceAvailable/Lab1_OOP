#include <iostream>
#include <vector>
#include <regex>
#include <limits>
#define MAX_NAME_LENGTH 50
using namespace std;

enum PhanLoai {
    XuatSac, Gioi, Kha, TrungBinh, Yeu
};

/**
 * Clear cin buffer. Việc này giúp loại bỏ các kí tự thừa trong buffer sau khi nhập một số.
 */
void cleanBuffer() {
    cin.ignore ( 100 , '\n' ); 
}

struct HocSinh {
    string hovaten;
    float toan, van, ngoaingu;
    float diemTB;
    int hocLuc;
};

/**
 * Kiểm tra tên hợp lệ.
 * @param name Tên cần kiểm tra.
 * @return `true` nếu tên hợp lệ, ngược lại `false`. Có sử dụng regex.
 */
bool checkName(string name) {
    if (name.length() > MAX_NAME_LENGTH) {
        return false;
    }
    regex pattern("^[A-Z][a-z]*( [A-Z][a-z]*)+$");
    return regex_match(name, pattern);
}

/**
 * Kiểm tra điểm hợp lệ.
 * @param diem Điểm cần kiểm tra.
 * @return `true` nếu điểm trong khoảng 0-10, ngược lại `false`.
 */
bool checkDiem(float diem) {
    return diem >= 0 && diem <= 10;
}

/**
 * Tính điểm trung bình.
 * @param toan Điểm toán.
 * @param van Điểm văn.
 * @param ngoaingu Điểm ngoại ngữ.
 * @return Điểm trung bình. Trọng số toán gấp đôi.
 */
float diemTrungBinh(int toan, int van, int ngoaingu) {
    return (2 * toan + van + ngoaingu) / 4;
}

/**
 * Phân loại học sinh dựa vào điểm trung bình.
 * @param hs Học sinh cần phân loại.
 * @return Phân loại học lực.
 */
int phanLoaiHocSinh(HocSinh hs) {
    if (hs.diemTB >= 9) {
        return XuatSac;
    } else if (hs.diemTB >= 8) {
        return Gioi;
    } else if (hs.diemTB >= 6.5) {
        return Kha;
    } else if (hs.diemTB >= 5) {
        return TrungBinh;
    } else {
        return Yeu;
    }
}

/**
 * Xuất thông tin học sinh.
 * @param hs Học sinh cần xuất thông tin.
 */
void xuat(HocSinh &hs) {
    cout << "--- Họ và tên: " << hs.hovaten << endl;
    cout << "--- Điểm toán: " << hs.toan << endl;
    cout << "--- Điểm văn: " << hs.van << endl;
    cout << "--- Điểm ngoại ngữ: " << hs.ngoaingu << endl;
    cout << "--- Điểm trung bình: " << hs.diemTB << endl;
    cout << "--- Học lực: ";
    switch (hs.hocLuc) {
        case XuatSac:
            cout << "Xuất sắc\n";
            break;
        case Gioi:
            cout << "Giỏi\n";
            break;
        case Kha:
            cout << "Khá\n";
            break;
        case TrungBinh:
            cout << "Trung bình\n";
            break;
        case Yeu:
            cout << "Yếu\n";
            break;
    }
}

/**
 * Tìm học sinh có điểm trung bình cao nhất.
 * @param hs Danh sách học sinh.
 * @param size Số lượng học sinh.
 * @return Học sinh có điểm trung bình cao nhất.
 */
HocSinh timHocSinhCoDiemTBCaoNhat(vector<HocSinh> &hs, int size) {
    HocSinh max = hs[0];
    for (int i = 1; i < size; i++) {
        if (hs[i].diemTB > max.diemTB) {
            max = hs[i];
        }
    }
    return max;
}

/**
 * Tìm học sinh theo tên.
 * @param hs Danh sách học sinh.
 * @param size Số lượng học sinh.
 * @param name Tên cần tìm.
 * @return Danh sách học sinh có tên chứa `name`.
 */
vector<HocSinh> timHocSinhTheoTenRegex(vector<HocSinh> &hs, int size, string name) {
    vector<HocSinh> result;
    if (name.length() > MAX_NAME_LENGTH) {
        return result;
    }
    std::regex pattern(".*" + name + ".*", std::regex_constants::icase);
    for (int i = 0; i < size; i++) {
        if (regex_search(hs[i].hovaten, pattern)) {
            result.push_back(hs[i]);
        }
    }
    return result;
}

/**
 * Danh sách học sinh có điểm toán thấp nhất.
 * @param hs Danh sách học sinh.
 * @param size Số lượng học sinh.
 * @return Danh sách học sinh có điểm toán thấp nhất.
 */
vector<HocSinh> danhSachHocSinhCoDiemToanThapNhat(vector<HocSinh> &hs, int size) {
    vector<HocSinh> result;
    float min = hs[0].toan;
    for (int i = 1; i < size; i++) {
        if (hs[i].toan < min) {
            min = hs[i].toan;
        }
    }
    for (int i = 0; i < size; i++) {
        if (hs[i].toan == min) {
            result.push_back(hs[i]);
        }
    }
    return result;
}

/**
 * Nhập thông tin học sinh. Có kiểm tra tính hợp lệ của đầu vào.
 * @param hs Danh sách học sinh.
 * @param size Số lượng học sinh.
 */
void nhap(vector<HocSinh> &hs, int size) {
    cin.ignore();
    cout << "Nhập tên các học sinh, viết hoa chữ cái đầu, không có dấu, số và kí tự đặc biệt:\n";
    for (int i = 0; i < size; i++) {
        cout << "Học sinh thứ " << i + 1 << ": " << endl;
        string name;
        cout << "--- Họ và tên: "; getline(cin, name);
        while (!checkName(name)) {
            cin.clear();
            cout << "Tên không hợp lệ, vui lòng nhập lại: "; getline(cin, name);
        }
        hs[i].hovaten = name;
        float diem;
        cout << "--- Điểm toán: "; cin >> diem;
        while (!checkDiem(diem)) {
            cout << "Điểm không hợp lệ, vui lòng nhập lại: "; cin >> diem;
        }
        hs[i].toan = diem;
        cout << "--- Điểm văn: "; cin >> diem;
        while (!checkDiem(diem)) {
            cout << "Điểm không hợp lệ, vui lòng nhập lại: "; cin >> diem;
        }
        hs[i].van = diem;
        cout << "--- Điểm ngoại ngữ: "; cin >> diem;
        while (!checkDiem(diem)) {
            cout << "Điểm không hợp lệ, vui lòng nhập lại: "; cin >> diem;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        hs[i].ngoaingu = diem;
        hs[i].diemTB = diemTrungBinh(hs[i].toan, hs[i].van, hs[i].ngoaingu);
        hs[i].hocLuc = phanLoaiHocSinh(hs[i]);
    }
}

/**
 * In thông tin học sinh.
 * @param hs Danh sách học sinh.
 * @param size Số lượng học sinh.
 */
void inHoTenDiemTBVaPhanLoad(vector<HocSinh> &hs, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Học sinh thứ " << i + 1 << ": \n";
        xuat(hs[i]);
    }
}

/**
 * In menu chức năng.
 */
void printMenu() {
    cout << "1. In điểm trung bình và phân loại học lực của học sinh.\n";
    cout << "2. Tìm học sinh có điểm trung bình cao nhất.\n";
    cout << "3. Tìm học sinh theo tên.\n";
    cout << "4. Danh sách học sinh có điểm toán thấp nhất.\n";
    cout << "5. Clear screen.\n";
    cout << "6. Thoát.\n";
}

/**
 * Hàm main là hàm chính thực hiện gọi các hàm cần thiết để quản lí học sinh. Các công việc chính:
 * - Nhập số lượng học sinh.
 * - Nhập thông tin học sinh.
 * - Hiển thị menu chương trình.
 * - Cho phép người dùng chọn chức năng.
 * - Tùy vào chức năng người dùng chọn, gọi hàm tương ứng.
 */
int main() {
    int n; cout << "Nhập số lượng học sinh: "; cin >> n;
    system("clear");
    vector<HocSinh> hs(n);
    nhap(hs, n);
    system("clear");
    cout << "Chương trình quản lí học sinh.\n";
    while (true) {
        printMenu();
        int choice; cout << ">> "; cin >> choice;
        cin.ignore();
        system("clear");
        if (choice == 1) {
            inHoTenDiemTBVaPhanLoad(hs, n);
        } else if (choice == 2) {
            HocSinh max = timHocSinhCoDiemTBCaoNhat(hs, n);
            cout << "Học sinh có điểm trung bình cao nhất: \n";
            xuat(max);
        } else if (choice == 3) {
            string name; cout << "Nhập tên cần tìm: "; cin.ignore(); getline(cin, name);
            vector<HocSinh> result = timHocSinhTheoTenRegex(hs, n, name);
            cout << "Kết quả tìm kiếm: \n";
            if (result.size() == 0) {
                cout << "--- Không tìm thấy học sinh nào.\n";
            }
            for (int i = 0; i < result.size(); i++) {
                xuat(result[i]);
            }
        } else if (choice == 4) {
            vector<HocSinh> result = danhSachHocSinhCoDiemToanThapNhat(hs, n);
            cout << "Danh sách học sinh có điểm toán thấp nhất: \n";
            for (int i = 0; i < result.size(); i++) {
                xuat(result[i]);
            }
        } else if (choice == 5) {
            system("clear");
        } else if (choice == 6) {
            cout << "Bye!\n";
            break;
        }
    }
}