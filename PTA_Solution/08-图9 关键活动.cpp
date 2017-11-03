/*08-图9 关键活动
输入样例:
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2

输出样例:
17
1->2
2->4
4->6
6->7

关键活动，就是计算最早完工时间后，再逆拓扑排序计算最晚完工时间
最后记录关键活动

*/

#include <iostream>
#include <queue>
using namespace std;
#define INF 9999999

int n, m, a, b, c;
int M[100][100];
int InputOrder[100][100];
int inDegree[100];
int outDegree[100];
int Earliest[100];
int Latest[100];

int main() {
	cin >> n >> m;
	fill (M[0], (M[0] + 100 * 100), INF);
	fill (InputOrder[0], (InputOrder[0] + 100 * 100), INF);
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		M[b - 1][a - 1] = c;
		InputOrder[b - 1][a - 1] = i;
	}
	fill (Earliest, Earliest + 100, 0);
	fill (Latest, Latest + 100, INF);
	queue<int> q, p;
	int cnt = 0;
	int comtime = 0;
	for (int i = 0; i < n; i++) {
		inDegree[i] = 0;
		outDegree[i] = 0;
		for (int j = 0; j < n; j++) {
			if (M[i][j] != INF)
				inDegree[i]++;
			if (M[j][i] != INF)
				outDegree[i]++;
		}
		if (inDegree[i] == 0)
			q.push (i);
		if (outDegree[i] == 0)
			p.push (i);
	}
	while (!q.empty()) {			//最早完工时间
		int v = q.front();
		q.pop();
		cnt++;
		for (int w = 0; w < n; w++) {
			if (M[w][v] != INF) {
				if (Earliest[v] + M[w][v] > Earliest[w])
					Earliest[w] = Earliest[v] + M[w][v];
				if (Earliest[w] > comtime)
					comtime = Earliest[w];
				if (--inDegree[w] == 0)
					q.push (w);
			}
		}
	}
	if (cnt != n) {
		cout << 0;
		return 0;
	}
	cout << comtime << endl;
	for (int i = 0; i < n; i++) {
		if (outDegree[i] == 0)
			Latest[i] = Earliest[i];
	}
	while (!p.empty()) {			//最晚完工时间
		int v = p.front();
		p.pop();
		for (int w = 0; w < n; w++) {
			if (M[v][w] != INF) {
				if (Latest[v] - M[v][w] < Latest[w])
					Latest[w] = Latest[v] - M[v][w];
				if (--outDegree[w] == 0)
					p.push (w);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		inDegree[i] = 0;
		for (int j = 0; j < n; j++) {
			if (M[i][j] != INF)
				inDegree[i]++;
		}
		if (inDegree[i] == 0 && Latest[i] == Earliest[i])
			q.push (i);
	}
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		p.push (v);
		for (int w = 0; w < n; w++) {
			if (M[w][v] != INF && Earliest[w] == Latest[w])
				q.push (w);
		}
	}
	int a = p.front();
	p.pop();
	int b;
	while (!p.empty()) {
		b = p.front();
		p.pop();
		cout << a + 1  << "->" <<  b + 1 << endl;
		a = b;
	}
	return 0;
}
