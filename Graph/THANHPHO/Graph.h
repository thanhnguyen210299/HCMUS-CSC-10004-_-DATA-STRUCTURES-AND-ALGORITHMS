#include <math.h>
#include <fstream>

using namespace std;

#define MAX_INT 10e9

struct Vertice
{
	float _x;
	float _y;
	int _parent;
	float _value;
	bool _visited;
};

class Graph
{
private:
	Vertice *list;
	int n;
	float **map;

	void CreateDistance();
public:
	Graph();
	void Prim();
	void PrintResult();
	void clear();
};
