#include "AlphabetNode.h"



AlphabetNode::AlphabetNode()//Initialization of variables
{
	alphabet = '\0';
	bst = new WordBST;
	pLeft = '\0';
	pRight = '\0';
}


AlphabetNode::~AlphabetNode()//Frees memory
{
	delete bst;
}

char AlphabetNode::GetAlphabet()//Return alphabet
{
	return this->alphabet;
}
WordBST* AlphabetNode::GetBST()//Return WordBST
{
	return this->bst;
}
AlphabetNode* AlphabetNode::GetLeft()//Return left node;
{
	return this->pLeft;
}
AlphabetNode* AlphabetNode::GetRight()//Return right node
{
	return this->pRight;
}
void AlphabetNode::SetAlphabet(char alphabet)//Change alphabet
{
	this->alphabet=alphabet;
}
void AlphabetNode::SetLeft(AlphabetNode* node)//Change left node
{
	this->pLeft=node;
}
void AlphabetNode::SetRight(AlphabetNode* node)//Change right node
{
	this->pRight=node;
}
