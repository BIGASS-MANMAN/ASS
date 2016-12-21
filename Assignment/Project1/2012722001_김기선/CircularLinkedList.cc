#include "CircularLinkedList.h"
#include "Manager.h"


CircularLinkedList::CircularLinkedList()	//constructor 
{
	pHead = NULL;		//reset
}


CircularLinkedList::~CircularLinkedList()	//Destructor
{
	
	if (pHead == NULL)
		return;

	WordNode* pCur = pHead;
	WordNode* pTemp = pCur;

	while (1)
	{
		if (pCur == NULL)
			return;

		pTemp = pCur;
		pCur = pCur->GetNext();
		pTemp->SetNext(NULL);
		pTemp = NULL;
		delete pTemp;
	}
	

}

WordNode* CircularLinkedList::Gethead()		//return head
{
	return pHead;
}

void CircularLinkedList::Insert(WordNode * node)			// LOAD, TEST
{
	WordNode* pCur = pHead;		//reset
	if (pHead == NULL)			//if empty
		pHead = node;			//head appointed
	else                       //head isn't empty
	{
		while (pCur->GetNext() != NULL&&pCur->GetNext() != pHead)	//loop for search the location
			pCur = pCur->GetNext();			//move to the next addess
		pCur->SetNext(node);				//set the next addess
		node->SetNext(pHead);				//set the next addess for circulary system
	}
}

WordNode* CircularLinkedList::Search(char * word)				// SEARCH, UPDATE
{

	WordNode* pCur = pHead;		//reset
	if (pHead == NULL)			//if empty
		return 0;				//return for error message
	while (1)
	{
		Manager manager;		//declaration
		if (word != NULL)		//if not empty
		{
			if (strcmp(pCur->GetWord(), word) == 0)	//if success the search
				return pCur;					//return Current address values
			pCur = pCur->GetNext();				//move to the next addess		
			if (pCur == pHead)					//if variable is moved to the last
				return 0;						//return for error message
		}
		else                    //if empty
			return 0;			//return for error message
	}
}

bool CircularLinkedList::Print()                     // PRINT
{
	ofstream fout("log.txt", ios::app);		//file open		
	WordNode* pCur = pHead;			//reset to head
	if (pHead == NULL)			//if empty
	{
		fout.close();			//file close
		return 0;					//return for error message
	}
		
	else
	{
		fout << "======== PRINT ========" << endl;
		while (1)
		{
			fout << pCur->GetWord() << "\t" << pCur->GetMean() << endl;
			pCur = pCur->GetNext();
			if (pCur == pHead || pCur == NULL)	//if the variable located in last node
				break;
		}
		fout << "=======================" << endl << endl;
		fout.close();	//file close
		return 1;	//success
	}
}

bool CircularLinkedList::Save()								// SAVE
{
	ofstream fout;			//file variable
	fout.open("memorized_word.txt");	//file open
	if (pHead == NULL)		//if empty
	{
		fout.close();		//file close
		return 0;			//return 0
	}
	else
	{
		WordNode* pCur = pHead;		//reset to head
		while (1)
		{
			if (pCur->GetNext() == pHead || pCur->GetNext() == NULL)			//if the variable located in last node's prev
				fout << pCur->GetWord() << "\t" << pCur->GetMean();			//print to the file not include "endl"
			else
				fout << pCur->GetWord() << "\t" << pCur->GetMean() << endl;
			pCur = pCur->GetNext();
			if (pCur == pHead || pCur == NULL)						//the variable located in last node
				break;
		}
		fout.close();			//file close
		return 1;
	}
}
