#include "WordNode.h"
using namespace std;

WordNode::WordNode()
{
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}


WordNode::~WordNode()
{
}

char * WordNode::Change_Case(char * word)
{
	for (int i = 0; i<strlen(word) + 1; i++) {
		if (word[i] >= 65 && word[i] <= 90)
			word[i] += 32;
	}
	return word;
}

char * WordNode::GetWord() {
	return wordmean.first;
}

char * WordNode::GetMean() {
	return wordmean.second;
}

WordNode * WordNode::GetLeft() {
	return pLeft;
}

WordNode * WordNode::GetRight() {
	return pRight;
}	

WordNode * WordNode::GetNext() {
	return pNext;
}

void	WordNode::SetWord(char * word) {
	wordmean.first = new char[32];
	strcpy(wordmean.first, word);
}

void	WordNode::SetMean(char * mean) {
	wordmean.second = new char[32];
	strcpy(wordmean.second, mean);
}

void	WordNode::SetLeft(WordNode * node) {
	pLeft = node;
}

void	WordNode::SetRight(WordNode * node) {
	pRight = node;
}

void	WordNode::SetNext(WordNode * node) {
	pNext = node;
}
