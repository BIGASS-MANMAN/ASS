#include "WordNode.h"

// The WordNode constructor
WordNode::WordNode()
{
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}

// The WordNode destructor
WordNode::~WordNode()
{
	if (pLeft != NULL)
		delete pLeft;
	if (pRight != NULL)
		delete pRight;
	if (pNext != NULL)
		delete pNext;
}

char * WordNode::GetWord()
{
	return wordmean.first;
}

char * WordNode::GetMean()
{
	return wordmean.second;
}

WordNode * WordNode::GetLeft()
{
	return pLeft;
}

WordNode * WordNode::GetRight()
{
	return pRight;
}

WordNode * WordNode::GetNext()
{
	return pNext;
}

void WordNode::SetWord(char * word)
{
	wordmean.first = word;
}

void WordNode::SetMean(char * mean)
{
	wordmean.second = mean;
}

void WordNode::SetLeft(WordNode * node)
{
	pLeft = node;
}

void WordNode::SetRight(WordNode * node)
{
	pRight = node;
}

void WordNode::SetNext(WordNode * node)
{
	pNext = node;
}
