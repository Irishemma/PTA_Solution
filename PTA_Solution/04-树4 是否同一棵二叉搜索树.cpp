/*
04-树4 是否同一棵二叉搜索树
输入样例：
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0

输出样例:
Yes
No
No

构建两个BST，比较左右节点
*/
#include <iostream>
using namespace std;

struct Node {
    Node (int num) : data (num) { Left = Right = NULL; }
    int data;
    Node *Left, *Right;
};

struct BST {
    BST() { atree = btree =  NULL; }
    Node * atree, *btree;
    Node* insert (int num, Node* bst) {
        if (!bst)
            bst = new Node (num);
        else {
            if (num < bst->data)
                bst->Left = insert (num, bst->Left);
            else
                bst->Right = insert (num, bst->Right);
        }
        return bst;
    }
    bool a_b (Node* atree, Node* btree) {
        if (!atree && !btree)
            return true;
        if (!atree && btree || atree && !btree || atree->data != btree->data)
            return false;
        return (a_b (atree->Left, btree->Left) && a_b (atree->Right, btree->Right) );
    }
    Node * destroy (Node * bst) {
        if (bst) {
            bst->Left = destroy (bst->Left);
            bst->Right = destroy (bst->Right);
            delete bst;
            bst = NULL;
        }
        return bst;
    }
};
int main() {
    int n, l, num;
    BST bst;
    Node * root = NULL;
    cin >> n;
    while (n != 0) {
        cin >> l;
        for (int i = 0; i < n; i++) {
            cin >> num;
            bst.atree = bst.insert (num, bst.atree);
        }
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < n; j++) {
                cin >> num;
                bst.btree = bst.insert (num, bst.btree);
            }
            if (bst.a_b (bst.atree, bst.btree) )
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
            bst.btree = bst.destroy (bst.btree);
        }
        bst.atree = bst.destroy (bst.atree);
        cin >> n;
    }
    return 0;
}
