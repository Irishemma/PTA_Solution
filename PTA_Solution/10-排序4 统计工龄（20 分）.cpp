/*10-排序4 统计工龄（20 分）

输入样例:
8
10 2 0 5 7 2 5 2

输出样例:
0:1
2:3
5:2
7:1
10:1
*/

#include <iostream>
using namespace std;
int num[51];

int main() {
	int n, c1;
	fill (num, num + 51, 0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> c1;
		num[c1]++;
	}
	for (int i = 0; i < 51; i++) {
		if (num[i] != 0)
			cout << i << ":" << num[i] << endl;
	}
	return 0;
}