#include <iostream>
#include <cstring>
#include <fstream>
#include "Queue.h"
using namespace std;

Queue::Queue()
{
	pHead = '\0';
	cnt = 0;
}

Queue::~Queue()
{
	//delete all Node
	for (; pHead;) delete Pop();
}

void Queue::Push(WordNode * node)
{
	if (!pHead)		//first insert
	{
		pHead = node;
		cnt++;
		return;
	}
	else            //other insert
	{
		//push back
		for (WordNode* temp = pHead; temp; temp = temp->GetNext())
		{
			if (!temp->GetNext())
			{
				temp->SetNext(node);
				cnt++;
				return;
			}
		}
	}
}

WordNode* Queue::Pop()
{
	if(!pHead)
		return '\0';
	else
	{
		//pop front
		WordNode* delNode = pHead;
		pHead = pHead->GetNext();
		delNode->SetNext('\0');
		cnt--;
		return delNode;
	}
}

WordNode* Queue::Search(char * word)
{
	WordNode* temp = pHead;
	//search word of wordNode for comparison
	for (; temp; temp = temp->GetNext())
	{
		if (!strcmp(temp->GetWord(), word))
			break;
	}

	return temp;	//return wordNode of searched word
}

bool Queue::Print()						// PRINT
{
	ofstream output("log.txt", ios::app);	//open log.txt continuous

	if (output.is_open())
	{
		if (!pHead)
			return false;
		else
		{
			//print word and mean in order
			output << "======== PRINT ========" << endl;
			for (WordNode* temp = pHead; temp; temp = temp->GetNext())
				output << temp->GetWord() << " " << temp->GetMean() << endl;

			output.close();
			return true;
		}
	}
	//error code
	else
	{
		output.close();
		return false;
	}
}

bool Queue::Save()								// SAVE
{
	ofstream flush("to_memorize_word.txt");
	flush.close();

	ofstream output("to_memorize_word.txt", ios::app);	//new text open

	if (output.is_open())
	{
		if (!pHead)
			return false;
		else
		{
			//print word and mean in order
			for (WordNode* temp = pHead; temp; temp = temp->GetNext())
				output << temp->GetWord() << " " << temp->GetMean() << endl;

			output.close();
			return true;
		}
	}
	else
	{
		//error code
		output.close();
		return false;
	}
}
