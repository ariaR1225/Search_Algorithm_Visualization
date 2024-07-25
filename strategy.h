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
}