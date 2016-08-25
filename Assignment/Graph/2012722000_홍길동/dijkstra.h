#pragma once
#include "edge.h"
#include "node.h"
#include "LeftistTree.h"
#include "graph.h"

class dijkstra
{
private:
	int** CostArray;
	node* ShortPath;
	LeftistTree LFT;
	int COUNT;

public:
	dijkstra();
	int MakeShortPath(char From, char To, node* GraphRoot);
	void MakeCostArr(node* GraphRoot);


};