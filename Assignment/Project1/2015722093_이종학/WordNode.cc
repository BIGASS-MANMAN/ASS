#include "WordNode.h"



WordNode::WordNode() //constructor
{
	pLeft = '\0'; //initialzation
	pRight = '\0';
	pNext = '\0';
	wordmean.first = word;
	wordmean.second = mean;
}


WordNode::~WordNode()
{
}

void WordNode::SetWord(char * word) //Set Word
{
	strcpy(wordmean.first, word);
}

void WordNode::SetMean(char * mean) //Set Mean
{
	strcpy(wordmean.second, mean);
}

void WordNode::SetNext(WordNode * node) //Set Queue Next Pointer
{
	pNext = node;
}

void WordNode::SetLeft(WordNode * node) //Set BST Left Pointer
{
	pLeft = node;
}

void WordNode::SetRight(WordNode * node) //Set BST Right Pointer
{
	pRight = node;
}

char* WordNode::GetWord() //Get Word
{
	return wordmean.first;
}

char* WordNode::GetMean() //Get Mean
{
	return wordmean.second;
}

WordNode* WordNode::GetNext() //Get Queue Next Pointer
{
	return pNext;
}

WordNode* WordNode::GetLeft() //Get BST Left Pointer
{
	return pLeft;
}

WordNode* WordNode::GetRight() //Get BST Right Pointer
{
	return pRight;
}