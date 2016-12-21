#include "Queue.h"
/************************************************************/
/*This is Queue.cc that structred Queue						*/
/*Also, It is declaration about Queue Class					*/
/************************************************************/
Queue::Queue()
{
/*Contructor assigns pHead, pTail to NULL					*/
	pHead = '\0';
	pTail = '\0';
}

Queue::~Queue()
{
/* Destructor free all dynamic memory used in this.			*/
/* I implemented this 2 STEP.								*/
/*		1. pCur progress from pHead to NULL					*/
/*		2. delete Temp that copied pCur at that point.		*/
	WordNode *pCur = pHead;
	WordNode *temp = '\0';
	while(pCur) {
		temp = pCur;
		pCur = pCur->GetNext();
		delete temp;
	}
}

void Queue::Push(WordNode *node) {
/* Push seems like Linked-List.								*/
/* So, new Node must connect rear's Next					*/
	WordNode *pCur = pHead;
	if(!pHead) pHead=pTail=node;
	else {
		while(pCur->GetNext()) pCur=pCur->GetNext();
		pCur->SetNext(node);
		pTail = node;
	}
}

WordNode *Queue::Pop() {
/* Queue Structures do FIFO(First-In, First-Out).					*/
/* So, returns front's node, and re-define front's next to front	*/
	WordNode *pCur = pHead;
	if(!pHead) return NULL;
	pHead = pHead->GetNext();
	pCur->SetNext(NULL);
	return pCur;
}

WordNode *Queue::Pop_back() {
/* I hope to implement like Stack Structures or Dequeue in STL Lib.	 */
/* So, this functions pop rear, and re-deine rear's previous to rear */
	WordNode *pCur = pHead;
	WordNode *temp = NULL;
	if(!pHead) return NULL;
	if(pHead==pTail) {
		temp = pHead;
		pHead = pTail = NULL;
		return temp;
	}
	while(pCur->GetNext()!=pTail) {
		pCur = pCur->GetNext();
	}
	temp=pTail;
	pTail=pCur;
	pTail->SetNext(NULL);
	return temp;
}

WordNode *Queue::Search(char *word) {
/* It is the Search about Queue											*/
/* can implement to use strcmp() with parameters both word in the pair	*/
	WordNode *pCur = pHead;
	while(pCur) {
		if(strcmp(pCur->GetWord(),word)) pCur = pCur->GetNext();
		else return pCur;
	}
	return NULL;
}

WordNode *Queue::top() {
/* it returns pTail */
	return pTail;
}
bool Queue::Print() {
/* it prints all WordNodes from pHead to pTail */
	WordNode *pCur = pHead;
	if(!pHead) return false;
	ofstream log(LOG_FILENAME,ios::app);
	log<<"========= PRINT ========\n";
	while(pCur) {
		log<<pCur->GetWord()<<" "<<pCur->GetMean()<<"\n";
		pCur=pCur->GetNext();
	}
	log<<"========================\n\n";
	log.close();
	return true;
}

bool Queue::Save() {
/*it copies all data ranged in pHead to pTail from MEMORY to DISK(.txt)*/ 
	WordNode *temp = pHead;
	ofstream f(TO_MEMORIZE_FILENAME);
	if (!f) return false;
	while(temp) {
		f << temp->GetWord() << "\t" << temp->GetMean() << endl;
		temp = temp->GetNext();
	}
	f.close();
	return true;
}

bool Queue::isEmpty() {
/* if pHead is NULL, it returns true								*/
	return pHead? false : true;
}
