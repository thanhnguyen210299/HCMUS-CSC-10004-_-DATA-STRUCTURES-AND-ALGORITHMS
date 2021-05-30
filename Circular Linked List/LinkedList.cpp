#include<iostream>
#include <conio.h>
#include <time.h>

using namespace std;

struct Node
{
	int data;
	Node *next;
};

Node *newNode(int data)
{
	Node *temp = new Node;
	temp->next = temp;
	temp->data = data;
	return temp;
}

void Josephus(int n, int m)
{
	Node *head = newNode(1);

	Node *prev = head;
	for (int i = 2; i <= n; i++)
	{
		prev->next = newNode(i);
		prev = prev->next;
	}
	prev->next = head; 
	
	Node *ptr1 = head, *ptr2 = prev;
	while (ptr1->next != ptr1)
	{
		int count = 1;
		while (count != m)
		{
			ptr2 = ptr1;
			ptr1 = ptr1->next;
			count++;
		}

		ptr2->next = ptr1->next;
		Node *p = ptr1;
		ptr1 = ptr2->next;
		delete p;
	}

	cout << "The win is " << ptr1->data << endl;
}

void main()
{
	int n, k;
	cout << "Nhap n, k: ";
	cin >> n >> k;
	clock_t start, end;
	start = clock();
	Josephus(n, k);
	end = clock();
	cout << "Time: " << (end - start) * 1000 << " ms" << endl;

	_getch();
}