#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int getM (int c1, int c2) {
    if (c2 > c1)
        c1 ^= c2 ^= c1 ^= c2;
    return c1 * (c1 + 1) / 2 + c2;
}
class Graphic {
  public:
    Graphic (int N) : nodeCount (N) {
        node.resize (N * (N + 1) / 2);
        visited.resize (N);
    }
    void cal_BFS (int k) {
        curr_count = 1;
        floor_count = 0;
        int last = k;
        int tail = k;
        visited[k] = 1;
        visitQ.push (k);
        while (visitQ.size() != 0) {
            int ss = visitQ.front();
            visitQ.pop();
            for (int j = 1; j < nodeCount; j++) {
                if (node[getM (j, ss)] && (!visited[j]) ) {
                    visited[j] = 1;
                    visitQ.push (j);
                    curr_count++;
                    tail = j;
                }
            }
            if (ss == last) {
                floor_count++; last = tail;
            }
            if (floor_count == 6)
                break;
        }
        visited.clear();
        visited.resize (nodeCount);
        queue<int> empty;
        visitQ.swap (empty);
    }

    int floor_count;
    int curr_count;
    queue<int> visitQ;
    vector<int> visited;
    vector<int> node;
    int nodeCount;
};


int main() {
    int N, M, c1, c2;
    cin >> N >> M;
    Graphic g (N + 1);
    for (int i = 0; i < M; i++) {
        cin >> c1 >> c2;
        g.node[getM (c1, c2)] = 1;
    }
    for (int i = 1; i < N + 1; i++) {
        g.cal_BFS (i);
        double percent = g.curr_count * 100.0 / (double) N;
        printf ("%d: %.2lf", i, percent);
        cout << '%' << endl;
    }
    return 0;
}