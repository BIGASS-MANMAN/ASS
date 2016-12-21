#include "Queue.h"

Queue::Queue()
{
	pHead = NULL;
	alpHead = NULL;
	nodeCnt = 0;
}
Queue::~Queue()
{
	WordNode* pDel = NULL;
	while (pHead)
	{
		pDel = pHead;
		pHead = pHead->GetNext();
		delete pDel;
	}
}
bool Queue::IsEmpty()
{
	if (pHead == NULL)
		return true;
	else
		return false;
}
void Queue::Push(WordNode* node)
{
	WordNode* pCur = pHead;
	if (pHead == NULL)	pHead = node;
	else
	{
		while (pCur->GetNext())	pCur = pCur->GetNext();
		pCur->SetNext(node);
	}
	nodeCnt++;
}
WordNode* Queue::Pop()
{
	WordNode* pCur = pHead;
	// if head is null
	if (pHead == NULL)	return NULL;
	// return 1st node and set 2nd header
	else
	{
		pHead = pHead->GetNext();
		pCur->SetNext(NULL);
		nodeCnt--;
		return pCur;
	}
}
WordNode* Queue::Search(char* word)
{
	WordNode* pCur = pHead;	
	// visit all node in queue
	while (pCur)
	{
		if (strcmp(pCur->GetWord(), word) == 0)
			break;
		pCur = pCur->GetNext();
	}
	return pCur;
}
bool Queue::Print()
{
	bool printflag = true;
	//error if head is empty
	if (pHead == NULL)
		return false;
	// call print function
	else
		printflag = Print(pHead);
	return printflag;
}
bool Queue::Print(WordNode* pCur)
{
	ofstream fout;
	fout.open("log.txt", ios::app);
	if (fout.fail())
		return false;
	fout << "= == == == = PRINT == == == ==" << endl;
	//visit all node in queue and save
	while (pCur)
	{
		fout << pCur->GetWord() << "	" << pCur->GetMean() << endl;
		pCur = pCur->GetNext();
	}
	fout << "= == == == == ==  == == == ==" << endl << endl;
	fout.close();
	return true;
}
bool Queue::Save()
{
	ofstream fout;
	WordNode* pCur = pHead;
	if (pHead == NULL)
		return false;	
	//file open
	fout.open("to_momerize_word.txt");
	while (pCur)
	{
		//save all word and mean in queue
		fout << pCur->GetWord() << "\t" << pCur->GetMean() << endl;
		pCur = pCur->GetNext();
	}
	fout.close();
	return true;
}
int Queue::GetNodeCnt()
{
	return nodeCnt;
}
bool Queue::alisempty()
{
	if (alpHead == '\0')
		return true;
	else
		return false;
}
void		Queue::alPush(AlphabetNode *node)
{
	if (alpHead == NULL)//when node insert at first  
		alpHead = node;

	else
	{
		AlphabetNode * pCur = alpHead;//make a pCur pointer 

		while (pCur->GetNext())
			pCur = pCur->GetNext();// pCur pointer that is last insert Node

		pCur->SetNext(node);//node connect with next of pCur
	}
}
AlphabetNode *	Queue::alPop()
{
	if (alpHead == NULL)//empty is return 0
		return 0;

	AlphabetNode *pCur = alpHead;
	alpHead = alpHead->GetNext();//set pHead is next node
	pCur->SetNext(0);//pCur is pop node
	return pCur;
}