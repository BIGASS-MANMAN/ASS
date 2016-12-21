#include "CircularLinkedList.h"



CircularLinkedList::CircularLinkedList()//CircularLinkedList constructor
{
	pHead = '\0';
}


CircularLinkedList::~CircularLinkedList() //CircularLinkedList destructor
{
	WordNode *temp = NULL;
	WordNode *current = pHead;
	if (current == NULL)
	{
		return ; //already current is NULL, finish
	}
	while (current->GetNext()!=pHead)
	{
		temp = current->GetNext();	 
		delete current;	
		current = temp;
	}//current is pHead, do GetNext() until  pointing own self
	delete current;//if current->GetNext() = pHead, delete current 
	pHead = NULL;//change pHead to NULL


}


void		CircularLinkedList::Insert(WordNode * node)			// LOAD, TEST
{
	WordNode * current = pHead;
	WordNode* temp = NULL;
	temp = Search(node->GetWord());
	if (temp != NULL)
	{
		return;
	}//if word is already exist, quit
	if (current == NULL)
	{
		pHead = node;
		node->SetNext(pHead);
		return;
	}//if CircularLinkedList is empty, setting insert word to pHead
	else
	{
		while (current->GetNext() != pHead)
		{
			current = current->GetNext();
		}//do GetNext() until next node is pHead
		current->SetNext(node);
		node->SetNext(pHead);
	}//finish GetNext(), inserting word and SetNext to pHead
	return;

}
WordNode *	CircularLinkedList::Search(char * word)			// SEARCH, UPDATE
{
	WordNode* current = pHead;
	if (current == NULL)
	{
		return NULL; 
	}
	while (current)
	{
		if (strcmp(word, current->GetWord()) == 0)
		{
			return current;
		}//if current is search word, return current
		else if (current->GetNext() == pHead)
		{
			return NULL;
		}
		current = current->GetNext();
	}//do GetNext() until find word
	return NULL;
}
bool		CircularLinkedList::Print()							// PRINT
{
	return false;
}
bool		CircularLinkedList::Save()								// SAVE
{
	if (IsEmpty())
	{
		return false;
	}//if CircularLinkedList is empty, finish
	else
	{
		WordNode * current = pHead;
		ofstream ouf;
		ouf.open("memorized_word.txt");
		if (current == NULL || !ouf.good())
		{// oftream ouf; ouf.open("memorized_word.txt");
			return false;
		}//checking current, ouf flag good
		while (current)
		{
			ouf << current->GetWord() << "	" << current->GetMean() << endl;//save word and mean line by line
			if (current->GetNext() == pHead)//do GetNext() until check one cycle
			{
				break;
			}
			current = current->GetNext();
			
		}
		ouf.close();
		return true;
	}
}

bool        CircularLinkedList::IsEmpty()//checking function CircularLinkedList is empty
{
	WordNode * current = pHead;
	if (current == NULL)
	{
		return true;
	}//if CircularLinkedList is empty, return true
	else
	{
		return false;
	}//if CircularLinkedList is not empty, return false
}


void CircularLinkedList::SetHead(WordNode * node)//function for setting Head pointer
{
	pHead = node;
}

WordNode * CircularLinkedList::GetHead()//function for getting Head data
{
	return pHead;
}