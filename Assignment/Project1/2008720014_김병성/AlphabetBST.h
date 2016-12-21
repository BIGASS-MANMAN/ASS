#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public:
	AlphabetNode * root;
	int WordCnt;

public:
	AlphabetBST();
	~AlphabetBST();

	void Rec_preorder_Print();
	void Rec_preorder_Print(AlphabetNode * currentNode);
	void Iter_preorder_Print();

	void Rec_inorder_Print();
	void Rec_inorder_Print(AlphabetNode * currentNode);
	void Iter_inorder_Print();

	void Rec_postorder_Print();
	void Rec_postorder_Print(AlphabetNode * currentNode);
	void Iter_postorder_Print();

	void Iter_level_Print();

	int				GetWordCnt();
	AlphabetNode *  Getroot();
	void			Insert(AlphabetNode * node);	// run
	bool			Print(char * order);			// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
};

#endif
