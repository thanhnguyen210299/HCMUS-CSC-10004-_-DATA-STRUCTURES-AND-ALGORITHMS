#include <stdio.h> 
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define edge pair<int,int>

class Graph 
{
private:
	vector<pair<float, edge>> G; // graph
	vector<pair<float, edge>> T; // mst
	int *parent;
	int V; // number of vertices/nodes in graph

	void AddWeightedEdge(int u, int v, float w);
	int find_set(int i);
	void union_set(int u, int v);
public:
	Graph();
	void kruskal();
	void print();
	void clear();
};


