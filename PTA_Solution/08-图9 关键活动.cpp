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
最后用key记录关键活动，只要一条边两点各自最早和最晚完工时间相等，则为关键路径
有两个算例不能AC，猜测是多出口。最晚完工时间的初始值应该设为全局最早完工时间，
因为那些早完成的出口可以等到全局完工再结束。

*/

#include <iostream>
#include <queue>
#include <stack>
using namespace std;
#define INF 9999999

int n, m, a, b, c;
int M[100][100];
int key[100][100];
stack<int> s[100];
int inDegree[100];
int outDegree[100];
int Earliest[100];
int Latest[100];

int main() {
	cin >> n >> m;
	fill (M[0], (M[0] + 100 * 100), INF);
	fill (key[0], (key[0] + 100 * 100), INF);
	fill (outDegree, outDegree + 100, 0);
	fill (Earliest, Earliest + 100, 0);
	fill (Latest, Latest + 100, INF);
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		M[b - 1][a - 1] = c;
		s[a - 1].push (b - 1);
	}
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
	while (!q.empty()) {
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
			Latest[i] = comtime;
		//Latest[i] = Earliest[i];
	}
	while (!p.empty()) {
		int v = p.front();
		p.pop();
		for (int w = 0; w < n; w++) {
			if (M[v][w] != INF) {
				if (Latest[v] - M[v][w] < Latest[w])
					Latest[w] = Latest[v] - M[v][w];
				if (--outDegree[w] == 0)
					p.push (w);
				if (Latest[v] == Earliest[v] && Latest[w] == Earliest[w])
					key[w][v] = 1;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		while (!s[i].empty()) {
			int v = s[i].top();
			s[i].pop();
			if (key[i][v] != INF)
				cout << i + 1 << "->" << v + 1 << endl;
		}
	}
	return 0;
}
