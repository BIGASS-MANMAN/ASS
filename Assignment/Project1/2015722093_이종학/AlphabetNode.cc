#include "AlphabetNode.h"



AlphabetNode::AlphabetNode() //Constructor
{
	alphabet = '\0'; //initialization
	bst = new WordBST; //allocation
	pLeft = '\0';
	pRight = '\0';
	pNext = NULL;
}


AlphabetNode::~AlphabetNode() //destructor
{
	delete bst;
}

void AlphabetNode::SetAlphabet(char alphabet) //Set alphabet
{
	this->alphabet = alphabet;
}

void AlphabetNode::SetLeft(AlphabetNode *node) //Set BST Left Pointer
{
	pLeft = node;
}

void AlphabetNode::SetRight(AlphabetNode *node) //Set BST Right Pointer
{
	pRight = node;
}

void AlphabetNode::SetNext(AlphabetNode * node) //Set BST Next Pointer
{
	pNext = node;
}

char AlphabetNode::GetAlphabet() //Get Alphabet 
{
	return alphabet;
}

WordBST* AlphabetNode::GetBST() //Get WordBST
{
	return bst;
}

AlphabetNode* AlphabetNode::GetLeft() //Get BST Left Pointer
{
	return pLeft;
}

AlphabetNode* AlphabetNode::GetRight() //Get BST Right Pointer
{
	return pRight;
}

AlphabetNode * AlphabetNode::GetNext() //Get BST Next Pointer
{
	return pNext;
}