#include "WordNode.h"

/////////////////WORD NODE////////////////////
WordNode::WordNode()
{
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
	Parent ='\0';
}
WordNode::~WordNode()
{
	delete pLeft;
	delete pRight;
	delete pNext;
	delete Parent;
}

/////////////////WORD STACK////////////////////
void Stack::Push(WordNode* n)
{
	if(pHead==NULL) //set the pHead if pHead is empty
		pHead=n;
	else
	{
		if(n!=NULL){
			n->SetNext(pHead);
			pHead=n;
		}
	}
}
WordNode* Stack::Pop()
{	
	if(pHead==NULL)	//return NULL if pHead is empty
		return NULL;

	WordNode* node=pHead->GetNext();
	WordNode* popnode;
	
	if(node!=NULL){
		pHead->SetNext(NULL);
		popnode=pHead;
		pHead=node;
	}
	else{	//there is a node in Stack
		popnode=pHead;
		pHead=NULL;
	}

	return popnode;
}