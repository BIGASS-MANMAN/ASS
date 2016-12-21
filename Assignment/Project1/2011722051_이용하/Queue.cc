#pragma warning (disable : 4996)
#include "Queue.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <utility>

using namespace std;

void strchange(char * a);  // change big letter to small letter
int mystrcmp(char * a, char * b);  // string compare ignoring the case of character

Queue::Queue()
{
	pHead = '\0';
}

Queue::~Queue()
{
	while (pHead != NULL)
	{
		WordNode * pCur = pHead;
		pHead = pHead->GetNext(); // move current node
		delete pCur; // delete head node
	}
}

void Queue::Push(WordNode * node)
{
	WordNode * pNew;
	pNew = new WordNode;
	pNew->SetWord(node->GetWord()); // input word
	pNew->SetMean(node->GetMean()); // input mean
	pNew->SetNext(NULL);
	if (pHead == NULL) // pHead is NULL
		pHead = pNew; // pNew become pHead
	else // pHead isn't NULL
	{
		WordNode * pCur = pHead;
		while (pCur->GetNext() != NULL)
			pCur = pCur->GetNext(); // move pCur
		pCur->SetNext(pNew); // pNew is next node
	}
}

WordNode * Queue::Pop()
{
	if (pHead == NULL)
		return 0;
	WordNode * temp = new WordNode;
	WordNode * pCur = pHead;
	pHead = pCur->GetNext(); // head node change
	temp->SetWord(pCur->GetWord()); // copy word
	temp->SetMean(pCur->GetMean()); // copy mean
	delete pCur; // pop(delete) node
	return temp; // return copy node
}

WordNode * Queue::Search(char * word)
{
	WordNode * pCur = pHead;
	if (pHead == NULL)
		return 0;
	while (pCur != NULL)
	{
		if (mystrcmp(pCur->GetWord(), word) == 0) // compare word
			return pCur; // if word is exist, return node
		else
			pCur = pCur->GetNext(); // move node
	}
	return 0;
}

bool Queue::Print() 
{
	ofstream log;
	log.open("log.txt", ios::app); // log.txt open
	WordNode * pCur = pHead;
	if (pCur == NULL) // pHead == NULL
		return 0;
			
	else // pHead != NULL
	{
		while (pCur != NULL) // print word,mean until pCur is NULL
		{
			cout << pCur->GetWord() << "/" << pCur->GetMean() << endl;
			log << pCur->GetWord() << "/" << pCur->GetMean() << endl;
			pCur = pCur->GetNext(); // move node
		}
		log.close(); // close log file
		return 1;
	}
}

bool Queue::Save()
{
	ofstream fout;
	fout.open("to_memorize_word.txt"); // open to_memorize_word.txt
	WordNode * pCur = pHead;
	if (pCur == NULL) // pHead == NULL
		return 0;
	else // pHead != NULL
	{
		while (pCur != NULL)
		{
			fout << pCur->GetWord() << " " << pCur->GetMean() << endl; // print word,mean
			pCur = pCur->GetNext(); // move node
		}
		fout.close(); // file close
		return 1;
	}
}

int Queue::GetWordCount()
{
	int cnt = 0;
	WordNode * pCur = new WordNode;
	pCur = pHead;
	while (pCur != NULL)
	{
		cnt++; // count
		pCur = pCur->GetNext(); // move next node
	}
	return cnt;
}

void strchange(char * a) // change big letter to small letter
{
	int len, i;
	len = strlen(a);
	for (i = 0; i<len; i++)
		if (a[i] >= 65 && a[i] <= 90) // A~Z
			a[i] += 32; // A+32=a ... Z+32=z
}
int mystrcmp(char *a, char *b) // string compare ignoring the case of character
{
	char temp1[100];
	char temp2[100];

	if (a == NULL || b == NULL)
		return -1;

	strcpy(temp1, a); // temp1 = a;
	strcpy(temp2, b); // temp2 = b;
	strchange(temp1); // change a to temp1
	strchange(temp2); // change b to temp2
	if (strcmp(temp1, temp2) > 0)
		return 1;
	else if (strcmp(temp1, temp2) == 0)
		return 0;
	else
		return -1;
}
