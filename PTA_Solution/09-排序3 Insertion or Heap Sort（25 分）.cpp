//
//  09-排序3 Insertion or Heap Sort（25 分）.cpp
//  PTA2
//
//  Created by zl on 17/11/24.
//  Copyright © 2017年 zl. All rights reserved.
/*
Sample Input 1:

10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Sample Output 1:

Insertion Sort
1 2 3 5 7 8 9 4 6 0
Sample Input 2:

10
3 1 2 8 7 5 9 4 6 0
6 4 5 1 0 3 2 7 8 9
Sample Output 2:

Heap Sort
5 4 3 1 0 2 6 7 8 9
*/

#include <iostream>
using namespace std;

int n, c1;
int o[101];

bool equal (int a[], int b[]) {
	int i;
	for (i = 0; i < n; i++) {
		if (a[i] != b[i])
			break;
	}
	return i == n;
}
template <class T>
bool Insertion_sort (T a[], int n) { //插入排序，交换次数和冒泡一样，所有的逆序对
	T tmp;
	bool flag = false;
	for (int p = 1; p < n; p++) {
		tmp = a[p];
		int i;
		for (i = p - 1; i >= 0 && tmp < a[i]; i--)
			a[i + 1] = a[i];
		a[i + 1] = tmp;
		if (flag) {
			cout << "Insertion Sort\n";
			for (int i = 0; i < n - 1; i++)
				cout << a[i] << ' ';
			cout << a[n - 1];
			return true;
		}
		if (equal (a, o))
			flag = true;
	}
	return flag;
}

template <class T>
void PercDown (T a[], int n,
               int i) { //堆排序，建堆耗时间，未必有快排和希尔排序快
	int parent, child;
	T X = a[i];
	for (parent = i; parent * 2 + 1 <= n - 1; parent = child) { //最大堆下滤
		child = parent * 2 + 1;
		if ((child != n - 1) && (a[child] < a[child + 1]))
			child++;
		if (X >= a[child])
			break;
		a[parent] = a[child];
	}
	a[parent] = X;
}

template <class T> void Heap_sort (T a[], int n) {
	bool flag = false;
	for (int i = n / 2 - 1; i >= 0; i--) {
		PercDown (a, n, i);
		if (flag) {
			cout << "Heap Sort\n";
			for (int i = 0; i < n - 1; i++)
				cout << a[i] << ' ';
			cout << a[n - 1];
			return;
		}
		if (equal (a, o))
			flag = true;
	}
	for (int i = n - 1; i > 0; i--) {
		swap (a[0], a[i]);
		PercDown (a, i, 0);
		if (flag) {
			cout << "Heap Sort\n";
			for (int i = 0; i < n - 1; i++)
				cout << a[i] << ' ';
			cout << a[n - 1];
			return;
		}
		if (equal (a, o))
			flag = true;
	}
}

int main() {
	int a[101], b[101];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> c1;
		a[i] = c1;
		b[i] = c1;
	}
	for (int i = 0; i < n; i++) {
		cin >> c1;
		o[i] = c1;
	}
	if (Insertion_sort (a, n))
		return 0;
	Heap_sort (b, n);
	return 0;
}