#include "dijkstra.h"

void dijkstra::MakeCostArr(node* GraphRoot)
{
	node* pCur = GraphRoot;
	edge* ppCur = NULL;
	int count = 0;
	while (pCur)
	{
		pCur = pCur->getNext();
		count++;
	}

	CostArray = new int*[count];
	for (int i = 0; i < count; ++i) {
		CostArray[i] = new int[count];
		memset(CostArray[i], INT_MAX, sizeof(int)*count);
	}
	//ADJROOT - node
	pCur = GraphRoot;

	for (int i = 0; i < count; i++)
	{

		for (int j = 0; j < count; j++)
		{
			ppCur = pCur->getEdge();
			if (i == j)
				CostArray[i][j] = 0;
			else
			{
				while (ppCur)
				{
					if (ppCur->getTo()->getIndex() == j)
					{
						CostArray[i][j] = ppCur->getCost();
						break;
					}
					ppCur = ppCur->getNext();
				}
			}
		}
		pCur = pCur->getNext();
	}

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			cout << CostArray[i][j] << " ";
		}
		cout << endl;
	}
	this->COUNT = count;
}
int dijkstra::MakeShortPath(char From, char To, node* GraphRoot)
{
	
	int S_index = 0;

	node* pFrom = GraphRoot, *pCur = NULL;
	node* pTo = GraphRoot;
	edge* ppCur = NULL;
	int* D;		//CostArray[X][i]
	node* S;	//selected node group

	S = new node[COUNT];
	ShortPath = new node[COUNT];
	D = new int[COUNT];

	while (pFrom)
	{
		if (pFrom->getID() == From)
			break;
		pFrom = pFrom->getNext();
	}
	if (!pFrom)
	{
		return -1;
	}
	while (pTo)
	{
		if (pTo->getID() == To)
			break;
		pTo = pTo->getNext();
	}

	if (!pTo)
	{
		return -1;
	}

	for (int i = 0; i < COUNT; i++)		//D배열은 From에서 To로 갈 수있는 edge의 cost 집합.
	{
		D[i] = CostArray[pFrom->getIndex()][i];
	}


	ppCur = pFrom->getEdge();
	while (ppCur)		//Leftist Tree를 이용한 choose
	{
		LFT.Insert(LFT.getRoot(), ppCur);
		ppCur = ppCur->getNext();
	}
	int i = 0;
	ppCur = pFrom->getEdge();
	for (i; i < COUNT; i++)			//ShortPath(goal array) 저장
	{

		if (ppCur->getFrom()->getIndex() == i)
		{
			while (!ppCur)
			{
				ShortPath[i] = *ppCur->getTo();
				ppCur = ppCur->getNext();
				i = 0;
			}
		}
	}
	S[0] = *pFrom;		

	edge* POP = '\0';
	ppCur = '\0';
	int u = 0;
	S[pFrom->getIndex()] = *pFrom;

	for (i = 1; i < COUNT - 1; i++)
	{
		POP = LFT.Delete();
		u = POP->getCost();
		S[i] = *POP->getTo();
		ShortPath[POP->getTo()->getIndex()] = *pFrom;
	}
}