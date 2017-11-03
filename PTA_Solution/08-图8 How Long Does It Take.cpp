/*08-图8 How Long Does It Take
Sample Input 1:
9 12
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
5 4 0
4 6 9
4 7 7
5 7 4
6 8 2
7 8 4
Sample Output 1:
18

Sample Input 2:
4 5
0 1 1
0 2 2
2 1 3
1 3 4
3 2 5
Sample Output 2:
Impossible

关键路径，其实就是拓扑排序加上一个最早完工时间Earliest

*/

#include <iostream>
#include <queue>
using namespace std;
#define INF 9999999

int n, m, a, b, c;
int M[100][100];
int inDegree[100];
int Earliest[100];

int main() {
	cin >> n >> m;
	fill (M[0], (M[0] + 100 * 100), INF);
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		M[a][b] = c;
	}
	fill (Earliest, Earliest + 100, 0);
	queue<int> q;
	int cnt = 0;
	int comtime = 0;
	for (int i = 0; i < n; i++) {
		inDegree[i] = 0;
		for (int j = 0; j < n; j++) {
			if (M[j][i] != INF)
				inDegree[i]++;
		}
		if (inDegree[i] == 0)
			q.push (i);
	}
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		cnt++;
		for (int w = 0; w < n; w++) {
			if (M[v][w] != INF) {
				if (Earliest[v] + M[v][w] > Earliest[w])
					Earliest[w] = Earliest[v] + M[v][w];
				if (Earliest[w] > comtime)
					comtime = Earliest[w];
				if (--inDegree[w] == 0)
					q.push (w);
			}
		}
	}
	if (cnt != n)
		cout << "Impossible";
	else {
		int comtime = 0;
		for (int i = 0; i < n; i++) {
			if (Earliest[i] > comtime)
				comtime = Earliest[i];
		}
		cout << comtime;
	}
	return 0;
}
