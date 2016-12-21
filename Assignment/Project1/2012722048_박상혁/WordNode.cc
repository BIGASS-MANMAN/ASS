#include "WordNode.h"
#include <cstring>
#include <iostream>
using namespace std;


WordNode::WordNode()
{
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}


WordNode::~WordNode()
{
}


char *		WordNode::GetWord()		// Get Word
{
	return wordmean.first;
}


char *		WordNode::GetMean()		// Get Word Mean
{
	return wordmean.second;
}


WordNode *	WordNode::GetLeft()		// Get BST Left Pointer
{
	return pLeft;
}


WordNode *	WordNode::GetRight()		// Get BST Right Pointer
{
	return pRight;
}


WordNode *	WordNode::GetNext()		// Get Queue Next Pointer
{
	return pNext;
}


void		WordNode::SetWord(char * word)		// Set Word
{
	int size = 0;
	
	while (word[size] != '\0')			// Count the length
		size++;

	wordmean.first = new char[size + 1];
	for (int i = 0; i <= size; i++)			// Set Word
		wordmean.first[i] = word[i];
}


void		WordNode::SetMean(char * mean)		// Set Word Mean
{
	int size = 0;

	while (mean[size] != '\0')			// Count the length
		size++;

	wordmean.second = new char[size + 1];
	for (int i = 0; i <= size; i++)			// Set mean
		wordmean.second[i] = mean[i];
}


void		WordNode::SetLeft(WordNode * node)	// Set BST Left Pointer
{
	pLeft = node;
}


void		WordNode::SetRight(WordNode * node)	// Set BST Right Pointer
{
	pRight = node;
}


void		WordNode::SetNext(WordNode * node)	// Set Queue Next Pointer
{
	pNext = node;
}
