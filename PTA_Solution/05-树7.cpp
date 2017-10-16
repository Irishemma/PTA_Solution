#include <iostream>
#include <vector>
#define MAXINDEX 1001
#define MINNUM -10001
using namespace std;

typedef int T;
struct HNode {
	T *data;
	int Size;
	int Capacity;
};

class MinHeap {
public:
	vector<T> data;
	int Capacity;
	int index;
	MinHeap(int cap) : Capacity(cap) {
		index = 0;
		data.resize(cap + 1);
		data[0] = MINNUM;
	}
	bool isEmpty() { return index == 0; }
	bool isFull() { return index == Capacity; }
	void adjustDown(int theIndex);
	void adjustUp(int theIndex);
	bool add(T x) {
		if (isFull())
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
		if (isEmpty())
			return;
		for (int i = index / 2; i > 0; i--) {
			adjustDown(i);
		}
	}
	void OutRoute(int theIndex) {
		for (int i = theIndex; i >= 2; i /= 2) {
			cout << data[i] << ' ';
		}
		cout << data[1];
	}
};
void MinHeap::adjustDown(int theIndex) {
	if (isEmpty())
		return;
	int parent, child;
	T x;
	x = data[theIndex];
	for (parent = theIndex; parent * 2 <= index; parent = child) {
		child = parent * 2;
		if ((child != index) && data[child] > data[child + 1])
			child++;
		if (x <= data[child])
			break;
		else
			data[parent] = data[child];
	}
	data[parent] = x;

}
void MinHeap::adjustUp(int theIndex) {
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
			}
			else
				theIndex = -1;
		}
	}
}
int main() {
	int N, M, num;
	cin >> N >> M;
	MinHeap minhp(N + 1);
	for (int i = 0; i < N; i++) {
		cin >> num;
		minhp.add(num);
	}
	minhp.BuildMinHeap();
	for (int i = 0; i < M; i++) {
		cin >> num;
		minhp.OutRoute(num);
		cout << endl;
	}
	return 0;
}



