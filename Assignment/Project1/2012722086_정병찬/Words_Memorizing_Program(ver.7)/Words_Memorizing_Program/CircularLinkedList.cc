#include "CircularLinkedList.h"



CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
}

CircularLinkedList::~CircularLinkedList()
{
}

void CircularLinkedList::Insert(WordNode * node)	// Insert a node in circular linked list
{
	WordNode * t = new WordNode;
	t = node;

	if (pHead == NULL)		// If no node exists yet
	{
		t->SetNext(t);
		pHead = t;
		return;
	}
	WordNode *temp = pHead;		// put "pHead" in "temp"
	while (temp->GetNext() != pHead)	// Until "temp" reaches right before "pHead"
	{
		temp = temp->GetNext();
	}
	temp->SetNext(t);
	t->SetNext(pHead);

}

WordNode * CircularLinkedList::Search(char * word)
{
	pSearch = pHead;
	if (pHead == NULL) return NULL;
	while (1)		// Starting from "pHead", search the node with the word received as parameter
	{

		if (!strcmp(pSearch->GetWord(), word))
			return pSearch;
		else
			pSearch = pSearch->GetNext();
		if (pSearch == pHead) break;
	}
	return NULL;
}

bool CircularLinkedList::Print()
{
	pPrint = pHead;		// Start from "pHead"
	if (pPrint == NULL)
		return false;
	cout << "======== PRINT ======== " << endl;

	while (1)	// Print the word and meaning of nodes until "pPrint" reaches "pHead" again.
	{
		cout << pPrint->GetWord() << " " << pPrint->GetMean() << endl;
		pPrint = pPrint->GetNext();
		if (pPrint == pHead) break;
	}
	cout << "=======================" << endl;
	return true;
}

bool CircularLinkedList::Save()
{
	ofstream fout;
	fout.open("memorized_word.txt", ios::trunc);		// Open the file to fix and save it
	pSave = pHead;
	if (pSave == NULL)
		return false;
	while (1)		// Starting from the next of "pHead", put the word and meaning in file until "pSave" reaches "pHead"
	{
		fout << pSave->GetWord() << " " << pSave->GetMean() << endl;
		pSave = pSave->GetNext();
		if (pSave == pHead) break;
	}
	fout.close();
	return true;
}

