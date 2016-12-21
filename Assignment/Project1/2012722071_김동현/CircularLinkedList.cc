#include "CircularLinkedList.h"

using namespace std;



CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
	pTail = '\0';
}


CircularLinkedList::~CircularLinkedList()      //It deletes the memory
{
	WordNode* pSearch = pHead;

	do {
		pHead = pSearch->GetNext();
		pSearch->SetNext(NULL);
		delete pSearch;
		pSearch = pHead;

	} while (pSearch != pTail);   ////turn the loop from head to tail

}

void CircularLinkedList::Insert(WordNode* node) {      //Insert function

	if (pHead == NULL) {      //when there is no node
		pHead = node;
		pTail = node;
	}
	else {                     //Connection node and also connection head and tail
		pTail->SetNext(node);
		pTail = node;
		pTail->SetNext(pHead);
	}
}

WordNode* CircularLinkedList::Search(char* word) {      //Search function

	WordNode* pSearch = pHead;
	do {
		if (strcmp(pSearch->GetWord(), word) == 0)   //when the word is found
			return pSearch;

		else
			pSearch = pSearch->GetNext();

	} while (pSearch != pTail);   ////turn the loop from head to tail

	return (WordNode*)0;
}

bool CircularLinkedList::Print() {      //Print function
	WordNode* pSearch = pHead;

	ofstream fout;
	fout.open("log.txt", ios::app);
	if (!fout)
		return false;

	if (pSearch == NULL)      //when there is no word output
		return false;

	do {
		cout << pSearch->GetWord() << " " << pSearch->GetMean();      //Print
		fout << pSearch->GetWord() << " " << pSearch->GetMean();
		pSearch = pSearch->GetNext();

	} while (pSearch != pTail);   ////turn the loop from head to tail

	return true;
}

bool CircularLinkedList::Save() {      //function Save
	WordNode* pSearch = pHead;
	ofstream fout;
	fout.open("MEMORIZED");

	if (!fout) {
		cout << "file is not open" << endl;      //when there is no file
		return false;
	}

	if (pSearch == NULL)      //when there is no output
		return false;

	do {
		fout << pSearch->GetWord() << " " << pSearch->GetMean() << endl;      //save
		pSearch = pSearch->GetNext();

	} while (pSearch != pTail);   ////turn the loop from head to tail

	return true;
}

