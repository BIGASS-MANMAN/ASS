#include "WordNode.h"
#include <string.h>



WordNode::WordNode()
{
	wordmean.first = new char[256]();
	wordmean.second = new char[256]();
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}


WordNode::~WordNode()
{
	delete wordmean.first;
	delete wordmean.second;
}


char* WordNode::GetWord()				{	return wordmean.first;}

char* WordNode::GetMean()				{	return wordmean.second;}

WordNode* WordNode::GetLeft()			{	return pLeft;}

WordNode* WordNode::GetRight()			{	return pRight;}

WordNode* WordNode::GetNext()			{	return pNext;}

void WordNode::SetWord(const char* word)		{	strcpy(wordmean.first,word);}

void WordNode::SetMean(const char* mean)		{	strcpy(wordmean.second,mean);}

void WordNode::SetLeft(WordNode* node)	{	pLeft = node;}

void WordNode::SetRight(WordNode* node)	{	pRight = node;}

void WordNode::SetNext(WordNode* node)	{	pNext = node;}