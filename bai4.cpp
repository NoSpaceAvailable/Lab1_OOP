#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/**
 * Hàm tính giai thừa bằng vòng lặp
 * @param n số nguyên
 * @return giai thừa của n
 */
double factorial(int n) {
    double res = 1;
    for (int i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

/**
 * Hàm main làm các công việc sau:
 * - Nhập số thực x
 * - Tính sin(x) bằng chuỗi Taylor
 * - In ra kết quả, độ chính xác đến 5 chữ số thập phân
 */
int main() {
    double res = 0;
    cout << "Nhập x: ";
    double x; cin >> x;
    double orig = x;
    bool isNegative = (x < 0);
    x = fmod(abs(x), 2 * M_PI);     // đưa x về khoảng [0, 2 * pi]
    double tmp = 1.0;

    for (int i = 0; i < 100; ++i) {
        tmp = pow(abs(x), 2 * i + 1) / factorial(2 * i + 1);
        if (tmp < 0.00001) break;
        if (i % 2 == 0) res += tmp;
        else res -= tmp;
    }
    cout << fixed << setprecision(5);
    cout << "sin(" << orig << ") = " << (isNegative ? -res : res) << '\n';
}
