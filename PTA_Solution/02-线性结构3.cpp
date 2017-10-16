// Äæ×ªÁ´±í


#include <iostream>
#include <vector>
using namespace std;
#define N 100000
struct Node {
public:
	Node(int add = 0, int data = 0, int next = 0) : add(add), data(data), next(next) {}
	unsigned long add;
	int data;
	int next;
	Node * Next;
};

int main() {
	int firstA, num, k;
	vector<Node> V(N), V2;
	cin >> firstA >> num >> k;
	for (int i = 0; i < num; i++) {
		int add, data, next;
		cin >> add >> data >> next;
		Node n1(add, data, next);
		V[add] = n1;
	}
}
