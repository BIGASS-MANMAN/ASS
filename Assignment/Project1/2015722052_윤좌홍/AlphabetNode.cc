#include "AlphabetNode.h"



AlphabetNode::AlphabetNode()
{
	alphabet = '\0';
	bst = new WordBST;
	pLeft = '\0';
	pRight = '\0';
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
AlphabetNode* AlphabetNode::GetNext()
{
	return pNext;
}
void AlphabetNode::SetAlphabet(char parm_alphabet)
{
	alphabet = parm_alphabet;
}
void AlphabetNode::SetLeft(AlphabetNode *node)
{
	pLeft = node;
}
void AlphabetNode::SetRight(AlphabetNode *node)
{
	pRight = node;
}
void AlphabetNode::SetNext(AlphabetNode *node)
{
	pNext = node;
}

AlphabetNode::~AlphabetNode()	//must Fix!!
{
	if(bst) delete bst;
}
