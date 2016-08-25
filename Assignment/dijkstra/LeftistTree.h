#pragma once
#include "Edge.h"

class LeftistTree
{
    private:
	Edge* root;
    public:
	LeftistTree();
	Edge* getRoot();
	void setRoot(Edge* root);
	Edge* Insert(Edge* a, Edge* b);
	Edge* Delete();
};
