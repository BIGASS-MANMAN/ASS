#include "WordNode.h"
#include <iostream>
#include <string>
using namespace std;


WordNode::WordNode()//Initialization of variables
{
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
	wordmean.first=NULL;
	wordmean.second=NULL;
}


WordNode::~WordNode()
{
}

char* WordNode::GetWord()//Return word
{
	return this->wordmean.first;
}
char* WordNode::GetMean()//Return mean
{
	return this->wordmean.second;
}
WordNode* WordNode::GetLeft()//Return left node
{
	return this->pLeft;
}
WordNode* WordNode::GetRight()//Return right node
{
	return this->pRight;
}
WordNode* WordNode::GetNext()//Return next node
{
	return this->pNext;
}
void WordNode::SetWord(char* word)//Change word
{
	this->wordmean.first=word;
}
void WordNode::SetMean(char* mean)//Change mean
{
	this->wordmean.second=mean;
}
void WordNode::SetLeft(WordNode* node)//Change left node
{
	this->pLeft=node;
}
void WordNode::SetRight(WordNode* node)//Change right node
{
	this->pRight=node;
}
void WordNode::SetNext(WordNode* node)//Change next node
{
	this->pNext=node;
}
