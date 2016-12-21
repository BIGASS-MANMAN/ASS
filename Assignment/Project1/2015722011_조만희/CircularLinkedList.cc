#include "CircularLinkedList.h"
#include <iostream>
#include <fstream>	//file in/out header
#include <string.h>

using namespace std;


CircularLinkedList::CircularLinkedList()
{
	pHead = NULL;	//initialize Head
}

CircularLinkedList::~CircularLinkedList()
{
	/* You must fill here */
}


void CircularLinkedList::Insert(WordNode *node)	//Insert (add to tail) function
{
	if (pHead == NULL){		//if there is no node
		pHead = node;	//assign node to Head
		pHead->SetNext(pHead);	//Head->Next is Head (single circular node)
	}
	else {
		WordNode *temp;	//create temp node

		for (temp = pHead; temp->GetNext() != pHead; temp = temp->GetNext());	//move from head to tail
		node->SetNext(pHead);
		temp->SetNext(node);	//tail->Next is Head	(circular link)
	}
}

WordNode *CircularLinkedList::Search(char *word)	//Search word function
{
	if (pHead == NULL)	//if there is no node
		return NULL;
	else	//if the Head exists
	{
		WordNode *temp;	//create temp node

		for (temp = pHead; temp->GetNext() != pHead; temp->SetNext(temp))	//ÇÑ¹ÙÄû ¿Õº¹
		{
			if (!strcmp(temp->GetWord(), word))	//if the word is found
				return temp;
			
			if (temp->GetNext() == pHead)	//if the word is not found (reached the end)
				return NULL;
		}
	}
}

bool CircularLinkedList::Print(ofstream& logfile)	//print CircularLinkedList function
{
	if (pHead == NULL)	//if there is no node
	{
		return true;
	}
	else if (pHead->GetNext() == pHead)	//if only the head node exists
	{
		cout << pHead->GetWord() << "\t" << pHead->GetMean() << endl;	//print out the Head's Word & Meaning
		logfile << pHead->GetWord() << "\t" << pHead->GetMean() << endl;	//print out the Head's Word & Meaning

	}
	else	//if more than one node exists
	{
		WordNode *temp;	//create new temp node

		for (temp = pHead; temp->GetNext() != pHead; temp->SetNext(temp));	//move from head to tail
		{
			cout << temp->GetWord() << "\t" << temp->GetMean();	//print out the Words & Meanings
			logfile << pHead->GetWord() << "\t" << pHead->GetMean() << endl;	//print out the Head's Word & Meaning
		}
	}
	return false;
}

bool CircularLinkedList::Save()	//Output "memorized_word.txt" function
{
	ofstream Memorized("memorized_word.txt");	//create output stream

	//no nodes are printed if there is no node

	if (pHead->GetNext() == pHead)	//if only the head exist
	{
		Memorized << pHead->GetWord() << "\t" << pHead->GetMean() << endl;	//print out the head's Word & Meaning
	}
	else	//if more than one node exist
	{
		WordNode *temp;	//create temp node
		temp = pHead;
		Memorized << temp->GetWord() << "\t" << temp->GetMean() << endl;	//print out the Words & Meanings

		for (temp = pHead->GetNext(); temp != pHead;temp = temp->GetNext())	//move from head to tail
			Memorized << temp->GetWord() << "\t" << temp->GetMean() << endl;	//print out the Words & Meanings
		
	}

	Memorized.close();	//close output stream
	return false;
}
