#pragma once

class node;
class edge
{
private:
	int Bandwidth;
	int Cost;
	node* pFrom;
	node* pTo;
	edge* pNext;

	edge* Left, *Right;
	int Shortest;
public:
	edge();
	void setFrom(node* fromNode);
	void setTo(node* toNode);
	void setBandwidth(int Bandwidth);
	void setCost(int Cost);
	void setNext(edge* Next);

	node* getFrom();
	node* getTo();
	int getBandwidth();
	int getCost();
	edge* getNext();

	void setLeft(edge* left);
	void setRight(edge* right);
	edge* getLeft();
	edge* getRight();

	void setShort(int Shortest);
	int getShort();
};