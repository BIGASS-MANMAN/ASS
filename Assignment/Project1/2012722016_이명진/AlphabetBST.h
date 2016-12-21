#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"
#include "Queue.h"
class Queue;
class AlphabetNode;
class AlphabetBST
{
public:
	AlphabetNode * root;
	int	WordCnt;
public:
	AlphabetBST();
	~AlphabetBST();

	AlphabetNode*	Get_Root() { return root; }	// get root
	void			Destroy(AlphabetNode* node);	// deallocate memory
	void			Insert(AlphabetNode * node);	// run
	bool			Print(char * order);						// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
	
	//recursive preorder
	void preorder();
	void preorder(AlphabetNode *currentNode);
	//nonrecursive preorder
	void Nonrecpreorder();
	//recursive inorder
	void Inorder();
	void Inorder(AlphabetNode *currentNode);
	//nonrecursive inorder
	void NonrecInorder();
	//recursive postorder
	void postorder();
	void postorder(AlphabetNode *currentNode);
	//nonrecursive postorder
	void Nonrecpostorder();
	//nonrecursive levelorder
	void Levelorder();
};

#endif
