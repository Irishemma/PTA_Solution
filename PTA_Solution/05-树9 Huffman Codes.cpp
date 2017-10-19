/*05-树9 Huffman Codes
Sample Input:
7
A 1 B 1 C 1 D 3 E 3 F 6 G 6
4
A 00000
B 00001
C 0001
D 001
E 01
F 10
G 11
A 01010
B 01011
C 0100
D 011
E 10
F 11
G 00
A 000
B 001
C 010
D 011
E 100
F 101
G 110
A 00000
B 00001
C 0001
D 001
E 00
F 10
G 11

Sample Output:
Yes
Yes
No
No

非常烦的一道题 ，要比较哈夫曼树和给的编码
建哈夫曼树需要建一个最小堆，考查了堆的insert和del操作
然后计算哈夫曼树的WPL值：所有非叶节点的和，
也就是每次取出两个数相加的时候，累加到WPL上。
注意：对堆内元素操作时，比较大小用v[i]->f，
      但是赋值时用v[i] = v[j]，原因是不能动最开始存储的权重值。
给的编码计算WPL值比较简单。比较前缀需要要构造树，如果每个编码都在
叶节点上，WPL值又和最优WPL值相等，则编码为哈夫曼编码。

*/
#include<iostream>
#include<vector>
#include<string>
using namespace std;
#define N -10001
struct HNode {
    HNode() { l = r = NULL; c = '-'; }
    char c;
    int f;
    HNode *l, *r;
};
struct Heap {
    Heap (int n) : cap (n) {
        size = 0; v.resize (n + 1);
        v[0] = new HNode; v[0]->f = N;
    }
    void insert (HNode* num) {
        int child = ++size;
        for (; v[child / 2]->f > num->f; child /= 2)
            v[child] = v[child / 2];
        v[child] = num;
    }
    void del (HNode * &x) {
        x = v[1];
        int p = 1, c;
        HNode * tmp = v[size--];
        for (; p * 2 <= size; p = c) {
            c = p * 2;
            if (v[c]->f > v[c + 1]->f)
                c++;
            if (tmp->f > v[c]->f)
                v[p] = v[c];
            else
                break;
        }
        v[p] = tmp;
    }
    int size;
    int cap;
    vector<HNode *> v;
};
struct Huff {
    Huff (int n) : n (n) { root = new HNode;	v.resize (n);  }
    void insert (char c, string s) {
        HNode * pos = root;
        int i;
        for ( i = 0; i < n; i++) {
            if (v[i]->c == c) break;
        }
        currWPL += v[i]->f * s.length();
        while (!s.empty() ) {
            if (s[0] == '0') {
                if (!pos->l)
                    pos->l = new HNode;
                pos = pos->l;
            } else {
                if (!pos->r)
                    pos->r = new HNode;
                pos = pos->r;
            }
            s = s.substr (1, s.size() );
        }
        pos->c = c;
    }
    void des (HNode * &T) {
        if (T) {
            des (T->l);
            des (T->r);
            delete T;
            T = NULL;
        }
    }
    bool check (HNode * &T) {
        if (T) {
            return (WPL == currWPL) &&
                   (check (T->l) && check (T->r) ) &&
                   ! (T->c != '-' && (T->l || T->r) ) &&
                   (T->l && T->r || !T->l && !T->r);
        }
        return true;
    }
    void buildHuff() {
        heap = new Heap (n);
        for (int i = 0; i < n; i++)
            heap->insert (v[i]);
        WPL = 0;
        while (heap->size != 1) {
            HNode * sum = new HNode;
            heap->del (sum->l);
            heap->del (sum->r);
            sum->f = sum->l->f + sum->r->f;
            WPL += sum->f;
            heap->insert (sum);
        }
    }
    int WPL;
    int currWPL;
    Heap* heap;
    HNode* root;
    int n;
    vector<HNode *> v;
};
int main() {
    int n, m, num;
    char c;
    string s;
    cin >> n;
    Huff h (n);
    for (int i = 0; i < n; i++) {
        cin >> c >> num;
        h.v[i] = new HNode;
        h.v[i]->c = c; h.v[i]->f = num;
    }
    h.buildHuff();
    cin >> m;
    for (int i = 0; i < m; i++) {
        h.currWPL = 0;
        for (int j = 0; j < n; j++) {
            cin >> c >> s;
            h.insert (c, s);
        }
        if (h.check (h.root) )
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
        h.des (h.root);
        h.root = new HNode;
    }
    h.des (h.heap->v[1]);
    return 0;
}