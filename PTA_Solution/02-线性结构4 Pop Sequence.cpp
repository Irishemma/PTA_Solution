/*
02-���Խṹ4 Pop Sequence
Sample Input:
5 7 5				//ջ�������� ���д�С�� case��
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

ģ����ջ��ջ�Ĺ��̣���ջ�����ڳ�ջ�����÷�
��ջ��С�ڳ�ջ������ʼ��ջѭ����ֱ��ջ�����ڳ�ջ��pop���ӵ���

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