#include "strategy.h"

namespace NAVIGATION
{
	void delay(const int& time)
	{
		clock_t now = clock();
		while (clock() - now < time){}
	}

	AStar::AStar(const int& _dist_type, const int& _algo_type) : dist_type(_dist_type), algo_type(_algo_type)
	{

	}

	bool AStar::search(const unique_ptr<GridMapBase>& map, vector<Node*>& result_nodes)
	{

	}

	int AStar::heuristicDist(const Node& node1, const Node& node2)
	{
		if (dist_type = DistType::Euclidean)
		{
			return hypot(node1.col - node2.col, node1.row - node2.row) * LEN;
		}

		else if (dist_type = DistType::Manhattan)
		{
			return(abs(node1.col - node2.col) + abs(node1.row - node2.row)) * LEN;

		}
		else if (dist_type == DistType::Chebyshev)
		{
			int len_col = abs(node1.col - node2.col);
			int len_row = abs(node1.row - node2.row);
			int x_step = min(len_col, len_row);
			int res_step = abs(len_col - len_row);
			return x_step * XLEN + res_step * LEN;
		}
		return 0;
	}

	void AStar::calcCost(const Node& current_node, Node& next_node, const Node& end_node)
	{
		next_node.g = current_node.g + step_len;
		next_node.h = heuristicDist(next_node, end_node);
		if (algo_type == AlgoType::Dijkstra)
		{
			next_node.h = 0;
		}
		else if (algo_type == AlgoType::BFS)
		{
			next_node.g = 0;
		}
		next_node.f = next_node.g + next_node.h;
		cout << "f = " << next_node.f << ", g = " << next_node.g << ", h = " << next_node.h << endl;
	}

	void AStar::printResult(const vector<Node*>& result_nodes)
	{
		cout << "num of waypoints: " << result_nodes.size() <<endl;
		cout << "num of search: " << close_set.size() <<endl;
		cout << "path len: " << path_len <<endl;
		for (const auto& result_node : result_nodes)
		{
			cout << "(" << result_node->row << ", " << result_node->col << ")" << endl;
			cout << "f = " << result_node->f << ", g = " << result_node->g << ", h = " << result_node->h << endl;
		}
	}

	void AStar::drawNodeStep(Node* const start, Node* const end, Node* const node, const int& time)
	{
		if (node != start && node != end)
		{
			BeginBatchDraw();
			node->drawNode();
			delay(time);
			EndBatchDraw();
		}
	}

	void AStar::drawResult(Node* const start, Node* const end, const vector<Node*>& result_nodes)
	{
		setfillcolor(GREEN);
		for (const auto& result_node : result_nodes)
		{
			drawNodeStep(start, end, result_node, RESULT_DELAY);
		}
	}

}