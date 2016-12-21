#include <iostream>
#include <fstream>
#include <cstring>
#include "CircularLinkedList.h"
using namespace std;


CircularLinkedList::CircularLinkedList()
{
	pHead = NULL;
}


CircularLinkedList::~CircularLinkedList()
{
	WordNode *cur = pHead, *temp = pHead;
	if (pHead) {
		if (cur->GetNext() == pHead)
		{
			delete cur;
		}
		else {
			cur = cur->GetNext();
			while (cur->GetNext() != pHead)
			{
				temp = cur;
				cur = cur->GetNext();
				delete temp;
			}
			delete cur;
			delete pHead;
		}
	}
}

void CircularLinkedList::Insert(WordNode * node)// LOAD, TEST
{
	WordNode *a=pHead;
	if (pHead == NULL)
	{
		pHead = node;
		pHead->SetNext(node);
		return;
	}
	if (a->GetNext() == pHead) {
		a->SetNext(node);
		node->SetNext(pHead);
		return;
	}

	while (a->GetNext() != pHead)
		a = a->GetNext();
	a->SetNext(node);
	node->SetNext(pHead);
}

WordNode *   CircularLinkedList::Search(char * word)// SEARCH, UPDATE
{
	if (pHead == NULL)
		return NULL;
	WordNode * a = pHead;
	if (a->GetNext() == pHead) {
		if (!strcasecmp(a->GetWord(), word))
			return a;
		else
			return 0;
	}
	a = a->GetNext();
	while (a != pHead) {
		if (!strcasecmp(a->GetWord(), word))
			return a;
		a = a->GetNext();
		if (!strcasecmp(a->GetWord(), word))
			return a;
	}
	

	return NULL;

}

bool CircularLinkedList::Print()// PRINT
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	WordNode *a;
	a = pHead;
	if (a == NULL)
		return false;
	else
	{
		cout << "======== PRINT ========" << endl;
		cout << a->GetWord() << " " << a->GetMean() << endl;

		flog << "======== PRINT ========" << endl;
		flog << a->GetWord() << " " << a->GetMean() << endl;
		a = a->GetNext();
		while (a != pHead)
		{
			cout << a->GetWord() << " " << a->GetMean() << endl;
			flog << a->GetWord() << " " << a->GetMean() << endl;
			a = a->GetNext();
		}
		cout << "=======================\n" << endl;
		flog << "=======================\n" << endl;
		flog.close();
		return true;
	}
}

bool CircularLinkedList::Save()
{
	WordNode *a;
	a = pHead;
	
	if (a == NULL)
	{
		return false;
	}
	ofstream fout;
	fout.open("memorized_word.txt",ios::trunc);
		fout << a->GetWord() << " " << a->GetMean() << endl;
		a = a->GetNext();
		while (a != pHead)
		{
			fout << a->GetWord() << " " << a->GetMean() << endl;
			a = a->GetNext();
		}
		fout.close();
		return true;
}
