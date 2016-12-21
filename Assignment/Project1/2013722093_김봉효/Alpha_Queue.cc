#include"Alpha_Queue.h"
#include <iostream>
#include<fstream>
using namespace std;
Alpha_Queue::Alpha_Queue()
{
	pHead = '\0';
}


Alpha_Queue::~Alpha_Queue()
{
	AlphabetNode* cur = pHead, *temp = 0;
	while (cur) {
		temp = cur;
		cur = cur->GetNext();
		delete temp;
	}

}
void Alpha_Queue::Push(AlphabetNode* node)
{

	if (pHead == NULL) {
		pHead = node;
		return;
	}
	AlphabetNode* rear = pHead;
	while (rear->GetNext() != NULL) {
		rear = rear->GetNext();
	}
	rear->SetNext(node);
}

AlphabetNode* Alpha_Queue::Pop()
{
	if (IsEmpty())
		return 0;
	AlphabetNode* front = pHead;
	pHead = pHead->GetNext();
	return front;
}


bool Alpha_Queue::IsEmpty()
{
	if (pHead == NULL)
		return 1;
	return 0;
}
