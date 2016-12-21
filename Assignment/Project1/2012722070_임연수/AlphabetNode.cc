#include "AlphabetNode.h"
/************************************************************/
/*This is AlphabetNode.cc that structred BST				*/
/*Also, It is declaration about AlphabetNode Class			*/
/************************************************************/
AlphabetNode::AlphabetNode()
{
/* Contructor sets alphabet, pLeft and pRight to NULL.		*/
/* The bst was allocated WordBST							*/
	alphabet = '\0';
	bst = new WordBST;
	pLeft = '\0';
	pRight = '\0';
}

AlphabetNode::~AlphabetNode()
{
/* Destructor free all dynamic memory used in this			*/
/* I implemented this recursively using post-order			*/
	if(!this) return;

	this->pLeft->~AlphabetNode();
	this->pRight->~AlphabetNode();

	delete bst;
}

char AlphabetNode::GetAlphabet() {
/* it returns character about alphabet						*/
	return alphabet;
}

WordBST *AlphabetNode::GetBST() {
/* it returns WordBST ranged in AlphabetNode				*/
	return bst;
}

AlphabetNode *AlphabetNode::GetLeft() {
/* it returns pLeft											*/
	return pLeft;
}

AlphabetNode *AlphabetNode::GetRight() {
/* it returns pRight											*/
	return pRight;
}

void AlphabetNode::SetAlphabet(char alphabet) {
/* it returns pLeft												*/
	this->alphabet = alphabet;
}

void AlphabetNode::SetLeft(AlphabetNode * node) {
/* it assigns node to pLeft										*/
	pLeft = node;
}

void AlphabetNode::SetRight(AlphabetNode * node) {
/* it assigns node to pRight									*/
	pRight = node;
}