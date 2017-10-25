/*07-图4 哈利·波特的考试
输入样例:
6 11
3 4 70
1 2 1
5 4 50
2 6 50
5 6 60
1 3 70
4 6 60
3 6 80
5 1 100
2 4 60
5 2 80
输出样例:
4 70

要熟练运用Dijkstra算法
*/

#include <iostream>
#include <vector>
#define INF 99999
using namespace std;

int main() {
    int n, m, c1, c2, w;
    cin >> n >> m;
    n = n + 1;
    vector<vector<int> > M (n);
    vector<int> Spell (n);
    int MaxIndex = 0, MaxSpell = INF;
    for (int i = 1; i < n; i++)
        M[i].resize (n);
    for (int i = 0; i < m; i++) {
        cin >> c1 >> c2 >> w;
        M[c1][ c2] = w;
        M[c2][ c1] = w;
    }
    for (int i = 1; i < n; i++) {
        vector<int> collected (n);
        vector<int> dist (n, INF);
        vector<int> path (n, -1);
        dist[i] = 0;
        int count = 0;
        while (1) {
            int j  = -1;
            int MaxDist = INF;
            for (int r = 1; r < n; r++) {
                if (collected[r] == false && dist[r] < MaxDist) {
                    j = r;
                    MaxDist = dist[r];
                }
            }
            if (j == -1)
                break;
            count++;
            collected[j] = true;
            for (int k = 1; k < n; k++) {
                if (collected[k] == false && M[j][ k] > 0 && (dist[j] + M[j][ k]) < dist[k]) {
                    dist[k] = dist[j] + M[j][ k];
                    path[k] = j;
                }
            }
        }
        if (count < n - 1) {
            cout << '0';
            return 0;
        }
        for (int j = 1; j < n; j++) {
            if (dist[j] > Spell[i]) {
                MaxIndex = j;
                Spell[i] = dist[j];
            }
        }
    }
    for (int i = 1; i < n; i++) {
        if (Spell[i] < MaxSpell) {
            MaxIndex = i;
            MaxSpell = Spell[i];
        }
    }
    cout << MaxIndex  << ' ' << MaxSpell;
    return 0;
}