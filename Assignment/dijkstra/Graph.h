#pragma once
#include "Edge.h"
#include "Node.h"

class Graph
{
    private:
	Node* m_pRoot;
    public:
	Graph();
	Node* getRoot();
	void MakeGraph(Edge* Edge);
};
