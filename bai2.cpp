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
 * Hàm kiểm tra mẫu số khác 0
 * @param a mẫu số cần kiểm tra
 * @return true nếu mẫu số khác 0, ngược lại false
 */
bool checkValid(int a) {
    return !(a == 0);
}

/**
 * Hàm kiểm tra xem phân số a có lớn hơn phân số b không
 * @param a phân số 1
 * @param b phân số 2
 * @return true nếu a > b, ngược lại false
 */
bool gt(PhanSo a, PhanSo b){
    return a.tuSo * b.mauSo > b.tuSo * a.mauSo;
}

/**
 * Hàm kiểm tra xem phân số a có bằng phân số b không
 * @param a phân số 1
 * @param b phân số 2
 * @return true nếu a = b, ngược lại false
 */
bool eq(PhanSo a, PhanSo b){
    return a.tuSo * b.mauSo == b.tuSo * a.mauSo;
}

/**
 * Hàm main làm các công việc sau:
 * - Nhập phân số 1
 * - Kiểm tra mẫu số khác 0
 * - Rút gọn phân số 1
 * - Nhập phân số 2
 * - Kiểm tra mẫu số khác 0
 * - Rút gọn phân số 2
 * - So sánh 2 phân số và in ra phân số lớn nhất. Nếu bằng nhau thì in ra "Equal!"
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
    ps1 = rutGon(ps1);
    cout << "Phân số 2: ";
    cin >> a >> b;
        if (!checkValid(b)) {
        cout << "Mẫu số phải khác 0\n";
        return 0;
    }
    PhanSo ps2 = {a, b};
    ps2 = rutGon(ps2);
    if (gt(ps1, ps2)) {
        cout << "Max: ";
        print(ps1);
    } else if (eq(ps1, ps2)) {
        cout << "Equal!\n";
    } else {
        cout << "Max: ";
        print(ps2);
    }
}