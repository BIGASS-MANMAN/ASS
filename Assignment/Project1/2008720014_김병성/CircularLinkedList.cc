#include "CircularLinkedList.h"
#include <fstream>

using namespace std;

CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
}


CircularLinkedList::~CircularLinkedList()
{
	/* You must fill here */

}

void CircularLinkedList::Insert(WordNode * node)
{
	if(!pHead)
		pHead = node;

	else {
		WordNode * TempNode = pHead;
		while (TempNode->GetNext() != pHead)
			TempNode = TempNode->GetNext();
		TempNode->SetNext(node);
		node->SetNext(pHead);
	}
}

WordNode * CircularLinkedList::GetpHead()
{
	return pHead;
}

WordNode * CircularLinkedList::Search(char * word)
{
	return nullptr;
}

bool CircularLinkedList::Print()
{
	ofstream FILEOUT;
	FILEOUT.open("log.txt", ios::app);

	WordNode *TempNode = pHead;
	if (!TempNode) return false;				// ERROR CASE; "MEMORIZED" word list does not exist

	FILEOUT << "======== PRINT ========" << endl;
	FILEOUT << TempNode->GetWord() << " " << TempNode->GetMean() << endl;
	while (TempNode->GetNext() != pHead) {
		TempNode = TempNode->GetNext();
		FILEOUT << TempNode->GetWord() << " " << TempNode->GetMean() << endl;
	}
	FILEOUT << "=======================" << endl << endl;

	FILEOUT.close();
}

bool CircularLinkedList::Save()
{
	return false;
}
