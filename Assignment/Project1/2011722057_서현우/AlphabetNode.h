#ifndef _ALPHABETNODE_H_
#define _ALPHABETNODE_H_

#include "WordBST.h"
#include <cstring>
class AlphabetNode
{
public:	
	char alphabet;				//Variable alphabet declarations
	WordBST * bst;				//Variable bst declarations (go to WordBST)
	AlphabetNode * pLeft;		// BST Left Pointer
	AlphabetNode * pRight;		// BST Right Pointer

public:
	AlphabetNode();//Constructor
	~AlphabetNode();//Destructor

	char			GetAlphabet();					// Get Alphabet
	WordBST	*		GetBST();						// Get Word BST
	AlphabetNode *	GetLeft();						// Get BST Left Pointer
	AlphabetNode *	GetRight();						// Get BST Right Pointer

	void			SetAlphabet(char alphabet);		// Set Alphabet
	void			SetLeft(AlphabetNode * node);	// Set BST Left Pointer
	void			SetRight(AlphabetNode * node);	// Set BST Right Pointer
};

#endif
