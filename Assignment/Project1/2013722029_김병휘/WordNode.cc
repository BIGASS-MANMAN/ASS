#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "WordNode.h"

WordNode::WordNode()
{
	wordmean.first = '\0';
	wordmean.second = '\0';
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}

WordNode::~WordNode()
{
	if (wordmean.first != '\0')
		delete wordmean.first;

	if (wordmean.second != '\0')
		delete wordmean.second;
}

char* WordNode::GetWord()
{
	return wordmean.first;
}

char* WordNode::GetMean()
{
	return wordmean.second;
}

WordNode* WordNode::GetLeft()
{
	return pLeft;
}

WordNode* WordNode::GetRight()
{
	return pRight;
}

WordNode* WordNode::GetNext()
{
	return pNext;
}

void WordNode::SetWord(char * word)
{
	if (wordmean.first != '\0')
		delete wordmean.first;

	wordmean.first = new char[strlen(word) + 1];
	strcpy(wordmean.first, word);
}

void WordNode::SetMean(char * mean)
{
	if (wordmean.second != '\0')
		delete wordmean.second;

	wordmean.second = new char[strlen(mean) + 1];
	strcpy(wordmean.second, mean);
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