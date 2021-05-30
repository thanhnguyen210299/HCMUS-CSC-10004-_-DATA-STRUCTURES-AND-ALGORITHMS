#include <limits>
#include <queue>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "YenTopKShortestPathsAlg.h"
#include "DijkstraShortestPathAlg.h"
#include "ReadFile.h"
#include <conio.h>

using namespace std;

void createGraph(Graph &CostGraph, Graph &DurationGraph, int number_vertices, vector<link> lk)
{
	CostGraph.set_number_vertices(number_vertices);
	DurationGraph.set_number_vertices(number_vertices);

	for (int i = 0; i < lk.size(); i++)
	{
		CostGraph.add_link(lk[i].u, lk[i].v, lk[i].Cost);
		DurationGraph.add_link(lk[i].u, lk[i].v, lk[i].Duration);
	}

	CostGraph.setv();
	DurationGraph.setv();
}

void PrintOut(YenTopKShortestPathsAlg yenAlg, int k, string source, string destination, vector<string> cities, vector<Link> lk)
{
	if (!yenAlg.has_next())
	{
		cout << "Sorry.HPAir does not fly from " << source << " to " << destination << "." << endl;
		return;
	}

	int j = 0;
	while (yenAlg.has_next() && j < k)
	{
		++j;
		cout << "Route " << j << ": ";

		vector<int> path;

		yenAlg.next()->getPath(path);
		int size = path.size();
		int t = 0;
		while (t < size)
		{
			cout << FindCity(path[t], cities);
			t++;
			if (t < size)
				cout << " - ";
		}
		cout << endl;

		int sumCost = 0, sumDuration = 0;
		for (t = 1; t < size; t++)
			FindEdge(path[t - 1], path[t], lk, cities, sumCost, sumDuration);
		cout << "Total Cost .............$" << sumCost << endl;
		cout << "Total Duration ......" << sumDuration << " hours" << endl;
	}
}

void testYenAlg(vector<string> cities, vector<link> lk)
{
	Graph CostGraph, DurationGraph;
	createGraph(CostGraph, DurationGraph, cities.size(), lk);

	// Read Request File
	ifstream f("requestFile");

	string line, source, destination;
	int startPos, foundPos, n, k, s, d;

	getline(f, line);
	k = stoi(line.substr(0, line.length()));

	getline(f, line);
	n = stoi(line.substr(0, line.length()));

	for (int i = 0; i < n; i++)
	{
		cout << endl;
		getline(f, line);
		foundPos = line.find(',', 0);
		source = line.substr(0, foundPos);

		int pos = startPos = foundPos + 2;
		foundPos = line.find(' ', startPos);
		while (foundPos != string::npos && (line[foundPos + 1] > '9' || line[foundPos + 1] < '0'))
		{
			startPos = foundPos + 1;
			foundPos = line.find(' ', startPos);
		}
		destination = line.substr(pos, foundPos - pos);

		int type = stoi(line.substr(foundPos + 1, 1));

		cout << "Request is to fly from " << source << " to " << destination << "." << endl;
		s = FindID(source, cities);
		d = FindID(destination, cities);
		if (s == -1)
		{
			cout << "Sorry.HPAir does not serve " << source << "." << endl;
			continue;
		}

		if (d == -1)
		{
			cout << "Sorry.HPAir does not serve " << destination << "." << endl;
			continue;
		}

		if (type == 1)
		{
			YenTopKShortestPathsAlg yenAlg(CostGraph, CostGraph.get_vertex(s), CostGraph.get_vertex(d));
			PrintOut(yenAlg, k, source, destination, cities, lk);
		}
		if (type == 2)
		{
			YenTopKShortestPathsAlg yenAlg(DurationGraph, DurationGraph.get_vertex(s), DurationGraph.get_vertex(d));
			PrintOut(yenAlg, k, source, destination, cities, lk);
		}
	}
	return;
}

void main()
{
	vector<string> cities;
	ReadCityFile(cities);

	vector<Link> flights;
	ReadFlightFile(flights, cities);

	testYenAlg(cities, flights);
	_getch();
}
