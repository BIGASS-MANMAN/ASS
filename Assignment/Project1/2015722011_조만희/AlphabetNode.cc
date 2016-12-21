#include "AlphabetNode.h"


// Constructor of AlphabetNode
AlphabetNode::AlphabetNode()
{
	// Set alphabet, pLeft, pRight to NULL
	alphabet = '\0';
	pLeft = '\0';
	pRight = '\0';

	// bst is new WordBST
	bst = new WordBST;
}

// Destructor of AlphabetNode
AlphabetNode::~AlphabetNode()
{
	// delete bst
	delete bst;
}

// Getter alphabet
char AlphabetNode::GetAlphabet()
{
	// return alphabet
	return alphabet;
}

// Getter bst
WordBST * AlphabetNode::GetBST()
{
	// return bst
	return bst;
}

// Getter pLeft( left child )
AlphabetNode * AlphabetNode::GetLeft()
{
	// return pLeft
	return pLeft;
}

// Getter pRight( right child )
AlphabetNode * AlphabetNode::GetRight()
{
	// return pRight
	return pRight;
}

// Setter alphabet
void AlphabetNode::SetAlphabet(char alphabet)
{
	// AlphabetNode's alphabet is alphabet passed by parameter
	AlphabetNode::alphabet = alphabet;
}

// Setter pLeft( left child )
void AlphabetNode::SetLeft(AlphabetNode * node)
{
	//pLeft is node
	pLeft = node;
}

// Setter pRight( right child )
void AlphabetNode::SetRight(AlphabetNode * node)
{
	//pRight is node
	pRight = node;
}