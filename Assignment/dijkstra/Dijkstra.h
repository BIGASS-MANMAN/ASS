#pragma once
#include "LeftistTree.h"
#include "Graph.h"

class Dijkstra
{
    private:
	int** CostArray;
	Node* ShortPath;
	LeftistTree LFT;
	int COUNT;

    public:
	Dijkstra();
	int MakeShortPath(char From, char To, Node* GraphRoot);
	void MakeCostArr(Node* GraphRoot);
};
