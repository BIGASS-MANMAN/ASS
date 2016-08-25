// _CRT_SECURE_NO_WARNINGS

#include "Manager.h"



Manager::Manager()

{
    CostArray = '\0';
    ShortPath = '\0';
    COUNT = 0;
}
Manager::~Manager()
{
    m_fin1.close();
    m_fin2.close();
    m_fout.close();
}

bool Manager::InputFileOpen1(const char* fname)
{
    m_fin1.open(fname);

    if (m_fin1.fail()) //file open fail
	return false;

    return true;
}
bool Manager::InputFileOpen2(const char* fname)
{
    m_fin2.open(fname);

    if (m_fin2.fail()) //file open fail
	return false;

    return true;
}

bool Manager::OutputFileOpen(const char* fname)
{
    m_fout.open(fname);

    if (m_fout.fail())	//file open fail
	return false;

    return true;
}

bool Manager::ProcessRoute(char* fname)
{
    char sentence[256];
    memset(sentence, '\0', 256);
    if (!InputFileOpen1(fname))
    {
	return false;
    }
    while (!m_fin1.eof())
    {
	m_fin1.getline(sentence, 256);
	MakeEdge(sentence);
    }
    return true;
}

void Manager::MakeEdge(char* sentence)
{
    char str[256];
    memset(str, 256, '\0');
    strcpy(str, sentence);
    
    char* temp = NULL;
    int bandwidth = 0, cost = 0;

    Node* FromNode = new Node;
    Node* ToNode = new Node;
    temp = strtok(str, "\t\n ");
    FromNode->setID(temp[0]);		//From Router ID set

    temp = strtok(NULL, "\t\n ");
    ToNode->setID(temp[0]);			//To Router ID set

    Edge* pNew = new edge;

    pNew->setFrom(FromNode);		//new Edge From Rounter set
    pNew->setTo(ToNode);		    //new Edge To Rounter set

    temp = strtok(NULL, "\t\n ");
    bandwidth = atoi(temp);
    pNew->setBandwidth(bandwidth);		//new Edge Bandwidth set

    temp = strtok(NULL, "\t\n ");
    cost = atoi(temp);
    pNew->setCost(cost);		    //new Edge Cost set

    this->m_Graph.MakeGraph(pNew);
}



Node* Manager::getGraphRoot()
{
    return this->m_Graph.getRoot();
}


void Manager::MakeCostArr(Node* GraphRoot)
{
    Node* pCur = GraphRoot;
    Edge* ppCur = NULL;
    int count = 0;
    while (pCur)
    {
	pCur = pCur->getNext();
	count++;
    }

    CostArray = new int*[count];
    for (int i = 0; i < count; ++i) {
	CostArray[i] = new int[count];
	for (int j = 0; j < count; j++)
	{
	    CostArray[i][j] = INT_MAX;
	}
    }
    //ADJROOT - Node
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
    COUNT = count;
}

Node* Manager::MakeShortPath(char From, char To, Node* GraphRoot)
{
    Node* pFrom = GraphRoot, *pCur = NULL;
    Node* pTo = GraphRoot;

    int* D;	    //CostArray[X][i]
    bool* S;	//selected Node group

    this->MakeCostArr(this->getGraphRoot());
    S = new bool[COUNT];
    for (int i = 0; i < COUNT; i++)
    {
	S[i] = false;
    }
    ShortPath = new Node[COUNT];
    D = new int[COUNT];

    while (pFrom)
    {
	if (pFrom->getID() == From)
	    break;
	pFrom = pFrom->getNext();
    }
    if (!pFrom)
    {
	return '\0';
    }
    while (pTo)
    {
	if (pTo->getID() == To)
	    break;
	pTo = pTo->getNext();
    }

    if (!pTo)
    {
	return '\0';
    }

    for (int i = 0; i < COUNT; i++)	//D배열은 From에서 To로 갈 수있는 Edge의 cost 집합.
    {
	D[i] = CostArray[pFrom->getIndex()][i];
    }

    Edge* ppCur = pFrom->getEdge();
    Edge* pTemp = '\0';
    int u = 0;
    int utow = 0;


    S[pFrom->getIndex()] = true;
    ShortPath[pFrom->getIndex()] = *pFrom;

    while (ppCur)
    {
	ShortPath[ppCur->getTo()->getIndex()] = *pFrom;//goal's temp's to's index = from
	LFT.setRoot(LFT.Insert(LFT.getRoot(), ppCur));//push to leftist tree
	ppCur = ppCur->getNext();//temp move next
    }
    ppCur = '\0';


    while(LFT.getRoot())
    {
	ppCur = this->LFT.Delete();
	u = ppCur->getTo()->getIndex();
	S[ppCur->getTo()->getIndex()] = true;
	for (int w = 0; w < COUNT; w++)
	{
	    if (S[w] == false)
	    {
		utow = this->CostArray[u][w];
		if ((utow != INT_MAX) && (D[u] + utow < D[w]))
		{
		    ShortPath[w] = *ppCur->getTo();

		    Edge* newEdge = new edge;
		    pTemp = this->find(u, w);
		    D[w] = D[u] + utow;
		    newEdge->setBandwidth(pTemp->getBandwidth());
		    newEdge->setCost(D[w]);
		    newEdge->setFrom(pFrom);
		    newEdge->setNext(pTemp->getNext());
		    newEdge->setTo(pTemp->getTo());
		    LFT.Insert(LFT.getRoot(), newEdge);
		}
	    }
	}
    }
    cout << endl;
    for (int i = 0; i < COUNT; i++)
    {
	cout << ShortPath[i].getID();
    }
    return ShortPath;
}


Edge* Manager::find(int v1, int v2)
{
    Node* dTemp = this->getGraphRoot();
    Edge* rTemp = '\0';
    while (dTemp)
    {
	if (dTemp->getIndex() == v1)
	{
	    rTemp = dTemp->getEdge();
	    while (rTemp)
	    {
		if (rTemp->getTo()->getIndex() == v2)
		    return rTemp;
		else
		    rTemp = rTemp->getNext();
	    }
	}
	dTemp = dTemp->getNext();
    }
    return '\0';
}



void Manager::setCount(int count)
{
    COUNT = count;
}



void Manager::PRINT(Node* path, Node* adjList, char from)
{
    int i = 0, j = 0, cnt = 0;
    Node* ShortestPath;
    Node temp;

    Node* pCur = '\0';
    Node* ppCur = adjList;
    m_fout << "\t------------------------make shortest path----------------------------";
    while (ppCur)
    {
	int i = 0;
	cnt = 0;
	ShortestPath = new Node[COUNT];
	for (int k = 0; k < COUNT; k++)
	{
	    ShortestPath[k].setID('\0');
	}
	pCur = adjList;
	if (ppCur->getID() == from)
	{
	    ppCur = ppCur->getNext();
	    if (!ppCur)
	    {
		break;
	    }
	}
	while (pCur->getID() != ppCur->getID())
	{
	    pCur = pCur->getNext();
	}

	ShortestPath[j] = *pCur;

	i = pCur->getIndex();
	j++;


	while ((&path[i])->getID() != '\0')
	{
	    if ((&path[i])->getID() == from)
	    {
		ShortestPath[j] = path[(&path[i])->getIndex()];

		break;
	    }
	    ShortestPath[j] = path[i];
	    j++;
	    i = (&path[i])->getIndex();
	}
	ppCur = ppCur->getNext();
	m_fout << endl;
	i = 0;
	for (i; ShortestPath[i].getID() != '\0'; i++)
	{
	    cnt++;
	}

	j = 0;
	i = cnt - 1;

	m_fout << "\tI";
	for (i; i >= 0; i--)
	{
	    m_fout << ShortestPath[i].getID() << "\t";
	}

	delete ShortestPath;
    }
    m_fout <<endl<<"\t---------------------------end print SP-------------------------------" << endl;
}
