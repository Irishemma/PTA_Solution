#include <iostream>
#include <vector>
using namespace std;

struct Hub {
    int data;
    int parent;
};
class FT {
  public:
    FT (int N) : cap (N) {
        data.resize (N + 1);
        for (int i = 0; i < data.size(); i++)
            data[i].parent = -1;
    }
    int getRoot (int x) {
        if (data[x].parent == -1)
            return x;
        else {
            for (; data[x].parent >= 0; x = data[x].parent);
            return x;
        }
    }
    void Union (int c1, int c2) {
        int r1, r2;
        r1 = getRoot (c1);
        r2 = getRoot (c2);
        if (data[r1].parent < data[r2].parent) {
            data[r1].parent += data[r2].parent;
            data[r2].parent = r1;
        } else  {
            data[r2].parent += data[r1].parent;
            data[r1].parent = r2;
        }
    }
    vector<Hub> & getData() { return data; }
    vector<Hub> data;
  private:
    int cap;
};

int main() {
    int N, c1, c2;
    char op;
    cin >> N;
    FT ft (N);
    cin >> op;
    while (op != 'S') {
        cin >> c1 >> c2;
        if (op == 'I')
            ft.Union (c1, c2);
        else if (op == 'C') {
            int r1, r2;
            r1 = ft.getRoot (c1);
            r2 = ft.getRoot (c2);
            if (r1 == r2 && (! (r1 < 0 && r2 < 0) ) )
                cout << "yes" << endl;
            else
                cout << "no" << endl;
        }
        cin >> op;
    }
    int count = 0;
    for (int i = 0; i < ft.getData().size(); i++) {
        if (ft.data[i].parent < 0)
            count++;
    }
    if (count > 2)
        cout << "There are " << count - 1 << " components.";
    else
        cout << "The network is connected.";
    return 0;
}