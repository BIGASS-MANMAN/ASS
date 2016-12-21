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

	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);							// PRINT
	bool		Save();								// SAVE

	void		visit(WordNode* node);			// Print WordNode data
	void		R_Preorder(WordNode* node);		// Recursive Preorder
	void		R_Inorder(WordNode* node);		// Recursive Inorder
	void		R_Postorder(WordNode* node);	// Recursive Postorder
	void		I_Preorder();					// Iterative Preorder
	void		I_Inorder();					// Iterative Inorder
	void		I_Postorder();					// Iterative Postorder
	void		I_Levelorder();					// Iterative Levelorder
	void		Deallocate(WordNode* node);		// Deallocate WordNode in class
};

#endif
