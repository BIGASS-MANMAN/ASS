#include "AlphabetNode.h"

AlphabetNode::AlphabetNode()
{
	alphabet = '\0';
	bst = new WordBST;
	pLeft = '\0';
	pRight = '\0';
	pNext = 0;
	visit = 0;
}


AlphabetNode::~AlphabetNode()
{
}

AlphabetNode * AlphabetNode::GetNext() {
	return pNext;
}
void AlphabetNode::SetNext(AlphabetNode * node) {
	pNext = node;
}
char AlphabetNode::GetAlphabet()
{
	return alphabet;
}

WordBST* AlphabetNode::GetBST()
{
	return bst;
}

AlphabetNode* AlphabetNode::GetLeft()
{
	return pLeft;
}

AlphabetNode* AlphabetNode::GetRight()
{
	return pRight;
}

WordBST* AlphabetNode::GetWordBST()
{
	return bst;
}

void AlphabetNode::SetAlphabet(char alphabet) // È®ÀÎ
{
	this->alphabet = alphabet;
}

void AlphabetNode::SetLeft(AlphabetNode* node)
{
	pLeft = node;
	return;
}

void AlphabetNode::SetRight(AlphabetNode* node)
{
	pRight = node;
	return;
}
