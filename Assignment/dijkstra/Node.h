#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Edge.h"

using namespace std;

class Node{
    private:
	char m_ID;
	int m_Index;
	Node* m_pNext;
	Edge* m_pEdge;
    public:
	Node();
	void setID(char ID);
	void setIndex(int Index);
	void setNext(Node* Next);
	void setEdge(Edge* Edge);

	char getID();
	int getIndex();
	Node* getNext();
	Edge* getEdge();
}
