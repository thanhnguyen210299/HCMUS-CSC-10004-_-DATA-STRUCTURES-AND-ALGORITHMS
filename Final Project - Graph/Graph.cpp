#include <limits>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Graph.h"

const double Graph::DISCONNECT = (numeric_limits<double>::max)();

Graph::Graph(const Graph& graph)
{
	m_nVertexNum = graph.m_nVertexNum;
	m_nEdgeNum = graph.m_nEdgeNum;
	m_vtVertices.assign(graph.m_vtVertices.begin(), graph.m_vtVertices.end());
	m_mpFaninVertices.insert(graph.m_mpFaninVertices.begin(), graph.m_mpFaninVertices.end());
	m_mpFanoutVertices.insert(graph.m_mpFanoutVertices.begin(), graph.m_mpFanoutVertices.end());
	m_mpEdgeCodeWeight.insert(graph.m_mpEdgeCodeWeight.begin(), graph.m_mpEdgeCodeWeight.end());
	m_mpVertexIndex.insert(graph.m_mpVertexIndex.begin(), graph.m_mpVertexIndex.end());
}

Graph::~Graph(void)
{
	clear();
}

void Graph::setv()
{
	m_nVertexNum = m_vtVertices.size();
	m_nEdgeNum = m_mpEdgeCodeWeight.size();
}


void Graph::set_number_vertices(const int& nVertices)
{
	m_nVertexNum = nVertices;
}

void Graph::add_link(const int& s, const int& d, const double& weight)
{
	BaseVertex* start_vertex_pt = get_vertex(s);
	BaseVertex* end_vertex_pt = get_vertex(d);

	m_mpEdgeCodeWeight[get_edge_code(start_vertex_pt, end_vertex_pt)] = weight;

	get_vertex_set_pt(end_vertex_pt, m_mpFaninVertices)->insert(start_vertex_pt);
	get_vertex_set_pt(start_vertex_pt, m_mpFanoutVertices)->insert(end_vertex_pt);
}

BaseVertex* Graph::get_vertex(int node_id)
{
	if (m_stRemovedVertexIds.find(node_id) != m_stRemovedVertexIds.end())
		return NULL;
	else
	{
		BaseVertex* vertex_pt = NULL;
		const map<int, BaseVertex*>::iterator pos = m_mpVertexIndex.find(node_id);

		if (pos == m_mpVertexIndex.end())
		{
			int vertex_id = m_vtVertices.size();
			vertex_pt = new BaseVertex();
			vertex_pt->setID(node_id);
			m_mpVertexIndex[node_id] = vertex_pt;

			m_vtVertices.push_back(vertex_pt);
		}
		else
			vertex_pt = pos->second;

		return vertex_pt;
	}
}

void Graph::clear()
{
	m_nEdgeNum = 0;
	m_nVertexNum = 0;

	for (map<BaseVertex*, set<BaseVertex*>*>::const_iterator pos = m_mpFaninVertices.begin(); pos != m_mpFaninVertices.end(); ++pos)
		delete pos->second;

	m_mpFaninVertices.clear();

	for (map<BaseVertex*, set<BaseVertex*>*>::const_iterator pos = m_mpFanoutVertices.begin(); pos != m_mpFanoutVertices.end(); ++pos)
		delete pos->second;
	m_mpFanoutVertices.clear();
	m_mpEdgeCodeWeight.clear();

	for_each(m_vtVertices.begin(), m_vtVertices.end(), DeleteFunc<BaseVertex>());
	m_vtVertices.clear();
	m_mpVertexIndex.clear();

	m_stRemovedVertexIds.clear();
	m_stRemovedEdge.clear();
}

int Graph::get_edge_code(const BaseVertex* start_vertex_pt, const BaseVertex* end_vertex_pt) const
{
	return start_vertex_pt->getID()*m_nVertexNum + end_vertex_pt->getID();
}


set<BaseVertex*>* Graph::get_vertex_set_pt(BaseVertex* vertex_, map<BaseVertex*, set<BaseVertex*>*>& vertex_container_index)
{
	BaseVertexPt2SetMapIterator pos = vertex_container_index.find(vertex_);

	if (pos == vertex_container_index.end())
	{
		set<BaseVertex*>* vertex_set = new set<BaseVertex*>();
		pair<BaseVertexPt2SetMapIterator, bool> ins_pos = vertex_container_index.insert(make_pair(vertex_, vertex_set));

		pos = ins_pos.first;
	}

	return pos->second;
}


double Graph::get_edge_weight(const BaseVertex* source, const BaseVertex* sink)
{
	int source_id = source->getID();
	int sink_id = sink->getID();

	if (m_stRemovedVertexIds.find(source_id) != m_stRemovedVertexIds.end() || m_stRemovedVertexIds.find(sink_id) != m_stRemovedVertexIds.end() || m_stRemovedEdge.find(make_pair(source_id, sink_id)) != m_stRemovedEdge.end())
		return DISCONNECT;
	else
		return get_original_edge_weight(source, sink);
}


void Graph::get_adjacent_vertices(BaseVertex* vertex, set<BaseVertex*>& vertex_set)
{
	int starting_vt_id = vertex->getID();

	if (m_stRemovedVertexIds.find(starting_vt_id) == m_stRemovedVertexIds.end())
	{
		set<BaseVertex*>* vertex_pt_set = get_vertex_set_pt(vertex, m_mpFanoutVertices);
		for (set<BaseVertex*>::const_iterator pos = (*vertex_pt_set).begin(); pos != (*vertex_pt_set).end(); ++pos)
		{
			int ending_vt_id = (*pos)->getID();
			if (m_stRemovedVertexIds.find(ending_vt_id) != m_stRemovedVertexIds.end() || m_stRemovedEdge.find(make_pair(starting_vt_id, ending_vt_id)) != m_stRemovedEdge.end())
				continue;

			vertex_set.insert(*pos);
		}
	}
}

void Graph::get_precedent_vertices(BaseVertex* vertex, set<BaseVertex*>& vertex_set)
{
	if (m_stRemovedVertexIds.find(vertex->getID()) == m_stRemovedVertexIds.end())
	{
		int ending_vt_id = vertex->getID();
		set<BaseVertex*>* pre_vertex_set = get_vertex_set_pt(vertex, m_mpFaninVertices);
		for (set<BaseVertex*>::const_iterator pos = (*pre_vertex_set).begin(); pos != (*pre_vertex_set).end(); ++pos)
		{
			int starting_vt_id = (*pos)->getID();
			if (m_stRemovedVertexIds.find(starting_vt_id) != m_stRemovedVertexIds.end() || m_stRemovedEdge.find(make_pair(starting_vt_id, ending_vt_id)) != m_stRemovedEdge.end())
				continue;

			vertex_set.insert(*pos);
		}
	}
}

double Graph::get_original_edge_weight(const BaseVertex* source, const BaseVertex* sink)
{
	map<int, double>::const_iterator pos =
		m_mpEdgeCodeWeight.find(get_edge_code(source, sink));

	if (pos != m_mpEdgeCodeWeight.end())
		return pos->second;
	else
		return DISCONNECT;
}