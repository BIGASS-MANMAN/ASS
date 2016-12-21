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

	void			Insert(AlphabetNode * node);	// run
	bool			Print(char * order);			// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
};

#endif
