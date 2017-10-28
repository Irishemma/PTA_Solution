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
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#define INF 999999
using namespace std;

int n, m, k, ds, i1, i2, l;
int G (int x) {
	return x + n;
}
int main() {
	cin >> n >> m >> k >> ds;
	string c1, c2;
	vector<vector<int> > len (n + m);
	vector<int> distSave;
	for (int i = 0; i < n + m; i++) {
		len[i].resize (n + m, INF);
	}
	for (int i = 0; i < k; i++) {
		cin >> c1 >> c2 >> l;
		i1 = c1[c1.length() - 1] - '0' + ((c1.length() == 2) ? n : 0);
		//cout << c2.length();
		i2 = c2[c2.length() - 1] - '0' + ((c2.length() == 2) ? n : 0);
		len[i1 - 1][i2 - 1] = l;
		len[i2 - 1][i1 - 1] = l;
	}
	//Test G1~Gm
	int minDist = 0;
	int minDistG = 0;
	for (int i = n; i < n + m; i++) {
		vector<int> dist (n + m, INF);
		vector<int> collected (n + m);
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
			if (v == n + m) {
				break;
			}
			collected[v] = true;
			for (int w = 0; w < n + m; w++) {
				if (!collected[k] && len[v][w] != INF) {
					if (dist[v] + len[v][w] < dist[w]) {
						dist[w] = dist[v] + len[v][w];
					}
				}
			}
		}
		int min = INF;
		int max = 0;
		int j;
		for (j = 0; j < n; j++) {
			if (dist[j] < min) {
				min = dist[j];
			}
			if (dist[j] > max) {
				max = dist[j];
			}
		}
		if (max > ds) {
			continue;
		}
		if (min > minDist) {
			minDist = min;
			minDistG = i;
			distSave.swap (dist);
		}
	}
	if (minDist == 0) {
		cout << "No Solution";
	} else {
		int i;
		int min = INF;
		int sum = 0;
		for (i = 0; i < distSave.size(); i++) {
			sum += distSave[i];
			if (distSave[i] < min) {
				min = distSave[i];
			}
		}
		double avg = sum /= (n + m - 1);
		cout << 'G' << minDistG << endl;
		cout << setprecision (1) << min << avg;
	}
	return 0;
}