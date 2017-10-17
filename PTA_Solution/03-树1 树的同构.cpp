/*
03-树1 树的同构
Sample Input:
8				//节点数，i行对应i号节点，从0开始编号
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -

Sample Output:
Yes


*/

#include <iostream>
#include <vector>
using namespace std;
struct Node {
    Node (char cha) : c (cha) { Left = Right = NULL; root = true; }
    char c;
    bool root;
    int c1, c2;
    Node * Left, *Right;
};
typedef Node * BinTree;

bool a_b (Node*a, Node*b) {
    if (a == NULL && b == NULL)
        return true;
    if (a != NULL && b != NULL)
        return a->c == b->c;
    return false;
}
int main() {
    int n, m;
    char cha, c1, c2;
    bool flag = true;
    cin >> n;
    vector<Node *> v1 (n);
    for (int i = 0; i < n; i++) {
        cin >> cha >> c1 >> c2;
        v1[i] = new Node (cha);
        v1[i]->c1 = c1 - '0';
        v1[i]->c2 = c2 - '0';
    }
    cin >> m;
    if (n == m) {
        for (int i = 0; i < n; i++) {
            if (v1[i]->c1 != ('-' - '0') ) {
                v1[i]->Left = v1[v1[i]->c1];
                v1[v1[i]->c1]->root = false;
            }
            if (v1[i]->c2 != ('-' - '0') ) {
                v1[i]->Right = v1[v1[i]->c2];
                v1[v1[i]->c2]->root = false;
            }
        }
        vector<Node *> v2 (n);
        for (int i = 0; i < n; i++) {
            cin >> cha >> c1 >> c2;
            v2[i] = new Node (cha);
            v2[i]->c1 = c1 - '0';
            v2[i]->c2 = c2 - '0';
        }
        for (int i = 0; i < n; i++) {
            if (v2[i]->c1 != ('-' - '0') ) {
                v2[i]->Left = v2[v2[i]->c1];
                v2[v2[i]->c1]->root = false;
            }
            if (v2[i]->c2 != ('-' - '0') ) {
                v2[i]->Right = v2[v2[i]->c2];
                v2[v2[i]->c2]->root = false;
            }
        }
        for (int i = 0; i < n; i++) {
            int j = 0;
            for (; j < n; j++)
                if (v2[i]->c == v1[j]->c)
                    break;
            if (j == n) {
                flag = false;
                break;
            }
            if ( (a_b (v1[j]->Left, v2[i]->Left) && a_b (v1[j]->Right, v2[i]->Right) ) ||
                    (a_b (v1[j]->Left, v2[i]->Right) && a_b (v1[j]->Right, v2[i]->Left) ) )
                continue;
            flag = false;
            break;
        }
    } else
        flag = false;
    if (flag)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}