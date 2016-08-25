#include "Queue.h"

Queue::Queue()
{
    m_pHead = NULL;
}

Word* Queue::getHead()
{
    return m_pHead;
}

int Queue::Push(Word* Node)
{
    if(m_pHead == NULL)
    {
	m_pHead = Node;
	return 0;
    }
    else
    {
	Word* pCur = m_pHead;

	while(pCur->getNext())
	{
	    pCur = pCur->getNext();
	}
	pCur->setNext(Node);
	return 0;
    }
    return -1;
}
Word* Queue::Pop()
{
    if(m_pHead == NULL)
	return NULL;
    else
    {
	Word* temp = m_pHead;
	m_pHead = m_pHead->getNext();
	return temp;
    }
}

Word* Queue::Search(char* word)
{
    Word* pCur = m_pHead;

    while(pCur)
    {
	if(strcmp(pCur->getWord(),word)==0)
	    return pCur;
	pCur = pCur->getNext();
    }
    return NULL;
}
