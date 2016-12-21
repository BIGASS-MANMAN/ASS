#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "Queue.h"
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
	bool		Print(char * order);				// PRINT
	bool		Save();								// SAVE

	WordNode*	Get(WordNode* node, char* word);	//find same node
	WordNode*	GetRoot(){return root;}				//get root

	void		Visit(WordNode* n);					//print node
	void		R_PRE(WordNode* n);					//recursive pre-order
	void		R_IN(WordNode* n);					//recursive in-order
	void		R_POST(WordNode* n);				//recursive post-order
	void		I_PRE();							//iterative pre-order
	void		I_IN();								//iterative  in-order
	void		I_POST();							//iterative post-order
	void		I_LEVEL();							//iterative level-order

	void		Remove(WordNode* n);				//Removing WordBST
};

#endif