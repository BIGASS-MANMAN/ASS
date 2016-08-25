#pragma once
#include "edge.h"
#include "node.h"

class graph
{
private:
	node* root;
public:
	graph();
	node* getRoot();
	void MakeGraph(edge* Edge);

};
