#ifndef _ALPHABETNODE_H_
#define _ALPHABETNODE_H_
/************************************************************/
/*This is AlphabetNode.h that structred BST					*/
/*Also, It is definition about AlphabetNode Class			*/
/************************************************************/
#include "WordBST.h"

class AlphabetNode
{
private:
	/*MEMBER VARIABLE*/
	char alphabet;
	WordBST * bst;
	AlphabetNode * pLeft;		// BST Left Pointer
	AlphabetNode * pRight;		// BST Right Pointer

public:
	/*CONSTRUCTOR, DESTRUCTOR*/
	AlphabetNode();
	~AlphabetNode();

	/*GET METHOD */
	char			GetAlphabet();					// Get Alphabet
	WordBST	*		GetBST();						// Get Word BST
	AlphabetNode *	GetLeft();						// Get BST Left Pointer
	AlphabetNode *	GetRight();						// Get BST Right Pointer

	/*SET METHOD */
	void			SetAlphabet(char alphabet);		// Set Alphabet
	void			SetLeft(AlphabetNode * node);	// Set BST Left Pointer
	void			SetRight(AlphabetNode * node);	// Set BST Right Pointer
};

#endif
