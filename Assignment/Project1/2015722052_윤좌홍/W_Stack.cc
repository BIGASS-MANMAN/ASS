#include "W_Stack.h"


W_Stack::W_Stack(void)
{
	pHead = 0;	//constructor setting: standard inserting stack pointer pHead
}
void W_Stack::Push(WordNode *push_node)
{
	if(push_node == 0) return;		//if pointer variable is point out null, stop function
	if(push_node) push_node->SetNext(0);	//because of using queue, pNext is initialization value
	if(pHead != 0){				//not first inserting
		for(WordNode *cur = pHead; cur; cur = cur->GetNext()){
			if(cur->GetNext() == 0){//searching empty inserting space 
				cur->SetNext(push_node);//setting node
				break;
			}
		}
	}
	else
		pHead = push_node;		//first inserting
}
WordNode * W_Stack::Pop()
{
	WordNode *cur = pHead;
	WordNode *prev = pHead;
	if(pHead){
		for( ; ;cur = cur->GetNext() ){//first in, last out implementation
			if(cur->GetNext() == 0){
				break;
			}
			prev = cur;
		}
		if(cur == pHead){
			pHead= 0;
		}
		else{
			prev->SetNext(0);
		}
		return cur;			//checking pHead pointer
	}
	else
		return 0;
}
//in this case
//1. simillary queue's first in, first out in characteristic
//2. using Iterator Lever ordering
WordNode * W_Stack::First_Pop()
{
	WordNode * cur = pHead;
	if(pHead){
		pHead = pHead->GetNext();
		return cur;
	}
	else return 0;
}
bool W_Stack::isEmpty()
{
	if(pHead){
		return false;
	}
	else
		return true;
}

W_Stack::~W_Stack(void)
{
}

