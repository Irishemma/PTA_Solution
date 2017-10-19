/* 05-树7 堆中的路径
输入样例:
5 3
46 23 26 24 10
5 4 3

输出样例:
24 23 10
46 23 10
26 10

建堆，要清楚入堆的流程。

*/
#include<iostream>
#include<vector>
using namespace std;
#define N -10001
struct Heap {
    Heap (int n) : cap (n) { size = 0; v.resize (n + 1); v[0] = N; }
    void insert (int num) {
        int child = ++size;
        for (; v[child / 2] > num ; child /= 2)
            v[child] = v[child / 2];
        v[child] = num;
    }
    void out (int i) {
        bool flag = true;
        for (int j = i; j >= 1; j /= 2) {
            if (!flag)
                cout << ' ';
            if (flag)
                flag = false;
            cout << v[j];
        }
    }
    int size;
    int cap;
    vector<int> v;
};
int main() {
    int n, m, num;
    cin >> n >> m;
    Heap h (n);
    for (int i = 0; i < n; i++) {
        cin >> num;
        h.insert (num);
    }
    for (int i = 0; i < m; i++) {
        cin >> num;
        h.out (num);
        cout << endl;
    }
    return 0;
}