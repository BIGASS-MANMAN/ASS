#include "CircularQueue.h"

CircularQueue::CircularQueue()
{
    m_pHead = NULL;
}

Word* CircularQueue::getHead()
{
    return m_pHead;
}

int CircularQueue::Push(Word* Node)
{
    if(m_pHead == NULL)
    {
	m_pHead = Node;
	m_pHead->setNext(m_pHead);
	return 0;
    }
    else
    {
	Word* pCur = m_pHead;

	while(pCur->getNext() != m_pHead)
	{
	    pCur = pCur->getNext();
	}
	pCur->setNext(Node);
	Node->setNext(m_pHead);
	return 0;
    }
    return -1;
}
Word* CircularQueue::Pop()
{
    if(m_pHead == NULL)
	return NULL;
    else
    {
	Word* temp = m_pHead;
	Word* tail = m_pHead;

	while(tail->getNext() != m_pHead)
	    tail = tail->getNext();

	if(m_pHead == tail)
	{
	    m_pHead = NULL;
	    return temp;
	}

	m_pHead = m_pHead->getNext();
	tail->setNext(m_pHead);
	return temp;
    }
}
Word* CircularQueue::Search(char* word)
{
    Word* pCur = m_pHead;

    if(m_pHead == NULL)
    {
	return NULL;
    }

    while(1)
    {
	if(strcmp(pCur->getWord(),word) == 0)
	    return pCur;
	if(pCur->getNext() == m_pHead)
	    break;
	pCur = pCur->getNext();
    }
    return NULL;
}
