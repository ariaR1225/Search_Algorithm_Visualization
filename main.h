#pragma once
#include "strategy.h"

namespace NAVIGATION
{
	class Navigate
	{
	public:
		Navigate();
		bool process(const int& _dist_type, const int& algo_type);

	public:
		vector<Node*> result_nodes;
		unique_ptr<GridMapBase> grid_map_ptr;
		unique_ptr<StrategyBase> strategy_ptr;
	};
}