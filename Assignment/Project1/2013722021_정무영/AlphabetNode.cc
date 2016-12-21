#include "AlphabetNode.h"



AlphabetNode::AlphabetNode()
{
	alphabet = '\0';
	bst = new WordBST;
	pLeft = '\0';
	pRight = '\0';
	wordCnt = 0;
}


AlphabetNode::~AlphabetNode()
{
	delete bst;
}

char AlphabetNode:: GetAlphabet() { 
	return alphabet;
}// Get Alphabet
WordBST	* AlphabetNode::GetBST() {
	return bst;
}						// Get Word BST
AlphabetNode * AlphabetNode::GetLeft() {
	return pLeft;
}						// Get BST Left Pointer
AlphabetNode * AlphabetNode::GetRight() {
	return pRight;
}						// Get BST Right Pointer
void AlphabetNode::SetAlphabet(char alphabet) {
	this->alphabet = alphabet;
}		// Set Alphabet
void AlphabetNode::SetLeft(AlphabetNode * node) {
	pLeft = node;
}	// Set BST Left Pointer
void AlphabetNode::SetRight(AlphabetNode * node) {
	pRight = node;
}	// Set BST Right Pointer