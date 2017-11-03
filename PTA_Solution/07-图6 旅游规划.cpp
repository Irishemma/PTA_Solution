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
		dm[i].resize (n);
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
		for (int i = 0; i < n; i++) {
			if (!collected[i] && dist[i] < minDist) {
				minDist = dist[i];
				v = i;
			}
		}
	}
	return 0;
}