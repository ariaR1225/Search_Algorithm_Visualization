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
		// init start
		open_queue.emplace(*map->start_node);
		open_set.insert(map->start_node);
		Node* current_node = map->start_node; // ptr to start

		// set move direction 
		vector<pair<int, int>> move_step = // use pair for direction
		{
			pair <int, int>(0, 1),
			pair <int, int>(0, -1),
			pair <int, int>(1, 0),
			pair <int, int>(-1, 0),
			pair <int, int>(-1, 1),
			pair <int, int>(-1, -1),
			pair <int, int>(1, -1),
			pair <int, int>(1, 1),
		};

		// search
		while (!open_queue.empty())
		{
			// current node
			int r = open_queue.top().row;
			int c = open_queue.top().col;
			current_node = &map->grid_map[r][c];
			cout << "CURRENT NODE: f = " << current_node->f << ", g = " << current_node->g << ", h = " << current_node->h << endl;

			// draw close
			setfillcolor(YELLOW);
			drawNodeStep(map->start_node, map->end_node, current_node, SEARCH_DELAY);

			open_queue.pop();
			open_set.erase(current_node);
			close_set.insert(current_node);

			// reach end node
			if (current_node == map->end_node)
			{
				path_len = current_node->g;

				// store to result_nodes from current to start
				while (current_node->parent_node) // start has empty parent_node
				{
					current_node->node_type = NodeType::way_pt;
					result_nodes.emplace_back(current_node);
					current_node = current_node->parent_node;
				}
				reverse(result_nodes.begin(), result_nodes.end());
				cout << "Successful!" << endl;

				// recover start and end node type
				map->start_node->node_type = NodeType::start;
				map->end_node->node_type = NodeType::end;

				// print
				printResult(result_nodes);
				map->printMap();
				drawResult(map->start_node, map->end_node, result_nodes);
				return true;
			}

			// search
			for (auto i = move_step.begin(); i != move_step.end(); i++)
			{
				Node temp_node(r + i->first, c + i->second);
				if (map->outOfMap(temp_node)) // skip if out of bound
				{
					continue;
				}

				Node* next_node = &map->grid_map[temp_node.row][temp_node.col]; // create next node if node out of bound
				if (close_set.find(next_node) != close_set.end() // if is in close_set (already visited)
					|| map->obs_nodes.find(next_node) != map->obs_nodes.end()) // or in obs
				{
					continue; // skip
				}

				step_len = abs(i->first) == abs(i->second) ? XLEN : LEN; // either side or diagonal
				if (open_set.find(next_node) != open_set.end()) // already in open
				{
					if (current_node->g + step_len < next_node->g)
					{
						calcCost(*current_node, *next_node, *map->end_node);
						next_node->parent_node = current_node;
					}
				}
				else // not in open, add to open
				{
					calcCost(*current_node, *next_node, *map->end_node);
					next_node->parent_node = current_node;
					open_queue.emplace(*next_node);
					open_set.insert(next_node);

					// draw open
					setfillcolor(LIGHTCYAN);
					drawNodeStep(map->start_node, map->end_node, current_node, SEARCH_DELAY);
				}
			}

		}

		// fail to search
		cout << "Failed!" << endl;
		drawResult(map->start_node, map->end_node, result_nodes);
		return false;
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
		cout << "COST: f = " << next_node.f << ", g = " << next_node.g << ", h = " << next_node.h << endl;
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