#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"
#include "Queue.h"
#include "Stack.h"
#include <string.h>

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
	void		Visit(WordNode*currentNode);
	void		Preorder(WordNode* currentNode);
	void	    Inorder(WordNode* currentNode);
	void		Postorder(WordNode* currentNode);
	void		NonrecInorder(WordNode* currentNode);
	void		LevelOrder(WordNode* currentNode);
	void		NonrecPreorder(WordNode* currentNode);
	void		NonrecPostorder(WordNode* currentNode);
};

#endif
