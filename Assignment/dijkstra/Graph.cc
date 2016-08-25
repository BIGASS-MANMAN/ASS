#include "Graph.h"
Graph::Graph()
{
    m_pRoot = '\0';
}
Node* Graph::getRoot()
{
    return m_pRoot;
}
void Graph::MakeGraph(Edge* Edge)
{
    int flag = 0;		//setEdge flag
    Node* pCur = m_pRoot;
    Node* prevCur = '\0';
    Edge* ppCur = '\0';

    if (!m_pRoot)			//If empty AdjacentList
    {
	m_pRoot = Edge->getFrom();	//root = From vertex in Edge
	m_pRoot->setNext(Edge->getTo());//root's next vertex = To vertex in Edge
	m_pRoot->setEdge(Edge);

	Edge* Newedge = new edge;
	NewEdge->setBandwidth(Edge->getBandwidth());
	NewEdge->setCost(Edge->getCost());
	NewEdge->setFrom(Edge->getTo());
	NewEdge->setTo(Edge->getFrom());
	m_pRoot->getNext()->setEdge(NewEdge);

	Edge->getFrom()->setIndex(0);
	Edge->getTo()->setIndex(1);

	return;
    }
    else
    {
	while (pCur)
	{
	    if (Edge->getFrom()->getID() == pCur->getID())
		Edge->getFrom()->setIndex(pCur->getIndex());
	    
	    if (Edge->getTo()->getID() == pCur->getID())
		Edge->getTo()->setIndex(pCur->getIndex());
	    pCur = pCur->getNext();
	}
	pCur = m_pRoot;
	while (pCur)	    //until pCur is NULL
	{
	    if (pCur->getID() == Edge->getFrom()->getID())  //If pCur's ID == From vertex's ID in Edge
	    {
		ppCur = pCur->getEdge();    //ppCur = pCur's Edge

		while (ppCur->getNext())
		{
		    ppCur = ppCur->getNext();
		}
		ppCur->setNext(Edge);	    //Connect Edge to pCur's last Edge
		flag = 1;		    //set flag
		break;
	    }
	    prevCur = pCur;
	    pCur = pCur->getNext();
	}
	if (flag == 0)			    //If no set Edge, Connect vertex to pCur's last vertex
	{
	    prevCur->setNext(Edge->getFrom());
	    Edge->getFrom()->setEdge(Edge);
	    Edge->getFrom()->setIndex(prevCur->getIndex() + 1);
	}
	//Initialize Cursor and flag
	flag = 0;
	pCur = m_pRoot;
	prevCur = '\0';
	ppCur = '\0';

	Edge* Newedge = new edge;
	NewEdge->setBandwidth(Edge->getBandwidth());
	NewEdge->setCost(Edge->getCost());
	NewEdge->setFrom(Edge->getTo());
	NewEdge->setTo(Edge->getFrom());

	while (pCur)			    //Repeat process using Edge's to vertex
	{
	    if (pCur->getID() == Edge->getTo()->getID())
	    {
		ppCur = pCur->getEdge();
		while (ppCur->getNext())
		{
		    ppCur = ppCur->getNext();
		}
		ppCur->setNext(NewEdge);
		flag = 1;
		break;
	    }
	    prevCur = pCur;
	    pCur = pCur->getNext();
	}
	if (flag == 0)
	{
	    prevCur->setNext(Edge->getTo());
	    Edge->getTo()->setEdge(NewEdge);
	    Edge->getTo()->setIndex(prevCur->getIndex() + 1);
	}
    }
}
