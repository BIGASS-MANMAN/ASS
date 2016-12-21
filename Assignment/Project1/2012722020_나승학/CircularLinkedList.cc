#include "CircularLinkedList.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

CircularLinkedList::CircularLinkedList()		
{
	pHead = '\0';	// CircularLinkedList phead set NULL
	pTail = '\0';	// CircularLinkedList ptail set NULL
}


CircularLinkedList::~CircularLinkedList()
{
	WordNode* p = pHead, *pp = 0;	// word node pointer p set phead, pointer pp set 0
	if (!pHead)return;				// If condition is not phead, then return
	if (pHead == pTail) {			// If condition, phead eq ptail
		delete pHead;				// Delete phead
		return;						// return
	}
	p=pHead->GetNext();				// set p as next node of pHead
	pHead->SetNext(0);				// phead pointing setnext
	while(p) {						// Active function
		pp = p;						// set pp as p
		p = p->GetNext();			// p is p pointing getnext
		delete pp;					// Delete pp
	}			// repetiton p is not phead
}

void		CircularLinkedList::Insert(WordNode * node)			// LOAD, TEST
{
	WordNode* p = pHead;		// word node pointer p set phead
	if (!pHead) {				// If condition is not phead
		pHead = node;			// phead set node
		pTail = node;			// ptail set node
		node->SetNext(node);	// node pointing setnext
	}
	else {						// or
		pTail->SetNext(node);	// ptail pointing setnext
		pTail = node;			// ptail set node
		pTail->SetNext(pHead);	// ptail pointing setnext
	}
}
WordNode *	CircularLinkedList::Search(char * word)				// SEARCH, UPDATE
{
	WordNode* p = pHead;									// word node pointer p set phead
	while (p) {												// repetiton
		if (strcmp(word, p->GetWord()) == 0)return p;		// If condition, string compare word and pointed p, then return p
		p = p->GetNext();									// p set p pointing getnext
	}
	return 0;												// end of function
}
bool		CircularLinkedList::Print()							// PRINT
{
	WordNode* p = pHead;										// word node pointer p set phead
	ofstream fout;												// open file stream fout
	if (!pHead)return 0;										// If condition is not phead, then end of function
	fout.open("log.txt", ios_base::app);						// open file
	fout << "======== PRINT ========" << endl;					// print inner file
	cout << "======== PRINT ========" << endl;
	do {														// Active function
		fout << p->GetWord() << "\t" << p->GetMean() << endl;	// print inner file
		cout << p->GetWord() << "\t" << p->GetMean() << endl;
		p = p->GetNext();										// p set p pointing getnext
	} while (p != pHead);										// repetiton
	fout << "=======================" << endl;
	cout << "=======================" << endl;
	fout.close();												// file close
	return 1;													// return value 1
}
bool		CircularLinkedList::Save()							// SAVE
{
	WordNode * p = pHead;										// word node pointer p se phead
	ofstream fout;												// open file stream fout
	fout.open("memorized_word.txt", ios_base::out);				// open file
	if (!fout.is_open() || !p)return 0;							// is not openr, then end of function
	do {														// Active function
		fout << p->GetWord() << "\t" << p->GetMean() << endl;	// print inner file
		p = p->GetNext();										// p set p pointing getnext
	}while (p != pHead);										// repetiton p is not p head
	fout.close();												// close file
	return 1;													// return value 1
}

WordNode *	CircularLinkedList::Delete(WordNode * node)
{
	WordNode *p = pHead, *pp = '\0';		// word node pointer p set phead, pointer pp set 0
	while (p != node) {					// repetiton
		pp = p;							// pp set p
		p = p->GetNext();				// p set p pointing getnext
	}
	pp->SetNext(p->GetNext());			// pp pointing setnext
	return p;							// return value p
}

bool	CircularLinkedList::IsEmpty()
{
	if (pHead)return 0;					// is phead, then end of function
	else return 1;						// or return 1
}
