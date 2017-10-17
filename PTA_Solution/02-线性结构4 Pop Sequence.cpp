/*
02-线性结构4 Pop Sequence
Sample Input:
5 7 5				//栈的容量， 序列大小， case数
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2

Sample Output:
YES
NO
NO
YES
NO

模拟入栈出栈的过程，当栈顶大于出栈数则置否，
当栈顶小于出栈数，则开始入栈循环，直至栈顶等于出栈，pop并扔掉。

*/

#include <iostream>
#include <stack>
using namespace std;

int main() {
	int m, n, k;
	int Nowin, Nowout;
	cin >> m >> n >> k;
	for (int i = 0; i < k; i++) {
		bool flag = true;
		Nowin = 1;
		stack<int > s;
		for (int j = 0; j < n; j++) {
			cin >> Nowout;
			if (!flag)
				continue;
			if (!s.empty() && s.top() > Nowout)
				flag = false;
			while (s.empty() || s.top() < Nowout) {
				s.push(Nowin++);
				if (s.size() > m)
					flag = false;
			}
			s.pop();
		}
		if (flag)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}