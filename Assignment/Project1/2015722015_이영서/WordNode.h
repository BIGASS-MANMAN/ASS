#ifndef _WORDNODE_H_
#define _WORDNODE_H_

#include <utility>
#include <iostream>
using namespace std;

/////////////////WORD NODE////////////////////
class WordNode
{
private:
	std::pair<char *, char *> wordmean;
	WordNode * pLeft;	// BST Left Pointer
	WordNode * pRight;	// BST Right Pointer
	WordNode * pNext;	// Queue&Stack Next Pointer
	WordNode * Parent;	// parent node

public:
	WordNode();
	~WordNode();
	
	char *		GetWord(){return wordmean.first;}			// Get Word
	char *		GetMean(){return wordmean.second;}			// Get Word Mean
	WordNode *	GetLeft(){return pLeft;}					// Get BST Left Pointer
	WordNode *	GetRight(){return pRight;}					// Get BST Right Pointer
	WordNode *	GetNext(){return pNext;}					// Get Queue Next Pointer
	WordNode *  GetParent(){return Parent;}					// Get Parent

	void		SetWord(char * word){wordmean.first=word;}		// Set Word
	void		SetMean(char * mean){wordmean.second=mean;}		// Set Word Mean
	void		SetLeft(WordNode * node){pLeft=node;}			// Set BST Left Pointer
	void		SetRight(WordNode * node){pRight=node;}			// Set BST Right Pointer
	void		SetNext(WordNode * node){pNext=node;}			// Set Queue Next Pointer
	void		SetParent(WordNode * node){Parent=node;}		// Set Parent node
};
/////////////////WORD STACK////////////////////
class Stack
{
private:
	WordNode * pHead;

public:
	Stack(){pHead=NULL;}
	~Stack(){};

	void		Push(WordNode * n);		//push node
	WordNode *	Pop();					//pop node
		
	WordNode* GetHead(){return pHead;}	//get pHead in Stack
};

#endif
