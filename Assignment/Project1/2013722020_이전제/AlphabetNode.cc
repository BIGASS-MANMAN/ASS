#include "AlphabetNode.h"



AlphabetNode::AlphabetNode()// AlphabetNode constructor without parameter
{
	alphabet = '\0';
	bst = new WordBST;
	pLeft = '\0';
	pRight = '\0';
	
}


AlphabetNode::~AlphabetNode() // AlphabetNode destructor
{
	delete bst;
}


char			AlphabetNode::GetAlphabet()					// Get Alphabet
{
	return alphabet;
}
WordBST	*		AlphabetNode::GetBST()					// Get Word BST
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

void			AlphabetNode::SetAlphabet(char Alphabet)		// Set Alphabet
{
	alphabet = Alphabet;
}
void			AlphabetNode::SetLeft(AlphabetNode * node)	// Set BST Left Pointer
{
	pLeft = node;
}
void			AlphabetNode::SetRight(AlphabetNode * node)	// Set BST Right Pointer
{
	pRight = node;
}