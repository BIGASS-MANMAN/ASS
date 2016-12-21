#pragma once

#include "Node.h"
#include <stdlib.h>

class BST
{
    private:
	Node* pRoot;

    public:
	BST();
	void setRoot(Node* Root);
	Node* getRoot();
	Node* Insert(int value);
	int Delete(int value);
	char* traversal(Node* pCur, char* arr);
};

