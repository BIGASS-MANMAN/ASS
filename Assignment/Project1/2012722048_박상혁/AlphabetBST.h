#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public:
	AlphabetNode * root;		// BST's root
	int WordCnt;			// Number of words

public:
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);		// run
	bool			Print(char * order);			// PRINT
	AlphabetNode *		Search(char alphabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();					// SAVE

	void			R_PreOrder(AlphabetNode * node, char * order);		// Reculsive PreOrder traversal
	void			R_InOrder(AlphabetNode * node, char * order);		// Reculsive InOrder traversal
	void			R_PostOrder(AlphabetNode * node, char * order);		// Reculsive PostOrder traversal
	void			Save_InOrder(AlphabetNode * node);			// Save using Inorder traversal
};


class AlphabetStack
{
public:
	AlphabetNode * pHead;		// Head pointer

public:
	AlphabetStack();
	~AlphabetStack();

	void		Push(AlphabetNode * node);	// Insert node
	void		Pop();				// Cut the node link
	AlphabetNode *	Top();				// Return end node
};


class AlphabetQueue
{
public:
	AlphabetNode * pHead;		// Head pointer

public:
	AlphabetQueue();
	~AlphabetQueue();

	void		Push(AlphabetNode * node);	// LOAD, ADD
	AlphabetNode *	Pop();				// MOVE
};

#endif
