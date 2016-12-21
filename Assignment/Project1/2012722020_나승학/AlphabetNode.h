#ifndef _ALPHABETNODE_H_
#define _ALPHABETNODE_H_

#include "WordBST.h"
class WordBst;					// WordBst Class Forward Declaration
class AlphabetNode
{
private:
	char alphabet;				// alphabet Node, type character
	WordBST * bst;				// WordBST Pointer bst			
	AlphabetNode * pLeft;		// BST Left Pointer
	AlphabetNode * pRight;		// BST Right Pointer
	AlphabetNode * pNext;		// BST Next Pointer

public:
	AlphabetNode();				// Constructor
	~AlphabetNode();			// Destructor

	char			GetAlphabet();					// Get Alphabet
	WordBST	*		GetBST();						// Get Word BST
	AlphabetNode *	GetLeft();						// Get BST Left Pointer
	AlphabetNode *	GetRight();						// Get BST Right Pointer
	AlphabetNode *	GetNext();						// Get BST Next Pointer

	void			SetAlphabet(char alphabet);		// Set Alphabet
	void			SetLeft(AlphabetNode * node);	// Set BST Left Pointer
	void			SetRight(AlphabetNode * node);	// Set BST Right Pointer
	void			SetNext(AlphabetNode * node);	// Set BST Next Pointer
	
};

#endif
