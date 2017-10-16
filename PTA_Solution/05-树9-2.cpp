#include <iostream>
#include <vector>
#include <string>
#define MINNUM -10000
using namespace std;

struct TNode {
    char c;
    int f;
    bool isLeaf;
    int route;
    TNode *Left, *Right;
    TNode() { Left = Right = NULL; c = '\0'; f = 0; route = 0; }
    operator int() { return f; }/*
    TNode & operator= (int x) {
        f = x;
        return *this;
    }*/
    TNode (const TNode & Tt) {
        c = Tt.c;
        f = Tt.f;
        isLeaf = Tt.isLeaf;
        route = Tt.route;
        Left = Tt.Left;
        Right = Tt.Right;
    }
};
typedef TNode T;
class MinHeap {
  public:
    vector<T*> data;
    int Capacity;
    int index;
    MinHeap (int cap = 64) : Capacity (cap) {
        index = 0;
        data.resize (cap + 1);
        data[0] = new T;
        data[0]->f = MINNUM;
    }
    bool isEmpty() { return index == 0; }
    bool isFull() { return index == Capacity; }
    void adjustDown (int theIndex);
    void adjustUp (int theIndex);/*
    void add (int x) {
        T* Tt = new T;
        Tt->f = x;
        add (Tt);
    }*/
    void reset (int cap = 64) {
        for (int i = 0; i < data.size(); i++)
            if (data[i])
                delete data[i];
        Capacity = cap;
        index = 0;
        data.resize (cap + 1);
        data[0] = new T;
        data[0]->f = MINNUM;
    }
    bool add (T* x) {
        if (isFull() )
            return false;
        if (index == 0) {
            data[++index] = x;
            return true;
        }
        int i = ++index;
        for (; data[i / 2] > x; i /= 2)
            data[i] = data[i / 2];
        data[i] = x;
        return true;
    }
    void BuildMinHeap() {
        if (isEmpty() )
            return;
        for (int i = index / 2; i > 0; i--)
            adjustDown (i);
    }
    T* DeleteMin();
};
void MinHeap::adjustDown (int theIndex) {
    if (isEmpty() )
        return;
    int parent, child;
    T *x = data[theIndex];
    for (parent = theIndex; parent * 2 <= index; parent = child) {
        child = parent * 2;
        if ( (child != index) && *data[child] > *data[child + 1])
            child++;
        if (*x <= *data[child])
            break;
        else
            data[parent] = data[child];
    }
    data[parent] = x;
}
TNode *MinHeap::DeleteMin() {
    if (isEmpty() )
        return NULL;
    int parent, child;
    TNode * MinItem = data[1];
    TNode * X = data[index--];
    for (parent = 1; parent * 2 <= index; parent = child) {
        child = parent * 2;
        if ( (child != index) && (*data[child] > *data[child + 1]) )
            child++;
        if (*X <= *data[child])
            break;
        else
            data[parent] = data[child];
    }
    data[parent] = X;
    return MinItem;
}
void MinHeap::adjustUp (int theIndex) {
    /*
        if (theIndex > index)
            return;
        while (theIndex > -1) {
            T temp = data[theIndex];
            int parent = (theIndex - 1) / 2;
            if (parent >= 0) {
                if (temp < data[parent]) {
                    data[theIndex] = data[parent];
                    data[parent] = temp;
                    theIndex = parent;
                } else
                    theIndex = -1;
            }
        }*/
}

typedef TNode HuffTree;

class HuffCode {
  public:
    vector<char> vecC;
    vector<int> vecF;
    HuffTree * huf;
    MinHeap minhp;
    int WPL, optWPL;
    HuffCode() {
        WPL = 0;
    }
    ~HuffCode() {
        Destroy (huf);
       // minhp.reset();
    }
    void buildOptTree() {
        for (int i = 0; i < vecF.size(); i++) {
            T* Tt = new T;
            Tt->f = vecF[i];
            minhp.add (Tt);
        }
        minhp.BuildMinHeap();
        while (minhp.index != 1) {
            HuffTree * T = new TNode;
            T->Left = minhp.DeleteMin();
            T->Right = minhp.DeleteMin();
            T->f = T->Left->f + T->Right->f;
            minhp.add (T);
            minhp.BuildMinHeap();
        }
        huf = minhp.DeleteMin();
        preH (huf, 0); // ¼ÆËãoptWPL
        optWPL = WPL;
        Destroy ( huf);
        huf = NULL;
    }
    void preH (HuffTree * _huf, int route) {
        if (!_huf)
            return;
        _huf->route = route;
        if (!_huf->Left && !_huf->Right) {
            WPL += _huf->f * _huf->route;
            return;
        }
        preH (_huf->Left, route + 1);
        preH (_huf->Right, route + 1);
    }
    bool Insert (char _c, int _f, string s) {
        if (s == "")
            return false;
        if (!huf) {
            huf = new TNode;
            huf->isLeaf = false;
        }
        int _route = s.size();
        HuffTree * _huf = huf;
        for (; s != ""; s = s.substr (1) ) {
            if (s[0] == '0') {
                if (!_huf->Left)
                    _huf->Left = new TNode;
                _huf = _huf->Left;
            } else {
                if (!_huf->Right)
                    _huf->Right = new TNode;
                _huf = _huf->Right;
            }
            _huf->isLeaf = false;
        }
        _huf->isLeaf = true;
        _huf->c = _c;
        _huf->f = _f;
        _huf->route = _route;
        return true;
    }
    HuffTree *Destroy (HuffTree *_huf) {
        if (_huf) {
            _huf->Left = Destroy (_huf->Left);
            _huf->Right = Destroy (_huf->Right);
            delete _huf;
            _huf = NULL;
        }
        return _huf;
    }
    bool isAllLeaf (HuffTree * _huff) {
        if (!_huff)
            return true;
        if ( (!_huff->isLeaf) && (_huff->c != '\0') )
            return false;
        return (isAllLeaf (_huff->Left) && isAllLeaf (_huff->Right) );
    }
    bool isAllDegree2 (HuffTree * _huff) {
        if (_huff) {
            if (_huff->Left && _huff->Right)
                return (isAllDegree2 (_huff->Left) && isAllDegree2 (_huff->Right) );
            if (!_huff->Left && !_huff->Right)
                return true;
            else return false;
        }
        return true;
    }
    bool isOpt (HuffTree * _huff) {
        WPL = 0;
        preH (_huff, 0);
        return (WPL == optWPL);
    }
    bool isHuffTree() {
        return (isOpt (huf) && isAllDegree2 (huf) && isAllLeaf (huf) );
    }
};

int main() {
    int N, M, num;
    HuffCode *hcode = new HuffCode;
    cin >> N;
    char c; int f; string s;
    for (int i = 0; i < N; i++) {
        cin >> c >> f;
        hcode->vecC.push_back (c);
        hcode->vecF.push_back (f);
    }
    hcode->minhp.data.resize (N + 1);
    hcode->minhp.Capacity = N;
    hcode->buildOptTree();
    cin >> M;
    for (int i = 0; i < M; i++) {
        bool flag = true;
        for (int j = 0; j < N; j++) {
            cin >> c >> s;
            int k = 0;
            for (; k < hcode->vecC.size(); k++) {
                if (hcode->vecC[k] == c)
                    break;
            }
            flag = hcode->Insert (c, hcode->vecF[k], s);
        }
        if (hcode->isHuffTree() && flag)
            cout << "Yes" << endl;
        else cout << "No" << endl;
        hcode->huf = hcode->Destroy (hcode->huf);
    }
    delete hcode;
    hcode = NULL;
    return 0;
}
