/*09-排序1 排序（25 分）
输入样例:

11
4 981 10 -17 0 -20 29 50 8 43 -5
输出样例:

-20 -17 -5 0 4 8 10 29 43 50 981
*/
#include <iostream>
using namespace std;
#define CUTOFF 50

template <class T> void Swap (T& a, T& b) {
	a ^= b ^= a ^= b;
}

template <class T>
void Bubble_sort (T a[], int n) { //冒泡排序，简单，稳定，支持链表存储
	bool flag = false;
	for (int p = n - 1; p >= 0; p--) {
		for (int i = 0; i < p; i++)
			if (a[i] > a[i + 1]) {
				swap (a[i], a[i + 1]);
				flag = true;
			}
		if (!flag)
			break;
	}
}

template <class T>
void Insertion_sort (T a[], int n) { //插入排序，交换次数和冒泡一样，所有的逆序对
	T tmp;
	for (int p = 1; p < n; p++) {
		tmp = a[p];
		int i;
		for (i = p - 1; i >= 0 && tmp < a[i]; i--)
			a[i + 1] = a[i];
		a[i + 1] = tmp;
	}
}

int Pow (int num, int power) {
	int sum = 1;
	for (int i = 0; i < power; i++)
		sum *= num;
	return sum;
}
template <class T>
void Shell_sort (T a[], int n) { //希尔排序，一次消多个逆序对，交换次数减少
	T tmp;
	int si = 2;
	/*
	int st = 0, stmp[100], Sedgewick[100];
	for (; st <= n;) {
	st = 9*Pow (4, si) - 9 * Pow (2, si) + 1;
	stmp[si++] = st;
	}
	for (int i = 0; i < si - 3; i++)
	Sedgewick[i] = stmp[si - 2 - i];
	Sedgewick[si - 2] = 0;
	Sedgewick[si - 3] = 1;
	si = 0;*/
	int Sedgewick[] = { 16001, 8929, 3905, 2161, 929, 505, 209,
	                    109,   41,   19,   5,    1,   0
	                  };
	for (si = 0; Sedgewick[si] >= n; si++)
		;
	for (int d = Sedgewick[si]; d > 0; d = Sedgewick[++si]) {
		for (int p = d; p < n; p++) {
			tmp = a[p];
			int i;
			for (i = p; i >= d && tmp < a[i - d]; i -= d)
				a[i] = a[i - d];
			a[i] = tmp;
		}
	}
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
	for (int i = n / 2 - 1; i >= 0; i--)
		PercDown (a, n, i);
	for (int i = n - 1; i > 0; i--) {
		swap (a[0], a[i]);
		PercDown (a, i, 0);
	}
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
	int length = 1;
	T* tmpa = new T[n];
	if (tmpa != NULL) {
		while (length < n) {
			Merge_pass (a, tmpa, n, length);
			length *= 2;
			Merge_pass (tmpa, a, n, length);
			length *= 2;
		}
		delete[] tmpa;
	} else
		cout << "error";
}


template <class T>
T Median3 (T a[], int left, int right) {
	int mid = (left + right) / 2;
	if (a[left] > a[mid])
		swap (a[left], a[mid]);
	if (a[left] > a[right])
		swap (a[left], a[right]);
	if (a[mid] > a[right])
		swap (a[mid], a[right]);
	swap (a[mid], a[right - 1]);
	return a[right - 1];
}

template <class T>
void Quicksort (T a[], int left, int right) {
	if (CUTOFF <= right - left) {
		int pivot = Median3 (a, left, right);
		int i = left, j = right - 1;
		for (;;) {
			while (a[++i] < pivot) {}
			while (a[--j] > pivot) {}
			if (i < j)
				swap (a[i], a[j]);
			else break;
		}
		swap (a[i], a[right - 1]);
		Quicksort (a, left, i - 1);
		Quicksort (a, i + 1, right);
	} else
		Insertion_sort (a + left, right - left + 1);
}

template < class T>
void Quick_sort (T a[], int n) {
	Quicksort (a, 0, n - 1);
}

int main() {
	int n, c1;
	cin >> n;
	int a[100001];
	for (int i = 0; i < n; i++) {
		cin >> c1;
		a[i] = c1;
	}
	Quick_sort (a, n);
	for (int i = 0; i < n - 1; i++)
		cout << a[i] << ' ';
	cout << a[n - 1];
	return 0;
}