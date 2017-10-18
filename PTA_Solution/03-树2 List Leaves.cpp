/*
03-树2 List Leaves
Sample Input:
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6

Sample Output:
4 1 5

很简单，层次遍历，判断是否叶节点就好了

*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct Node {
    Node() { root = true; Left = Right = NULL; }
    int data;
    int c1, c2;
    bool root;
    Node * Left, *Right;
};
typedef Node * BinTree;
void Leaves (BinTree btree) {
    queue<Node*> q;
    Node* curr = NULL;
    bool flag = true;
    q.push (btree);
    while (!q.empty() ) {
        curr = q.front();
        q.pop();
        if (!curr->Left && !curr->Right) {
            if (!flag)
                cout << ' ';
            if (flag)
                flag = false;
            cout << curr->data;
        }
        if (curr->Left)
            q.push (curr->Left);
        if (curr->Right)
            q.push (curr->Right);
    }
}
int main() {
    int n, num;
    char c1, c2;
    cin >> n;
    vector<Node *> v (n);
    for (int i = 0; i < n; i++) {
        cin >> c1 >> c2;
        v[i] = new Node;
        v[i]->data = i;
        v[i]->c1 = c1 - '0'; v[i]->c2 = c2 - '0';
    }
    for (int i = 0; i < n; i++) {
        if (v[i]->c1 != '-' - '0') {
            v[i]->Left = v[v[i]->c1];
            v[v[i]->c1]->root = false;
        }
        if (v[i]->c2 != '-' - '0') {
            v[i]->Right = v[v[i]->c2];
            v[v[i]->c2]->root = false;
        }
    }
    int i;
    for (i = 0; i < n; i++) {
        if (v[i]->root)
            break;
    }
    Leaves ( v[i]);
    for (int i = 0; i < n; i++)
        delete v[i];
    return 0;
}