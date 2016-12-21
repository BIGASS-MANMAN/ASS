#include "CircularLinkedList.h"


CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
}


CircularLinkedList::~CircularLinkedList()
{
	if (pHead != '\0')		// node exist in CircularLinkedList
	{
		WordNode *temp, *cur;

		while(pHead->GetNext() != pHead)
		{ 
			cur = pHead;		// cur is last node
			temp = pHead->GetNext();

			while (cur->GetNext() != pHead)		// Search for last node
				cur = cur->GetNext();
			cur->SetNext(temp);		// Set last node's next node to temp

			// Deallocate head pointer
			if (pHead->GetWord() != '\0')
				delete[] pHead->GetWord();
			if (pHead->GetMean() != '\0')
				delete[] pHead->GetMean();
			delete pHead;

			pHead = temp;		// change head pointer
		}
		// Deallocate remained head pointer
		if (pHead->GetWord() != '\0')
			delete[] pHead->GetWord();
		if (pHead->GetMean() != '\0')
			delete[] pHead->GetMean();
		delete pHead;
	}
}

void CircularLinkedList::Insert(WordNode * node)	// LOAD, TEST
{
	if (pHead == '\0')	
	{ 
		node->SetNext(node);
		pHead = node;		// node is head pointer
	}
	else  // pHead has node
	{
		WordNode *cur = pHead;
		while (cur->GetNext() != pHead)		// Search for last word
			cur = cur->GetNext();
		
		cur->SetNext(node);		// insert node to end of CirculrLinkedList
		node->SetNext(pHead);	//inserted node's next node is head pointer
		
		return;
	}
}


WordNode *	CircularLinkedList::Search(char * word)		// SEARCH, UPDATE
{
	WordNode *cur = pHead;
	if (pHead == '\0')
		return 0;

	while (cur->GetNext() != pHead)
	{
		if (strcmp(cur->GetWord(),word)==0)		// if find a word
			return cur;		// return finded node
		cur = cur->GetNext();
	}

	// cur is last node in CirculrLinkedList
	if (strcmp(cur->GetWord(),word)==0)		// if find a word
		return cur;		// return found node
	else
		return 0;		// failure search
}


bool		CircularLinkedList::Print()		// PRINT
{
	if (pHead == '\0')
		return 0;
	else
	{	// print data to "log.txt" file and display
		ofstream fout;
		fout.open("log.txt", ios::app);		// Print 'MEMORIZED' word in "log.txt" file
		WordNode *cur = pHead;

		fout << "======== PRINT ========" << endl;
		cout << "======== PRINT ========" << endl;
		while (cur->GetNext() != pHead)
		{
			fout << cur->GetWord() << " " << cur->GetMean() << endl;
			cout << cur->GetWord() << " " << cur->GetMean() << endl;
			cur = cur->GetNext();
		}
		if (cur->GetNext() == pHead)		// end node in CircularLinkedList
		{
			fout << cur->GetWord() << " " << cur->GetMean() << endl;
			cout << cur->GetWord() << " " << cur->GetMean() << endl;
			fout << "=======================" << endl << endl;
			cout << "=======================" << endl << endl;
			fout.close();
		}
		return 1;
	}
}


bool		CircularLinkedList::Save()		// SAVE
{
	if (pHead == '\0')
		return 0;
	else
	{	// print data to "memorized_word.txt" file
		ofstream fout;
		fout.open("memorized_word.txt", ios::app);
		WordNode *cur = pHead;
		while (cur->GetNext() != pHead)
		{
			fout << cur->GetWord() << "\t" << cur->GetMean() << endl;
			cur = cur->GetNext();
		}
		if (cur->GetNext() == pHead)		// end node in CircularLinkedList
		{
			fout << cur->GetWord() << "\t" << cur->GetMean() << endl;
			fout.close();
		}
		return 1;
	}
}

