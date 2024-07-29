#pragma once

#include <queue>
#include<cmath>
#include "grid_map.h"

using std::priority_queue, std::pair;

namespace NAVIGATION
{
	enum DistType // distance type
	{
		Euclidean,
		Manhattan,
		Chebyshev
	};

	enum AlgoType
	{
		Dijkstra,
		BFS,
		AStar
	};

	class StrategyBase
	{
	public:
		virtual bool search(const unique_ptr<GridMapBase>& map, vector<Node*>& result_nodes) = 0;
	};

	class AStar : public StrategyBase
	{
	public:
		AStar(const int& _dist_type, const int& _algo_type);
		bool search(const unique_ptr<GridMapBase>& map, vector<Node*>& result_nodes) override;
		int heuristicDist(const Node& node1, const Node& node2);
		void calcCost(const Node& current_node, Node& next_node, const Node& end_node);
		void printResult(const vector<Node*>& result_nodes);
		void drawNodeStep(Node* const start, Node* const end, Node* const node, const int& time);
		void drawResult(Node* const start, Node* const end, const vector<Node*>& result_nodes);

	public:
		priority_queue<Node> open_queue; // no pointer, auto push min top , BST
		unordered_set<Node*> open_set; // quick search, sync with open_queue
		unordered_set<Node*> close_set; // searched nodes
		
		int dist_type = DistType::Manhattan;
		int algo_type = AlgoType::AStar;
		int path_len = 0;
		int step_len = 0;

	};

}