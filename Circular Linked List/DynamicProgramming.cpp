#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

int J(int m, int n)
{
	if (n == 1) 
		return 1;
	if (m == 1)
		return n;
	if (n <= m) 
		return (J(m, n - 1) + m - 1) % n + 1;
	int K = J(m, n - n / m);
	if (K <= n%m) 
		return K + n - n%m;
	int L = K - n%m;
	return L + (L - 1) / (m - 1);
}

void main()
{
	int n, k;
	cout << "Nhap n, k: ";
	cin >> n >> k;
	clock_t start, end;
	start = clock();
	cout << "The win: " << J(k, n) << endl;
	end = clock();
	cout << "Time: " << (end - start) * 1000 << " ms" << endl;
	_getch();
}