#include "main.h"
// using namespace NAVIGATION;

namespace NAVIGATION
{
	Navigate::Navigate()
	{
		Node start_node(6, 5, NodeType::start);
		Node end_node(28, 40, NodeType::end);
		grid_map_ptr = make_unique<GridMap>(start_node, end_node);
		system("pause");
	}

	bool Navigate::process(const int& _dist_type, const int& _algo_type)
	{
		strategy_ptr = make_unique<AStar>(_dist_type, _algo_type);
		return strategy_ptr->search(grid_map_ptr, result_nodes);
	}
}

int main()
{
	initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE); //init easyX

	unique_ptr<NAVIGATION::Navigate> navigate_ptr = make_unique<NAVIGATION::Navigate>();
	if (navigate_ptr->process(NAVIGATION::DistType::Manhattan, NAVIGATION::AlgoType::Astar))
	{
		cout << "Navigation complete" << endl;
	}

	system("pause");
	closegraph(); //close window
	return 0;
}