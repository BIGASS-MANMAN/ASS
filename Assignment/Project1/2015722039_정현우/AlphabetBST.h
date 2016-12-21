#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public:
	AlphabetNode * root;//Alphabet Bst's root
	int WordCnt;//Number of Word Node
public:
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);	// run
	bool			Print(char * order);			// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE

	void R_PRE(AlphabetNode * node);	//Recursive preorder
	void I_PRE();						//Interative preorder
	void R_IN(AlphabetNode * node);		//Recursive IN order
	void I_IN();						//interative IN order
	void R_POST(AlphabetNode *node);	//Recursive Post order
	void I_POST();						//Interative post order
	void I_LEVEL();						//Interative LEVEL order
};

#endif
