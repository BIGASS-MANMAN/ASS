#include "CircularLinkedList.h"

// Constructor
CircularLinkedList::CircularLinkedList()
{
	pHead = (WordNode *)malloc(sizeof(WordNode));
	pTail = pHead;
	pTail->SetNext(pHead);
	writable = false;
}

// Destructor
CircularLinkedList::~CircularLinkedList()
{
	pHead = NULL;
	pTail = NULL;
}

// Insert into linked list.
void CircularLinkedList::Insert(WordNode * node)
{
	writable = true;
	WordNode * start = pHead;
	WordNode * temp = pHead;
	// If the next pointer is start
	while (temp->GetNext() != start)
	{
		temp = temp->GetNext();
	}
	temp->SetNext((WordNode *)malloc(sizeof(WordNode)));
	temp = temp->GetNext();
	temp->SetWord(node->GetWord());
	temp->SetMean(node->GetMean());
	temp->SetNext(start);
}

// Searching and finding function in linked list.
WordNode * CircularLinkedList::Search(char * word)
{
	WordNode * start = pHead;
	WordNode * temp = pHead;
	temp = temp->GetNext();
	while (temp != start)
	{
		if (strcmp(temp->GetWord(), word) == 0)
		{
			return temp;
		}
		temp = temp->GetNext();
	}
	return NULL;
}

// Return the head pointer.
WordNode * CircularLinkedList::getHead()
{
	return pHead;
}

// Setting the head node function.
void CircularLinkedList::setHead(WordNode * node)
{
	pHead = node;
}

WordNode * CircularLinkedList::getTail()
{
	return pTail;
}

void CircularLinkedList::setTail(WordNode * node)
{
	pTail = node;
}

// Printing all the nodes.
bool CircularLinkedList::Print()
{
	int count = 0;
	WordNode * start = pHead;
	WordNode * pointer = pHead->GetNext();

	wofstream out("log.txt", ios::app);

	while (pointer != NULL)
	{
		if (pointer == start && count == 0)
		{
			return false;
		}
		if (pointer == start && count != 0)
		{
			return true;
		}

		cout << pointer->GetWord() << " " << pointer->GetMean() << endl;
		out << pointer->GetWord() << " " << pointer->GetMean() << endl;
		pointer = pointer->GetNext();
		count++;
	}
	return true;
}

// The saving function.
bool CircularLinkedList::Save()
{
	ofstream outFile("memorized_word.txt");
	outFile.close();
	if (!writable)
	{
		return false;
	}
	else
		SaveWord(pHead, pHead->GetNext(), 0);
	return true;
}

// Saving all the words function.
void CircularLinkedList::SaveWord(WordNode * start, WordNode * pointer, int count)
{
	ofstream outFile("memorized_word.txt", ios::app);
	if (pointer == start && count == 0)
	{
		return;
	}
	if (pointer == start && count != 0)
	{
		return;
	}
	outFile << pointer->GetWord() << " " << pointer->GetMean() << endl;
	SaveWord(start, pointer->GetNext(), count++);
	outFile.close();
}