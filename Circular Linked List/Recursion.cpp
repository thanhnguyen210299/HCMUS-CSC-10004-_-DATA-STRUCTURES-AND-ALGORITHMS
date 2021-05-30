#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

int josephus(int n, int k)
{
	if (n == 1)
		return 1;
	else
		return (josephus(n - 1, k) + k - 1) % n + 1;
}

int j(int n, int k)
{
	int t = 1;
	for (int i = 2; i <= n; i++)
		t = (t + k - 1) % i + 1;
	return t;
}

void main()
{
	int n, k;
	cout << "Nhap n, k: ";
	cin >> n >> k;
	clock_t start, end;
	start = clock();
	cout << "The win: " << j(n, k) << endl;
	end = clock();
	cout << "Time: " << (end - start) * 1000 << " ms" << endl;
	_getch();
}