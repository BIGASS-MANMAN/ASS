#include "AlphabetNode.h"

AlphabetNode::AlphabetNode()
{
	alphabet = '\0';
	bst = new WordBST;
	bst->root = '\0';
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}

AlphabetNode::~AlphabetNode()
{
	delete bst;
}

char AlphabetNode::GetAlphabet()
{
	return alphabet;
}

WordBST* AlphabetNode::GetBST()
{
	if (bst->root != '\0')
		return bst;
	else
		return 0;
}

AlphabetNode* AlphabetNode::GetLeft()
{
	return pLeft;
}

AlphabetNode* AlphabetNode::GetRight()
{
	return pRight;
}

AlphabetNode* AlphabetNode::GetNext()
{
	return pNext;
}

void AlphabetNode::SetAlphabet(char alphabet)
{
	this->alphabet = alphabet;
}

void AlphabetNode::SetLeft(AlphabetNode * node)
{
	pLeft = node;
}

void AlphabetNode::SetRight(AlphabetNode * node)
{
	pRight = node;
}

void AlphabetNode::SetNext(AlphabetNode * node)
{
	pNext = node;
}