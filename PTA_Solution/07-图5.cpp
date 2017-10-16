#include <iostream>
#include <vector>
using namespace std;

struct Point {
	int x;
	int y;
};
int getM(int c1, int c2) {
	if (c2 > c1)
		c1 ^= c2 ^= c1 ^= c2;
	return c1 * (c1 + 1) / 2 + c2;
}
class Graphic {
public:
	Graphic(int N) : nodeCount(N) {
		node.resize(N * (N + 1) / 2);
		visited.resize(N);
		point.resize(N);
	}
	bool visitN_DFS(int k) {
		if (node[getM(k, nodeCount - 1)])
			return true;
		visited[k] = 1;
		for (int j = 1; j < nodeCount - 1; j++)
			if (node[getM(j, k)] && (!visited[j])) {
				if (visitN_DFS(j))
					return true;
			}
		return false;
	}
	vector<Point> point;
	vector<int> visited;
	vector<int> node;
	int nodeCount;
};

int main() {
	int N, D, x, y;
	cin >> N >> D;
	Graphic g(N + 2);
	for (int i = 1; i < N + 1; i++) {
		cin >> x >> y;
		g.point[i].x = x;
		g.point[i].y = y;
	}
	int an = 50 - D;
	for (int i = 1; i < N + 1; i++) {
		Point p = g.point[i];
		//   if ( (p.x * p.x + p.y * p.y) <= (D + 7.5) * (D + 7.5 ) )
		//        g.node[getM (i, 0)] = 1;
		if (p.x >= an || p.x <= (-an) || p.y >= an || p.y <= (-an))
			g.node[getM(i, N + 1)] = 1;
		for (int j = i + 1; j < N + 1; j++) {
			Point pt = g.point[j];
			if ((p.x - pt.x) * (p.x - pt.x) + (p.y - pt.y) * (p.y - pt.y) <= D * D)
				g.node[getM(i, j)] = 1;
		}
	}
	int i = 1;
	for (; i < N + 1; i++) {
		if (!g.visited[i]) {
			Point p = g.point[i];
			if ((p.x * p.x + p.y * p.y) >(D + 7.5) * (D + 7.5))
				continue;
			if (g.visitN_DFS(i)) {
				cout << "Yes" << endl;
				return 0;
			}
		}
	}
	if (i == N + 1)
		cout << "No" << endl;
	return 0;
}