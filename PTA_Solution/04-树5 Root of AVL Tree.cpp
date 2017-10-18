/*
04-树5 Root of AVL Tree
Sample Input 1:
5
88 70 61 96 120

Sample Output 1:
70

注意LL、RR等函数的写法，还有节点高度的计算
*/
#include<iostream>
using namespace std;

int max (int a, int b) { return a > b ? a : b; }

struct Node {
    Node (int num) : data (num) { Left = Right = NULL; height = 0; }
    int data;
    int height;
    Node* Left, *Right;
};

struct AVLTree {
    AVLTree() { root = NULL; }
    Node * root;
    void insert (int num, Node * &T) {
        if (!T)
            T = new Node (num);
        else if (num < T->data) {
            insert (num, T->Left);
            if (calHeight (T->Left) - calHeight (T->Right) == 2) {
                if (num < T->Left->data)
                    LL (T);
                else
                    LR (T);
            }
        } else if (num > T->data) {
            insert (num, T->Right);
            if (calHeight (T->Left) - calHeight (T->Right) == -2) {
                if (num < T->Right->data)
                    RL (T);
                else
                    RR (T);
            }
        }
    }
    int calHeight (Node * &T) {
        if (!T)
            return -1;
        else
            return  max (calHeight (T->Left), calHeight (T->Right) ) + 1;
    }
    void Destroy (Node * &T) {
        if (T) {
            Destroy (T->Left);
            Destroy (T->Right);
            delete T;
            T = NULL;
        }
    }
    void LL (Node * &T) {
        Node * tmp = T;
        T = T->Left;
        tmp->Left = T->Right; // T->Right can be NULL
        T->Right = tmp;
    }
    void RR (Node * &T) {
        Node * tmp = T;
        T = T->Right;
        tmp->Right = T->Left;
        T->Left = tmp;
    }
    void LR (Node * & T) {
        RR (T->Left);
        LL (T);
    }
    void RL (Node * & T) {
        LL (T->Right);
        RR (T);
    }
};

int main() {
    int n, num;
    cin >> n;
    AVLTree avl;
    for (int i = 0; i < n; i++) {
        cin >> num;
        avl.insert (num, avl.root);
    }
    cout << avl.root->data;
    avl.Destroy (avl.root);
    return 0;
}