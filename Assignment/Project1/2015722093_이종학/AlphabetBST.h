#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public:
	AlphabetNode * root;
	int WordCnt;
	AlphabetNode * pHead;

public:
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);	// run
	bool			Print(char * order);						// PRINT
	AlphabetNode *	Search(char alphabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
	void		Preorder(AlphabetNode * node);
	void		Inorder(AlphabetNode * node);
	void		Postorder(AlphabetNode * node);
	void		StackPush(AlphabetNode * node);
	AlphabetNode *	StackPop();
	void		QueuePush(AlphabetNode * node);
	AlphabetNode *	QueuePop();

};

#endif
