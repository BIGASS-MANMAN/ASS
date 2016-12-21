#pragma warning (disable : 4996)
#include "CircularLinkedList.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void strchange(char * a); // change big letter to small letter
int mystrcmp(char * a, char * b); // string compare ignoring the case of character

CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
	pTail = '\0';
}

CircularLinkedList::~CircularLinkedList()
{
	WordNode * pCur = pHead;
	if (pHead == NULL)
		delete pHead; // delete head node
	else if (pHead->GetNext() == NULL)
		delete pHead; // delete head node
	else
	{
		pTail->SetNext(NULL);
		while (pCur != NULL)
		{
			pCur = pCur->GetNext(); // move current node
			delete pHead; // delete head node
			pHead = pCur; // current node is head node
		}
	}

}

void CircularLinkedList::Insert(WordNode * node)
{
	WordNode * pNew;
	pNew = new WordNode;
	pNew->SetWord(node->GetWord()); // input word
	pNew->SetMean(node->GetMean()); // input mean
	pNew->SetNext(pHead); // point head node
	if (pHead == NULL) // if pHead is NULL
	{
		pHead = pNew; // pNew become pHead
		pTail = pNew; // pNew become pTail
	}
	else // pHead ins't NULL
	{
		pTail->SetNext(pNew); // pTail point pNew
		pTail = pTail->GetNext(); // pNew become pTail
	}
}

WordNode * CircularLinkedList::Search(char * word)
{
	WordNode * pCur = pHead;
	if (pCur == NULL) // pHead == NULL
		return 0;
	else
	{
		while (pCur != pTail) // until last node
		{
			if (mystrcmp(pCur->GetWord(), word) == 0) // compare word
			{
				return pCur; // if word is exist, return node
				break;
			}
			else
			{
				pCur = pCur->GetNext(); // move node
				continue;
			}
		}
		if (pCur == pTail) // last node
		{
			if (mystrcmp(pCur->GetWord(), word) == 0) // compare word
				return pCur; // if word is exist, return node
			else
				return 0;
		}
		return 0;
	}
}

bool CircularLinkedList::Print()
{
	ofstream log;
	log.open("log.txt", ios::app); // log.txt open
	WordNode * pCur = pHead;
	if (pCur == NULL) // pHead == NULL
		return 0;
	
	else // pHead != NULL
	{
		while (1) // print all node in the circular list
		{
			if (pCur == pTail) // last node
			{
				cout << pCur->GetWord() << "/" << pCur->GetMean() << endl;
				log << pCur->GetWord() << "/" << pCur->GetMean() << endl;
				break;
			}
			cout << pCur->GetWord() << "/" << pCur->GetMean() << endl;
			log << pCur->GetWord() << "/" << pCur->GetMean() << endl;
			pCur = pCur->GetNext(); // move node
		}
		log.close(); // close log file
		return 1;
	}
}

bool CircularLinkedList::Save()
{
	ofstream fout;
	fout.open("memorized_word.txt"); // open memorized_word.txt
	WordNode * pCur = pHead;
	if (pCur == NULL) // pHead == NULL
		return 0;
	else // pHead != NULL
	{
		while (1) // print all node in the circular list
		{
			if (pCur == pTail) // last node
			{
				fout << pCur->GetWord() << "/" << pCur->GetMean() << endl;
				break;
			}
			fout << pCur->GetWord() << "/" << pCur->GetMean() << endl;
			pCur = pCur->GetNext(); // move node
		}
		fout.close(); // file close
		return 1;
	}
}
