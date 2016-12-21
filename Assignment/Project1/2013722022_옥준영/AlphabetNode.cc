#include "AlphabetNode.h"



AlphabetNode::AlphabetNode()
{
	alphabet = '\0';
	bst = new WordBST;
	pLeft = '\0';
	pRight = '\0';
}


AlphabetNode::~AlphabetNode()
{
	delete bst;
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

void			AlphabetNode::SetAlphabet(char s_alphabet)		// Set Alphabet
{
	alphabet = s_alphabet;
}
void			AlphabetNode::SetLeft(AlphabetNode * node)	// Set BST Left Pointer
{
	pLeft = node;
}
void			AlphabetNode::SetRight(AlphabetNode * node)	// Set BST Right Pointer
{
	pRight = node;
}