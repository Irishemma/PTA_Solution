/*PAT-1072. Gas Station

Sample Input 1:
4 3 11 5
1 2 2
1 4 2
1 G1 4
1 G2 3
2 3 2
2 G2 1
3 4 2
3 G3 2
4 G1 3
G2 G1 1
G3 G2 2
Sample Output 1:
G1
2.0 3.3
Sample Input 2:
2 1 2 10
1 G1 9
2 G1 20
Sample Output 2:
No Solution
*/

#include <iostream>
#include <vector>
#include <string>
#define INF 999999
using namespace std;

int G (int x) {
	return x + n;
}
int n, m, k, ds, i1, i2, l;
int main() {
	cin >> n >> m >> k >> ds;
	string c1, c2;
	vector<int> len (n + m);
	for (int i = 0; i < n + m; i++) {
		len[i].resize (n + m, INF);
	}
	for (int i = 0; i < n + m; i++) {
		cin >> c1 >> c2 >> l;
		i1 = c1[c1.length()] - '0' + (c1.length() == 2) ? n : 0;
		i2 = c1[c2.length()] - '0' + (c2.length() == 2) ? n : 0;
		len[i1][i2] = l;
		len[i2][i1] = l;
	}
	//Test G1~Gm
	int minDist = 0;
	for (int i = n; i < n + m; i++) {
		vector<int> dist (n + m, INF);
		vector<int> coll (n + m);
		dist[i] = 0;
		while (1) {
			int v = 0;
			int minJDist = INF;
			int j;
			for (j = 0; j < n + m; j++) {
				if (dist[j] < minJDist) {
					v = j;
					minJDist = dist[j];
				}
			}
			if (j == n + m) {
				break;
			}
			for (int k = 0; k < n + m; k++) {

			}
		}
	}
	if (minDist == 0) {
		cout << "No Solution";
	} else {
	}
	return 0;
}