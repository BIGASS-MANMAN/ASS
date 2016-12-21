#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"
#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public:
	AlphabetNode * root;

public:
	AlphabetBST();
	~AlphabetBST();

	void Insert(AlphabetNode * node);	// INSERT
	bool Print(char * order);						// PRINT

	/* Recursive */
	void Inorder(AlphabetNode*pCur, char*order);
	void Preorder(AlphabetNode*pCur, char*order);
	void Postorder(AlphabetNode*pCur, char*order);
	/* None Recursive */
	void NONR_Preorder(char*order);
	void NONR_Postorder(char*order);
	void NONR_Inorder(char*order);

	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE

	void Preorder_Save(AlphabetNode * t); // Recursive function use to Save.
};

#endif
