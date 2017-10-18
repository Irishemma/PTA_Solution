/*
03-树3 Tree Traversals Again
Sample Input:
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop

Sample Output:
3 4 2 6 5 1

push是先序遍历，pop是中序遍历。存储两个遍历，分左右子树提取递归即可。

*/

#include<iostream>
#include<vector>
#include<stack>
#include<string>
using namespace std;
struct BinTree {
    BinTree() { flag = true; vpop.resize (0); }
    vector<int > vpush, vpop, vout;
    int n;
    bool flag;
    void out (int rootI, int aI, int bI) {
        int i = aI;
        for (; i < bI + 1; i++) {
            if (vpop[i] == vpush[rootI])
                break;
        }
        if (aI <= i - 1)
            out (rootI + 1, aI, i - 1);
        if (i + 1 <= bI)
            out (rootI + i + 1 - aI, i + 1, bI);
        if (!flag)
            cout << ' ';
        if (flag)
            flag = false;
        cout << vpop[i];
    }
};
int main() {
    int n, num;
    string op;
    stack<int > s;
    BinTree btree;
    cin >> n;
    cin >> op >> num;
    s.push (num);
    btree.vpush.push_back (num);
    while (btree.vpop.size() != n) {
        cin >> op;
        if (op == "Push") {
            cin >> num;
            s.push (num);
            btree.vpush.push_back (num);
        } else {
            int num = s.top();
            s.pop();
            btree.vpop.push_back (num);
        }
    }
    btree.n = n;
    btree.out (0, 0, n - 1);
    return 0;
}