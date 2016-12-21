#include "WordNode.h"
WordNode::WordNode()
{
	wordmean.first = NULL;
	wordmean.second = NULL;
	pLeft = NULL;
	pRight = NULL;
	pNext = NULL;
}
WordNode::WordNode(char* word, char* mean)
{
	int str_len = strlen(word) + 1;
	wordmean.first = new char[str_len];
	strcpy(wordmean.first,  word);

	str_len = strlen(mean) + 1;
	wordmean.second = new char[str_len];
	strcpy(wordmean.second,  mean);

	pLeft = NULL;
	pRight = NULL;
	pNext = NULL;
}
WordNode::~WordNode()
{
	if(wordmean.first != NULL)
		delete wordmean.first;
	if (wordmean.second != NULL)
		delete wordmean.second;	
	pLeft = NULL;
	pRight = NULL;
	pNext = NULL;
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
void WordNode::SetWord(char* word)
{
	int str_len = strlen(word) + 1;
	if (wordmean.first != NULL)
		delete wordmean.first;
	wordmean.first = new char[str_len];
	strcpy(wordmean.first, word);
}
void WordNode::SetMean(char* mean)
{
	int str_len = strlen(mean) + 1;
	if (wordmean.second != NULL)
		delete wordmean.second;
	wordmean.second = new char[str_len];
	strcpy(wordmean.second,  mean);
}
void WordNode::SetLeft(WordNode* node)
{
	pLeft = node;
}
void WordNode::SetRight(WordNode* node)
{
	pRight = node;
}
void WordNode::SetNext(WordNode* node)
{
	pNext = node;
}

