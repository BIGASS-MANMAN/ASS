#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "Queue.h"
#include "WordNode.h"
class Queue;
class WordNode;
class WordBST
{
public:
	WordNode * root;	// Word BST Root
	
public:
	WordBST();
	~WordBST();

	WordNode*	Get_Root();
	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);							// PRINT
	bool		Save();								// SAVE
	void		Destroy(WordNode* node);

	void preorder();
	void preorder(WordNode *currentNode);
	void Nonrecpreorder();
	void Inorder();
	void Inorder(WordNode *currentNode);
	void NonrecInorder();
	void postorder();
	void postorder(WordNode *currentNode);
	void Nonrecpostorder();
	void Levelorder();
	void Visit(WordNode *currentNode);
};

#endif
