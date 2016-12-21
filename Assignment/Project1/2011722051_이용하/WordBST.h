#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"
#include <utility>

class WordBST
{
public:
	WordNode * root;	// Word BST Root

public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);							// PRINT
	bool		Save();								// SAVE
	void		R_IN(char * order);					// Recursive inorder
	void		R_IN(WordNode * node, char * order); // Recursive inorder
	void		R_PRE(char * order);				// Recursive pre-order
	void		R_PRE(WordNode * node, char * order); // Recursive pre-order
	void		R_POST(char * order);				// Recursive post-order
	void		R_POST(WordNode * node, char * order); // Recursive post-order
	void		I_PRE(char * order);				// Iterative pre-order
	void		I_IN(char * order);					// Iterative inorder
	void		I_POST(char * order);				// Iterative post-order
	void		I_LEVEL(char * order);				// Iterative level-order
	void		Visit(WordNode * node, char * order); // visit
	int			GetWordCount();						// Word count
	void		SetZero_IN();						// using I_POST
};

#endif
