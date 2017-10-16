#include <iostream>
#include <vector>
using namespace std;
struct Node {
    friend ostream & operator << (ostream&, const Node &);
  public:
    Node (int add = 0, int data = 0, int next = 0) : add (add), data (data), next (next) {}
    unsigned long add;
    int data;
    int next;
};
ostream & operator << (ostream & out, const Node & x) {
    int t = x.add;
    int i = 1;
    while (t = t / 10)
        i++;
    for (int j = 0; j < 5 - i; i++)
        cout << '0';
    out << x.add << ' ' << x.data << ' ';
    if (x.next != -1) {
        i = 1;
        t = x.next;
        while (t = t / 10)
            i++;
        for (int j = 0; j < 5 - i; i++)
            cout << '0';
    }
    cout << x.next;
    return out;
}

void Reverse (vector<Node> & V, int a1, int a2) {
    a1--; a2--;
    for (int i = a1; i <= (a1 + a2) / 2; i++) {
        Node n1 = V[i];
        V[i] = V[a2 + a1 - i];
        V[a2 + a1 - i] = n1;
    }
}
#define N 100000
int main() {
    int firstA, num, k;
    vector<Node> V (N), V2 ;
    cin >> firstA >> num >> k;
    for (int i = 0; i < num; i++) {
        int add, data, next;
        cin >> add >> data >> next;
        Node n1 (add, data, next);
        V[add] = n1;
    }
    V2.push_back (V[firstA]);
    for (int i = 1; V2[i - 1].next != -1; i++)
        V2.push_back ( V[V2[i - 1].next]);
    int i = 1;
    while (i + k - 1 < num) {
        Reverse (V2, i, i + k - 1);
        i = i + k;
    }
    for (i = 0; i < V2.size()-1; i++)
        cout << V2[i] << endl;
	cout << V2[i];
    return 0;
}