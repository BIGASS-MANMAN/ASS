#pragma once

class Node;
class Edge
{
    private:
	int m_Bandwidth;
	int m_Cost;
	Node* m_pFrom;
	Node* m_pTo;
	Edge* m_pNext;

	Edge* m_Left, *m_Right;
	int m_Shortest;
    public:
	Edge();
	void setFrom(Node* From);
	void setTo(Node* To);
	void setBandwidth(int Bandwidth);
	void setCost(int Cost);
	void setNext(Edge* Next);

	Node* getFrom();
	Node* getTo();
	int getBandwidth();
	int getCost();
	Edge* getNext();

	void setLeft(Edge* Left);
	void setRight(Edge* Right);
	Edge* getLeft();
	Edge* getRight();

	void setShort(int Shortest);
	int getShort();
};
