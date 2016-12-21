#include "Queue.h"

Queue::Queue()
{
	pHead = '\0';
	pPop = new WordNode;	// Do dynamic allocation with "pPop" in constructor
}

Queue::~Queue()
{
}

void Queue::Push(WordNode * node)	// Push the word node in queue
{
	WordNode * t = new WordNode;
	t = node;
	if (Search(node->GetWord())) return;
	if (pHead == NULL)	// If no node exists
	{
		pHead = t;
		pTail = t;
	}
	else
	{
		pTail->SetNext(t);
		pTail = t;
	}

}

WordNode * Queue::Pop()
{
	pPop = pHead;

	if (!IsEmpty())
	{
		return NULL;
	}

	pHead = pPop->GetNext();	// Move the "pHead" to its next node before doing pop
	return pPop;

}

bool Queue::IsEmpty()	// Check if the queue is empty
{
	if(pHead == NULL)	return false;
	else return true;
}

WordNode * Queue::Front()
{
	return pTail;
}

WordNode * Queue::Search(char * word)
{
	pSearch = pHead;
	if (pHead == NULL) return NULL;
	while (pSearch)		// Search the word from the "pHead"
	{
		if (!strcmp(pSearch->GetWord(), word))
			return pSearch;
		else
			pSearch = pSearch->GetNext();
	}
	return NULL;
}

bool Queue::Print()		// Print the contents of queue from "pHead" to the tail of queue
{
	pPrint = pHead;
	if (pPrint == NULL)
		return false;

	cout << "======== PRINT ========" << endl;
	while (pPrint != NULL)
	{
		cout << pPrint->GetWord() << " " << pPrint->GetMean() << endl;
		pPrint = pPrint->GetNext();
	}
	cout << "=======================" << endl;
	return true;
}

bool Queue::Save()
{
	ofstream fout;
	fout.open("to_memorize_word.txt", ios::trunc);
	pSave = pHead;
	if (pSave == NULL)
		return false;
	while (pSave != NULL)		// Starting from the "pHead", put the word and meaning in file until it reaches the end of queue
	{
		fout << pSave->GetWord() << " " << pSave->GetMean() << endl;
		pSave = pSave->GetNext();
	}
	fout.close();
	return true;
}

int Queue::count()
{
	int count = 0;
	WordNode * node = pHead;

	while (1) {		// Count the number of nodes
		count++;
		node = node->GetNext();
		if (node->GetNext() == NULL) break;
	}
	return count;
}