#include "GraphElements.h"
#include <map>
#include <set>

struct Link
{
	int u;
	int v;
	int FlightNumber;
	double Cost;
	double Duration;
};

typedef Link link;

#pragma once

using namespace std;

class Path : public BasePath
{
public:

	Path(const std::vector<BaseVertex*>& vertex_list, double weight) :BasePath(vertex_list, weight){}
};

class Graph
{
public:

	const static double DISCONNECT;

	typedef set<BaseVertex*>::iterator VertexPtSetIterator;
	typedef map<BaseVertex*, set<BaseVertex*>*>::iterator BaseVertexPt2SetMapIterator;

protected:

	map<BaseVertex*, set<BaseVertex*>*> m_mpFanoutVertices;
	map<BaseVertex*, set<BaseVertex*>*> m_mpFaninVertices;
	map<int, double> m_mpEdgeCodeWeight;
	vector<BaseVertex*> m_vtVertices;
	int m_nEdgeNum;
	int m_nVertexNum;

	map<int, BaseVertex*> m_mpVertexIndex;

	set<int> m_stRemovedVertexIds;
	set<pair<int, int> > m_stRemovedEdge;

public:

	Graph(const Graph& rGraph);
	Graph() { clear(); }
	~Graph(void);

	void clear();

	void set_number_vertices(const int& nVertices);
	void add_link(const int& s, const int& d, const double& weight);
	void setv();

	BaseVertex* get_vertex(int node_id);

	int get_edge_code(const BaseVertex* start_vertex_pt, const BaseVertex* end_vertex_pt) const;
	set<BaseVertex*>* get_vertex_set_pt(BaseVertex* vertex_, map<BaseVertex*, set<BaseVertex*>*>& vertex_container_index);

	double get_original_edge_weight(const BaseVertex* source, const BaseVertex* sink);

	double get_edge_weight(const BaseVertex* source, const BaseVertex* sink);
	void get_adjacent_vertices(BaseVertex* vertex, set<BaseVertex*>& vertex_set);
	void get_precedent_vertices(BaseVertex* vertex, set<BaseVertex*>& vertex_set);

	void remove_edge(const pair<int, int> edge)
	{
		m_stRemovedEdge.insert(edge);
	}

	void remove_vertex(const int vertex_id)
	{
		m_stRemovedVertexIds.insert(vertex_id);
	}

	void recover_removed_edges()
	{
		m_stRemovedEdge.clear();
	}

	void recover_removed_vertices()
	{
		m_stRemovedVertexIds.clear();
	}

	void recover_removed_edge(const pair<int, int> edge)
	{
		m_stRemovedEdge.erase(m_stRemovedEdge.find(edge));
	}

	void recover_removed_vertex(int vertex_id)
	{
		m_stRemovedVertexIds.erase(m_stRemovedVertexIds.find(vertex_id));
	}

};
