#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int getM (int c1, int c2) {
    if (c2 > c1) {
        c2 ^= c1 ^= c2;
        c1 ^= c2;
    }
    return c1 * (c1 + 1) / 2 + c2;
}
class Graphic {
  public:
    Graphic (int N) : nodeCount (N) {
        node.resize (N * (N + 1) / 2);
        visited.resize (N);
    }
    void visitN_DFS (int k) {
		visited[k] = 1;
        cout << k << ' ';
        for (int j = 0; j < nodeCount; j++)
            if (node[getM (j, k)] && (!visited[j]) ) {
                visited[j] = 1;
                visitN_DFS (j);
            }
    }
    void visitN_BFS (int k) {
		visited[k] = 1;
        cout << k << ' ';
        for (int j = 0; j < nodeCount; j++) {
            if (node[getM (j, k)] && (!visited[j]) ) {
                visited[j] = 1;
                visitQ.push (j);
            }
        }
        while (visitQ.size() != 0) {
            int ss = visitQ.front();
            visitQ.pop();
            visitN_BFS (ss );
        }
    }

    queue<int> visitQ;
    vector<int> visited;
    vector<int> node;
    int nodeCount;
};


int main() {
    int N, E, c1, c2;
    cin >> N >> E;
    Graphic g (N);
    for (int i = 0; i < E; i++) {
        cin >> c1 >> c2;
        g.node[getM (c1, c2)] = 1;
    }
    for (int i = 0; i < N; i++) {
        if (!g.visited[i]) {
            cout << "{ ";
            g.visitN_DFS (i);
            cout << "}" << endl;
        }
    }
    g.visited.clear();
    g.visited.resize (N);
    for (int i = 0; i < N; i++) {
        if (!g.visited[i]) {
            cout << "{ ";
            g.visitN_BFS (i);
            cout << "}" << endl;
        }
    }
    return 0;
}