#include "WordNode.h"


WordNode::WordNode()
{
	wordmean.first[32];
	wordmean.second[32];
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}


WordNode::~WordNode()
{
}

char* WordNode::GetWord()
{
	return wordmean.first;
}

char* WordNode::GetMean()
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
