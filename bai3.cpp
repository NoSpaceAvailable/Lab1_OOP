#include <iostream>
using namespace std;

/**
 * Hàm tìm ước chung lớn nhất của 2 số
 * @param a số nguyên
 * @param b số nguyên
 * @return ước chung lớn nhất của a và b, sử dụng đệ quy, giải thuật Euclid
 */
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

struct PhanSo {
    int tuSo, mauSo;
};

/**
 * Hàm rút gọn phân số
 * @param a phân số cần rút gọn
 * @return phân số sau khi rút gọn
 */
PhanSo rutGon(PhanSo a) {
    int ucln = gcd(a.tuSo, a.mauSo);
    int newTS = a.tuSo / ucln;
    int newMS = a.mauSo / ucln;
    return PhanSo{newTS, newMS};
}

/**
 * Hàm in ra phân số
 * @param ps phân số cần in
 */
void print(PhanSo ps) {
    if (ps.tuSo == 0) {
        cout << 0 << '\n';
        return;
    } else if (ps.mauSo < 0) {
        cout << ps.tuSo * -1 << '/' << ps.mauSo * -1 << '\n';
    } else if (ps.tuSo % ps.mauSo == 0) {
        if (ps.mauSo < 0) {
            cout << ps.tuSo * (-1) / ps.mauSo << '\n';
            return;
        } else {
            cout << ps.tuSo / ps.mauSo << '\n';
        }
    } else {
        cout << ps.tuSo << '/' << ps.mauSo << '\n';
    }
}

/**
 * Hàm kiểm tra mẫu số khác 0
 * @param a mẫu số cần kiểm tra
 * @return true nếu mẫu số khác 0, ngược lại false
 */
bool checkValid(int a) {
    return !(a == 0);
}

/**
 * Hàm tính tổng 2 phân số
 * @param a phân số thứ nhất
 * @param b phân số thứ hai
 * @return phân số tổng của a và b, đã rút gọn
 */
PhanSo tong(PhanSo a, PhanSo b) {
    return rutGon(PhanSo {a.tuSo * b.mauSo + a.mauSo * b.tuSo, a.mauSo * b.mauSo});
}

/**
 * Hàm tính hiệu 2 phân số
 * @param a phân số thứ nhất
 * @param b phân số thứ hai
 * @return phân số hiệu của a và b, đã rút gọn
 */
PhanSo hieu(PhanSo a, PhanSo b) {
    return rutGon(PhanSo {a.tuSo * b.mauSo - a.mauSo * b.tuSo, a.mauSo * b.mauSo});
}

/**
 * Hàm tính tích 2 phân số
 * @param a phân số thứ nhất
 * @param b phân số thứ hai
 * @return phân số tích của a và b, đã rút gọn
 */
PhanSo tich(PhanSo a, PhanSo b) {
    return rutGon(PhanSo {a.tuSo * b.tuSo, a.mauSo * b.mauSo});
}

/**
 * Hàm tính thương 2 phân số
 * @param a phân số thứ nhất
 * @param b phân số thứ hai
 * @return phân số thương của a và b, đã rút gọn
 */
PhanSo thuong(PhanSo a, PhanSo b) {
    if (rutGon(b).tuSo == 0) {
        cout << "Can't divide a to b because b is equal to ";
        return PhanSo {0, 1};
    }
    return rutGon(PhanSo {a.tuSo * b.mauSo, a.mauSo * b.tuSo});
}

/** 
 * Hàm main làm các công việc sau:
 * - Nhập 2 phân số
 * - Kiểm tra mẫu số khác 0
 * - Tính tổng, hiệu, tích, thương 2 phân số
 * - In ra kết quả
 */
int main() {
    int a, b;
    cout << "Phân số 1: ";
    cin >> a >> b;
    if (!checkValid(b)) {
        cout << "Mẫu số phải khác 0\n";
        return 0;
    }
    PhanSo ps1 = {a, b};
    cout << "Phân số 2: ";
    cin >> a >> b;
        if (!checkValid(b)) {
        cout << "Mẫu số phải khác 0\n";
        return 0;
    }
    PhanSo ps2 = {a, b};

    cout << "Tổng: "; print(tong(ps1, ps2));
    cout << "Hiệu: "; print(hieu(ps1, ps2));
    cout << "Tích: "; print(tich(ps1, ps2));
    cout << "Thương: "; print(thuong(ps1, ps2));
}