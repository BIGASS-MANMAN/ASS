#ifndef _ASTACK_H_
#define _ASTACK_H_
#include "AlphabetNode.h"
class A_Stack
{
public:
	A_Stack(void);
	AlphabetNode *pHead;
	void Push(AlphabetNode * node);
	AlphabetNode * Pop();
	AlphabetNode * First_Pop();
	bool isEmpty();
	~A_Stack(void);
};

#endif
