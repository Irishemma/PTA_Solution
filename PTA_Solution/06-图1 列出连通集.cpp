/*06-图1 列出连通集
输入样例:
8 6
0 7
0 1
2 0
4 1
2 4
3 5

输出样例:
{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }

基础的DFS，BFS操作
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int pos (int c1, int c2) {
    if (c1 < c2)
        c1 ^= c2 ^= c1 ^= c2;
    return c1 * (c1 + 1) / 2 + c2;
}
void DFS (int i, vector<int> & M, vector<int> & visited) {
    visited[i] = true;
    cout << i << ' ';
    for (int j = 0; j < visited.size(); j++) {
        if (M[pos (i, j)] && !visited[j])
            DFS (j, M, visited);
    }
}
int main() {
    int n, m, c1, c2;
    cin >> n >> m;
    vector<int> M (n * (n + 1) / 2);
    vector<int> visited (n);
    queue<int> q;
    for (int k = 0; k < m; k++) {
        cin >> c1 >> c2;
        M[pos (c1, c2)] = 1;
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cout << "{ ";
            DFS (i, M, visited);
            cout << "}\n";
        }
    }
    //BFS
    visited.clear();
    visited.resize (n);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cout << "{ ";
            q.push (i);
            visited[i] = true;
            while (!q.empty() ) {
                int f = q.front();
                q.pop();
                cout << f << ' ' ;
                for (int j = 0; j < f; j++) {
                    if (M[pos (f, j)] && !visited[j]) {
                        q.push (j);
                        visited[j] = true;
                    }
                }
                for (int j = f + 1; j < n; j++) {
                    if (M[pos (f, j)] && !visited[j]) {
                        q.push (j);
                        visited[j] = true;
                    }
                }
            }
            cout << "}\n";
        }
    }
    return 0;
}
