#include "CircularLinkedList.h"
#include <fstream>
#include <string.h>
#include <iostream>
using namespace std;



CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
}


CircularLinkedList::~CircularLinkedList()
{
	/* You must fill here */
	WordNode* pCur = pHead;
	WordNode* prev = pCur;
	while(pHead != '\0')
	{
		pCur = pHead;
		prev = pCur;
		while(pCur->GetNext() != pHead)
		{
			prev = pCur;
			pCur = pCur->GetNext();
		}
		prev->SetNext(pHead);
		delete pCur;
	}
}

void CircularLinkedList::Insert(const char* word, const char* mean)
{
	WordNode* node = new WordNode();
	node->SetWord(word);
	node->SetMean(mean);
	Insert(node);
}

void CircularLinkedList::Insert(WordNode* node)
{
	WordNode* ptr = pHead;
	if(pHead == '\0')
	{
		pHead = node;
		node->SetNext(pHead);
	}
	else
	{
		while(ptr->GetNext() != pHead)
		{
			ptr = ptr->GetNext();
		}
		ptr->SetNext(node);
		node->SetNext(pHead);
	}
}

WordNode* CircularLinkedList::Search(const char* word)
{
	if(pHead == '\0')
		return '\0';
	else
	{
		WordNode* ptr = pHead;
		while(ptr->GetNext() != pHead)
		{
			if(strcmp(ptr->GetWord(),word) == 0)
				return ptr;
			else
				ptr = ptr->GetNext();
		}
		if(strcmp(ptr->GetWord(), word) == 0)
			return ptr;
		else
			return '\0';
	}
}

bool CircularLinkedList::Print()
{
	if(pHead == '\0')
		return false;
	else
	{
		ofstream fout;
		fout.open("log.txt",ios::app);
		WordNode* ptr = pHead;
		while(ptr->GetNext() != pHead)
		{
			fout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
			cout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
			ptr = ptr->GetNext();
		}
		fout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
		cout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
		fout << endl;
		fout.close();
		return true;
	}
}

bool CircularLinkedList::Save()
{
	if(pHead == '\0')
		return false;
	else
	{
		ofstream fout;
		fout.open("memorized_word.txt",ios::trunc);
		WordNode* ptr = pHead;
		while(ptr->GetNext() != pHead)
		{
			fout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
			ptr = ptr->GetNext();
		}
		fout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
		fout.close();
		return true;
	}
}
