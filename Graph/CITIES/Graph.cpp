#include "Graph.h"

/////////////////////////Helper Function//////////////////////////////

struct Point
{
	int _id;
	float _x;
	float _y;
};

float Distance(Point u, Point v)
{
	return sqrt((u._x - v._x) * (u._x - v._x) + (u._y - v._y) * (u._y - v._y));
}

////////////////////////////////////Private//////////////////////////////////////////////
void Graph::AddWeightedEdge(int u, int v, float w)
{
	G.push_back(make_pair(w, edge(u, v)));
}

int Graph::find_set(int i) 
{
	if (i == parent[i])
		return i;
	else
		return find_set(parent[i]);
}

void Graph::union_set(int u, int v)
{
	parent[u] = parent[v];
}

/////////////////////////////////////////////////Public/////////////////////////////////////////
Graph::Graph() 
{
	ifstream fin("cities.txt");
	fin >> V;

	Point *list = new Point[V];

	for (int i = 0; i < V; i++)
		fin >> list[i]._id >> list[i]._x >> list[i]._y;

	fin.close();

	parent = new int[V];

	for (int i = 0; i < V; i++)
		parent[i] = i;

	G.clear();
	T.clear();

	Point u, v;
	for (int i = 0; i < V; i++)
	{
		for (int j = i + 1; j < V; j++)
		{
			u = list[i];
			v = list[j];
			float tmp = Distance(u, v);

			AddWeightedEdge(u._id - 1, v._id - 1, tmp);
			AddWeightedEdge(v._id - 1, u._id - 1, tmp);
		}
	}

	delete[] list;
}

void Graph::clear()
{
	delete[] parent;
}

void Graph::kruskal() 
{
	int i, uRep, vRep;
	sort(G.begin(), G.end());

	for (i = 0; i < G.size(); i++) 
	{
		uRep = find_set(G[i].second.first);
		vRep = find_set(G[i].second.second);
		if (uRep != vRep) 
		{
			T.push_back(G[i]);
			union_set(uRep, vRep);
		}
	}
}

void Graph::print()
{
	ofstream fout("result.txt");

	float sum = 0;
	for (int i = 0; i < T.size(); i++)
		sum += T[i].first;
	fout << sum << endl;

	for (int i = 0; i < T.size(); i++)
	{
		fout << T[i].second.first + 1 << " " << T[i].second.second + 1 << " " << T[i].first << endl;
	}

	fout.close();
}
