#ifndef _WSTACK_H_
#define _WSTACK_H_
#include "WordNode.h"
class W_Stack
{
public:
	W_Stack(void);
	WordNode *pHead;
	void Push(WordNode * node);
	WordNode * Pop();
	WordNode * First_Pop();
	bool isEmpty();
	~W_Stack(void);
};
#endif
