#include "SinglyLinkedList.h"
#include <iostream>
#include <conio.h>
#include <random>

#define MAX 1000000000;
using namespace std;

void random(int n, SinglyLinkedList &a)
{
	int k = MAX;
	random_device rd;
	uniform_int_distribution<int> uni(-k, k);
	mt19937 rng(rd());
	for (int i = 0; i < n; i++)
		a.insertLast(uni(rng));
}

bool check(int n, SinglyLinkedList a)
{
	for (int i = 1; i < n; i++)
		if (a.get(i) < a.get(i - 1))
			return false;
	return true;
}

void RadixSort(SinglyLinkedList &a, int n)
{
	// Tim max
	int m = a.getFirst(), tmp;
	for (int i = 1; i < n; i++)
	{
		tmp = a.get(i);
		if (tmp > m)
			m = tmp;
	}

	// Sap xep
	int exp = 1, k;
	int bucket[20];
	SinglyLinkedList b(n);
	while (m / exp > 0)
	{
		for (int i = 0; i < 20; i++)
			bucket[i] = 0;
		for (int i = 0; i < n; i++)
		{
			tmp = (a.get(i) / exp) % 10 + 10;
			bucket[tmp]++;
		}
		for (int i = 1; i < 20; i++)
			bucket[i] += bucket[i - 1];

		for (int i = n - 1; i >= 0; i--)
		{
			k = a.get(i);
			tmp = (k / exp) % 10 + 10;
			b.set(k, bucket[tmp] - 1);
			bucket[tmp]--;
		}
		a = b;
		if (check(n, a))
			break;
		exp *= 10;
	}
	b.clear();
}

int main(int argc, char** argv) {
	cout << "Nhap n: ";
	int n;
	cin >> n;

	SinglyLinkedList a;
	random(n, a);
	//a.print();
	RadixSort(a, n);
	if (check(n, a))
		cout << "TRUE\n";
	else
		cout << "FALSE\n";
	//a.print();

	_getch();
	return 0;
}