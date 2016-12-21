#include "Queue.h"
#include <fstream>
#include <iostream>
using namespace std;
Queue::Queue()
{    
	pHead = '\0';
}

Queue::~Queue()
{
	WordNode*pCur = pHead;

	while (pCur) { // pCur is not NULL, repeat.
		pHead = pHead->GetNext();
		delete pCur;
		pCur = pHead;
	}
}

void Queue::Push(WordNode * node) {
	WordNode * pCur;
	
	if (pHead == NULL) // if queue is empty
		pHead = node;
	else { // if queue is not empty
		pCur = pHead;

		while (pCur->GetNext() != NULL)  // repeat, when pCur is last node of queue, exit.
			pCur = pCur->GetNext();

		pCur->SetNext(node); // new node is next of pCur.
	}
}

WordNode* Queue::Pop()
{
	if (pHead == NULL) // if no node in queue
		return NULL;

	WordNode * pCur = pHead;
	pHead = pCur->GetNext();

	pCur->SetNext(NULL); // reset of pCur's node pointer
	return pCur; // delete pCur.
}

WordNode* Queue::Search(char*word) 
{
	WordNode*pCur = pHead;
	while (pCur) { // if pCur is not NULL
		if (strcasecmp(pCur->GetWord(), word) == 0) // if pCur's word = search word
			return pCur;
		else
			pCur = pCur->GetNext();
	}

	return NULL; // fail to search
}

bool Queue::Print() {
	WordNode*pCur = pHead;

	if (pHead == NULL) // no node in queue
		return false;
	else { // node exist in queue -> PRINT
		ofstream foutprintq;
		foutprintq.open("log.txt", ios::app);
		cout << "======== PRINT ========" << endl;
		foutprintq << "======== PRINT ========" << endl;

		while (pCur) {
			cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
			foutprintq << pCur->GetWord() << " " << pCur->GetMean() << endl;
			pCur = pCur->GetNext();
		}

		cout << "=======================" << endl << endl;
		foutprintq << "=======================" << endl << endl;
		return true;
	}
}

bool Queue::Save() {
	WordNode*pCur = pHead;

	if (pHead != NULL) { // node exist in queue
		ofstream fout;
		fout.open("to_memorize_word.txt");

		while (pCur) {
			fout << pCur->GetWord() << "," << pCur->GetMean() << endl;
			pCur = pCur->GetNext();
		}

		fout.close();
		return true;
	}
	else
		return false; // no node in queue
}
