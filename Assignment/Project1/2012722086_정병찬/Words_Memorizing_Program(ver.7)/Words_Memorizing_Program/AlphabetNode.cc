#include "AlphabetNode.h"




AlphabetNode::AlphabetNode()	// Initialize member variables in constructor
{
	Alphabet = NULL;
	bst = new WordBST;
	pLeft = NULL;
	pRight = NULL;
}

AlphabetNode::~AlphabetNode()
{
}

char AlphabetNode::GetAlphabet()
{
	return Alphabet;		// Get the alphabet
}

WordBST * AlphabetNode::GetBST()
{
	return bst;			// Get the bst
}

AlphabetNode * AlphabetNode::GetLeft()
{
	return pLeft;		// Get the left child
}

AlphabetNode * AlphabetNode::GetRight()
{
	return pRight;		// Get the right child
}

void AlphabetNode::SetAlphabet(char alphabet)
{
	Alphabet = alphabet;		// Set the alphabet
}

void AlphabetNode::SetLeft(AlphabetNode * node)
{
	pLeft = node;		// Set the left child 
}

void AlphabetNode::SetRight(AlphabetNode * node)
{
	pRight = node;		// Set the right child
}
