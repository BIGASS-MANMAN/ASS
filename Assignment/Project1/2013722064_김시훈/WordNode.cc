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
	free(wordmean.first);
	free(wordmean.second);
}

char* WordNode::GetWord()               // Get Word
{
	return wordmean.first;
}

char* WordNode::GetMean()               // Get Word Mean
{
	return wordmean.second;
}

WordNode* WordNode::GetLeft()            // Get BST Left Pointer
{
	return pLeft;
}

WordNode* WordNode::GetRight()               // Get BST Right Pointer
{
	return pRight;
}

WordNode* WordNode::GetNext()               // Get Queue Next Pointer
{
	return pNext;
}

void WordNode::SetWord(char* word)
{
	wordmean.first = (char*)malloc(sizeof(char) * 50);	
	strncpy(wordmean.first, word, strlen(word) + 1);
}

void WordNode::SetMean(char* mean)
{
	wordmean.second = (char*)malloc(sizeof(char) * 50);	
	strncpy(wordmean.second, mean, strlen(mean) + 1);
}

void WordNode::SetLeft(WordNode * node)   // Set BST Left Pointer
{
	pLeft = node;
}

void WordNode::SetRight(WordNode * node)// Set BST Right Pointer
{
	pRight = node;
}

void WordNode::SetNext(WordNode * node)   // Set Queue Next Pointer
{
	pNext = node;
}
