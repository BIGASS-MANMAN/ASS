#pragma once
#include <iostream>
#include "edge.h"
class LeftistTree
{
private:
	edge* root;
public:
	LeftistTree();
	edge* getRoot();
	void setRoot(edge* root);
	edge* Insert(edge* a, edge* b);
	edge* Delete();

};