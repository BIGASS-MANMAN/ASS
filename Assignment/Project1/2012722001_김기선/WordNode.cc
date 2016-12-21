#include "WordNode.h"

WordNode::WordNode()
{
///////////reset//////////////
	pLeft = NULL;		
	pRight = NULL;		
	pNext = NULL;		
	wordmean.first = NULL;		//word
	wordmean.second = NULL;		//mean
}


WordNode::~WordNode()
{
}

char* WordNode::GetWord()	//return word
{
	return wordmean.first;
}

char* WordNode::GetMean()	//return mean
{
	return wordmean.second;
}

WordNode* WordNode::GetLeft()	//return left child
{
	return pLeft;
}

WordNode* WordNode::GetRight()	//return right child
{
	return pRight;
}

WordNode* WordNode::GetNext()	//return next
{
	return pNext;
}

void WordNode::SetWord(char* word)	//set word
{
	wordmean.first = word;
}

void WordNode::SetMean(char* mean)	//set mean
{
	wordmean.second = mean;
}

void WordNode::SetLeft(WordNode * node)   // Set BST Left Pointer
{
	pLeft = node;
}

void WordNode::SetRight(WordNode * node)   // Set BST Right Pointer
{
	pRight = node;
}

void WordNode::SetNext(WordNode * node)   // Set Queue Next Pointer
{
	pNext = node;
}
