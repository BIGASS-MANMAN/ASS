#include "CircularLinkedList.h"


CircularLinkedList::CircularLinkedList() //constructor
{
	pHead = '\0';
}


CircularLinkedList::~CircularLinkedList() //destructor
{
	WordNode *pWork, *pWork2;

	if (pHead == NULL) //In the absence of list
	{
		return; //Error
	}
	pWork = pHead->GetNext();
	if (pWork == pHead) //clrcularLinkedList have one Node
	{
		delete pHead; //delete Node
		return;
	}
	while (1)
	{
		pWork2 = pWork; //pWork2 = pPrev
		if (pWork2 == pHead) //pWork2 is last Node
		{
			delete pWork2; //delete Node
			break;
		}
		pWork = pWork->GetNext();
		delete pWork2; //delete Node
	}
}

void CircularLinkedList::Insert(WordNode * node) //Insert Node
{
	WordNode *pWork;

	if (pHead == NULL) //In the absence of list
	{
		pHead = node;
		node->SetNext(pHead);
	}
	else
	{
		pWork = pHead;
		while (pWork->GetNext() != pHead) //until pWork is last Node
		{
			pWork = pWork->GetNext();
		}
		pWork->SetNext(node);
		node->SetNext(pHead);
	}
}

WordNode* CircularLinkedList::Search(char * word) //Search Node
{
	WordNode *pWork;

	if (pHead == NULL) //In the absence of list
	{
		return 0;
	}
	pWork = pHead;
	while (1)
	{
		if (strcmp(pWork->GetWord(), word) == 0) //Search Word
		{
			return pWork; //return Search Word
		}
		else
		{
			if (pWork->GetNext() == pHead) //pWork is last Node
			{
				break;
			}
			pWork = pWork->GetNext();
		}
	}
	return 0; //Not find Word
}

bool CircularLinkedList::Print() //Print list
{
	WordNode *pWork;

	if (pHead == NULL) //In the absence of list
	{
		return 0; //Error
	}
	else
	{
		pWork = pHead;
		ofstream flog;
		flog.open("log.txt", ios::app);
		flog << "======== PRINT ========" << endl;
		while (1)
		{
			if (pWork == NULL)
			{
				break;
			}
			flog << pWork->GetWord() << " " << pWork->GetMean() << endl;
			pWork = pWork->GetNext();
			if (pWork == pHead) //pWork is last Node
			{
				break;
			}
		}
		flog << "====================" << endl << endl;
		flog.close(); //file open
		return 1; //Success
	}
}

bool CircularLinkedList::Save() //Save list
{
	ofstream fout; //write file
	fout.open("memorized_word.txt"); //file open

	if (!fout) //file is not open
	{
		cout << "400" << endl;
		return 0;//Error
	}

	WordNode *pWork;
	pWork = pHead;
	while (pWork != NULL) //until pWork is last Node
	{
		fout << pWork->GetWord() << " " << pWork->GetMean() << endl; //file out
		pWork = pWork->GetNext();
		if (pWork == pHead) //pWork is last Node
		{
			break;
		}
	}

	fout.close(); //write flie close
	return 1; //Success
}
