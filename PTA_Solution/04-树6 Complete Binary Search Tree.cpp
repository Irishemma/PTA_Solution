/*
04-��6 Complete Binary Search Tree
Sample Input:
10
1 2 3 4 5 6 7 8 9 0

Sample Output:
6 3 8 1 5 7 9 0 2 4

���Ȱ����������ź���Ȼ���ж�CBST�����һ����û�й����ߣ�
�������ߣ��������������ݹ���������
û�����ߣ����ơ�������ʱ��ͺܷ����ر����״�

�������˳�Խ��ʦ�Ľ��⣬����ֱ�Ӽ����������Ľڵ��������㣬
�����±�ļ����������˺ܶ࣡
*/
#include<iostream>
#include<vector>
using namespace std;
struct Node {
    Node (int d) : d (d) { l = r = NULL; }
    int d;
    Node *l, *r;
};
int countL (int a, int b) {
    int n = b - a + 1;
    int sum = 0;
    int i = 1;
    for (; n - sum > 0; i *= 2 )
        sum += i;
    if (n - sum + i / 4 > 0)
        return (sum - i / 2);
    else
        return (n - i / 4) ;
}
struct CBST {
    CBST (int n) : n (n) { bst = NULL; cbst.resize (n + 1); }
    void insert (int num, Node * &bst) {
        if (!bst)
            bst = new Node (num);
        else {
            if (num < bst->d)
                insert (num, bst->l);
            else
                insert (num, bst->r);
        }
    }
    void inorder (Node * & bst) {
        if (bst) {
            inorder (bst->l);
            v.push_back (bst->d);
            inorder (bst->r);
        }
    }
    void destroy (Node * & bst) {
        if (bst) {
            destroy (bst->l);
            destroy (bst->r);
            delete bst;
            bst = NULL;
        }
    }
    void out() {
        bool flag = true;
        for (int i = 1; i < n + 1; i++) {
            if (!flag)
                cout << ' ';
            if (flag)
                flag = false;
            cout << cbst[i];
        }
    }
    void fill (int i, int aI, int bI) {
        if (aI == bI) {
            cbst[i] = v[aI];
            return;
        } else if (aI > bI)
            return;
        int L = countL (aI, bI);
        cbst[i] = v[aI + L];
        fill (i * 2, aI, aI + L - 1);
        fill (i * 2 + 1, aI + L + 1, bI);
    }
    Node * bst;
    int n;
    vector<int> v;
    vector<int> cbst;
};
int main() {
    int n, num;
    cin >> n;
    CBST cb (n);
    for (int i = 0; i < n; i++) {
        cin >> num;
        cb.insert (num, cb.bst);
    }
    cb.inorder (cb.bst);
    cb.fill (1, 0, n - 1);
    cb.out();
    cb.destroy (cb.bst);
    return 0;
}