
#ifndef _WORDBST_H_
#define _WORDBST_H_
#include "WordNode.h"

#include<fstream>
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
	bool		IsEmpty();
	void		Print(WordNode* p);
	void		R_Preorder(WordNode* p);						// Recursive Pre-order
	void		R_Inorder(WordNode* p);						// Recursive In-order
	void		R_Postorder(WordNode* p);						// Recursive Post-order
	void		I_Preorder();						// Iterative Pre-order
	void		I_Inorder();						// Iterative In-order
	void		I_Postorder();						// Iterative Post-order
	void		I_Levelorder();						// Iterative Lever-order
	void		R_Preorder_save(WordNode* p);       // Recursive Prev-order
	void		save_node(WordNode* p);
	void		Dellocate(WordNode* p);
	void		SetVisitZero(WordNode* p);
};

#endif
