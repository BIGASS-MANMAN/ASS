#include "Queue.h"
#include <iostream>
#include <fstream>	//file in/out header
#include <string.h>

using namespace std;


Queue::Queue()
{
	pHead = NULL;	//initialize Head
}

Queue::~Queue()
{
	/* You must fill here */

}


void Queue::Push(WordNode *node)	//Push (add node after tail) function
{
	if(pHead == NULL)	//if there is no node
	{
		pHead = node;		//assign node to Head
		pHead->SetNext(NULL);	//Head->Next is NULL
	}
	else				//if more than one node exists
	{
		WordNode *temp;	//create new temp node

		for (temp = pHead; temp->GetNext() != NULL; temp = temp->GetNext());	//move from head to tail
		
		temp->SetNext(node);	//tail->next is NULL
	}
}

WordNode *Queue::Pop()	//Pop (remove head Node) function
{
	if (pHead == NULL)		//if there is no node
	{
		return NULL;
	}
	else if (pHead->GetNext() == pHead)	//if only the Head exists
	{
		pHead = NULL;	//Head is NULL
	}
	else	//if more than two nodes exist
	{
		WordNode *temp;	//create temp node
		
		temp = pHead->GetNext();	//assign Head->NextNode to temp
		pHead->SetNext(NULL);	//Head->Next is NULL
		pHead = temp;	//assign temp(Head->NextNode) to HeadNode

	}
	return pHead;
}

WordNode *Queue::Search(char *word)	//Search Word function
{
	WordNode *temp;	//create temp node

	for (temp = pHead; temp != NULL; temp = temp->GetNext()) //move from head to tail
	{
		if (!strcmp(temp->GetWord(),word)) //if the word is found
			return temp;
	}
	return NULL;
}

bool Queue::Print(ofstream& logfile)	//Print Queue list function
{
	if (pHead == NULL)	//if there is no node
	{
		logfile.close();
		return true;
	}
	else if (pHead->GetNext() == pHead)	//if only the Head exists
	{
		cout << pHead->GetWord() << "\t" << pHead->GetMean() << endl;	//print out the Head's Word & Meaning
		logfile << pHead->GetWord() << "\t" << pHead->GetMean() << endl;	//print out the Head's Word & Meaning
	}
	else	//if more than one node exists
	{
		WordNode *temp;	//create new temp node

		for (temp = pHead; temp != NULL; temp = temp->GetNext())	//move from head to tail
		{
			cout << temp->GetWord() << "\t" << temp->GetMean() << endl;	//print out the Words & Meanings
			logfile << temp->GetWord() << "\t" << temp->GetMean() << endl;	//print out the Head's Word & Meaning
		}
	}
	return false;
}

bool Queue::Save()	//Output "to_memorize_word.txt" function
{
	ofstream Memorize("to_memorize_word.txt");	//create output stream

	//no nodes are printed if there is no node

	if (pHead->GetNext() == NULL)	//if only the head exist
	{															
		Memorize << pHead->GetWord() << "\t" << pHead->GetMean() << endl;	//print out the head's Word & Meaning
	}
	else	//if more than one node exist
	{
		WordNode *temp;	//create temp node

		for (temp = pHead; temp != NULL; temp = temp->GetNext())	//move from head to tail
		{
			Memorize << temp->GetWord() << "\t" << temp->GetMean() << endl;	//print out the Words & Meanings
		}
	}

	Memorize.close();	//close output stream
	return false;
}

bool Queue::Empty()
{
	return pHead == NULL;
}

WordNode * Queue::Front()
{
	return pHead;
}
