#include "A_Stack.h"


A_Stack::A_Stack(void)
{
	pHead = 0;
}
void A_Stack::Push(AlphabetNode *push_node)
{
	if(push_node == 0) return;
	if(push_node) push_node->SetNext(0);
	if(pHead != 0){
		for(AlphabetNode *cur = pHead; cur; cur = cur->GetNext()){
			if(cur->GetNext() == 0){
				cur->SetNext(push_node);
				break;
			}
		}
	}
	else
		pHead = push_node;
}
AlphabetNode * A_Stack::Pop()
{
	AlphabetNode *cur = pHead;
	AlphabetNode *prev = pHead;
	if(pHead){
		for( ; ;cur = cur->GetNext() ){
			if(cur->GetNext() == 0){
				break;
			}
			prev = cur;
		}
		if(cur == pHead){
			pHead = 0;
		}
		else{
			prev->SetNext(0);
		}
		return cur;
	}
	else
		return 0;
}
AlphabetNode * A_Stack::First_Pop()
{
	AlphabetNode * cur = pHead;
	if(pHead){
		pHead = pHead->GetNext();
		return cur;
	}
	else return 0;
}
bool A_Stack::isEmpty()
{
	if(pHead){
		return false;
	}
	else
		return true;
}

A_Stack::~A_Stack(void)
{
}

