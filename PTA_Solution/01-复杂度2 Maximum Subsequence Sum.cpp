/*
01-复杂度2 Maximum Subsequence Sum

和上一题类似，注意最大和子列的头尾如何保存。

*/

#include <iostream>
using namespace std;

#define N 100001
int main() {
    int num;
    int a[N];
    int ThisSum, MaxSum, na, nb;
    int tempIndex = 0;
    bool allNegtive = true;
    ThisSum = MaxSum = 0;
    cin >> num;
    for (int i = 0; i < num; i++) {
        cin >> a[i];
        if (a[i] >= 0 && allNegtive) {
            allNegtive = false;
            na = nb = a[i];
        }
        ThisSum += a[i];
        if (ThisSum > MaxSum) {
            MaxSum = ThisSum;
            nb = a[i];
            na = a[tempIndex];
        } else if (ThisSum < 0) {
            tempIndex = i + 1;
            ThisSum = 0;
        }
    }
    if (!MaxSum)
        if (allNegtive) {
            na = a[0]; nb = a[num - 1];
        } else
            na = nb = 0;
    cout << MaxSum << ' ';
    cout << na << ' ' << nb;
    return 0;
}