#include "AlphabetNode.h"



AlphabetNode::AlphabetNode() // AlphabetNode constructor
{
	alphabet = '\0';
	bst = new WordBST;
	pLeft = '\0';
	pRight = '\0';
        sample = new WordNode();
}


AlphabetNode::~AlphabetNode() // AlphabetNode destructor
{
	delete bst;
}

void AlphabetNode::Setsample(char* a) // Setsample Function
{
	this->sample->SetWord(a);
}

WordNode* AlphabetNode::Getsample() // Getsample Function
{
	return sample;
}

char AlphabetNode::GetAlphabet() {               // Get Alphabet
	return alphabet;
}
WordBST   * AlphabetNode::GetBST() {                  // Get Word BST
	return bst;
}
AlphabetNode *AlphabetNode::GetLeft() {                  // Get BST Left Pointer
	return pLeft;
}
AlphabetNode *AlphabetNode::GetRight() {                  // Get BST Right Pointer
	return pRight;
}

void AlphabetNode::SetAlphabet(char alphabet) {      // Set Alphabet
	this->alphabet = alphabet;
}
void AlphabetNode::SetLeft(AlphabetNode * node) {   // Set BST Left Pointer
	this->pLeft = node;
}
void AlphabetNode::SetRight(AlphabetNode * node) {   // Set BST Right Pointer
	this->pRight = node;
}
