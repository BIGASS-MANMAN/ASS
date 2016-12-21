#include "WordNode.h"



WordNode::WordNode()
{
	pLeft = 0;
	pRight = 0;
	pNext = 0;
	isDel = false;

	wordmean.first = new char[32];
	wordmean.second = new char[32];

	memset(wordmean.first, 0, sizeof(wordmean.first));
	memset(wordmean.second, 0, sizeof(wordmean.second));
}
char* WordNode::GetWord(){
	return word;
}
char* WordNode::GetMean(){
	return mean;
}
WordNode* WordNode::GetLeft(){
	return pLeft;
}
WordNode* WordNode::GetRight(){
	return pRight;
}
WordNode* WordNode::GetNext(){
	return pNext;
}
void WordNode::SetWord(char* a_word){
	isDel = true;
	strncpy(wordmean.first, a_word, sizeof(char) * 32);
	strncpy(word, a_word, sizeof(char) * 32);
	strcpy(word, a_word);
}
void WordNode::SetMean(char* a_mean){
	strncpy(wordmean.second, a_mean, sizeof(char) * 32);
	strncpy(mean, a_mean, sizeof(char) * 32);
	strcpy(mean, a_mean);
}
void WordNode::SetLeft(WordNode* a_node){
	pLeft = a_node;
}
void WordNode::SetRight(WordNode* a_node){
	pRight = a_node;
}
void WordNode::SetNext(WordNode* a_node){
	pNext = a_node;
}
WordNode::~WordNode()
{
	isDel = false;
	if(wordmean.first) delete wordmean.first;
	if(wordmean.second) delete wordmean.second;
}
