/*
02-线性结构3 Reversing Linked List

第一次做的时候偷懒直接用数组进行翻转，现在用链表来做一遍

*/

#include <iostream>
#include <vector>
using namespace std;
#define N 100000
struct Node {
  public:
    Node (int add = 0, int data = 0, int next = 0) : add (add), data (data), next (next) { Next = NULL; }
    unsigned long add;
    int data;
    int next;
    Node * Next;
};

Node * Reverse (Node * & L, int k) {
    Node * Old_head = L->Next;
    Node * New_head = NULL;
    Node * temp = L;
    for (int i = 0; i < k ; i++) {
        temp = Old_head->Next;
        Old_head->Next = New_head;
        New_head = Old_head;
        Old_head = temp;
    }
    Node * t = L->Next;
    L->Next->Next = Old_head;
    L->Next = New_head;
    return t;
}

int main() {
    int firstA, num, k;
    vector<Node *> V (N);
    cin >> firstA >> num >> k;
    Node * temp = NULL, *L;
    for (int i = 0; i < num; i++) {
        int add, data, next;
        cin >> add >> data >> next;
        temp = new Node (add, data, next);
        V[add] = temp;
    }
    L = new Node;
    L->Next = V[firstA];
    int i = firstA;
    for (num = 1; V[i]->next >= 0; i = V[i]->next) {
        V[i]->Next = V[V[i]->next];
        num++;
    }
    Node * NewL = L;
    i = 1;
    bool flag = true;
    for (; k * i <= num; i++) {
        if (flag) {
            NewL = Reverse (L, k);
            flag = false;
        } else
            NewL = Reverse (NewL, k);
    }
    L = L->Next;
    while (L->Next) {
        printf ("%05d %d %05d\n", L->add, L->data, L->Next->add);
        Node * t = L;
        L = L->Next;
        delete t;
    }
    printf ("%05d %d -1\n", L->add, L->data);
    return 0;
}
