#include "Queue.h"

Queue::Queue()											//constructor
{
	pHead = '\0';										//pHead is NULL
}
Queue::~Queue()											//destructor
{
	WordNode * pWork = pHead;
	while (pWork != NULL)								//all of queue's node is deleted
	{
		pHead = pHead->GetNext();
		delete pWork;
		pWork = pHead;
	}
}

void		Queue::Push(WordNode * node)				// queue's push function
{
	if (pHead == '\0')									//if pHead is NULL
	{
		pHead = node;									//pHead == node
	}
	else												//else
	{
		WordNode *pWork = pHead;						//node is queue's last node
		while (pWork->GetNext() != NULL)
		{
			pWork = pWork->GetNext();
		}
		pWork->SetNext(node);
	}
}
WordNode *	Queue::Pop()								// queue's pop function
{
	if (pHead == NULL)									//if pHead is NULL return NULL
		return NULL;
	else
	{													//else
		WordNode *pWork = pHead;						//return queue's phead and pHead set pHead's Next
		pHead = pHead->GetNext();
		pWork->SetNext(NULL);
		return pWork;
	}
}
WordNode *	Queue::Search(char * word)					// find node that same word infomation with word in queue
{
	if (pHead == NULL)									//if pHead is NULL return NULL
		return NULL;
	else
	{													//else
														//traslate word to little alphabet
		char word2[100] = { 0 };
		int loop = 0;
		while (word[loop] != '\0')
		{
			if (word[loop] <= 90 && word[loop] >= 65)
			{
				word2[loop] = word[loop] + 32;
				loop++;
			}
			else
				break;
		}

		WordNode *pWork = pHead;						//while find same node or pWork not exit 
		while (strcmp(pWork->GetWord(), word) && strcmp(pWork->GetWord(),word2))
		{
			pWork = pWork->GetNext();					//pWork is pWork's Next
			if (pWork == NULL)
			{
				return NULL;
			}
		}
		return pWork;									//return pWork
	}
}
bool		Queue::Print()								// Print function
{
	if (pHead == NULL)									//if pHead is NULL
		return 0;										//return 0
	Log.open("Log.txt", ios::app);						//open log.txt for print to log.txt
	WordNode *pWork = pHead;
	cout << "======== PRINT ========" << endl;
	Log << "======== PRINT ========" << endl;
	while (pWork != NULL)								//print all of queue's node and write in log.txt
	{
		cout << pWork->GetWord() << " " << pWork->GetMean() << endl;
		Log << pWork->GetWord() << " " << pWork->GetMean() << endl;
		pWork = pWork->GetNext();
	}
	cout << "=======================" << endl;
	Log << "=======================" << endl;
	return 1;
}
bool		Queue::Save()								//SAVE function
{
	Wmemory.open("to_memorize_word.txt");				//open to_memorize_word.txt to write infomation
	if (pHead == NULL)									//if pHead not eixt, error
	{
		Wmemory.close();
		return 1;
	}
	WordNode *pWork = pHead;
	while (pWork != NULL)								//write queue's infomation in to_memorize_word .txt
	{
		Wmemory << pWork->GetWord() << " " << pWork->GetMean() << "\n";
		pWork = pWork->GetNext();
	}
	Wmemory.close();									//close to_memorize_word.txt
	return 0;
}
bool		Queue::Empty() {							//queue's enpty function
	int i = 0;
	if (pHead == NULL)
		return 1;
	else
		return 0;
}
WordNode *	Queue::Front()								//return pHead
{
	return pHead;

}

