#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{

public:
	AlphabetNode * root;
	int WordCnt;
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);				// run
	bool			Print(char * order);					// PRINT
	AlphabetNode *		Search(char alphabet);					// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
	void			inSave(AlphabetNode * root);			// for Save
	int				GetWordCnt();
	
	void			SetWordCnt(int word_cnt);	

	void		R_IN(AlphabetNode* root, char * order);	//R_IN
	
	void		R_PRE(AlphabetNode * root, char * order);	//R_PRE
	
	void		R_POST(AlphabetNode * root, char * order);	//R_PRE

	bool		I_IN(char * order);					//I_IN
	bool		I_PRE(char * order);				//I_PRE
	bool		I_POST(char * order);				//I_POST
	bool		I_LEVEL(char * order);				//I_LEVEL
	

	void			Clear(AlphabetNode* root);				// for delete
};
#endif
