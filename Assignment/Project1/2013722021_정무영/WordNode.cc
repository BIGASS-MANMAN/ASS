#include "WordNode.h"



WordNode::WordNode()
{
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
	wordmean.first = word;
	wordmean.second = mean;
}


WordNode::~WordNode()
{
}

char * WordNode::GetWord() {
	return wordmean.first;
}			// Get Word
char * WordNode::GetMean() {
	return wordmean.second;
}					// Get Word Mean
WordNode * WordNode::GetLeft() {
	return pLeft;
}					// Get BST Left Pointer
WordNode * WordNode::GetRight() {
	return pRight;
}// Get BST Right Pointer
WordNode * WordNode::GetNext() {
	return pNext;
}					// Get Queue Next Pointer
void WordNode::SetWord(char * word) {
	strcpy(wordmean.first, word);
}		// Set Word
void WordNode::SetMean(char * mean) {
	strcpy(wordmean.second , mean);
}		// Set Word Mean
void WordNode::SetLeft(WordNode * node) {
	pLeft = node;
}	// Set BST Left Pointer
void WordNode::SetRight(WordNode * node) {
	pRight = node;
}	// Set BST Right Pointer
void WordNode::SetNext(WordNode * node) {
	pNext = node;
}	// Set Queue Next Pointer