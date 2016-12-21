#ifndef _ALPHABETNODE_H_
#define _ALPHABETNODE_H_

#include "WordBST.h"
class WordBST;

class AlphabetNode
{
private:
	char alphabet;              // store the alphabet
	WordBST* bst;               // declare the word bst that is connected with alphabet node
	AlphabetNode* pLeft;		// BST Left Pointer
	AlphabetNode* pRight;		// BST Right Pointer
	AlphabetNode* pNext;        // Alphabet noder next pointer using in stack

public:
	AlphabetNode();
	~AlphabetNode();

	char			GetAlphabet();					// Get Alphabet
	WordBST*		GetBST();						// Get Word BST
	AlphabetNode*	GetLeft();						// Get BST Left Pointer
	AlphabetNode*	GetRight();						// Get BST Right Pointer
	AlphabetNode*	GetNext();						// Get alphabet node next Pointer using in queue and stack

	void			SetAlphabet(char alphabet);		// Set Alphabet
	void			SetLeft(AlphabetNode * node);	// Set BST Left Pointer
	void			SetRight(AlphabetNode * node);	// Set BST Right Pointer
	void			SetNext(AlphabetNode * node);	// Set alphabet node next Pointer using in queue and stack
};

#endif
