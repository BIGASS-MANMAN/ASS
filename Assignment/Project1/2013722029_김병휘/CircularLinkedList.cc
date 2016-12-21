#include <fstream>
#include <cstring>
#include "CircularLinkedList.h"
using namespace std;


CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
}


CircularLinkedList::~CircularLinkedList()
{
	//delete all node 
	if (!pHead) return;
	else if (pHead == pHead->GetNext()) //delete if node count is one
	{
		delete pHead;
		return;
	}
	else  //root is not NULL
	{
		//delete nextNode repeatedly
		WordNode* temp = pHead->GetNext();
		for (; temp;)
		{
			if (temp == pHead)
			{
				delete temp;
				return;
			}
			WordNode* delNode = temp;
			temp = temp->GetNext();
			delete delNode;
		}
	}
}

void CircularLinkedList::Insert(WordNode * node)		// LOAD, TEST
{
	if (!pHead)		//first insert
	{
		pHead = node;
		pHead->SetNext(pHead);
		return;
	}
	else if (pHead == pHead->GetNext())	//second insert
	{
		pHead->SetNext(node);
		pHead->GetNext()->SetNext(pHead);
		return;
	}
	else  //other insert
	{
		//push back insert
		for (WordNode* temp = pHead; ; temp = temp->GetNext())
		{
			if (temp->GetNext() == pHead)
			{
				temp->SetNext(node);
				temp->GetNext()->SetNext(pHead);
				return;
			}
		}
	}
}

WordNode* CircularLinkedList::Search(char * word)
{
	//search word of wordNode for comparison
	if (!pHead) return '\0'; //error code
	else if (pHead == pHead->GetNext())	//only one Node
	{
		if (!strcmp(pHead->GetWord(), word)) return pHead;
		else return '\0';	//error code
	}
	else 
	{
		//Searching
		if (!strcmp(pHead->GetWord(), word)) return pHead;
		else
		{
			for (WordNode* temp = pHead->GetNext(); temp != pHead; temp = temp->GetNext())
			{
				if (!strcmp(temp->GetWord(), word)) return temp;
			}
			return '\0';	//error code
		}
	}
}

bool CircularLinkedList::Print()							// PRINT
{
	ofstream output("log.txt", ios::app); //open log.txt continuous

	if (output.is_open())
	{
		//no wordNode
		if (!pHead)
		{
			output.close();
			return false;
		}
		else
		{
			//print word and mean in order
			output << "======== PRINT ========" << endl;
			for (WordNode* temp = pHead; temp; temp = temp->GetNext())
			{
				if (temp->GetNext() == pHead)
				{
					output << temp->GetWord() << " " << temp->GetMean() << endl;

					output.close();
					return true;
				}
				output << temp->GetWord() << " " << temp->GetMean() << endl;
			}
		}
	}
	//error code
	else
		return false;
}

bool CircularLinkedList::Save()								// SAVE
{
	ofstream flush("memorized_word.txt");
	flush.close();

	ofstream output("memorized_word.txt", ios::app);	//new text open

	if (output.is_open())
	{
		if (!pHead)
		{
			output.close();
			return false;
		}
		else
		{
			//print word and mean in order
			for (WordNode* temp = pHead; ; temp = temp->GetNext())
			{
				if (temp->GetNext() == pHead)
				{
					output << temp->GetWord() << " " << temp->GetMean() << endl;
					
					output.close();
					return true;
				}
				output << temp->GetWord() << " " << temp->GetMean() << endl;
			}
		}
	}
	//error code
	else
	{
		output.close();
		return false;
	}
}
