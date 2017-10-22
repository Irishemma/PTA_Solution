/*06-图3 六度空间
输入样例:
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
输出样例:
1: 70.00%
2: 80.00%
3: 90.00%
4: 100.00%
5: 100.00%
6: 100.00%
7: 100.00%
8: 90.00%
9: 80.00%
10: 70.00%

要掌握last，tail，floor更新的时间：
1. push完根节点的所有节点后，last还等于根节点，此时更新last，并加一层
2.	  pop到最后一个子节点并push孙节点后，发现last==i，此时继续更新last
3.		queue<int>().swap(q)清空队列
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int p (int c1, int c2) {
    if (c1 < c2)
        c1 ^= c2 ^= c1 ^= c2;
    return c1 * (c1 + 1) / 2 + c2;
}
int main() {
    int n, m, c1, c2;
    cin >> n >> m;
    n = n + 1;
    vector<int> M (n * (n + 1) / 2);
    queue<int> q;
    vector<int> visited (n);
    for (int i = 0; i < m; i++) {
        cin >> c1 >> c2;
        M[p (c1, c2)] = 1;
    }
    //BFS
    int count, last, floor, tail;
    for (int i = 1; i < n; i++) {
        visited.clear();
        visited.resize (n);
        queue<int>().swap (q);
        q.push (i);
        visited[i] = 1;
        count = floor = 0;
        last = i;
        while (!q.empty() ) {
            int j = q.front();
            q.pop();
            for (int k = 1; k < n; k++) {
                if (!visited[k] && M[p (j, k)]) {
                    q.push (k);
                    visited[k] = 1;
                    tail = k;
                    count++;
                }
            }
            if (last == j) {
                floor++; last = tail;
            }
            if (floor == 6)
                break;
        }
        printf ("%d: %0.2lf%%\n", i, (count + 1.0) * 100 / (n - 1.0) );
    }
    return 0;
}