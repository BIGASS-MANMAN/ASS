#include "Node.h"
#include "Edge.h"

Edge::edge()
{
    m_pFrom = '\0';
    m_pTo = '\0';
    m_Bandwidth = 0;
    m_Cost = 0;
    m_pNext = '\0';
    m_pLeft = '\0';
    m_pRight = '\0';
    m_Shortest = 0;

}
void Edge::setFrom(Node* From)
{
    m_pFrom = From;
}
void Edge::setTo(Node* To)
{
    m_pTo = To;
}
void Edge::setBandwidth(int Bandwidth)
{
    m_Bandwidth = Bandwidth;
}
void Edge::setCost(int Cost)
{
    m_Cost = Cost;
}
void Edge::setNext(edge* Next)
{
    m_pNext = Next;
}

Node* Edge::getFrom()
{
    return m_pFrom;
}
Node* Edge::getTo()
{
    return m_pTo;
}
int Edge::getBandwidth()
{
    return m_Bandwidth;
}
int Edge::getCost()
{
    return m_Cost;
}
Edge* edge::getNext()
{
    return m_pNext;
}

void Edge::setLeft(edge* Left)
{
    m_Left = Left;
}
void Edge::setRight(edge* Right)
{
    m_Right = Right;
}
void Edge::setShort(int Shortest)
{
    m_Shortest = Shortest;
}
Edge* edge::getLeft()
{
    return m_Left;
}
Edge* edge::getRight()
{
    return m_Right;
}
int Edge::getShort()
{
    return m_Shortest;
}
