#include "CircularLinkedList.h"

CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
}
CircularLinkedList::~CircularLinkedList()//delete cll
{
	WordNode *pCur = pHead;
	
	if (pHead == NULL)
		return;
	while (1)//find tail and set next NULL
	{
		if (pCur->GetNext() == pHead)
			break;
		pCur = pCur->GetNext();
	}
	pCur->SetNext(NULL);
	
	//delete node untill tail
	while (pHead)
	{
		pCur = pHead;
		pHead = pHead->GetNext();
		delete pCur;
	}
}
WordNode* CircularLinkedList::Get_Head()
{
	return pHead;
}
void CircularLinkedList::Insert(WordNode * node)			// LOAD, TEST
{
	if (pHead == NULL)//if pHead is empty, it is fitst insert
		pHead = node;
	else
	{
		WordNode *pCur = pHead;
		while (pCur->GetNext())//search a last insert node            
		{
			if (pCur->GetNext() == pHead)  //if next of pCur is pHead,it is last node
				break;
			pCur = pCur->GetNext();
		}
		pCur->SetNext(node);    //set next
		node->SetNext(pHead);  //connect to pHead
	}
}
WordNode *	CircularLinkedList::Search(char * word)				// SEARCH, UPDATE
{
	WordNode* pCur = pHead;
	if (pCur == NULL)        //if pHead is empty,it have not node
		return NULL;

	while (pCur)
	{
		if (strcmp(pCur->GetWord(), word) == 0)   //it search same word
			break;
		else
			pCur = pCur->GetNext(); //if word and word of pCur different, go to next

		if (pCur == pHead)  //if pCur is last node, no same word
			return NULL;
	}
	return pCur;
}
bool		CircularLinkedList::Print()							// PRINT
{
	WordNode *pCur = pHead;

	if (pHead == NULL)        //if it have not node
		return false;

	ofstream fout;
	fout.open("log.txt", ios::app);

	fout << "==========print===========" << endl;
	while (pCur)//print
	{
		fout << pCur->GetWord() << "	" << pCur->GetMean() << endl;
		pCur = pCur->GetNext();
		if (pCur == pHead)  //it mean that already print all node
			break;
	}
	fout << "==========================" << endl << endl;
	fout.close();
	return true;
}
bool		CircularLinkedList::Save()								// SAVE
{
	ofstream fout;
	fout.open("memorized_word.txt", ios::app);

	WordNode* pCur = pHead;

	while (pCur)// print
	{
		fout << pCur->GetWord() << "	" << pCur->GetMean() << endl;
		pCur = pCur->GetNext();

		if (pCur == pHead)
			break;
	}

	fout.close();//fileclose
	return true;
}