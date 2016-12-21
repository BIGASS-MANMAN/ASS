#include "AlphabetNode.h"

// The constructor
AlphabetNode::AlphabetNode()
{
	alphabet = '\0';
	bst = new WordBST;
	pLeft = '\0';
	pRight = '\0';
}

// The destructor
AlphabetNode::~AlphabetNode()
{
	delete bst;
}

// This alphabet returning
char AlphabetNode::GetAlphabet()
{
	return alphabet;
}

// the alphabet's BST
WordBST * AlphabetNode::GetBST()
{
	return bst;
}

// The left and right child
AlphabetNode * AlphabetNode::GetLeft()
{
	return pLeft;
}

AlphabetNode * AlphabetNode::GetRight()
{
	return pRight;
}

// Set the alphabet
void AlphabetNode::SetAlphabet(char alphabet)
{
	this->alphabet = alphabet;
}

void AlphabetNode::SetLeft(AlphabetNode * node)
{
	this->pLeft = node;
}

void AlphabetNode::SetRight(AlphabetNode * node)
{
	this->pRight = node;
}