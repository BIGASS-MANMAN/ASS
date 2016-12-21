#pragma once
#include "Word.h"

class Queue
{
    private:
	Word* m_pHead;

    public:
	Queue();
	Word* getHead();
	int Push(Word* Node);
	Word* Pop();
	Word* Search(char* word);
};
