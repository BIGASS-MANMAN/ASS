#include "AlphabetNode.h"

AlphabetNode::AlphabetNode()
{
	alphabet = '\0';
	bst = new WordBST;
	pLeft = NULL;
	pRight = NULL;
}


AlphabetNode::~AlphabetNode()
{
	alphabet = '\0';
	delete bst;
	pLeft = NULL;
	pRight = NULL;
}

char AlphabetNode::GetAlphabet()
{
	return alphabet;
}

AlphabetNode * AlphabetNode::GetLeft()
{
	return pLeft;
}

AlphabetNode * AlphabetNode::GetRight()
{
	return pRight;
}

void AlphabetNode::SetAlphabet(char alphabet1)
{
	alphabet = alphabet1;
}

void AlphabetNode::SetLeft(AlphabetNode* node)
{
	pLeft = node;
}

void AlphabetNode::SetRight(AlphabetNode * node)
{
	pRight = node;
}

WordBST * AlphabetNode::GetBST()
{
	return bst;
}


