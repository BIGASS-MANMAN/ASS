#ifndef _ALPHABETNODE_H_
#define _ALPHABETNODE_H_

#include "WordBST.h"

class AlphabetNode
{
private:
	char alphabet;
	WordBST * bst;
	AlphabetNode * pLeft;		// BST Left Pointer
	AlphabetNode * pRight;		// BST Right Pointer
	AlphabetNode * pNext;		// aStack Next Pinter

public:
	AlphabetNode();
	~AlphabetNode();

	char			GetAlphabet();					// Get Alphabet
	WordBST	*		GetBST();						// Get Word BST
	AlphabetNode *	GetLeft();						// Get BST Left Pointer
	AlphabetNode *	GetRight();						// Get BST Right Pointer
	AlphabetNode *	GetNext();						// Get aStack Next Pointer

	void			SetAlphabet(char alphabet);		// Set Alphabet
	void			SetLeft(AlphabetNode * node);	// Set BST Left Pointer
	void			SetRight(AlphabetNode * node);	// Set BST Right Pointer
	void			SetNext(AlphabetNode * node);	// Set aStack Next Pointer
};

#endif
