//
//  09-排序2 Insert or Merge（25 分）.cpp
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
3 1 2 8 7 5 9 4 0 6
1 3 2 8 5 7 4 9 0 6
Sample Output 2:

Merge Sort
1 2 3 8 4 5 7 9 0 6
*/
//

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
void Merge (T a[], T tmpa[], int l, int r, int rend) { //归并排序，递归方法，稳定
	int lend = r - 1;
	int n = rend - l + 1;
	int tmp = l;
	while (l <= lend && r <= rend) {
		if (a[l] <= a[r])
			tmpa[tmp++] = a[l++];
		else
			tmpa[tmp++] = a[r++];
	}
	while (l <= lend)
		tmpa[tmp++] = a[l++];
	while (r <= rend)
		tmpa[tmp++] = a[r++];
	for (int i = 0; i < n; i++, rend--)
		a[rend] = tmpa[rend];
}
template <class T>
void Merge_pass (
    T a[], T tmpa[], int n,
    int length) { //归并排序，非递归方法，稳定高效，但是需要多一倍存储，一般用于外排序。
	int i;
	for (i = 0; i < n - 2 * length; i += 2 * length)
		Merge (a, tmpa, i, i + length, i + 2 * length - 1);
	if (i + length < n)
		Merge (a, tmpa, i, i + length, n - 1);
	else
		for (int j = i; j < n; j++)
			tmpa[j] = a[j];
}

template <class T> void Merge_sort (T a[], int n) {
	bool flag = false;
	int length = 1;
	T* tmpa = new T[n];
	if (tmpa != NULL) {
		while (length < n) {
			Merge_pass (a, tmpa, n, length);
			length *= 2;
			if (flag) {
				cout << "Merge Sort\n";
				for (int i = 0; i < n - 1; i++)
					cout << a[i] << ' ';
				cout << a[n - 1];
				return;
			}
			if (equal (a, o))
				flag = true;
			Merge_pass (tmpa, a, n, length);
			length *= 2;
			if (flag) {
				cout << "Merge Sort\n";
				for (int i = 0; i < n - 1; i++)
					cout << a[i] << ' ';
				cout << a[n - 1];
				return;
			}
			if (equal (a, o))
				flag = true;
		}
		delete[] tmpa;
	} else
		cout << "error";
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
	Merge_sort (b, n);
	return 0;
}