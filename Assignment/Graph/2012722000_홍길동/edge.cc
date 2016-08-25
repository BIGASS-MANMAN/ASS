#include "node.h"
#include "edge.h"

edge::edge()
{
	pFrom = '\0';
	pTo = '\0';
	Bandwidth = '\0';
	Cost = '\0';
	pNext = '\0';
}
void edge::setFrom(node* fromNode)
{
	pFrom = fromNode;
}
void edge::setTo(node* toNode)
{
	pTo = toNode;
}
void edge::setBandwidth(int bandwidth)
{
	Bandwidth = bandwidth;
}
void edge::setCost(int cost)
{
	Cost = cost;
}
void edge::setNext(edge* Next)
{
	pNext = Next;
}

node* edge::getFrom()
{
	return pFrom;
}
node* edge::getTo()
{
	return pTo;
}
int edge::getBandwidth()
{
	return Bandwidth;
}
int edge::getCost()
{
	return Cost;
}
edge* edge::getNext()
{
	return pNext;
}

void edge::setLeft(edge* left)
{
	Left = left;
}
void edge::setRight(edge* right)
{
	Right = right;
}
void edge::setShort(int shortest)
{
	Shortest = shortest;
}
edge* edge::getLeft()
{
	return Left;
}
edge* edge::getRight()
{
	return Right;
}
int edge::getShort()
{
	return Shortest;
}