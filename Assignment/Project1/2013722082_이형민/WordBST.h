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
	bool		Inorder(WordNode*subroot);//print order
	bool		Preorder(WordNode*subroot);//print order
	bool		Postorder(WordNode*subroot);//print order
	bool		Nonrec_Inorder();//print order
	bool		Nonrec_Postorder();//print order
	bool		Nonrec_Preorder();//print order
	bool		Level_order();//print order

	bool		preorder_save(WordNode * currentNode);//for saving order
	void		postorder_delete(WordNode * currentNode);//for destructing order
	void		Insert(WordNode * node);			// insert
	WordNode *	Delete(char * word);				// delete
	WordNode *	Search(char * word);	// search
	char*		GetBigWord(char * word);//change small word to big word
	bool		Print(char * order);							// PRINT
	bool		Save();								// SAVE
};

#endif
