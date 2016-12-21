#include "Queue.h"
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

	
Queue::Queue()			// Constructor
{
	pHead = '\0';		// set initial pHead is NULL
	pTail = '\0';		// set initial pTail is NULL
	WordCnt = 0;		// word current set 0
}


Queue::~Queue()			// Destructor
{
	
	WordNode*p = pHead, *pp = '\0';	// word node Pointer p set phead, pointer pp set 0
	while (p) {						// repetition
		pp = p;						// pointer pp set p
		p = p->GetNext();			// point p set p pointing getNext
		if (p == pp)p = '\0';			// If condition for p eq pp, then p set 0
		delete pp;					// Delete pp
	}
}

void		Queue::Push(WordNode * node)			// LOAD, ADD
{
	WordNode* temp = pTail;		// word node pointer temp, initial temp set pTail
	if (!pHead) {				// is not phead
		pHead = node;			// phead set node
		pTail = node;			// pTail set node
	}		
	else{						// or
		pTail->SetNext(node);	// ptail pointing setNext
		pTail = node;			// ptail set node
	}
	WordCnt++;					// increasing 1, word current wordcnt 
}
WordNode *	Queue::Pop()							// MOVE
{
	WordNode* temp = pHead;			// word node pointer temp set phead
	if(IsEmpty())return 0;			// is not, then end of function
	else {							// or
		temp = pHead;				// temp set phead
		pHead = pHead->GetNext();	// phead set pointing getnext
		if (pHead == 0)pTail = '\0';	// If condition phead eq 0, then ptail set 0
		temp->SetNext('\0');			// temp pointing setnext
		WordCnt--;					// word current wordcnt decrease 1
		return temp;				// return value is temp
	}
	return 0;						// end of function
}
WordNode *	Queue::Search(char * word)				// SEARCH, UPDATE
{
	WordNode* p = pHead;								// word node pointer p set phead
	while (p) {											// repetition
		if (strcmp(p->GetWord(), word) == 0)return p;	// If condition, string compare, p and getword, then return p
		p = p->GetNext();								// p set p pointing getNext
	}
	return 0;											// end of function
}
bool		Queue::Print()							// PRINT
{
	ofstream fout;														// open file stream fout
	WordNode* p = pHead;												// wordnode pointer p set phead
	if (!pHead)return 0;												// is not phead, then end of function
	else {																// or
		fout.open("log.txt", ios_base::app);							// open file
		fout << "======== PRINT ========" << endl;						// print inner file
		cout << "======== PRINT ========" << endl;
		while(p){														// repetiton
			fout << p->GetWord() << "\t" << p->GetMean() << endl;		// print inner file
			cout << p->GetWord() << "\t" << p->GetMean() << endl;
			p = p->GetNext();											// p set p pointing getNext
		}
		fout << "=======================" << endl;
		cout << "=======================" << endl;
		fout.close();													// file close
		return 1;														// return value 1
	}
}
bool		Queue::Save()							// SAVE
{
	ofstream fout;													// open file stream fout
	WordNode * p = pHead;											// word node pointer p set phead
	fout.open("to_memorize_word.txt", ios_base::out);				// open file
	if (!p || !fout.is_open())return 0;								// is not open, then end of function
	while (p) {														// repetiton
		fout << p->GetWord() << '\t' << p->GetMean() << endl;		// print inner file
		p = p->GetNext();											// p set p pointing getnext
	}	
	fout.close();													// file close
	return 1;														// return value 1
}

bool		Queue::IsEmpty()
{
	if (pHead == 0)return 1;		// If condition phead eq 0, then return 1
	else return 0;					// or end of function
}

int			Queue::WordNumber()
{
	return WordCnt;					// return value word current wordcnt
}
