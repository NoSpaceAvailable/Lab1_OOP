#include <vector>
#include <iostream>
using namespace std;

int a, b;

/**
 * @brief Hàm computeLPSArray nhằm mục đích tính toán mảng LPS (Longest Prefix Suffix) cho một mảng đầu vào A. 
 * @brief Mảng LPS này được sử dụng trong thuật toán KMP (Knuth-Morris-Pratt) để tìm kiếm chuỗi con, giúp tránh việc lặp lại các phép so sánh không cần thiết. 
 * @brief Cụ thể, mảng LPS tại mỗi vị trí i lưu trữ độ dài của tiền tố dài nhất của chuỗi con kết thúc tại i mà cũng là hậu tố của chuỗi con đó. 
 * @brief Điều này giúp thuật toán KMP có thể bỏ qua một số phép so sánh khi tìm kiếm chuỗi con trong chuỗi lớn hơn.
 * @param A vector đầu vào
 * @return vector LPS
 */
vector<int> computeLPSArray(const vector<int>& A) {
    int len = 0;
    int i = 1;
    vector<int> lps(a, 0);

    while (i < a) {
        if (A[i] == A[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

/**
 * @brief Hàm KMPSearch thực hiện việc tìm kiếm mảng con A trong chuỗi lớn hơn B.
 * @brief Bởi vì thực chất một chuỗi cũng là một mảng, nên thuật toán này cũng có 
 * @brief thể áp dụng cho mảng hoặc các object có dạng mảng như vector.
 * @param A vector con cần tìm kiếm
 * @param B vector lớn hơn
 * @return vector chứa các vị trí xuất hiện của vector con A vector mảng B
 * @note Độ phức tạp thời gian: O(a + b)
 */
vector<int> KMPSearch(const vector<int>& A, const vector<int>& B) {
    vector<int> res;

    vector<int> lps = computeLPSArray(A);
    int i = 0, j = 0; 

    while (j < b) {
        if (A[i] == B[j]) {
            i++;
            j++;

            if (i == a) {
                res.push_back(j - i);
                i = lps[i - 1];
            }   
        }
        else {
            if (i != 0) {
                i = lps[i - 1];
            } else {
                j++;
            }
        }
    }

    return res;
}

/**
 * Hàm main là hàm chính thực hiện gọi các hàm cần thiết để tìm kiếm mảng con A trong mảng B.
 * - Đầu tiên nhập độ dài của mảng A và B.
 * - Tiếp theo nhập các phần tử của mảng A và B.
 * - Gọi hàm KMPSearch để tìm kiếm mảng con A trong mảng B.
 * - In ra số lần xuất hiện và các vị trí xuất hiện của mảng con A trong mảng B.
 */
int main() {
    cout << "Nhập độ dài mảng A và B: ";
    cin >> a >> b;

    vector<int> A(a + 1), B(b + 1);
    cout << "Nhập mảng A: ";
    for (int i = 0; i < a; ++i) {
        cin >> A[i];
    }

    cout << "Nhập mảng B: ";
    for (int i = 0; i < b; ++i) {
        cin >> B[i];
    }

    vector<int> res = KMPSearch(A, B);

    cout << "Số lần xuất hiện mảng con: " << res.size() << '\n';
    cout << "Các index: ";
    for (int pos : res) {
        cout << pos << " ";
    }
    cout << '\n';
}