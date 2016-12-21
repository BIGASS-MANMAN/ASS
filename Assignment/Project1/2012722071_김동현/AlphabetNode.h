#ifndef _ALPHABETNODE_H_
#define _ALPHABETNODE_H_

#include "WordBST.h"
#include <cstring>

class AlphabetNode
{
private:
	char alphabet;
	WordBST * bst;
	AlphabetNode * pLeft;		// BST Left Pointer
	AlphabetNode * pRight;		// BST Right Pointer

public:
	AlphabetNode();
	~AlphabetNode();

	char			GetAlphabet();
	WordBST	*		GetBST();
	AlphabetNode *	GetLeft();						// Get BST Left Pointer
	AlphabetNode *	GetRight();						// Get BST Right Pointer

	void			SetAlphabet(char alphabet1);		// Set Alphabet
	void			SetLeft(AlphabetNode * node);	// Set BST Left Pointer
	void			SetRight(AlphabetNode * node);	// Set BST Right Pointer
};

#endif
