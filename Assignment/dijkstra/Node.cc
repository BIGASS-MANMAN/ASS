#include "Node.h"

Node::node()
{
    m_ID = '\0';
    m_Index = 0;
    m_pNext = '\0';
    m_pEdge = '\0';
}
void Node::setID(char ID)
{
	m_ID = ID;
}
void Node::setIndex(int Index)
{
	m_Index = Index;
}
void Node::setNext(node* Next)
{
	m_pNext = Next;
}
void Node::setEdge(edge* Edge)
{
	m_pEdge = Edge;
}

char Node::getID()
{
	return m_ID;
}
int Node::getIndex()
{
	return m_Index;
}
Node* node::getNext()
{
	return m_pNext;
}
edge* Node::getEdge()
{
	return m_pEdge;
}
