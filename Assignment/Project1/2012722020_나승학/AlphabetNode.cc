#include "AlphabetNode.h"



AlphabetNode::AlphabetNode()
{

	alphabet = '\0';		// alphabet set NULL
	bst = new WordBST;		// bst dynamic allocation wordbst
	pLeft = '\0';			// pleft set NULL
	pRight = '\0';			// pright set NULL	
	pNext = '\0';			// pnext set NULL
}


AlphabetNode::~AlphabetNode()		// Destructor
{
	delete bst;	// Delete WORDBST
}

char			AlphabetNode::GetAlphabet()					// Get Alphabet
{	
	return alphabet;										// return alphabet
}
WordBST	*		AlphabetNode::GetBST()						// Get Word BST
{
	return bst;												// return bst
}
AlphabetNode *	AlphabetNode::GetLeft()						// Get BST Left Pointer
{
	return pLeft;											// return pleft
}
AlphabetNode *	AlphabetNode::GetRight()					// Get BST Right Pointer
{
	return pRight;											// return pright
}
AlphabetNode *	AlphabetNode::GetNext()						// Get NEXT 
{
	return pNext;											// return pnext
}
void			AlphabetNode::SetAlphabet(char alphabet)	// Set Alphabet
{
	AlphabetNode::alphabet = alphabet;						// alphabet set alphabet
}
void			AlphabetNode::SetLeft(AlphabetNode * node)	// Set BST Left Pointer
{
	pLeft = node;											// pleft set node
}
void			AlphabetNode::SetRight(AlphabetNode * node)	// Set BST Right Pointer
{
	pRight = node;											// pright set node
}
void			AlphabetNode::SetNext(AlphabetNode * node)	// Set Next 
{
	pNext = node;											// pnext set node
}