#pragma once
#include <iostream>
#include <graphics.h>
#include <ctime>
#include <assert.h>
#include <vector>
#include <unordered_set>

#include "config.h"


using std::cout, std::endl;
using std::vector, std::unordered_set, std::unique_ptr, std::make_unique;

namespace NAVIGATION
{
	enum NodeType
	{
		normal,
		start,
		end,
		obs,
		way_pt,
	};

	class Node
	{
	public:
		Node() = default;
		Node(const int& r, const int& c, const int& type = NodeType::normal); // row, col, type
		void drawNode() const;

	public:
		int row = 0; //row in map
		int col = 0; // col in map

		int f = 0; // local total cost
		int g = 0; // total cost from start
		int h = 0; // total cost till end

		int node_type = NodeType::normal;
		Node* parent_node = nullptr;
	};

	class GridMapBase // parent
	{
	public:
		bool GridMapInit(const Node& start, const Node& end);
		void printMap(); // console
		void drawMap(); // viz
		bool outOfMap(const Node& node);
		virtual void addObs() = 0;

	public:
		vector<vector<Node>> grid_map;
		Node* start_node = nullptr;
		Node* end_node = nullptr;
		unordered_set<Node*> obs_nodes; // hash table: fast searsh
	};

	class GridMap : public GridMapBase
	{
	public:
		GridMap(const Node& start, const Node& end);
		void addObs() override;
	};
} // end of namespace NAVIGATION