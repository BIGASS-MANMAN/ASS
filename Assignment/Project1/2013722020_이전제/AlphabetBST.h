#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public://declare public pointer of AlphabetBST
	AlphabetNode * root;
	int WordCnt;

public: //the member function of AlphabetBST
	AlphabetBST();
	~AlphabetBST();
	bool            IsEmpty();
	void			Insert(AlphabetNode * node);	// run
	bool			Print(char * order);						// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
	void            Making(char alpha);
	int             GetWordCnt();
	AlphabetNode * GetRoot();
	void           WordCount(int check);
	void           destruc(AlphabetNode* node);
	void            Pre_save(AlphabetNode* node);
	bool R_PRE(AlphabetNode* node);
	bool R_IN(AlphabetNode* node);  //print functions
	bool R_POST(AlphabetNode* node);
	bool I_POST(AlphabetNode* node);
	bool I_IN(AlphabetNode* node);
	bool I_PRE(AlphabetNode* node);
	bool I_LEVEL(AlphabetNode* node);
};


#endif
