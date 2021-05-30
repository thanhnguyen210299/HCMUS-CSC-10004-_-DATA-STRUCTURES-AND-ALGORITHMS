#include "List.h"

List::List()
{
	ifstream fin("SARS.INP");

	fin >> _itemCount >> _beginner;

	_map = new Node *[_itemCount + 1];
	_visited = new bool[_itemCount + 1];

	int k, x;
	for (int i = 1; i <= _itemCount; i++)
	{
		_map[i] = NULL;
		_visited[i] = false;

		fin >> k;
	
		if (k != 0)
			for (int j = 1; j <= k; j++)
			{
				fin >> x;
				Insert(i, x);
			}
	}

	fin.close();
}
void List::Insert(int id, int value)
{
	Node * k = new Node(value);

	if (_map[id] == NULL)
	{
		_map[id] = k;
		return;
	}

	Node * tmp = _map[id];
	Node * prev = NULL;
	while (tmp != NULL)
	{
		if (tmp->getValue() == value)
			return;
		prev = tmp;
		tmp = tmp->getNext();
	}

	if (tmp == NULL)
		prev->setNext(k);
}

void List::DFS(int u)
{
	_visited[u] = true; // đánh dấu đỉnh u đã đi qua
	for (Node * v = _map[u]; v; v = v->getNext()) // với mỗi đỉnh v kề với u
		if (!_visited[v->getValue()]) // nếu v chưa đánh dấu, tới thăm đỉnh v
			DFS(v->getValue());
}

void List::FindConnect()
{
	ofstream fout("SARS.out");

	DFS(_beginner);
	
	int count = 0;
	for (int i = 1; i <= _itemCount; i++)
		if (_visited[i])
			count++;
	fout << count << endl;

	for (int i = 1; i <= _itemCount; i++)
		if (_visited[i])
			fout << i << " ";

	fout.close();
}

List::~List()
{
	delete[] _map;
	delete[] _visited;
}
