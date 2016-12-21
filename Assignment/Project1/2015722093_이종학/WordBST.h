#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "Queue.h"

class WordBST
{
public:
	WordNode * root;	// Word BST Root
	WordNode * pHead;

public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);							// PRINT
	bool		Save();								// SAVE
	void		Preorder(WordNode * node);
	void		Inorder(WordNode * node);
	void		Postorder(WordNode * node);
	void		StackPush(WordNode * node);
	WordNode *	StackPop();
};

#endif
