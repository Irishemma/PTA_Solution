#include <iostream>
#include <stack>
using namespace std;

int main() {
    int m, n, k;
    int Nowin, Nowout;
    cin >> m >> n >> k;
    for (int i = 0; i < k; i++) {
        Nowin = 1;
        bool flag = true;
        stack<int> s;
        for (int j = 0; j < n; j++) {
            cin >> Nowout;
            if (!flag)
                continue;
            while (Nowin <= Nowout) {
                if (s.size() > m - 1)
                    flag = false;
                s.push (Nowin);
                Nowin++;
            } // Nowin->s
            if (flag && s.size() >= 1 && s.top() == Nowout)
                s.pop();
            else flag = false;
        }
        if (flag)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}

//
//int main()
//{
//	int M, N, K;
//	//  freopen("C:\\Users\\Jimko\\Desktop\\cin.txt","r",stdin);
//	cin >> M >> N >> K;
//	for (int i = 0; i<K; i++) {
//		stack<int> s;
//		bool flag = true;
//		int t = 1;
//		for (int j = 0; j<N; j++) {        //测试数据逐个输入
//			int num;
//			cin >> num;
//			if (flag) {
//				while (s.empty() || s.top() != num) {
//					s.push(t);
//					if (s.size()>M) {
//						flag = false;
//						break;
//					}
//					t++;            //有序进栈
//				}
//				if (flag && s.size() >= 1 && s.top() == num)      //出栈条件
//					s.pop();
//			}
//		}
//		if (flag)
//			printf("YES\n");
//		else
//			printf("NO\n");
//	}
//	return 0;
//}