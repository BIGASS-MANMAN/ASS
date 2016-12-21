#include "WordNode.h"

WordNode::WordNode()//initialize all pointer in Node
{
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}
WordNode::~WordNode() // delete all of infomation in Node
{
	delete wordmean.first;
	delete wordmean.second;
}

char *		WordNode::GetWord() { return wordmean.first; }				// Get Word
char *		WordNode::GetMean() { return wordmean.second; }				// Get Word Mean
WordNode *	WordNode::GetLeft() { return pLeft; }						// Get BST Left Pointer
WordNode *	WordNode::GetRight() { return pRight; }						// Get BST Right Pointer
WordNode *	WordNode::GetNext() { return pNext; }						// Get Queue Next Pointer
void		WordNode::SetWord(char * word) { wordmean.first = word; }	// Set Word
void		WordNode::SetMean(char * mean) { wordmean.second = mean; }	// Set Word Mean
void		WordNode::SetLeft(WordNode * node) { pLeft = node; }		// Set BST Left Pointer
void		WordNode::SetRight(WordNode * node) { pRight = node; }		// Set BST Right Pointer
void		WordNode::SetNext(WordNode * node) { pNext = node; }		// Set Queue Next Pointer