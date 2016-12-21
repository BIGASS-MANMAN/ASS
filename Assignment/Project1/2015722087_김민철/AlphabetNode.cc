#include "AlphabetNode.h"

AlphabetNode::AlphabetNode()
{
	alphabet = '\0';
	bst = new WordBST; // dynamic allocation WordBST
	pLeft = '\0';
	pRight = '\0';
}

AlphabetNode::~AlphabetNode()
{
	delete bst;
}
char AlphabetNode::GetAlphabet() {
	return alphabet;
}

WordBST*AlphabetNode::GetBST() {
	return bst;
}
AlphabetNode*AlphabetNode::GetLeft() {
	return pLeft;
}
AlphabetNode*AlphabetNode::GetRight() {
	return pRight;
}
void AlphabetNode::SetAlphabet(char alphabet) {
	this->alphabet = alphabet;
}
void AlphabetNode::SetLeft(AlphabetNode*node) {
	pLeft = node;
}
void AlphabetNode::SetRight(AlphabetNode*node) {
	pRight = node;
}

