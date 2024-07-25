#include "main.h"
using namespace NAVIGATION;


int main()
{
	initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE); //init easyX

	Node start_node(6, 5, NodeType::start);
	Node end_node(28, 40, NodeType::end);
	unique_ptr<GridMapBase> grid_map_ptr = make_unique<GridMap>(start_node, end_node);

	system("pause");
	closegraph(); //close window
	return 0;
}