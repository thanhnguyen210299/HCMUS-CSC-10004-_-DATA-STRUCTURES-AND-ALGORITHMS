#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <random>
#include <conio.h>

using namespace std;

void random(int n, int *a, int k)
{
	random_device rd;
	uniform_int_distribution<int> uni(0, k);
	mt19937 rng(rd());
	for (int i = 0; i < n; i++)
		a[i] = uni(rng);
}

void check(int n, int * a) 
{
	for (int i = 1; i < n; i++)
		if (a[i] < a[i - 1])
		{
			cout << "FALSE\n";
			return;
		}
	cout << "TRUE\n";
	return;
}

void print(int n, int * a)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

void copy(int n, int *& a, int * tmp)
{
	for (int i = 0; i < n; i++)
		a[i] = tmp[i];
}

void swap(int &a, int &b) 
{
	int temp = a;
	a = b;
	b = temp;
}

///////////////////////////////////////////////O(N^2)/////////////////////////////////////

//Thuat toan Bubble Sort (sap xep noi bot)
void bubbleSort(int *a, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = n - 1; j > i; j--)
			if (a[j] < a[j - 1])
				swap(a[j], a[j - 1]);
}

//Thuat toan Shaker Sort
void shakerSort(int * a, int n)
{
	int j;
	int l = 0, r = n - 1, k = n - 1;
	while (l < r)
	{
		for (j = r; j > l; j--)
			if (a[j] < a[j - 1])
			{
				swap(a[j], a[j - 1]); 
				k = j;
			}
		l = k;
		for (j = l; j < r; j++)
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]); 
				k = j;
			}
		r = k;
	}
}

//Thuat toan Selection Sort (sap xep chon truc tiep)
void selectionSort(int *a, int n)
{
	int mini;
	for (int i = 0; i < n; i++)
	{
		mini = i;
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[mini])
				mini = j;
		if (mini != i)
			swap(a[i], a[mini]);
	}
}

//Thuat toan Insertion Sort (sap xep chen truc tiep)
void insertionSort(int * a, int n)
{
	int x, pos;
	for (int i = 1; i < n; i++)
	{
		x = a[i];//Luu gia tri a[i] lai tren x
		pos = i - 1;
		while (pos >= 0 && a[pos] > x)
		{
			a[pos + 1] = a[pos];//doi cho cac phan tu se dung sau x
			pos--;
		}
		a[pos + 1] = x;//chen x vao day
	}
}

//Thuat toan Binary Insertion Sort
void binaryInsertionSort(int * a, int n)
{
	int l, r, m;
	int x; //lưu giá trị a[i] tránh bị ghi đè khi dời chỗ các phần tử.
	for (int i = 1; i < n; i++)
	{
		x = a[i]; 
		l = 0; 
		r = i - 1;
		while (l <= r) // tìm vị trí chèn x
		{
			m = (l + r) / 2; // tìm vị trí thích hợp m
			if (x < a[m]) 
				r = m - 1;
			else 
				l = m + 1;
		}
		for (int j = i - 1; j >= l; j--)
			a[j + 1] = a[j]; // dời các phần tử sẽ đứng sau x
		a[l] = x; // chèn x vào dãy
	}
}

//Thuat toan Shell Sort
void shellSort(int* a, int n)
{
	int h = 1, X, i, j;
	
	// Tìm khoảng cách h cho danh sách
	while (h <= n / 3)
		h = h * 3 + 1;
	
	while (h > 0)
	{
		// Thuc hien hoan doi giua 2 phan tu co khoang cach h
		for (i = h; i < n; i++)
		{
			X = a[i];
			j = i; // vi tri cua X
			while (a[j - h] > X && j > h - 1)
			{
				a[j] = a[j - h];
				j -= h;
				if (j - h < 0)
					break;
			}
			a[j] = X;
		}
		h = (h - 1) / 3;
	}
}

///////////////////////////////////////////////O(NlogN)//////////////////////////////////

//Thuat toan HeapSort
void shiftUp(int *a, int l, int r)
{
	int i = l;
	int j = 2 * i + 1;
	int x = a[i];
	while (j < r)
	{
		if ((j < r - 1) && (a[j] < a[j + 1]))
			j++;
		if (x >= a[j])
			break;
		a[i] = a[j];
		i = j;
		j = 2 * i + 1;
	}
	a[i] = x;
}

void createHeap(int n, int *a)
{
	int l = (n / 2) - 1;
	while (l >= 0)
	{
		shiftUp(a, l, n);
		l--;
	}
}

void heapSort(int n, int * a)
{
	createHeap(n, a);
	int r = n;
	while (r > 1)
	{
		swap(a[0], a[r - 1]);
		r--;
		shiftUp(a, 0, r);
	}
}

//Thuat toan QuickSort
void quickSort(int * a, int l, int r)
{
	int k = a[(l + r) / 2];
	int i = l;
	int j = r;
	while (i < j)
	{
		while (a[i] < k) 
			i++;       
		while (a[j] > k) 
			j--;     
		if (i <= j)
		{
			if (i < j)
				swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	
	if (l < j) 
		quickSort(a, l, j);
	if (i < r) 
		quickSort(a, i, r);
}

//qsort trong C
int compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

void Qsort(int *a, int n)
{
	qsort(a, n, sizeof(int), compare);
}

//Thuat toan MergeSort
void merge(int * a, int l, int mid, int r, int *b)
{
	// Trộn mảng a1 = a[left..mid] và a2 = a[mid+1, right] thành mảng b
	int i = l;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= r)
	{
		if (a[i] <= a[j])
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}

	//Nạp phần còn lại của a1 và a2 vào cuối mảng b
	while (i <= mid)
		b[k++] = a[i++];
	while (j <= r)
		b[k++] = a[j++];

	for (int i = l, k = 0; i <= r; i++, k++)
		a[i] = b[k];
}

void mergeSort(int * a, int l, int r, int *b)
{
	if (l < r)
	{
		int mid = (l + r) / 2;
		mergeSort(a, l, mid, b);
		mergeSort(a, mid + 1, r, b);

		merge(a, l, mid, r, b);
	}
}

//////////////////////////////////////////O(N)/////////////////////////

//Thuat toan Counting Sort
void countingSort(int n, int * a, int *f, int *b)
{
	// Tim GTLN & GTNN
	int max = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] > max)
			max = a[i];
	}

	// Tao mang dem
	int m = max + 1;
	
	for (int i = 0; i < m; i++)
		f[i] = 0;

	for (int i = 0; i < n; i++)
		f[a[i]]++;
	
	for (int i = 1; i < m; i++)
	{
		f[i] += f[i - 1];
	}
	
	// Sap xep
	for (int i = n - 1; i >= 0; i--)
	{
		b[f[a[i]] - 1] = a[i];
		f[a[i]]--;
	}

	for (int i = 0; i < n; i++)
	{
		a[i] = b[i];
	}
}

// Thuat toan RadixSort
void radixSort(int * a, int n, int *b)
{
	// Tim max
	int m = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] > m)
			m = a[i];
	}

	// Sap xep
	int exp = 1;
	while (m / exp > 0)
	{
		int bucket[10] = { 0 };

		int tmp;
		
		for (int i = 0; i < n; i++)
		{
			tmp = (a[i] / exp) % 10;
			bucket[tmp]++;
		}

		for (int i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];
		
		for (int i = n - 1; i >= 0; i--)
		{
			tmp = (a[i] / exp) % 10;
			b[bucket[tmp] - 1] = a[i];
			bucket[tmp]--;
		}

		for (int i = 0; i < n; i++)
			a[i] = b[i];
		exp *= 10;
	}
}

//Thuat toan Flash Sort
void flashSort(int *a, int n, int *L)
{
	int k, m = n / 2;
	int nmin = 0, nmax = 0;
	for (long i = 0; i < n; i++)
	{
		if (a[i] < a[nmin])
			nmin = i;
		if (a[i] > a[nmax])
			nmax = i;
	}

	float c1 = ((float)(m - 1) / (a[nmax] - a[nmin]));
	float c2 = c1*a[nmin];

	for (int k = 0; k <= m; k++)
		L[k] = 0;

	for (int i = 0; i < n; i++)
	{
		k = (int)(c1*a[i] - c2);
		L[k] ++;
	}

	for (int k = 1; k <= m; k++)
		L[k] += L[k - 1];


	swap(a[0], a[nmax]);

	int nmove = 0, flash, hold;
	int j = 0;
	k = m - 1;
	while (nmove < n)
	{
		while (j > L[k] - 1)
		{
			j++;
			k = (int)(c1*a[j] - c2);
		}
		flash = a[j];
		while (j <= L[k] - 1)
		{
			k = (int)(c1*flash - c2);
			hold = a[L[k] - 1];
			a[L[k] - 1] = flash;
			L[k]--;
			flash = hold;
			nmove++;
		}
	}
	// Giai doan 3
	for (k = 1; k <= m; k++)
	{
		for (int i = L[k] - 2; i >= L[k - 1]; i--)
		{
			if (a[i + 1] < a[i])
			{
				hold = a[i];
				j = i;
				while (a[j + 1] < hold)
				{
					a[j] = a[j + 1];
					j++;
				}
				a[j] = hold;
			}
		}
	}
}

void main()
{
	//Tao mang random
	int n, k;
	cout << "Nhap n: ";
	cin >> n;
	cout << "Nhap k: ";
	cin >> k;
	int *tmp = new int[n];
	int *a = new int[n];
	random(n, tmp, k);
	//print(n, tmp);
	
	clock_t begin, end;
	///////O(N^2)//////
	
	//Thuat toan Bubble Sort
	copy(n, a, tmp);
	begin = clock();
	bubbleSort(a, n);
	end = clock();
	check(n, a);
	cout << "Bubble Sort: Time run: " << (double)(end - begin)*1000 / CLOCKS_PER_SEC << " ms" << endl;

	//Thuat toan Shaker Sort
	copy(n, a, tmp);
	begin = clock();
	shakerSort(a, n);
	end = clock();
	check(n, a);
	cout << "Shaker Sort: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;

	//Thuat toan Selection Sort
	copy(n, a, tmp);
	begin = clock();
	selectionSort(a, n);
	end = clock();
	check(n, a);
	cout << "Selection Sort: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;

	//Thuat toan Insertion Sort
	copy(n, a, tmp);
	begin = clock();
	insertionSort(a, n);
	end = clock();
	check(n, a);
	cout << "Insertion Sort: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;

	//Thuat toan Binary Insertion Sort
	copy(n, a, tmp);
	begin = clock();
	binaryInsertionSort(a, n);
	end = clock();
	check(n, a);
	cout << "Binary Insertion Sort: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;
	
	//Thuat toan Shell Sort
	copy(n, a, tmp);
	begin = clock();
	shellSort(a, n);
	end = clock();
	check(n, a);
	cout << "Shell Sort: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;

	///////O(NLOGN)//////

	cout << endl;

	//Thuat toan QuickSort
	copy(n, a, tmp);
	begin = clock();
	quickSort(a, 0, n - 1);
	end = clock();
	check(n, a);
	cout << "QuickSort: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;

	//Thuat toan qsort trong C
	copy(n, a, tmp);
	begin = clock();
	Qsort(a, n);
	end = clock();
	//print(n, a);
	cout << "QuickSort - C: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;

	//Thuat toan HeapSort
	copy(n, a, tmp);
	begin = clock();
	heapSort(n, a);
	end = clock();
	check(n, a);
	//print(n, a);
	cout << "HeapSort: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;

	//Thuat toan MergeSort
	copy(n, a, tmp);
	int *b = new int[n + 1];
	begin = clock();
	mergeSort(a, 0, n - 1, b);
	end = clock();
	check(n, a);
	delete[]b;
	cout << "MergeSort: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;

	///////O(N)//////

	cout << endl;

	//Thuat toan CoutingSort
	copy(n, a, tmp);
	int *f = new int[k+1];
	b = new int[n + 1];
	begin = clock();
	countingSort(n, a, f, b);
	end = clock();
	check(n, a);
	delete[]b;
	delete[]f;
	cout << "Counting Sort: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;
	
	//Thuat toan RadixSort
	copy(n, a, tmp);
	begin = clock();
	int *b = new int[n + 1];
	radixSort(a, n, b);
	end = clock();
	check(n, a);
	delete[]b;
	cout << "Radix Sort: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;
	
	//Thuat toan Flashort
	copy(n, a, tmp);
	begin = clock();
	int *f = new int[n/2+1];
	flashSort(a, n, f);
	end = clock();
	check(n, a);
	//print(n, a);
	cout << "Flash Sort: Time run: " << (double)(end - begin) * 1000 / CLOCKS_PER_SEC << " ms" << endl;
	delete[]f;

	_getch();
}

