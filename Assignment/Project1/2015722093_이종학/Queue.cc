#include "Queue.h"


Queue::Queue() //constructor
{
	pHead = '\0'; //initialzation
}


Queue::~Queue() //destructor
{
	WordNode *pWork;

	pWork = pHead;
	while (pHead != NULL) //until pHead is nothing
	{
		pHead = pWork->GetNext();
		delete pWork; //delete Node
		pWork = pHead;
	}
}

void Queue::Push(WordNode *Node) //Push WordNode
{
	WordNode *pWork;

	if (Node == NULL) //There isn't Node
		return;
	pWork = pHead;
	Node->SetNext(NULL);
	if (pHead == NULL) //There isn't Queue
	{
		pHead = Node;
	}
	else
	{
		while (pWork->GetNext() != NULL) //until pWork is last Node
		{
			pWork = pWork->GetNext();
		}
		pWork->SetNext(Node);
	}
}

WordNode* Queue::Pop()
{
	WordNode *pWork;

	if (pHead == NULL) //There isn't Queue
	{
		return 0;
	}
	pWork = pHead;
	pHead = pWork->GetNext();

	return pWork;
}

WordNode* Queue::Search(char * word) //Search Node
{
	WordNode *pWork;

	pWork = pHead;
	while (pWork != NULL) //until pWork isn't Node
	{
		if (strcmp(pWork->GetWord(), word) == 0) //Search Node
		{
			return pWork; //return Search Node
		}
		else //Not Search Node
		{
			pWork = pWork->GetNext();
		}
	}
	return 0; //In the absence of Node
}

bool Queue::Print()
{
	WordNode *pWork;
	ofstream flog; //Write file
	flog.open("log.txt", ios::app); //file open

	if (pHead == NULL) //In the absence of Node
	{
		return 0; //Error
	}
	pWork = pHead;
	flog << "======== PRINT ========" << endl;
	while (pWork != NULL) //until pWork is last Node
	{
		flog << pWork->GetWord() << " " << pWork->GetMean() << endl;
		pWork = pWork->GetNext();
	}
	flog << "====================" << endl;
	flog.close(); //file close
	return 1; //Success
}

bool Queue::Save() //Save Word
{
	ofstream fout; //write file
	fout.open("to_memorize_word.txt"); //file open

	if (!fout) //if file is not open
	{
		return 0; //Error
	}

	WordNode *pWork;
	pWork = pHead;
	while (pWork != NULL) //until pWork is last Node
	{
		fout << pWork->GetWord() << " " << pWork->GetMean() << endl;
		pWork = pWork->GetNext();
	}

	fout.close(); //file close
	return 1; //Success
}
