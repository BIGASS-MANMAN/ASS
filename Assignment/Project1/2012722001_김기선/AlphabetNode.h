#ifndef _ALPHABETNODE_H_		//prevent header crash
#define _ALPHABETNODE_H_

#include "WordBST.h"	//include header

class AlphabetNode		//declare class node
{
public:	//private member//
	char alphabet;	//data 1
	WordBST * bst;	//data 2 (bst)
	AlphabetNode * pLeft;		// BST Left Pointer
	AlphabetNode * pRight;		// BST Right Pointer
	AlphabetNode * pNext;		// for using stack, queue

public:		//public member//
	AlphabetNode(); 	//constructor
	~AlphabetNode();    //destructor

	char			GetAlphabet();					// Get Alphabet
	WordBST	*		GetBST();						// Get Word BST
	AlphabetNode *	GetLeft();						// Get BST Left Pointer
	AlphabetNode *	GetRight();						// Get BST Right Pointer
	AlphabetNode *	GetNext();						// Get Next Pointer

	void			SetAlphabet(char alphabet);		// Set Alphabet
	void			SetLeft(AlphabetNode * node);	// Set BST Left Pointer
	void			SetRight(AlphabetNode * node);	// Set BST Right Pointer
	void			SetNext(AlphabetNode * node);	// Set Next Pointer
};

#endif

