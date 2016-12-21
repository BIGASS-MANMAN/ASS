#include "Queue.h"

// Constructor
Queue::Queue()
{
	pHead = '\0';
	pTail = '\0';
}

// Destructor
Queue::~Queue()
{
	pHead = NULL;
	pTail = NULL;
}

// The queue push function.
void Queue::Push(WordNode * node)
{
	WordNode *x = new WordNode;
	x->SetWord(node->GetWord());
	x->SetMean(node->GetMean());
	// if the queue is empty
	if (pHead == NULL)
	{
		pHead = x;
	}
	// until reaching the final node.
	else
	{
		pTail->SetNext(x);
	}
	pTail = x;
}

// The queue pop function.
WordNode * Queue::Pop()
{
	if (empty())
		return NULL;
	// Get the node from the head.
	WordNode *temp = pHead;
	char * word = pHead->GetWord();
	char * mean = pHead->GetMean();
	pHead = pHead->GetNext();
	free(temp);
	WordNode *x = new WordNode;
	x->SetWord(word);
	x->SetMean(mean);
	return x;
}

// If the queue is empty.
bool Queue::empty()
{
	if (pHead == NULL)
		return true;
	else 
		return false;
}

// The queue search function.
WordNode * Queue::Search(char * word)
{
	WordNode *ptr = pHead;
	while (ptr != NULL)
	{
		if (strcmp(ptr->GetWord(), word) == 0)
		{
			return ptr;
		}
		ptr = ptr->GetNext();
	}
	return NULL;
}

// Display all the nodes from the queue.
void Queue::Display()
{
	WordNode *ptr = pHead;
	while (ptr != NULL)
	{
		cout << "< Word >" << endl;
		cout << ptr->GetWord() << endl;
		cout << ptr->GetMean() << endl;
		ptr = ptr->GetNext();
	}
}

// the Printing function.
bool Queue::Print()
{
	ofstream out("log.txt", ios::app);
	WordNode *ptr = pHead;
	if (ptr == NULL)
		return false;
	while (ptr != NULL)
	{
		cout << ptr->GetWord() << " " << ptr->GetMean() << endl;
		out << ptr->GetWord() << " " << ptr->GetMean() << endl;
		ptr = ptr->GetNext();
	}
	return true;
}

// The saving function.
bool Queue::Save()
{
	ofstream outFile("to_memorize_word.txt");
	if (empty())
	{
		return false;
	}
	while (!empty())
	{
		WordNode * node = Pop();
		outFile << node->GetWord() << " " << node->GetMean() << endl;
	}
	outFile.close();
	return true;
}