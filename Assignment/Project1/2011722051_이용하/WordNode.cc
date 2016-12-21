#include "WordNode.h"

WordNode::WordNode()
{
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
	cnt = 0;
}

WordNode::~WordNode()
{
}

char * WordNode::GetWord()
{
	return wordmean.first; // return word
}

char * WordNode::GetMean()
{
	return wordmean.second; // return mean
}

WordNode * WordNode::GetLeft()
{
	return pLeft; // return BST left pointer
}

WordNode * WordNode::GetRight()
{
	return pRight; // return BST right pointer
}

WordNode * WordNode::GetNext()
{
	return pNext; // return QUEUE next pointer
}

int WordNode::GetCount()
{
	return cnt; // return count
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

void WordNode::SetCount(int count)
{
	cnt = count;
}
