/*07-图6 旅游规划
输入样例:
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
输出样例:
3 40

简单的Dijkstra算法可以解决，判断路径最短之后，再多加个花费判断即可。

*/
#include <iostream>
#include <vector>
#define INF 99999
using namespace std;

int main() {
	int n, m, s, d, c1, c2, disti, costi;
	cin >> n >> m >> s >> d;
	vector<int> dist (n, INF);
	vector<int> path (n, INF);
	vector<int> cost (n, INF);
	vector<int> collected (n);
	vector< vector<int> > dm (n);
	vector< vector<int> > cm (n);
	for (int i = 0; i < n; i++) {
		dm[i].resize (n, INF);
		cm[i].resize (n);
	}
	for (int i = 0; i < m; i++) {
		cin >> c1 >> c2 >> disti >> costi;
		dm[c1][c2] = disti;
		dm[c2][c1] = disti;
		cm[c1][c2] = costi;
		cm[c2][c1] = costi;
	}
	dist[s] = 0;
	cost[s] = 0;
	while (1) {
		int minDist = INF;
		int v = 0;
		for (int w = 0; w < n; w++) {
			if (!collected[w] && dist[w] < minDist) {
				minDist = dist[w];
				v = w;
			}
		}
		if (v == d) {
			break;
		}
		collected[v] = true;
		for (int w = 0; w < n; w++) {
			if (!collected[w])
				if ((dist[v] + dm[v][w] < dist[w]) ||
				        (dist[v] + dm[v][w] == dist[w] && cost[v] + cm[v][w] < cost[w])) {
					dist[w] = dist[v] + dm[v][w];
					cost[w] = cost[v] + cm[v][w];
					path[w] = v;
				}
		}
	}
	cout << dist[d] << ' ' << cost[d];
	return 0;
}