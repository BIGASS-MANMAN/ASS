#include "AlphabetNode.h"

AlphabetNode::AlphabetNode()
{
	alphabet = NULL;
	bst = new WordBST;
	pLeft = NULL;
	pRight = NULL;
	pNext = NULL;
}

AlphabetNode::~AlphabetNode()
{
	//deallocate bst
	if(bst != NULL)
		delete bst;
	pLeft = NULL;
	pRight = NULL;
	pNext = NULL;
}
char			AlphabetNode::GetAlphabet()					// Get Alphabet
{
	return alphabet;
}
WordBST	*		AlphabetNode::GetBST()						// Get Word BST
{
	return bst;
}
AlphabetNode *	AlphabetNode::GetLeft()						// Get BST Left Pointer
{
	return pLeft;
}
AlphabetNode *	AlphabetNode::GetRight()						// Get BST Right Pointer
{
	return pRight;
}
AlphabetNode *	AlphabetNode::GetNext()
{
	return pNext;
}
void			AlphabetNode::SetAlphabet(char alphabet)		// Set Alphabet
{
	this->alphabet = alphabet;
}
void			AlphabetNode::SetLeft(AlphabetNode * node)	// Set BST Left Pointer
{
	pLeft = node;
}
void			AlphabetNode::SetRight(AlphabetNode * node)	// Set BST Right Pointer
{
	pRight = node;
}
void			AlphabetNode::SetNext(AlphabetNode * node)
{
	pNext = node;
}
