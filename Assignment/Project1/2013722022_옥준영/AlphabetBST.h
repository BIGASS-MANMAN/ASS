#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public:
	AlphabetNode * root;
	int WordCnt;		// number of inserted word

public:
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);	// run
	bool			Print(char * order);						// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
	void			alphabet_insert();				// alphabet insert

	int				GetCnt();			// return WordCnt
	void			R_Inorder(AlphabetNode * node, char * order);		// Recursive Inorder
	void			R_Preorder(AlphabetNode * node, char * order);		// Recursive Preorder
	void			R_Postorder(AlphabetNode * node, char * order);		// Recursive Postorder
	void			I_Inorder(char * order);			// Iterative Inorder
	void			I_Preorder(char * order);			// Iterative Preorder
	void			I_Postorder(char * order);			// Iterative Postorder
	void			I_Levelorder(char * order);			// Iterative Levelorder
	void			Deallocate(AlphabetNode* node);		// Deallocate AlphabetNode in class
};

#endif
