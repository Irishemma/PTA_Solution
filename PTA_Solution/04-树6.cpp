#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef int T;

class CBST {
  public:
    vector<T> data;
    vector<T> inData;

    int Capacity;
    int index;
    CBST (int cap) : Capacity (cap) {
        index = 0;
        data.resize (cap + 1);
        inData.resize (cap + 1);
    }
    bool isEmpty() { return index == 0; }
    bool isFull() { return index == Capacity; }
    bool GZX (int ia, int ib, int &lastLineCount, int &sum) {
        int n = ib - ia + 1;
        sum = 1;
        for (int i = 1; sum < n; i *= 2) {
            if (sum < n && n <= sum + i) {
                lastLineCount = n - sum;
                return false;
            } else if (sum + i < n && n <= sum + 2 * i) {
                lastLineCount = n - sum - i;
                return true;
            }
            sum = sum + i * 2;
        }
        return false;
    }
    void fill (int index, int _ia, int _ib) {
        if (_ia == _ib) {
            data[index] = inData[_ia];
            return;
        }
        int lastLineCount, sum;
        if (!GZX (_ia, _ib, lastLineCount, sum) ) {
            if (sum == 1) {
                data[index] = inData[_ib];
                data[index * 2] = inData[_ia];
                return;
            }
            int ia = _ia + sum - sum / 2 + lastLineCount;
            fill (index * 2, _ia, ia - 2);
            fillFull (index * 2 + 1, ia, _ib);
            data[index] = inData[ia - 1];
        } else {
            if (sum == 1) {
                data[index] = inData[_ia + 1];
                data[index * 2] = inData[_ia];
                data[index * 2 + 1] = inData[_ib];
                return;
            }
            int ib = sum + _ia - 1;
            fillFull (index * 2, _ia, ib);
            fill (index * 2 + 1, ib + 2, _ib);
            data[index] = inData[ib + 1];
        }
    }

    void fillFull (int _index, int ia, int ib) {
        data[_index] = inData[ (ia + ib) / 2];
        int mid = (ia + ib) / 2;
        int count = ib - ia;
        int lineCount = 2;
        int _ia = ia;
        for (; count > 1; count /= 2) {
            _index *= 2;
            _ia = (ia + mid) / 2;
            for (int i = 0; i < lineCount; i++)
                data[_index + i] = inData[_ia + (mid - _ia) * 2 * i];
            lineCount *= 2;
            mid = _ia;
        }
    }
};
int main() {
    int N, num;
    cin >> N;
    CBST cbst (N);
    for (int i = 1; i <= N; i++) {
        //num = i;
        cin >> num;
        cbst.inData[i] = num;
    }
    sort (cbst.inData.begin() + 1, cbst.inData.end() );
    cbst.fill (1, 1, N);
    for (int i = 1; i < N; i++)
        cout << cbst.data[i] << ' ';
    cout << cbst.data[N];
    return 0;
}
