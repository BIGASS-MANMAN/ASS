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

// Get Alphabet
char AlphabetNode::GetAlphabet()
{
	return alphabet;
}

// Get Word BST
WordBST* AlphabetNode::GetBST()
{
	return bst;
}

// Get BST Left Pointer
AlphabetNode* AlphabetNode::GetLeft()
{
	return pLeft;
}

// Get BST Right Pointer
AlphabetNode* AlphabetNode::GetRight()
{
	return pRight;
}

// Set Alphabet
void AlphabetNode::SetAlphabet(char alphabet)
{
	this->alphabet = alphabet;
}

// Set BST Left Pointer
void AlphabetNode::SetLeft(AlphabetNode * node)
{
	pLeft = node;
}

// Set BST Right Pointer
void AlphabetNode::SetRight(AlphabetNode * node)
{
	pRight = node;
}