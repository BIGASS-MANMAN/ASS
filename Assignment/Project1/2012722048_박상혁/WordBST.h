#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"

class WordBST
{
public:
	WordNode * root;	// Word BST Root

public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);		// LOAD, MOVE
	WordNode *	Delete(char * word);			// TEST
	WordNode *	Search(char * word);			// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);			// PRINT
	bool		Save();					// SAVE

	void		R_PreOrder(WordNode * node);		// Reculsive PreOrder traversal
	void		R_InOrder(WordNode * node);		// Reculsive InOrder traversal
	void		R_PostOrder(WordNode * node);		// Reculsive PostOrder traversal
	void		Save_PreOrder(WordNode * node);		// Save using PreOrder traversal
};


class Stack
{
public:
	WordNode * pHead;	// Head pointer

public:
	Stack();
	~Stack();

	void		Push(WordNode * node);		// Insert node
	void		Pop();				// Cut the node link
	WordNode *	Top();				// Return end node
};

#endif
