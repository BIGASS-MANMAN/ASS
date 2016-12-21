#include "Queue.h"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

Queue::Queue()
{
	pHead = '\0';		// Head pointer
}


Queue::~Queue()
{
	if (!pHead)		// If Queue is empty
		return;

	WordNode * pCur = 0;
	while (pHead)		// While Queue is not empty
	{
		pCur = pHead;			// pCur point first node
		pHead = pHead->GetNext();	// pHead point next node
		pCur->SetNext(0);		// Set first node's Next pointer 0
		delete pCur;			// Delete first node
	}
}


void		Queue::Push(WordNode * node)	// LOAD, ADD
{
	if (!pHead)		// If Queue is empty
	{
		pHead = node;	// Head pointer point the new node
		return;
	}

	WordNode * pCur = pHead;	// pCur point first node
	while (pCur->GetNext())		// Until pCur point end node
	{
		if (!strcmp(pCur->GetWord(), node->GetWord()))	// If new node's word is duplicated
			return;

		pCur = pCur->GetNext();	// pCur point next node
	}
	if (!strcmp(pCur->GetWord(), node->GetWord()))	// If new node's word is duplicated
		return;
	pCur->SetNext(node);	// pCur point new node
}


WordNode *	Queue::Pop()		// MOVE
{
	if (!pHead)		// If Queue is empty
		return 0;
	
	WordNode * pCur = pHead;		// pCur point first node
	pHead = pHead->GetNext();		// pHead point next node
	pCur->SetNext(0);			// Set the first node's next pointer 0
	return pCur;				// Return that node
}


WordNode *	Queue::Search(char * word)	// SEARCH, UPDATE
{
	if (!pHead)		// If Queue is empty
		return 0;

	WordNode * pCur = pHead;	// pCur point first node
	while (pCur)			// Explore Queue
	{
		if (strcasecmp(pCur->GetWord(), word) == 0)	// Compare word non case-sensitive, if same word
			return pCur;
		pCur = pCur->GetNext();		// pCur point next node
	}
	return 0;
}


bool		Queue::Print()		// PRINT
{
	ofstream fout("log.txt", ios::app);	// open the log.txt

	if (!pHead)			// If Queue is empty
		return false;

	WordNode * pCur = pHead;	// pCur point first node
	fout << "======== PRINT ========" << endl;
	cout << "======== PRINT ========" << endl;
	while (pCur)			// Explore Queue
	{
		fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		pCur = pCur->GetNext();		// pCur point next node
	}
	fout << "=======================" << endl << endl;
	cout << "=======================" << endl << endl;
	fout.close();
	return true;
}


bool		Queue::Save()		// SAVE
{
	if (!pHead)			// If Queue is empty
		return false;

	ofstream fout("to_memorize_word.txt");	// open the text file
	
	WordNode * pCur = pHead;	// pCur point first node
	while (pCur)			// Explore Queue
	{
		fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		pCur = pCur->GetNext();		// pCur point next node
	}
	fout.close();
	return true;
}
