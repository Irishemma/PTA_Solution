#include <iostream>
#include <vector>
using namespace std;
#define N 100000
struct Node {
  public:
    Node (int add = 0, int data = 0, int next = 0) : add (add), data (data), next (next) {}
    unsigned long add;
    int data;
    int next;
};

int main() {
    int firstA, num, k;
    vector<Node> V (N), V2;
    cin >> firstA >> num >> k;
    for (int i = 0; i < num; i++) {
        int add, data, next;
        cin >> add >> data >> next;
        Node n1 (add, data, next);
        V[add] = n1;
    }
    V2.push_back (V[firstA]);
    for (int i = 1; V2[i - 1].next != -1; i++)
        V2.push_back (V[V2[i - 1].next]);
    int a1 = 0;
    int a2 = a1 + k - 1;
    while (a2 <= V2.size() - 1) {
        for (int i = 0; i <= (k - 1) / 2; i++) {
            Node n1 = V2[a1 + i];
            V2[a1 + i] = V2[a2 - i];
            V2[a2 - i] = n1;
        }
        a1 += k;
        a2 = a1 + k - 1;
    }
    k = 0;
    for (; k < V2.size() - 1; k++)
        printf ("%05d %d %05d\n", V2[k].add, V2[k].data, V2[k + 1].add);
    printf ("%05d %d -1\n", V2[k].add, V2[k].data);
    return 0;
}
