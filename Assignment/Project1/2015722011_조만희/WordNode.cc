#include "WordNode.h"
#include <string.h>

// Constructor of WordNode
WordNode::WordNode()
{
	// Initialize properties
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}

// Destructor of WordNode
WordNode::~WordNode()
{
	// delete wordmean
	delete wordmean.first;
	delete wordmean.second;
}

// Getter wordmean.first( Word )
char * WordNode::GetWord()
{
	// return Word
	return wordmean.first;
}

// Getter wordmean.second( Mean )
char * WordNode::GetMean()
{
	// return Mean
	return wordmean.second;
}

// Getter pLeft( Left child )
WordNode * WordNode::GetLeft()
{
	// return left child
	return pLeft;
}

// Getter pRight( Right child )
WordNode * WordNode::GetRight()
{
	// return right child
	return pRight;
}


WordNode * WordNode::GetNext()
{
	return pNext;
}

// Setter wordmean.first( Word )
void WordNode::SetWord(char * word)
{
	// Allocate memory to wordmean.first
	wordmean.first = new char[strlen(word) + 1];
	// And set wordmean.first to word
	strcpy(wordmean.first, word);
}

// Setter wordmean.second( Mean )
void WordNode::SetMean(char * mean)
{
	// Allocate memory to wordmean.second
	wordmean.second = new char[strlen(mean) + 1];
	// And set wordmean.second to mean
	strcpy(wordmean.second, mean);
}

// Setter pLeft( Left child )
void WordNode::SetLeft(WordNode * node)
{
	// Set pLeft to node
	pLeft = node;
}

// Setter pRight( Right child )
void WordNode::SetRight(WordNode * node)
{
	// Set pRight to node
	pRight = node;
}

void WordNode::SetNext(WordNode * node)
{
	pNext = node;
}
