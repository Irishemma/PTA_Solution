/*
02-线性结构2 一元多项式的乘法与加法运算

开二维数组，按照公式对两个多项式进行相加相乘，比较消耗空间？

看了网上其他人的例子，只存第一个多项式，在读第二个多项式时在线处理，空间省一些。

至于何老师讲的链表存储就算了，为了省空间还挺麻烦的，看了一遍不尝试了。

*/

#include <iostream>
using namespace std;
#define N 2001

void cal (int a[][2], int b[][2], int power1, int power2) {
    int t[N] = { 0 }, p[N] = { 0 };
    for (int i = 0; i < power1; i++) {
        for (int j = 0; j < power2; j++) {
            int aa = a[i][0] * b[j][0];
            int pp = a[i][1] + b[j][1];
            t[pp] += aa;
        }
    }
    bool flag = false;
    for (int i = N - 1; i >= 0; i--) {
        if (t[i] != 0) {
            if (flag)
                cout << ' ';
            flag = true;
            cout << t[i] << ' ' << i;
        }
    }
    if (!flag)
        cout << "0 0";
    cout << endl;
    for (int i = 0; i < power1; i++) {
        int pp = a[i][1];
        p[pp] += a[i][0];
    }
    for (int i = 0; i < power2; i++) {
        int pp = b[i][1];
        p[pp] += b[i][0];
    }
    flag = false;
    for (int i = N - 1; i >= 0; i--) {
        if (p[i] != 0) {
            if (flag)
                cout << ' ';
            flag = true;
            cout << p[i] << ' ' << i;
        }
    }
    if (!flag)
        cout << "0 0";
    cout << endl;
}

int main() {
    int power1, power2;
    int a[N][2], b[N][2];
    cin >> power1;
    for (int i = 0; i < power1; i++)
        cin >> a[i][0] >> a[i][1];
    cin >> power2;
    for (int i = 0; i < power2; i++)
        cin >> b[i][0] >> b[i][1];
    cal (a, b, power1, power2);
    return 0;
}
