#ifndef _WORDNODE_H_
#define _WORDNODE_H_
#include <cstring>
#include <utility>
#include <fstream>
#include <iostream>
using namespace std;

#pragma warning(disable:4996) 

class WordNode
{
private:
	std::pair<char*, char*> wordmean;
	//char word[32];
	//char mean[32];
	WordNode* pLeft;	// BST Left Pointer
	WordNode* pRight;	// BST Right Pointer
	WordNode* pNext;	// Queue Next Pointer
	WordNode* pSnext;	// Save sNext Pointer
	WordNode* pNext2;	// Queue2 Next2 Pointer

public:
	WordNode();
	~WordNode();

	char*		GetWord();					// Get Word
	char*		GetMean();					// Get Word Mean
	WordNode*	GetLeft();					// Get BST Left Pointer
	WordNode*	GetRight();					// Get BST Right Pointer
	WordNode*	GetNext();					// Get Queue Next Pointer
	WordNode*	GetSnext();					// Get Save sNext Pointer
	WordNode*   GetNext2();					// Get Queue2 Next2 Pointer

	void		SetWord(char* word);		// Set Word
	void		SetMean(char* mean);		// Set Word Mean
	void		SetLeft(WordNode* node);	// Set BST Left Pointer
	void		SetRight(WordNode* node);	// Set BST Right Pointer
	void		SetNext(WordNode* node);	// Set Queue Next Pointer
	void		SetSnext(WordNode* node);	// Set Save sNext Pointer
	void		SetNext2(WordNode* node);	// Set Queue2 Next2 Pointer

};

#endif
