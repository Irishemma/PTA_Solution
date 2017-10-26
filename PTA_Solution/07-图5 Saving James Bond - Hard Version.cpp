/* 07 - 图5 Saving James Bond - Hard Version
Sample Input 1:
17 15
10 -21
10 21
-40 10
30 -50
20 40
35 10
0 -10
-25 22
40 -40
-30 30
-10 22
0 11
25 21
25 10
10 10
10 35
-30 10
Sample Output 1:
4
0 11
10 21
10 35

最短路问题不能用DFS，只能用BFS
1. 第一跳就滤掉那些跳不到以及在岛上的点
2. 一步上岸也处理掉
3. 最短路数相同时，以第一跳最短为准
4. 把边框也看成一个节点
*/
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#define INF 99999
using namespace std;
struct cro {
    int x; int y;
};
int pos (int c1, int c2) {
    if (c1 < c2)
        c1 ^= c2 ^= c1 ^= c2;
    return c1 * (c1 + 1) / 2 + c2;
}
int main() {
    int n, D, x, y;
    cin >> n >> D;
    n = n + 1;
    vector<int> M (n * (n + 1) / 2);
    vector<cro> cros (n - 1);
    for (int k = 0; k < n - 1; k++) {
        cin >> x >> y;
        cros[k].x = x; cros[k].y = y;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            if ( (cros[i].x - cros[j].x) * (cros[i].x - cros[j].x) +
                    (cros[i].y - cros[j].y) * (cros[i].y - cros[j].y) <= D * D)
                M[pos (i, j)] = 1;
        }
        if (abs (cros[i].x) >= 50 - D || abs (cros[i].y) >= 50 - D)
            M[pos (i, n - 1)] = 1;
    }
    int steps = INF; vector<int> route;
    for (int i = 0; i < n - 1; i++) {
        vector<int> dist (n, INF);
        vector<int> path (n, -1);
        queue<int> q;
        if ( ( (cros[i].x * cros[i].x + cros[i].y * cros[i].y) > (D + 7.5) * (D + 7.5) ) ||
                (cros[i].x * cros[i].x + cros[i].y * cros[i].y) <= 7.5 * 7.5)
            continue;
        if (abs (cros[i].x) >= 50 - D || abs (cros[i].y) >= 50 - D) {
            cout << "1";
            return 0;
        }
        dist[i] = 1;
        q.push (i);
        while (!q.empty() ) {
            int j = q.front();
            q.pop();
            if (j == n - 1)
                break;
            for (int k = 0; k < n; k++) {
                if (M[pos (j, k)] && dist[k] == INF) {
                    dist[k] = dist[j] + 1;
                    path[k] = j;
                    q.push (k);
                }
            }
        }
        if (dist[n - 1] > steps || dist[n - 1] == INF)
            continue;
        if (!route.empty() ) {
            cro  a = cros[route[0]];
            cro  b = cros[i];
            if (b.x * b.x + b.y * b.y >= a.x * a.x + a.y * a.y)
                continue;
        }
        steps = dist[n - 1];
        stack<int> s;
        int tmp = path[n - 1];
        vector<int>().swap (route);
        while (tmp != i) {
            s.push (tmp);
            tmp = path[tmp];
        }
        route.push_back (i);
        while (!s.empty() ) {
            route.push_back (s.top() );
            s.pop();
        }
    }
    if (steps == INF)
        cout << "0";
    else {
        cout << steps << endl;
        for (int i = 0; i < route.size(); i++) {
            cout << cros[route[i]].x << ' '
                 << cros[route[i]].y << endl;
        }
    }
    return 0;
}