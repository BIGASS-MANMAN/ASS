#include "CircularLinkedList.h"
/************************************************************/
/*This is CircularLinkedList.cc that structred CLL			*/
/*Also, It is declaration about CircularLinkedList Class	*/
/************************************************************/
CircularLinkedList::CircularLinkedList()
{
/*Constructor assigns pHead, pTail to NULL.					*/
	pHead = '\0';
	pTail = '\0';
}


CircularLinkedList::~CircularLinkedList()
{
/* Destructor free all dynamic memory used in this.			*/
/* I implemented this 2 STEP.								*/
/*		1. reassign pHead to pHead's Next.					*/
/*		2. delete previos pHead.							*/
	WordNode *pTemp;

	while(pHead) {
		if(pHead->GetNext()==pHead) { // in case that stored one node.
			delete pHead;
			break;
		}
		pTemp = pHead;
		pHead = pHead->GetNext();
		pTail->SetNext(pHead);
		delete pTemp;
	}
}

void CircularLinkedList::Insert(WordNode * node) {
/* It is the insertion about Circular Linked-List Structure.	*/
/* If CLL is empty, assign node to root.						*/
/* If not, Insert the node as tail's Next						*/
/* pNext of the node that will be inserted MUST INDICATE pHEAD	*/
	if(!pHead) {
		pHead=node;
		pHead->SetNext(pHead);
	}
	else {
		node->SetNext(pHead);
		pTail->SetNext(node);
	}
	pTail = node;
}

WordNode * CircularLinkedList::Search(char * word) {
/* It is the Search about Circular Linked-List							*/
/* can implement to use strcmp() with parameters both word in the pair	*/
	WordNode *pCur = pHead;
	if(pCur) do {
		if(strcmp(pCur->GetWord(),word)) pCur = pCur->GetNext();
		else return pCur;
	} while(pCur!=pHead);
	return NULL;
}

bool CircularLinkedList::Print() {
/*It prints all pairs from pHead to pTail in this structure.	*/
	WordNode *pCur = pHead;
	if(!pHead) return false;
	ofstream log(LOG_FILENAME,ios::app);
	log<<"======== PRINT ========\n";
	do {
		log<<pCur->GetWord()<<" "<<pCur->GetMean()<<"\n";
		pCur=pCur->GetNext();
	} while(pCur!=pHead);
	log<<"=======================\n\n";
	log.close();
	return true;
}

bool CircularLinkedList::Save() {
/*it copies all data ranged in pHead to pTail from MEMORY to DISK(.txt)*/ 
	WordNode *temp = pHead;
	ofstream f(MEMORIZED_FILENAME);
	if (!(f&&temp)) return false;
	do {
		f << temp->GetWord() << "\t" << temp->GetMean() << endl;
		temp = temp->GetNext();
	} while (temp!=pHead);
	f.close();
	return true;
}

bool CircularLinkedList::isEmpty() {
/* if pHead is NULL, it returns true								*/
	return pHead ? false : true;
}
