#include "graph.h"
graph::graph()
{
	root = '\0';
}
node* graph::getRoot()
{
	return root;
}
void graph::MakeGraph(edge* Edge)
{
	int flag = 0;			//setEdge flag
	node* pCur = root;
	node* prevCur = '\0';
	edge* ppCur = '\0';

	if (!root)						//If empty AdjacentList
	{
		root = Edge->getFrom();		//root = From vertex in Edge
		root->setNext(Edge->getTo());//root's next vertex = To vertex in Edge
		root->setEdge(Edge);

		edge* Newedge = new edge;
		Newedge->setBandwidth(Edge->getBandwidth());
		Newedge->setCost(Edge->getCost());
		Newedge->setFrom(Edge->getTo());
		Newedge->setTo(Edge->getFrom());
		root->getNext()->setEdge(Newedge);

		Edge->getFrom()->setIndex(0);
		Edge->getTo()->setIndex(1);

		return;
	}
	else
	{
		while (pCur)
		{
			if (Edge->getFrom()->getID() == pCur->getID())
			{
				Edge->getFrom()->setIndex(pCur->getIndex());
			}
			if (Edge->getTo()->getID() == pCur->getID())
			{
				Edge->getTo()->setIndex(pCur->getIndex());
			}
			pCur = pCur->getNext();
		}
		pCur = root;
		while (pCur)		//until pCur is NULL
		{
			if (pCur->getID() == Edge->getFrom()->getID())	//If pCur's ID == From vertex's ID in Edge
			{
				ppCur = pCur->getEdge();	//ppCur = pCur's Edge

				while (ppCur->getNext())
				{
					ppCur = ppCur->getNext();
				}
				ppCur->setNext(Edge);		//Connect Edge to pCur's last edge
				flag = 1;					//set flag
				break;
			}
			prevCur = pCur;
			pCur = pCur->getNext();
		}
		if (flag == 0)						//If no set Edge, Connect vertex to pCur's last vertex
		{
			prevCur->setNext(Edge->getFrom());
			Edge->getFrom()->setEdge(Edge);
			Edge->getFrom()->setIndex(prevCur->getIndex() + 1);
		}
		//Initialize Cursor and flag
		flag = 0;
		pCur = root;
		prevCur = '\0';
		ppCur = '\0';

		edge* Newedge = new edge;
		Newedge->setBandwidth(Edge->getBandwidth());
		Newedge->setCost(Edge->getCost());
		Newedge->setFrom(Edge->getTo());
		Newedge->setTo(Edge->getFrom());

		while (pCur)						//Repeat process using Edge's to vertex
		{
			if (pCur->getID() == Edge->getTo()->getID())
			{
				ppCur = pCur->getEdge();
				while (ppCur->getNext())
				{
					ppCur = ppCur->getNext();
				}
				ppCur->setNext(Newedge);
				flag = 1;
				break;
			}
			prevCur = pCur;
			pCur = pCur->getNext();
		}
		if (flag == 0)
		{
			prevCur->setNext(Edge->getTo());
			Edge->getTo()->setEdge(Newedge);
			Edge->getTo()->setIndex(prevCur->getIndex() + 1);
		}

	}

}