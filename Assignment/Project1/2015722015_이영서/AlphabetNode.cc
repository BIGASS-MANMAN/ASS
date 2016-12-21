#include "AlphabetNode.h"



////////////////////////AlphabetNode class////////////////////////////
AlphabetNode::AlphabetNode()
{
	alphabet = '\0';
	bst = new WordBST;
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}


AlphabetNode::~AlphabetNode()
{
	delete bst;
	delete pLeft;
	delete pRight;
	delete pNext;
}

////////////////////////AlphabetQueue class////////////////////////////

void AlpaQueue::Push(AlphabetNode * node)
{
	if(pHead==NULL)	//set the pHead if ead is empty
		pHead=node;
	else
	{
		AlphabetNode* current=pHead;

		while(current->GetNext()){
			if(current->GetAlphabet()==node->GetAlphabet())
				return;//find same node
			current=current->GetNext();
		}
		current->SetNext(node);
	}
}
AlphabetNode* AlpaQueue::Pop()
{
	if(pHead==NULL)
		return NULL;

	AlphabetNode* node=pHead->GetNext();
	AlphabetNode* popnode;
	
	pHead->SetNext(NULL);
	popnode=pHead;
	pHead=node;
	
	return popnode;
}
////////////////////////AlphabetStack class////////////////////////////
AlphaStack::AlphaStack()
{
	
	pHead = '\0';
}

void AlphaStack::Push(AlphabetNode * n)
{
	if(pHead==NULL)	//set the pHead if pHead is empty
		pHead=n;
	else
	{
		if(n!=NULL){
			n->SetNext(pHead);
			pHead=n;
		}
	}
}
AlphabetNode* AlphaStack::Pop()
{
	if(pHead==NULL)	//return NULL if pHead is empty
		return NULL;

	AlphabetNode* node=pHead->GetNext();
	AlphabetNode* popnode;

	if(node!=NULL){
		pHead->SetNext(NULL);
		popnode=pHead;
		pHead=node;
	}
	else{	//there is a node in AlphaStack
		popnode=pHead;
		pHead=NULL;
	}

	return popnode;
}
