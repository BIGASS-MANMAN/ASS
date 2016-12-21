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
	void			R_PRE(AlphabetNode * cur, char * order);
	void			I_PRE(char * order);
	void			R_IN(AlphabetNode * cur, char * order);
	void			I_IN(char * order);
	void			R_POST(AlphabetNode * cur, char * order);
	void			I_POST(char * order);
	void			I_LEVEL(char * order);
	bool			Save();										// SAVE
	int				Alpha_bst_count();

};

#endif
