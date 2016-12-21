#include "CircularLinkedList.h"

CircularLinkedList::CircularLinkedList()
{
	pHead = '\0'; // pHead set NULL
}


CircularLinkedList::~CircularLinkedList()
{
	if (pHead != NULL) { // if node exist in queue,

		WordNode * pCur = pHead->GetNext(); // pCur point the node that pHead->Next
		WordNode * pTemp = pHead; // pTemp point the pHead node

		if (pHead == pCur) // only one node in circular,
			delete pCur; // delete that node.
		else { // if circular have two or more nodes,
			while (pCur->GetNext() != pHead) { // if pCur->Next is not pHead, Repeat while.
				pTemp = pCur->GetNext(); // pTemp point pCur->Next

				delete pCur; // delete pCur
				pCur = pTemp; // pCur point pCur->Next
			}
			delete pCur; // delete.
			delete pHead; // delete.
		}
	}
}
