#include "WordNode.h"

WordNode::WordNode()
{
	wordmean = std::make_pair(word, mean);
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}


WordNode::~WordNode()
{
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}

char * WordNode::GetWord()
{
	return wordmean.first;
}

char * WordNode::GetMean()
{
	return wordmean.second;
}

void WordNode::SetWord(char * WORD)
{
	strcpy(wordmean.first, WORD);
}

void WordNode::SetMean(char * MEAN)
{
	strcpy(wordmean.second, MEAN);
}

WordNode * WordNode::GetLeft()
{
	return pLeft;
}

WordNode * WordNode::GetRight()
{
	return pRight;
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

WordNode * WordNode::GetNext()
{
	return pNext;
}
