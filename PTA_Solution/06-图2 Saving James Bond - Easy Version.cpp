/*06-ͼ2 Saving James Bond - Easy Version
Sample Input 1:
14 20
25 -15
-25 28
8 49
29 15
-35 -2
5 28
27 -29
-8 -28
-20 -35
-25 -20
-13 29
-30 15
-35 40
12 12
Sample Output 1:
Yes

把边框也看成一个节点，DFS

*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct cro {
    int x; int y;
};
int pos (int c1, int c2) {
    if (c1 < c2)
        c1 ^= c2 ^= c1 ^= c2;
    return c1 * (c1 + 1) / 2 + c2;
}
bool DFS (int i, vector<int> & M, vector<int> & visited) {
    visited[i] = true;
    if (i == visited.size() - 1)
        return true;
    for (int j = 0; j < visited.size(); j++) {
        if (M[pos (i, j)] && !visited[j])
            if (DFS (j, M, visited))
                return true;
    }
    return false;
}
int main() {
    int n, D, x, y;
    cin >> n >> D;
    n = n + 1;
    vector<int> M (n * (n + 1) / 2);
    vector<int> visited (n);
    vector<cro *> cros (n - 1);
    for (int k = 0; k < n - 1; k++) {
        cin >> x >> y;
        cros[k] = new cro;
        cros[k]->x = x; cros[k]->y = y;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            if ( (cros[i]->x - cros[j]->x) * (cros[i]->x - cros[j]->x) +
                    (cros[i]->y - cros[j]->y) * (cros[i]->y - cros[j]->y) <= D * D)
                M[pos (i, j)] = 1;
        }
        if (abs (cros[i]->x) >= 50 - D || abs (cros[i]->y) >= 50 - D)
            M[pos (i, n - 1 )] = 1;
    }
    bool find = false;
    for (int i = 0; i < n - 1; i++) {
        if ( (cros[i]->x * cros[i]->x + cros[i]->y * cros[i]->y) > (D + 7.5) * (D + 7.5) )
            continue;
        visited.clear();
        visited.resize (n);
        find = DFS (i, M, visited);
        if (find)
            break;
    }
    if (find)
        cout << "Yes";
    else
        cout << "No";
    return 0;
}