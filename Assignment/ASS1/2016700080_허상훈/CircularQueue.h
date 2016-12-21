#pragma once
#include "Word.h"

class CircularQueue
{
    private:
	Word* m_pHead;

    public:
	CircularQueue();
	Word* getHead();
	int Push(Word* Node);
	Word* Pop();
	Word* Search(char* word);
};
