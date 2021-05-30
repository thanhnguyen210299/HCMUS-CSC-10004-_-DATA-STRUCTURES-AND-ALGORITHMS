#pragma once

#include <queue>
#include "DijkstraShortestPathAlg.h"
#include "YenTopKShortestPathsAlg.h"

using namespace std;

void YenTopKShortestPathsAlg::clear()
{
	m_nGeneratedPathNum = 0;
	m_mpDerivationVertexIndex.clear();
	m_vResultList.clear();
	m_quPathCandidates.clear();
}

void YenTopKShortestPathsAlg::_init()
{
	clear();
	if (m_pSourceVertex != NULL && m_pTargetVertex != NULL)
	{
		BasePath* pShortestPath = get_shortest_path(m_pSourceVertex, m_pTargetVertex);
		if (pShortestPath != NULL && pShortestPath->length() > 1)
		{
			m_quPathCandidates.insert(pShortestPath);
			m_mpDerivationVertexIndex[pShortestPath] = m_pSourceVertex;
		}
	}
}

BasePath* YenTopKShortestPathsAlg::get_shortest_path(BaseVertex* pSource, BaseVertex* pTarget)
{
	DijkstraShortestPathAlg dijkstra_alg(m_pGraph);
	return dijkstra_alg.get_shortest_path(pSource, pTarget);
}

bool YenTopKShortestPathsAlg::has_next()
{
	return !m_quPathCandidates.empty();
}

BasePath* YenTopKShortestPathsAlg::next()
{
	BasePath* cur_path = *(m_quPathCandidates.begin());

	m_quPathCandidates.erase(m_quPathCandidates.begin());
	m_vResultList.push_back(cur_path);

	int count = m_vResultList.size();

	BaseVertex* cur_derivation_pt = m_mpDerivationVertexIndex.find(cur_path)->second;
	vector<BaseVertex*> sub_path_of_derivation_pt;
	cur_path->SubPath(sub_path_of_derivation_pt, cur_derivation_pt);
	int sub_path_length = sub_path_of_derivation_pt.size();

	for (int i = 0; i<count - 1; ++i)
	{
		BasePath* cur_result_path = m_vResultList.at(i);
		vector<BaseVertex*> cur_result_sub_path_of_derivation_pt;

		if (!cur_result_path->SubPath(cur_result_sub_path_of_derivation_pt, cur_derivation_pt))
			continue;

		if (sub_path_length != cur_result_sub_path_of_derivation_pt.size())
			continue;

		bool is_equal = true;
		for (int i = 0; i<sub_path_length; ++i)
		{
			if (sub_path_of_derivation_pt.at(i) != cur_result_sub_path_of_derivation_pt.at(i))
			{
				is_equal = false;
				break;
			}
		}
		if (!is_equal)
			continue;

		BaseVertex* cur_succ_vertex = cur_result_path->GetVertex(sub_path_length + 1);
		m_pGraph->remove_edge(make_pair(cur_derivation_pt->getID(), cur_succ_vertex->getID()));
	}

	int path_length = cur_path->length();
	for (int i = 0; i<path_length - 1; ++i)
	{
		m_pGraph->remove_vertex(cur_path->GetVertex(i)->getID());
		m_pGraph->remove_edge(make_pair(cur_path->GetVertex(i)->getID(), cur_path->GetVertex(i + 1)->getID()));
	}

	DijkstraShortestPathAlg reverse_tree(m_pGraph);
	reverse_tree.get_shortest_path_flower(m_pTargetVertex);

	bool is_done = false;
	for (int i = path_length - 2; i >= 0 && !is_done; --i)
	{
		BaseVertex* cur_recover_vertex = cur_path->GetVertex(i);
		m_pGraph->recover_removed_vertex(cur_recover_vertex->getID());

		if (cur_recover_vertex->getID() == cur_derivation_pt->getID())
			is_done = true;

		BasePath* sub_path = reverse_tree.update_cost_forward(cur_recover_vertex);

		if (sub_path != NULL)
		{
			++m_nGeneratedPathNum;

			double cost = 0;
			reverse_tree.correct_cost_backward(cur_recover_vertex);

			vector<BaseVertex*> pre_path_list;
			for (int j = 0; j<path_length; ++j)
			{
				BaseVertex* cur_vertex = cur_path->GetVertex(j);
				if (cur_vertex->getID() == cur_recover_vertex->getID())
					break;
				else
				{
					cost += m_pGraph->get_original_edge_weight(cur_path->GetVertex(j), cur_path->GetVertex(1 + j));
					pre_path_list.push_back(cur_vertex);
				}
			}
			for (int j = 0; j<sub_path->length(); ++j)
				pre_path_list.push_back(sub_path->GetVertex(j));

			sub_path = new Path(pre_path_list, cost + sub_path->Weight());

			if (m_mpDerivationVertexIndex.find(sub_path) == m_mpDerivationVertexIndex.end())
			{
				m_quPathCandidates.insert(sub_path);
				m_mpDerivationVertexIndex[sub_path] = cur_recover_vertex;
			}
		}

		BaseVertex* succ_vertex = cur_path->GetVertex(i + 1);
		m_pGraph->recover_removed_edge(make_pair(cur_recover_vertex->getID(), succ_vertex->getID()));

		double cost_1 = m_pGraph->get_edge_weight(cur_recover_vertex, succ_vertex) + reverse_tree.get_start_distance_at(succ_vertex);

		if (reverse_tree.get_start_distance_at(cur_recover_vertex) > cost_1)
		{
			reverse_tree.set_start_distance_at(cur_recover_vertex, cost_1);
			reverse_tree.set_predecessor_vertex(cur_recover_vertex, succ_vertex);
			reverse_tree.correct_cost_backward(cur_recover_vertex);
		}
	}

	m_pGraph->recover_removed_edges();
	m_pGraph->recover_removed_vertices();

	return cur_path;
}

void YenTopKShortestPathsAlg::get_shortest_paths(BaseVertex* pSource, BaseVertex* pTarget, int top_k, vector<BasePath*>& result_list)
{
	m_pSourceVertex = pSource;
	m_pTargetVertex = pTarget;

	_init();
	int count = 0;
	while (has_next() && count <= top_k)
	{
		next();
		++count;
	}

	result_list.assign(m_vResultList.begin(), m_vResultList.end());
}
