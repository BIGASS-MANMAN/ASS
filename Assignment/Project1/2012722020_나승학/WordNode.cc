#include "WordNode.h"

WordNode::WordNode()
{
	pLeft = '\0'; // Pointer Left value is NULL
	pRight = '\0';// Pointer Right value is NULL
	pNext = '\0'; // Pointer Next value is NULL
}


WordNode::~WordNode()
{
}

char *		WordNode::GetWord()	// Get Word
{
	return wordmean.first;		// first Mean rerutn
}
char *		WordNode::GetMean()	// Get Word Mean
{
	return wordmean.second;		// second Mean return
}
WordNode *	WordNode::GetLeft()	// Get BST Left Pointer
{
	return pLeft;				// Pointer Left return
}
WordNode *	WordNode::GetRight()// Get BST Right Pointer
{
	return pRight;				// Pointer Right return
}
WordNode *	WordNode::GetNext()	// Get Queue Next Pointer
{
	return pNext;				// Pointer Next return
}

void		WordNode::SetWord(char * word)		// Set Word
{
	wordmean.first = word;						// Set the first mean
}
void		WordNode::SetMean(char * mean)		// Set Word Mean
{
	wordmean.second = mean;						// Set the second mean
}
void		WordNode::SetLeft(WordNode * node)	// Set BST Left Pointer
{
	pLeft = node;								// Pointer Left is pointing Node
}
void		WordNode::SetRight(WordNode * node)	// Set BST Right Pointer
{
	pRight = node;								// Pointer Right is pointing Node
}
void		WordNode::SetNext(WordNode * node)	// Set Queue Next Pointer
{	
	pNext = node;								// Pointer Next is pointing Node
}