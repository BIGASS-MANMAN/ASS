#include "node.h"

node::node()
{
	ID = '\0';
	pNext = '\0';
	pEdge = '\0';
}
void node::setID(char id)
{
	ID = id;
}
void node::setIndex(int Index)
{
	index = Index;
}
void node::setNext(node* Next)
{
	pNext = Next;
}
void node::setEdge(edge* Edge)
{
	pEdge = Edge;
}

char node::getID()
{
	return ID;
}
int node::getIndex()
{
	return index;
}
node* node::getNext()
{
	return pNext;
}
edge* node::getEdge()
{
	return pEdge;
}