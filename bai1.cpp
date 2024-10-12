#include <iostream>
using namespace std;

/**
 * Hàm tìm ước chung lớn nhất của 2 số
 * @param a số nguyên
 * @param b số nguyên
 * @return ước chung lớn nhất của a và b, sử dụng đệ quy
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
 * Hàm main làm các công việc sau:
 * - Nhập phân số
 * - Kiểm tra mẫu số khác 0
 * - Rút gọn phân số
 * - In ra phân số sau khi rút gọn
 */
int main() {
    
    int a, b; 
    while (true) {
        cout << "Nhập phân số: ";
        cin >> a >> b;
        if (b != 0) break;
        cout << "Mẫu số phải khác 0\n";
    }
    PhanSo ps = {a, b};
    cout << "Phân số sau khi rút gọn: ";
    print(rutGon(ps));
}