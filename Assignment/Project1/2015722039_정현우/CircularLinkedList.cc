#include "CircularLinkedList.h"

#include <fstream>
using namespace std;
CircularLinkedList::CircularLinkedList()			//constructor
{	
	pHead = NULL;									//pHead == NULL
}
CircularLinkedList::~CircularLinkedList()			//destructor
{
	if (pHead != NULL)								//pWork = pHead's Next and Loop pPrev is pWork and move pWork and delete pPrev
	{
		WordNode *pWork, *pPrev = NULL;				
		pWork = pHead->GetNext();
		while (pWork != pHead)
		{
			pPrev = pWork;
			pWork = pWork->GetNext();
			delete pPrev;
		}
		delete pHead;
	}
}

void		CircularLinkedList::Insert(WordNode * node)			// insert
{
	if (pHead) {												//if pHead exit
		WordNode *pWork = pHead;								//find circle's last and insert node at circle's last's next
		while (1) {
			if (pWork->GetNext() == pHead)	break;
			else pWork = pWork->GetNext();
		}
		pWork->SetNext(node);
		node->SetNext(pHead);
	}
	else {														//else pHead == node and pHead's next is pHead
		pHead = node;
		pHead->SetNext(pHead);
	}
}
WordNode *	CircularLinkedList::Search(char * word)				// Search
{
	WordNode *pWork = pHead;									
																//traslate word to little alphabet and copy
	char word2[100] = { 0 };
	int loop = 0;
	while (word[loop] != '\0')
	{
		if (word[loop] <= 90 && word[loop] >= 65)
		{
			word2[loop] = word[loop] + 32;
			loop++;
		}
		else
			break;
	}
	
	if (pWork == NULL) return NULL;								// pWork is NULL -> return NULL
	do															// while pHead != pWork and pWork's infomation != word or word2
	{
		if (!strcmp(pWork->GetWord(), word) || !strcmp(pWork->GetWord(), word2)) return pWork;
		else pWork = pWork->GetNext();							//pWork = pWork's Next
	} while (pWork != pHead);

	return NULL;
}
bool		CircularLinkedList::Print()							// Print
{
	if (!pHead) return 0;										//if pHead is NULL ,return 0
	Log.open("Log.txt", ios::app);								//onpen Lot.txt
	WordNode *pWork = pHead;
	cout << "======== PRINT ========" << endl;
	Log << "======== PRINT ========" << endl;
	do
	{
		cout << pWork->GetWord() << "  " << pWork->GetMean() << endl;//print all of Circle's node
		Log << pWork->GetWord() << "  " << pWork->GetMean() << endl;
		pWork = pWork->GetNext();
	} while (pWork != pHead);
	cout << "=======================" << endl;
	Log << "=======================" << endl;
	return 1;
}
bool		CircularLinkedList::Save()							// SAVE 
{
	if (!pHead) return 1;										//if pHead is empty , return 1
	WordNode *pWork = pHead;
	ofstream fo("memorized_word.txt");							//open memorized_word.txt
	if (pWork == NULL) return 1;
	do
	{															//save all of circle's node's infomation
		fo << pWork->GetWord() << "  " << pWork->GetMean() << endl;
		pWork = pWork->GetNext();
	} while (pWork != pHead);
	fo.close();													//close memorized_word.txt
	return 0;
}
