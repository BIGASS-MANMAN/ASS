#include "Queue.h"
#include <iostream>
#include <fstream>
using namespace std;

Queue::Queue()
{
	pHead = '\0';
}


Queue::~Queue()
{
	/* You must fill here */

}

WordNode * Queue::GetpHead()
{
	return pHead;
}

void	Queue::Push(WordNode * node)	// LOAD, ADD
{
	if(!pHead) 
		pHead = node;
	else {
		WordNode * _TempNode = pHead;
		while(_TempNode->GetNext()) {
			_TempNode = _TempNode->GetNext();
		}
		_TempNode->SetNext(node);
	}
}

WordNode * Queue::Pop() // MOVE
{
	if(!pHead) 
		throw "Not having words";

	WordNode * _TempNode = pHead;
	pHead = pHead->GetNext();
	return _TempNode;
}

WordNode * Queue::Search(char * word)	// SEARCH, UPDATE
{
											// no word

	if(!pHead) throw "No Word";				// yes word

	WordNode * _TempNode = pHead;
	while(_TempNode) {
		if(!strcmp(_TempNode->GetWord(),word))
			return _TempNode;
		_TempNode = _TempNode->GetNext();
	}
}

bool	Queue::Print()	// PRINT
{
	ofstream FILEOUT;
	FILEOUT.open("log.txt", ios::app);

	WordNode *TempNode = pHead;
	if (!TempNode) return false;					// ERROR CASE; "TO_MEMORIZE" word list does not exist

	FILEOUT << "======== PRINT ========" << endl;
	while (TempNode) {
		FILEOUT << TempNode->GetWord() << " " << TempNode->GetMean() << endl;
		TempNode = TempNode->GetNext();
	}
	FILEOUT << "=======================" << endl << endl;

	FILEOUT.close();
}

bool	Queue::Save()	// SAVE
{
	return 0;
}