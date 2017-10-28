/*
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1

考查最短路径数目、附加评价标准（点权和最大）
发现最短路时（一条），distC[w] = distC[v]
追加最短路数目时，distC[w] += distC[v]
路长更新（或相同），点权和更大时，profC[w] = profC[v] + prof[w]

*/
#include <iostream>
#include <vector>
#define INF 99999
using namespace std;

int main() {
	int n, m, s, d, c1, c2, l;
	cin >> n >> m >> s >> d;
	vector<int> dist (n, INF);
	vector<int> distCount (n);
	vector<int> collected (n);
	vector<int> prof (n);
	vector<int> profCount (n);
	vector< vector<int> > M (n);
	for (int i = 0; i < n; i++) {
		M[i].resize (n, INF);
	}
	for (int i = 0; i < n; i++) {
		cin >> c1;
		prof[i] = c1;
	}
	for (int i = 0; i < m; i++) {
		cin >> c1 >> c2 >> l;
		M[c1][c2] = l;
		M[c2][c1] = l;
	}
	dist[s] = 0;
	distCount[s] = 1;
	profCount[s] = prof[s];
	while (1) {
		int v = 0;
		int minDist = INF;
		for (int i = 0; i < n; i++) {
			if (!collected[i] && dist[i] < minDist) {
				minDist = dist[i];
				v = i;
			}
		}
		if (v == d) {
			break;
		}
		collected[v] = true;
		for (int w = 0; w < n; w++) {
			if (!collected[w] && M[v][w] != INF) {
				if (dist[v] + M[v][w] < dist[w]) {
					dist[w] = dist[v] + M[v][w];
					distCount[w] = distCount[v];
					profCount[w] = profCount[v] + prof[w];
				} else if (dist[v] + M[v][w] == dist[w]) {
					distCount[w] += distCount[v];
					if (profCount[v] + prof[w] > profCount[w]) {
						profCount[w] = profCount[v] + prof[w];
					}
				}
			}
		}
	}
	cout << distCount[d] << ' ' << profCount[d];
	return 0;
}