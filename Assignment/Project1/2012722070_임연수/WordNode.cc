#include "WordNode.h"
#include <cstring>
/************************************************************/
/*This is WordNode.cc that structred BST					*/
/*Also, It is declaration about WordNode Class				*/
/************************************************************/
WordNode::WordNode()
{
/*Constructor assigns all member variable to NULL*/
	wordmean.first='\0';
	wordmean.second='\0';
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}

WordNode::~WordNode() {
/*DESTRUCTOR deletes Word-Pair.							*/
/*Also, It's logic seems like recursively POST-order	*/ 
	if(!this) return;

	this->GetLeft()->~WordNode();
	this->GetRight()->~WordNode();

	delete wordmean.first;
	delete wordmean.second;
}

char* WordNode::GetWord() {
/*it returns word*/
	return wordmean.first;
}

char* WordNode::GetMean() {
/*it returns mean*/
	return wordmean.second;
}

WordNode* WordNode::GetLeft() {
/*it returns pLeft*/
	return pLeft;
}

WordNode* WordNode::GetRight() {
/*it returns pRight*/
	return pRight;
}

WordNode* WordNode::GetNext() {
/*it returns pNext*/
	return pNext;
}

void WordNode::SetVoca(char *word, char *mean) {
/*it calls SetWord, SetMean with parameter : word, mean*/
	SetWord(word);
	SetMean(mean);
}

void WordNode::SetWord(char * word) {
/*it set word to wordmean.first after dynamic-allocating	*/
	if(!word) return;
	wordmean.first = new char[strlen(word)+1];
	strcpy(wordmean.first,word);
}

void WordNode::SetMean(char * mean) {
/*it set word to wordmean.second after dynamic-allocating			*/
/*also, care the UPDATE case, it transform mean. so, do re-allocate */

	if(!mean) return;
	if(wordmean.second) delete wordmean.second; // in Case UPDATE
	wordmean.second = new char[strlen(mean)+1];
	strcpy(wordmean.second,mean);
}

void WordNode::SetLeft(WordNode * node) {
/*it set node to pLeft*/
	pLeft = node;
}

void WordNode::SetRight(WordNode * node) {
/*it set node to pRight*/
	pRight = node;
}

void WordNode::SetNext(WordNode * node) {
/*it set node to pNext*/
	pNext = node;
}