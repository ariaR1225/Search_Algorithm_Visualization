#include "grid_map.h"

namespace NAVIGATION
{
	Node::Node(const int& r, const int& c, const int& type)
		:row(r), col(c), node_type(type)
	{

	}

	void Node::drawNode() const
	{
		int left = ORIX + col * LEN;
		int right = left + LEN;
		int top = ORIY + row * LEN;
		int bottom = top + LEN;
		fillrectangle(left, top, right, bottom);
	}

	bool GridMapBase::GridMapInit(const Node& start, const Node& end)
	{
		if (outOfMap(start) || outOfMap(end))
		{
			cout << "invalid statr or end" << endl;
			return false;
		}

		// build map
		for (int i = 0; i < ROWS; i++)
		{
			vector<Node> temp_row;

			for (int j = 0; j < COLS; j++)
			{
				Node temp_node(i, j);
				temp_row.emplace_back(temp_node);
			}
			grid_map.emplace_back(temp_row);
		}

		// update start & end
		grid_map[start.row][start.col].node_type = NodeType::start;
		grid_map[end.row][end.col].node_type = NodeType::end;
		start_node = &grid_map[start.row][start.col];
		end_node = &grid_map[end.row][end.col];
		return true;
	}

	void GridMapBase::printMap()
	{
		cout << "Rows: " << ROWS << ", ColS: " << COLS << endl;
		cout << "start: [" << start_node->row << "," << start_node->col << "]\n" << 
			"end: [" << end_node->row << "," << end_node->col << "]" << endl;

		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				if (grid_map[i][j].node_type == NodeType::normal)
				{
					cout << "  ";
				}
				else
				{
					cout << grid_map[i][j].node_type << " ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	void GridMapBase::drawMap()
	{
		setbkcolor(WHITE);
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 1);
		cleardevice();

		BeginBatchDraw();

		// normal
		setfillcolor(WHITE);
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++)
			{
				grid_map[i][j].drawNode();
			}
		}

		// start
		setfillcolor(RED);
		start_node->drawNode();

		// end
		setfillcolor(BLUE);
		end_node->drawNode();

		// obs
		setfillcolor(BROWN);
		for (const auto& obs_node : obs_nodes) {
			obs_node->drawNode();
		}
			

		EndBatchDraw();
	}

	bool GridMapBase::outOfMap(const Node& node)
	{
		return (node.col < 0 || node.col >= COLS || node.row < 0 || node.row >= ROWS);
	}

	GridMap::GridMap(const Node& start, const Node& end)
	{
		assert(GridMapInit(start, end));
		addObs();
		printMap();
		drawMap();
	}

	void GridMap::addObs()
	{
		Node* temp_node;
		for (int i = 10; i < 35; i++)
		{
			temp_node = &grid_map[10][i];
			obs_nodes.insert(temp_node);
			temp_node->node_type = NodeType::obs;
		}

		for (int i = 10; i < 35; i++)
		{
			temp_node = &grid_map[34][i];
			obs_nodes.insert(temp_node);
			temp_node->node_type = NodeType::obs;
		}

		for (int i = 10; i < 35; i++)
		{
			temp_node = &grid_map[i][35];
			obs_nodes.insert(temp_node);
			temp_node->node_type = NodeType::obs;
		}
	}
}