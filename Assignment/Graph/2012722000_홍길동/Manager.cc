// _CRT_SECURE_NO_WARNINGS
#include "Manager.h"

Manager::Manager()
{
	CostArray = '\0';
	ShortPath = '\0';
	COUNT = 0;
	S_REQ_ROOT = '\0';
	F_REQ_ROOT = '\0';
	LF_S_ROOT = '\0';
	LF_F_ROOT = '\0';
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

	node* FromNode = new node;
	node* ToNode = new node;
	temp = strtok(str, "\t\n ");
	FromNode->setID(temp[0]);				//From Router ID set

	temp = strtok(NULL, "\t\n ");
	ToNode->setID(temp[0]);					//To Router ID set

	edge* pNew = new edge;

	pNew->setFrom(FromNode);				//new edge From Rounter set
	pNew->setTo(ToNode);					//new edge To Rounter set

	temp = strtok(NULL, "\t\n ");
	bandwidth = atoi(temp);
	pNew->setBandwidth(bandwidth);			//new edge Bandwidth set

	temp = strtok(NULL, "\t\n ");
	cost = atoi(temp);
	pNew->setCost(cost);					//new edge Cost set

	this->Graph.MakeGraph(pNew);
}

node* Manager::getGraphRoot()
{
	return this->Graph.getRoot();
}

bool Manager::COMMAND(char* fname)
{
	char sentence[256];
	memset(sentence, 256, '\0');
	char* buf = '\0';
	char cmd[9];
	memset(cmd, 9, '\0');

	memset(sentence, '\0', 256);

	if (!InputFileOpen2(fname))
	{
		return false;
	}

	while (!m_fin2.eof())
	{
		m_fin2.getline(sentence, 256);

		buf = strtok(sentence, "\t\n ");
		strcpy(cmd, buf);

		if(!strcmp(cmd,"request"))
		{ 
			this->REQUEST(buf);
		}
		
		else if(!strcmp(cmd, "linkfail"))
		{ 
			this->LINKFAIL(buf);
		}
		else if (!strcmp(cmd, "eos"))
		{
			this->EOS(buf);
		}
		else if (!strcmp(cmd, "end"))
		{ }
		else
		{
			cout << endl << "No matching Command" << endl;
			return false;
		}
	}
	return true;
}

void Manager::REQUEST(char* sentence)
{
	char* buf = '\0';
	char* INDEX = '\0';
	char* From = '\0';
	char* To = '\0';
	char* Bandwidth = '\0';
	node* path = '\0';
	bool flag = true;
	request* pCur = '\0';
	edge* C_edge = '\0';

	INDEX = strtok('\0', "\t\n ");

	From = strtok('\0', "\t\n ");

	To = strtok('\0', "\t\n ");

	Bandwidth = strtok('\0', "\t\n ");

	path = this->MakeShortPath(From[0], To[0], this->getGraphRoot());// , COUNT, this->getGraphRoot();
	request* newRequest = new request(atoi(INDEX), From[0], To[0], atoi(Bandwidth));
	newRequest->setShortPath(path, COUNT, this->getGraphRoot());
	cout << endl;
	for (int i = 0; (newRequest->getShortPath()[i]).getID() != '\0'; i++)
	{
		
		cout << (newRequest->getShortPath()[i]).getID();
	}
	cout << endl;
	//for (int i = 0; (&ShortPath[i+1])->getID() != '\0'; i++)
	for (int i = 0; (&newRequest->getShortPath()[i + 1])->getID() != '\0'; i++)
	{
		//If bandwidth in shortestpath is less than Request's bandwidth, Insert F_Request list
		if(this->find((&newRequest->getShortPath()[i])->getIndex(), (&newRequest->getShortPath()[i + 1])->getIndex())->getBandwidth()<atoi(Bandwidth))
		{
			pCur = this->F_REQ_ROOT;

			flag = false;
			if (!this->F_REQ_ROOT)
			{
				F_REQ_ROOT = newRequest;
			}
			else
			{
				while (F_REQ_ROOT->getF_Next())
				{
					pCur = pCur->getF_Next();
				}
				pCur->setF_Next(newRequest);
			}
			this->PRINT(path, this->getGraphRoot(), From[0]);
			m_fout << "deferred Request\t: " << newRequest->getIndex() << "\t" << newRequest->getBandwidth();
			for (int j = 0; newRequest->getShortPath()[j].getID() != '\0'; j++)
			{
				m_fout << "\t" << newRequest->getShortPath()[j].getID();
			}
			m_fout << endl;
			m_fout << endl;
			m_fout << endl;
			break;
		}
	}



	if (flag == true)
	{
		//Insert allocate Success request linked list
		pCur = this->S_REQ_ROOT;
		if (!this->S_REQ_ROOT)
		{
			S_REQ_ROOT = newRequest;
		}
		else
		{
			while (pCur->getS_Next())
			{
				pCur = pCur->getS_Next();
			}
			pCur->setS_Next(newRequest);
		}
		pCur = this->S_REQ_ROOT;
		//Subtract bandwidth
		for (int i = 0; (&newRequest->getShortPath()[i + 1])->getID() != '\0'; i++)
		{
			C_edge = this->find((&newRequest->getShortPath()[i])->getIndex(), (&newRequest->getShortPath()[i + 1])->getIndex());
			C_edge->setBandwidth(C_edge->getBandwidth() - atoi(Bandwidth));
		}
		this->PRINT(path, this->getGraphRoot(), From[0]);
		m_fout << "allocated Request\t: " << newRequest->getIndex() << "\t" << newRequest->getBandwidth();
		for (int j = 0; newRequest->getShortPath()[j].getID() != '\0'; j++)
		{
			m_fout << "\t" << newRequest->getShortPath()[j].getID();
		}
		m_fout << endl;
		m_fout << endl;
		m_fout << endl;
	}

}
bool Manager::EOS(char* sentence)
{
	char* INDEX = '\0';
	INDEX = strtok('\0', "\t\n ");

	request* pCur = S_REQ_ROOT;
	request* F_Cur = F_REQ_ROOT;
	request* F2_Cur = F_REQ_ROOT;
	request* F_prevCur = '\0';
	request* prevCur = '\0';
	node* shortPath = '\0';
	edge* currentEdge = '\0';
	bool flag = true;

	m_fout << "eos " << INDEX << endl;
	m_fout << "-----------------------------------start realloc-------------------------------" << endl;
	while (pCur)//Search matched EOS Index request in Success request linked list
	{
		if (pCur->getIndex() == atoi(INDEX))//If pCur's request index is same with EOS index
		{
			break;							//break
		}
		prevCur = pCur;
		pCur = pCur->getS_Next();
	}

	if (!pCur)//If no matching
	{
		cout << "No matching EOS INDEX" << endl;
		m_fout << "------------------------------------end realloc--------------------------------";
		m_fout << endl;
		m_fout << endl;
		return true;
	}
	shortPath = pCur->getShortPath();//shortPath = selected request's shortest path

	for (int i = 0; shortPath[i + 1].getID() != '\0'; i++)//selected request's shortest path's all edge's bandwidth + selected request's bandwidth 
	{
		currentEdge = find(shortPath[i].getIndex(), shortPath[i + 1].getIndex());
		currentEdge->setBandwidth(currentEdge->getBandwidth() + pCur->getBandwidth());
	}
	if (pCur == S_REQ_ROOT)	//If selected request is root, root = selected request's next request
	{
		S_REQ_ROOT = pCur->getS_Next();
	}
	else					//connect prev request to selected request's next request
	{		
		prevCur->setS_Next(pCur->getS_Next());
	}
	delete pCur;			//delete selected request

	while (F_Cur)			//allocate deferred request
	{
		shortPath = F_Cur->getShortPath();//shortPath = current deferred request's shortest path
		for (int i = 0; shortPath[i + 1].getID() != '\0'; i++)
		{
			currentEdge = find(shortPath[i].getIndex(), shortPath[i + 1].getIndex());
			if (currentEdge->getBandwidth() < F_Cur->getBandwidth())//If deferred request's bandwidth > shortest path's edge's bandwidth
			{
				flag = false;//skip
				break;
			}
		}
		if (flag == true)
		{
			//해당 리퀘스트 밴드위스 깎아줌
			for (int i = 0; shortPath[i + 1].getID() != '\0'; i++)
			{
				currentEdge = find(shortPath[i].getIndex(), shortPath[i + 1].getIndex());
				currentEdge->setBandwidth(currentEdge->getBandwidth() - F_Cur->getBandwidth());
			}
			pCur = S_REQ_ROOT;
			while (pCur->getS_Next())
			{
				pCur = pCur->getS_Next();
			}
			pCur->setS_Next(F_Cur);
			
			//realloc request print
			/*this->PRINT(pCur->getShortPath(), this->getGraphRoot(), pCur->getFrom());
			m_fout << "allocated Request\t: " << pCur->getIndex() << "\t" << pCur->getBandwidth();
			for (int j = 0; pCur->getShortPath()[j].getID() != '\0'; j++)
			{
				m_fout << "\t" << pCur->getShortPath()[j].getID();
			}
			m_fout << endl;*/
			this->PRINT(F_Cur->getShortPath(), this->getGraphRoot(), F_Cur->getFrom());
			m_fout << "allocated Request\t: " << F_Cur->getIndex() << "\t" << F_Cur->getBandwidth();
			for (int j = 0; F_Cur->getShortPath()[j].getID() != '\0'; j++)
			{
			m_fout << "\t" << F_Cur->getShortPath()[j].getID();
			}
			m_fout << endl;

			if (F_Cur == F_REQ_ROOT)
			{
				F_REQ_ROOT = F_Cur->getF_Next();
			}

			else
			{
				F_prevCur->setF_Next(pCur->getF_Next());
			}
		}
		F_prevCur = pCur;
		F_Cur = F_Cur->getF_Next();
		flag = true;
	}

	while (F2_Cur)
	{
		m_fout << "deferred Request\t: " << F2_Cur->getIndex() << "\t" << F2_Cur->getBandwidth();
		for (int j = 0; F2_Cur->getShortPath()[j].getID() != '\0'; j++)
		{
			m_fout << "\t" << F2_Cur->getShortPath()[j].getID();
		}
		m_fout << endl;
		F2_Cur = F2_Cur->getF_Next();
	}
	m_fout << "------------------------------------end realloc--------------------------------" << endl << endl;
	return true;
}

void Manager::LINKFAIL(char* sentence)
{
	char* From = '\0';
	char* To = '\0';
	From = strtok('\0', "\t\n ");
	To = strtok('\0', "\t\n ");
	request* S_Cur = S_REQ_ROOT;
	request* prev_S_Cur = '\0';
	request* F_Cur = F_REQ_ROOT;
	request* prev_F_Cur = '\0';
	request* LF_S_Cur = '\0';
	request* LF_F_Cur = '\0';
	edge* C_edge = '\0';
	edge* Target = '\0';
	node* path = '\0';

	bool flag = true;
	bool flag1 = true;

	m_fout << "linkfail " << From[0] << " " << To[0];
	m_fout << endl;
	m_fout << "----------------------------------start return bw------------------------------" << endl;


	while (S_Cur)
	{
		LF_S_Cur = LF_S_ROOT;
		path = S_Cur->getShortPath();
		for (int i = 0; (&path[i + 1])->getID() != '\0'; i++)
		{
			C_edge = this->find((&path[i])->getIndex(), (&path[i + 1])->getIndex());
			//If edge's from and to ID is same with Link Fail's from and to, return success request's all banwidth
			if((C_edge->getFrom()->getID() == From[0])&&(C_edge->getTo()->getID() == To[0]))
			{
				m_fout << "using faillink path\t: " << S_Cur->getIndex() << "\t" << S_Cur->getBandwidth();
				for (int k = 0; path[k].getID() != '\0'; k++)
				{
					m_fout << "\t" << path[k].getID();
				}
				m_fout << endl;
				Target = C_edge;
				for (int j = 0; path[j + 1].getID() != '\0'; j++)//selected request's shortest path's all edge's bandwidth + selected request's bandwidth 
				{
					C_edge = this->find((&path[j])->getIndex(), (&path[j + 1])->getIndex());
					C_edge->setBandwidth(C_edge->getBandwidth() + S_Cur->getBandwidth());
				}
				if (!LF_S_ROOT)
				{
					LF_S_ROOT = S_Cur;
				}
				else
				{
					while (LF_S_Cur->getLF_S_Next())
					{
						LF_S_Cur = LF_S_Cur->getLF_S_Next();
					}
					LF_S_Cur->setLF_S_Next(S_Cur);
					S_Cur->setLF_S_Next('\0');
				}
				break;
			}
		}
		S_Cur = S_Cur->getS_Next();
	}//success request reutrn bandwidth end

	while (F_Cur)
	{
		LF_F_Cur = LF_F_ROOT;
		path = F_Cur->getShortPath();
		for (int i = 0; (&path[i + 1])->getID() != '\0'; i++)
		{
			C_edge = this->find((&path[i])->getIndex(), (&path[i + 1])->getIndex());
			//If edge's from and to ID is same with Link Fail's from and to, return success request's all banwidth
			if ((C_edge->getFrom()->getID() == From[0]) && (C_edge->getTo()->getID() == To[0]))
			{
				for (int j = 0; path[j + 1].getID() != '\0'; j++)//selected request's shortest path's all edge's bandwidth + selected request's bandwidth 
				{
					C_edge = this->find((&path[j])->getIndex(), (&path[j + 1])->getIndex());
			//		C_edge->setBandwidth(C_edge->getBandwidth() + F_Cur->getBandwidth());
				}
				if (!LF_F_ROOT)
				{
					LF_F_ROOT = LF_F_Cur;
				}
				else
				{
					while (LF_F_Cur->getLF_F_Next())
					{
						LF_F_Cur = LF_F_Cur->getLF_F_Next();
					}
					LF_F_Cur->setLF_F_Next(F_Cur);
					F_Cur->setLF_F_Next('\0');
				}
				break;
			}
		}
		F_Cur = F_Cur->getF_Next();
	}//deferred request reutrn bandwidth end

	m_fout << "-----------------------------------end return bw-------------------------------" << endl;
	Target->setCost(INT_MAX);//Link Fail edge's bandwidth = INT_MAX
	this->find(Target->getTo()->getIndex(), Target->getFrom()->getIndex())->setCost(INT_MAX);
	this->CostArray[Target->getFrom()->getIndex()][Target->getTo()->getIndex()] = INT_MAX;
	this->CostArray[Target->getTo()->getIndex()][Target->getFrom()->getIndex()] = INT_MAX;
	//this->MakeShortPath(From[0], To[0], this->getGraphRoot());

	LF_S_Cur = LF_S_ROOT;
	LF_F_Cur = LF_F_ROOT;
	S_Cur = S_REQ_ROOT;
	F_Cur = F_REQ_ROOT;

	request* prev_LF_S_Cur = '\0';
	request* prev_LF_F_Cur = '\0';
	request* S_Search = '\0';
	request* F_Search = '\0';

	m_fout << "-----------------------------------start realloc-------------------------------" << endl;
	while (LF_S_Cur)
	{
		S_Search = S_REQ_ROOT;
		LF_S_Cur->setShortPath(this->MakeShortPath(LF_S_Cur->getFrom(), LF_S_Cur->getTo(), this->getGraphRoot()), COUNT, this->getGraphRoot());
		for (int i = 0; LF_S_Cur->getShortPath()[i + 1].getID() != '\0'; i++)
		{
			C_edge = this->find((&LF_S_Cur->getShortPath()[i])->getIndex(), (&LF_S_Cur->getShortPath()[i + 1])->getIndex());
			if (C_edge->getBandwidth() < LF_S_Cur->getBandwidth())
			{
				flag1 = false;
				if (!F_Cur)
				{
					F_REQ_ROOT = LF_S_Cur;

					if (!prev_LF_S_Cur)	//link fail linked list disconnect
					{
						LF_S_ROOT = LF_S_Cur->getLF_S_Next();
				//		LF_S_Cur->setLF_S_Next('\0');
					}
					else
					{
						prev_LF_S_Cur->setLF_S_Next(LF_S_Cur->getLF_S_Next());
				//		LF_S_Cur->setLF_S_Next('\0');
					}

					while (S_Search!=LF_S_Cur)//success request disconnect
					{
						prev_S_Cur = S_Search;
						S_Search = S_Search->getS_Next();
					}
					if (!prev_S_Cur)
					{
						S_REQ_ROOT = LF_S_Cur->getS_Next();
					}
					else
					{
						prev_S_Cur->setS_Next(LF_S_Cur->getS_Next());
					}
					LF_S_Cur->setS_Next('\0');
				}
				else
				{
					while (F_Cur->getF_Next())
					{
						F_Cur = F_Cur->getF_Next();
					}
					F_Cur->setF_Next(LF_S_Cur);

					if (!prev_LF_S_Cur)	//link fail linked list disconnect
					{
						LF_S_ROOT = LF_S_Cur->getLF_S_Next();
					}
					else
					{
						prev_LF_S_Cur->setLF_S_Next(LF_S_Cur->getLF_S_Next());
					}
				//	LF_S_Cur->setLF_S_Next('\0');

					while (S_Search != LF_S_Cur)//success request disconnect
					{
						prev_S_Cur = S_Search;
						S_Search = S_Search->getS_Next();
					}
					if (!prev_S_Cur)
					{
						S_REQ_ROOT = LF_S_Cur->getS_Next();
					}
					else
					{
						prev_S_Cur->setS_Next(LF_S_Cur->getS_Next());
					}
					LF_S_Cur->setS_Next('\0');
				}
				this->PRINT(LF_S_Cur->getShortPath(), this->getGraphRoot(), LF_S_Cur->getFrom());
				m_fout << "deferred Request\t: " << LF_S_Cur->getIndex() << "\t" << LF_S_Cur->getBandwidth();
				for (int j = 0; LF_S_Cur->getShortPath()[j].getID() != '\0'; j++)
				{
					m_fout << "\t" << LF_S_Cur->getShortPath()[j].getID();
				}
				m_fout << endl;
				break;
			}
		}
		if (flag1 == true)
		{
			this->PRINT(LF_S_Cur->getShortPath(), this->getGraphRoot(), LF_S_Cur->getFrom());
			m_fout << "allocated Request\t: " << LF_S_Cur->getIndex() << "\t" << LF_S_Cur->getBandwidth();
			for (int j = 0; LF_S_Cur->getShortPath()[j].getID() != '\0'; j++)
			{
				m_fout << "\t" << LF_S_Cur->getShortPath()[j].getID();
			}
			m_fout << endl;
			flag1 = false;
			if (!prev_LF_S_Cur)	//link fail linked list disconnect
			{
				LF_S_ROOT = LF_S_Cur->getLF_S_Next();
			}
			else
			{
				prev_LF_S_Cur->setLF_S_Next(LF_S_Cur->getLF_S_Next());
			}
		//	LF_S_Cur->setLF_S_Next('\0');
		}
		flag1 = true;
		prev_LF_S_Cur = LF_S_Cur;
		LF_S_Cur = LF_S_Cur->getLF_S_Next();
	}

	while (LF_F_Cur)
	{
		S_Search = F_REQ_ROOT;
		LF_F_Cur->setShortPath(this->MakeShortPath(LF_F_Cur->getFrom(), LF_F_Cur->getTo(), this->getGraphRoot()), COUNT, this->getGraphRoot());
		for (int i = 0; LF_F_Cur->getShortPath()[i + 1].getID() != '\0'; i++)
		{
			if (this->find((&LF_F_Cur->getShortPath()[i])->getIndex(), (&LF_F_Cur->getShortPath()[i + 1])->getIndex())->getBandwidth() < LF_F_Cur->getBandwidth())
			{
				flag = false;
			}
		}
		if (flag == true)
		{
			if (!S_Cur)
			{
				
				F_REQ_ROOT = LF_S_Cur;

				if (!prev_LF_F_Cur)	//link fail linked list disconnect
				{
					LF_F_ROOT = LF_F_Cur->getLF_F_Next();
				}
				else
				{
					prev_LF_F_Cur->setLF_F_Next(LF_F_Cur->getLF_F_Next());
				}
				LF_F_Cur->setLF_F_Next('\0');

				while (F_Search != LF_F_Cur)//success request disconnect
				{
					prev_F_Cur = F_Search;
					F_Search = F_Search->getF_Next();
				}
				if (!prev_F_Cur)
				{
					F_REQ_ROOT = LF_F_Cur->getF_Next();
				}
				else
				{
					prev_F_Cur->setF_Next(LF_F_Cur->getF_Next());
				}
				LF_F_Cur->setF_Next('\0');

			}
			else
			{
				while (S_Cur->getS_Next())
				{
					S_Cur = S_Cur->getS_Next();
				}
				S_Cur->setS_Next(LF_F_Cur);

				if (!prev_LF_F_Cur)	//link fail linked list disconnect
				{
					LF_F_ROOT = LF_F_Cur->getLF_F_Next();
				}
				else
				{
					prev_LF_F_Cur->setLF_F_Next(LF_F_Cur->getLF_F_Next());
				}
				LF_F_Cur->setLF_F_Next('\0');

				while (F_Search != LF_F_Cur)//success request disconnect
				{
					prev_F_Cur = F_Search;
					F_Search = F_Search->getF_Next();
				}
				if (!prev_F_Cur)
				{
					F_REQ_ROOT = LF_F_Cur->getF_Next();
				}
				else
				{
					prev_F_Cur->setF_Next(LF_F_Cur->getF_Next());
				}
				LF_F_Cur->setF_Next('\0');
			}
			this->PRINT(LF_F_Cur->getShortPath(), this->getGraphRoot(), LF_F_Cur->getFrom());

			m_fout << "allocated Request\t: " << LF_F_Cur->getIndex() << "\t" << LF_F_Cur->getBandwidth();
			for (int j = 0; LF_F_Cur->getShortPath()[j].getID() != '\0'; j++)
			{
				m_fout << "\t" << LF_F_Cur->getShortPath()[j].getID();
			}
			m_fout << endl;
		}
		prev_LF_F_Cur = LF_F_Cur;
		LF_F_Cur = LF_F_Cur->getLF_F_Next();
	}

	m_fout << endl;
	m_fout << "------------------------------------end realloc--------------------------------" << endl << endl;
	

}

void Manager::MakeCostArr(node* GraphRoot)
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
		for (int j = 0; j < count; j++)
		{
			CostArray[i][j] = INT_MAX;
		}
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
	COUNT = count;
}
node* Manager::MakeShortPath(char From, char To, node* GraphRoot)
{
	node* pFrom = GraphRoot, *pCur = NULL;
	node* pTo = GraphRoot;

	int* D;		//CostArray[X][i]
	bool* S;	//selected node group

	this->MakeCostArr(this->getGraphRoot());
	S = new bool[COUNT];
	for (int i = 0; i < COUNT; i++)
	{
		S[i] = false;
	}
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

	for (int i = 0; i < COUNT; i++)		//D배열은 From에서 To로 갈 수있는 edge의 cost 집합.
	{
		D[i] = CostArray[pFrom->getIndex()][i];
	}

	edge* ppCur = pFrom->getEdge();
	edge* pTemp = '\0';
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

					edge* newEdge = new edge;
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

edge* Manager::find(int v1, int v2)
{
	node* dTemp = this->getGraphRoot();
	edge* rTemp = '\0';
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

void Manager::PRINT(node* path, node* adjList, char from)
{
	int i = 0, j = 0, cnt = 0;
	node* ShortestPath;
	node temp;

	node* pCur = '\0';
	node* ppCur = adjList;
	m_fout << "\t------------------------make shortest path----------------------------";
	while (ppCur)
	{
		int i = 0;
		cnt = 0;
		ShortestPath = new node[COUNT];
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

void Manager::consoleprint()
{
	request* S_ROOT = S_REQ_ROOT;
	request* F_ROOT = F_REQ_ROOT;
	cout << "success request" << endl;
	while (S_ROOT)
	{
		cout << S_ROOT->getIndex();
		S_ROOT = S_ROOT->getS_Next();
	}
	cout << endl;
	cout << "deferred request" << endl;
	while (F_ROOT)
	{
		cout << F_ROOT->getIndex();
		F_ROOT = F_ROOT->getF_Next();
	}
}