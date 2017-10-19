/*05-树8 File Transfer
Sample Input 1:
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
S

Sample Output 1:
no
no
yes
There are 2 components.

这是个并查集的问题，掌握找根节点及合并不同树的方法

*/
#include<iostream>
#include<vector>
using namespace std;
struct File {
    File (int n) : n (n) { v.resize (n + 1, -1); }
    int n;
    vector<int> v;
    int root (int i) {
        int k = i;
        while (v[k] > 0)
            k = v[k];
        return k;
    }
    void connect (int c1, int c2) {
        if (v[root (c1)] < v[root (c2)] ) {
            v[root (c1)] += v[root (c2)];
            v[root (c2)] = root (c1);
        } else {
            v[root (c2)] += v[root (c1)];
            v[root (c1)] = root (c2);
        }
    }
    void check (int c1, int c2) {
        if (root (c1) == root (c2) && root (c1) > 0)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
};
int main() {
    int n, c1, c2;
    char op;
    cin >> n;
    File f (n);
    cin >> op;
    while (op != 'S') {
        cin >> c1 >> c2;
        if (op == 'I')
            f.connect (c1, c2);
        else
            f.check (c1, c2);
        cin >> op;
    }
    int count = 0;
    for (int i = 1; i < n + 1; i++) {
        if (f.v[i] < 0)
            count++;
    }
    if (count > 1)
        cout << "There are " << count << " components." << endl;
    else
        cout << "The network is connected.";
    return 0;
}