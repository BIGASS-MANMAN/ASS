#include "Queue.h"



Queue::Queue()
{
	pHead = '\0';
	word_cnt = 0;
}


Queue::~Queue()
{
	if (pHead != '\0')
	{
		WordNode *cur = pHead->GetNext();
		delete pHead;		// deallocate head node
		pHead = cur;
	}
}

void Queue::Push(WordNode * node)			// LOAD, ADD
{
	node->SetNext('\0');
	if (pHead == '\0')
	{
		pHead = node;		// insert node and node is head pointer
		word_cnt++;			// increase word count
		return;
	}
	WordNode *cur = pHead;
	while (cur->GetNext() != '\0')
		cur = cur->GetNext();
	cur->SetNext(node);		// insert node to end of Queue
	word_cnt++;
}

WordNode *	Queue::Pop()					// MOVE
{
	if (pHead == '\0')		// no word in queue
		return '\0';

	WordNode *cur = pHead;
	pHead = pHead->GetNext();		// change head pointer
	word_cnt--;		// decrease word count
	return cur;		// return previous head pointer
}


WordNode *	Queue::Search(char * word)		// SEARCH, UPDATE
{
	WordNode *cur = pHead;
	
	while (cur != '\0')		//  node exist in Queue
	{
		if (strcmp(cur->GetWord(),word)==0)		// if find a word 
			return cur;		// return found node
		cur = cur->GetNext();
	}
	return 0;		// failure search
}


bool		Queue::Print()					// PRINT
{
	if (pHead == '\0')
		return 0;
	else
	{	// print data to "log.txt" file and display
		ofstream fout;
		fout.open("log.txt", ios::app);		
		WordNode *cur = pHead;

		fout << "======== PRINT ========" << endl;
		cout << "======== PRINT ========" << endl;
		while (cur != '\0')
		{
			fout << cur->GetWord() << " " << cur->GetMean() << endl;
			cout << cur->GetWord() << " " << cur->GetMean() << endl;
			cur = cur->GetNext();
		}
		fout << "=======================" << endl << endl;
		cout << "=======================" << endl << endl;
		fout.close();
		return 1;
	}
}


bool		Queue::Save()					// SAVE
{
	if (pHead == '\0')		// queue has not node	
		return 0;		
	else
	{	// print data to "to_memorize_word.txt" file
		ofstream fout;
		fout.open("to_memorize_word.txt", ios::app);
		WordNode *cur = pHead;

		while (cur != '\0')
		{
			fout << cur->GetWord() << "\t" << cur->GetMean() << endl;
			cur = cur->GetNext();
		}
		fout.close();
		return 1;
	}
}