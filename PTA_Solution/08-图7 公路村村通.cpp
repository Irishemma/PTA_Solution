/*08-图7 公路村村通
输入样例:
6 15
1 2 5
1 3 3
1 4 7
1 5 4
1 6 2
2 3 4
2 4 6
2 5 2
2 6 6
3 4 6
3 5 1
3 6 1
4 5 10
4 6 8
5 6 3
输出样例:
12

Prim算法基本应用

*/


#include <iostream>
#include <vector>
#define INF 999999
using namespace std;

int n, m;
int main() {
	cin >> n >> m ;
	int c1, c2, road;
	vector<vector<int> > len (n);
	for (int i = 0; i < n; i++)
		len[i].resize (n, INF);
	for (int i = 0; i <  m; i++) {
		cin >> c1 >> c2 >> road;
		len[c1 - 1][c2 - 1] = road;
		len[c2 - 1][c1 - 1] = road;
	}
	vector<int> dist (n);
	for (int i = 0; i < n; i++)
		dist[i] = len[0][i];
	vector<int> parent (n, 0);
	int TotalWeight = 0;
	int VCount = 0;
	dist[0] = 0;
	VCount++;
	parent[0] = -1;
	while (1) {
		int minDist = INF;
		int v = -1;
		for (int i = 0; i < n; i++) {
			if (dist[i] != 0 && dist[i] < minDist) {
				minDist = dist[i];
				v = i;
			}
		}
		if (v == -1)
			break;
		TotalWeight += dist[v];
		dist[v] = 0;
		VCount++;
		for (int w = 0; w < n; w++) {
			if (dist[w] != 0 && len[v][w] < INF && len[v][w] < dist[w]) {
				dist[w] = len[v][w];
				parent[w] = v;
			}
		}
	}
	if (VCount < n)
		cout << -1;
	else
		cout << TotalWeight;
	return 0;
}