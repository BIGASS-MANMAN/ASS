#include "WordNode.h"

WordNode::WordNode()	//WordNode constructor
{
	wordmean.first = NULL;
	wordmean.second = NULL;
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}


WordNode::~WordNode()		//WordNode destructor
{
	wordmean.first = NULL;
	wordmean.second = NULL;
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}

char *	WordNode::GetWord()	
{
	return wordmean.first;
}// Get Word
char *	WordNode::GetMean()
{
	return wordmean.second;
}// Get Word Mean
WordNode *	WordNode::GetLeft()
{
	return pLeft;
}// Get BST Left Pointer
WordNode *	WordNode::GetRight()
{
	return pRight;
}// Get BST Right Pointer
WordNode *	WordNode::GetNext()
{
	return pNext;
}// Get Queue Next Pointer

void	WordNode::SetWord(char * word)
{
	if (wordmean.first != NULL)
	{
		delete wordmean.first;
	}
	wordmean.first = new char[strlen(word) + 1];
	strcpy(wordmean.first, word);
}// Set Word

void	WordNode::SetMean(char * mean)
{
	if (wordmean.second != NULL)
	{
		delete wordmean.second;
	}
	wordmean.second = new char[strlen(mean) + 1];
	strcpy(wordmean.second, mean);
}// Set Word Mean

void	WordNode::SetLeft(WordNode * node)
{
	pLeft = node;
}// Set BST Left Pointer

void		WordNode::SetRight(WordNode * node)
{
	pRight = node;
}// Set BST Right Pointer

void		WordNode::SetNext(WordNode * node)
{
	pNext = node;
}// Set Queue Next Pointer