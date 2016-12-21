#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public:
	AlphabetNode * root;
	int WordCnt;

public:
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);	// run
	bool			Print(char * order);						// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE

	void			Visit(AlphabetNode * Node, char * order); // visit
	void			R_PRE(char * order);			// Recursive pre-order
	void			R_PRE(AlphabetNode * Node, char * order); // Recursive pre-order
	void			I_PRE(char * order); // Iterative pre-order
	void			R_IN(char * order);				// Reucursive inorder
	void			R_IN(AlphabetNode * node, char * order); // Recursive inorder
	void			I_IN(char * order); // Iterative inorder
	void			R_POST(char * order);			// Recursive post-order
	void			R_POST(AlphabetNode * Node, char * order); // Recursive post-order
	void			I_POST(char * order); // Iterative post-order
	void			I_LEVEL(char * order); // Iterative level-order
	int				NULL_BST(); // bst root check
	void			SetWordCount(); // word count
	void			SetZero_IN(); // using Iterative post-order
};

#endif
