#include "AlphabetNode.h"
#include <utility>	

AlphabetNode::AlphabetNode()
{
	alphabet = '\0';
	bst = new WordBST;
	pLeft = '\0';
	pRight = '\0';
	cnt = 0;
}

AlphabetNode::~AlphabetNode()
{
	delete bst;
}

char AlphabetNode::GetAlphabet() // alphabet
{
	return alphabet;
}

WordBST * AlphabetNode::GetBST() // word bst
{
	return bst;
}

AlphabetNode * AlphabetNode::GetLeft() // point left node
{
	return pLeft;
}

AlphabetNode * AlphabetNode::GetRight() // point right node
{
	return pRight;
}

int AlphabetNode::GetCount() // count
{
	return cnt;
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

void AlphabetNode::SetCount(int count)
{
	cnt = count;
}
