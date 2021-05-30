#pragma once
#include "Node.h"
#include <fstream>
#include <iostream>

using namespace std;

class List
{
private:
	bool *_visited;
	int _itemCount;
	int _beginner;
	Node ** _map;
public:
	List();
	void Insert(int, int);
	void FindConnect();
	void DFS(int);
	~List();
};

