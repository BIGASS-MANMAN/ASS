#include "CircularLinkedList.h"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;


CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';		// Head pointer
}


CircularLinkedList::~CircularLinkedList()
{
	if (!pHead)		// If CLL is empty
		return;

	WordNode * pCur = 0;
	WordNode * pTemp = pHead;
	do {
		pCur = pHead;
		pHead = pHead->GetNext();
		delete pCur;
	} while (pHead != pTemp);
}


void		CircularLinkedList::Insert(WordNode * node)			// LOAD, TEST
{
	if (!pHead)		// If CLL is empty
	{
		pHead = node;			// Head pointer point the new node
		pHead->SetNext(pHead);		// Set the Next pointer
		return;
	}

	WordNode * pCur = pHead;
	while (pCur->GetNext() != pHead)	// Until the end node
		pCur = pCur->GetNext();		// Point the next node
	pCur->SetNext(node);			// pCur point the new node (Insert)
	node->SetNext(pHead);			// New node point the head pointer (Circular)
}


WordNode *	CircularLinkedList::Search(char * word)		// SEARCH, UPDATE
{
	if (!pHead)		// If CLL is empty
		return 0;
	
	WordNode * pCur = pHead;
	do {
		if (strcasecmp(pCur->GetWord(), word) == 0)	// If find the word
			return pCur;
		pCur = pCur->GetNext();
	} while (pCur != pHead);		// Explore until the end node
	return 0;
}


bool		CircularLinkedList::Print()		// PRINT
{
	ofstream fout("log.txt", ios::app);	// Open the log.txt

	if (!pHead)		// If CLL is empty
		return false;

	WordNode * pCur = pHead;
	fout << "======== PRINT ========" << endl;
	cout << "======== PRINT ========" << endl;
	do {
		fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		pCur = pCur->GetNext();
	} while (pCur != pHead);		// Explore until the end node
	fout << "=======================" << endl << endl;
	cout << "=======================" << endl << endl;
	fout.close();
	return true;
}


bool		CircularLinkedList::Save()		// SAVE
{
	if (!pHead)		// If CLL is empty
		return false;

	ofstream fout("memorized_word.txt");	// Opene the file

	WordNode * pCur = pHead;
	do {
		fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		pCur = pCur->GetNext();
	} while (pCur != pHead);		// Explore until the end node
	fout.close();
	return true;
}
