#include "WordNode.h"

WordNode::WordNode()
{	// Initialize the member variables in constructor
	pLeft = NULL;
	pRight = NULL;
	pNext = NULL;
	wordmean.first = new char;
	wordmean.second = new char;
}

WordNode::~WordNode()
{
}

char * WordNode::GetWord()
{
	return  wordmean.first;		// Get the word
}

char * WordNode::GetMean()
{
	return wordmean.second;		// Get the meaning of the word
}

WordNode * WordNode::GetLeft()
{
	return pLeft;		//	Get the left child
}

WordNode * WordNode::GetRight()
{
	return pRight;		// Get the right child
}

WordNode * WordNode::GetNext()
{
	return pNext;		// Get the next node
}

void WordNode::SetWord(char * word)
{
	strcpy(wordmean.first, word);	// Set the word
}

void WordNode::SetMean(char * mean)
{
	strcpy(wordmean.second, mean);		// Set the meaning of word
}

void WordNode::SetLeft(WordNode * node)
{
	pLeft = node;		// Set left child
}

void WordNode::SetRight(WordNode * node)
{
	pRight = node;		// Set right child
}

void WordNode::SetNext(WordNode * node)
{
	pNext = node;		// Set the next node
}
