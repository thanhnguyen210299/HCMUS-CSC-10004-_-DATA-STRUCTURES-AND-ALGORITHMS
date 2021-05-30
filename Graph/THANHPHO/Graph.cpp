#include "Graph.h"

//////////////////////////////////Helper Function/////////////////////////////////////
float Distance(Vertice u, Vertice v)
{
	return sqrt((u._x - v._x) * (u._x - v._x) + (u._y - v._y) * (u._y - v._y));
}

////////////////////////////////////////Private//////////////////////////////////
void Graph::CreateDistance()
{
	map = new float*[n];
	for (int i = 0; i < n; i++)
		map[i] = new float[n];

	for (int i = 0; i < n; i++)
	{
		map[i][i] = 0;
		for (int j = i + 1; j < n; j++)
		{
			float tmp = Distance(list[i], list[j]);
			map[i][j] = tmp;
			map[j][i] = tmp;
		}
	}
}

///////////////////////////////////////////////////////Public///////////////////////////////////////////
Graph::Graph()
{
	ifstream fin("THANHPHO.INP");
	fin >> n;

	list = new Vertice[n];

	for (int i = 0; i < n; i++)
	{
		fin >> list[i]._x >> list[i]._y;
		list[i]._parent = -1;
		list[i]._value = MAX_INT;
		list[i]._visited = false;
	}

	fin.close();

	CreateDistance();
}

void Graph::Prim()
{

	int EdgeCount = 0, u;
	float min;
	list[0]._value = 0;

	for (EdgeCount = 0; EdgeCount < n; EdgeCount++)
	{
		min = MAX_INT;
		for (int i = 0; i < n; i++)
			if (!list[i]._visited && list[i]._value < min)
			{
				min = list[i]._value;
				u = i;
			}

		list[u]._visited = true;

		for (int v = 0; v < n; v++)
			if (map[u][v] < list[v]._value && u != v & !list[v]._visited)
			{
				list[v]._parent = u;
				list[v]._value = map[u][v];
			}
	}
}


void Graph::PrintResult()
{
	ofstream fout("THANHPHO.OUT");

	float sum = 0;
	int u;
	for (int i = 0; i < n; i++)
		sum += list[i]._value;

	fout << n - 1 << " " << sum << endl;
	for (int v = 1; v < n; v++)
	{
		u = list[v]._parent;
		fout << list[u]._x << " " << list[u]._y << " " << list[v]._x << " " << list[v]._y << endl;
	}

	fout.close();
}

void Graph::clear()
{
	for (int i = 0; i < n; i++)
		delete[] map[i];
	delete[] map;
	delete[] list;
}
