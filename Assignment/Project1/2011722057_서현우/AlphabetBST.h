#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"
#include <cstring>
#include <fstream>
#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public:
	AlphabetNode * root;//Variable root declarations
	int WordCnt;//Variable WordCnt declarations (Use count wordnode in alphabetBST

public:
	AlphabetBST();//Constructor
	~AlphabetBST();//Destructor

	void			Insert(AlphabetNode * node);	//Function Push declarations (Use run)
	bool			Print(char * order);			//Function Push declarations (Use PRINT)
	AlphabetNode *	Search(char alpabet);			//Function Push declarations (Use  LOAD, MOVE, TEST, SEARCH, UPDATE)
	bool			Save();							//Function Push declarations (Use SAVE)
	void			R_PRE(AlphabetNode* node);//Function R_PRE declarations (Recursive pre order)
	void			I_PRE();//Function I_PRE declarations (Iterative pre order)
	void			R_IN(AlphabetNode* node);//Function R_IN declarations (Recursive in order)
	void			I_IN();//Function I_IN declarations (Iterative in order)
	void			R_POST(AlphabetNode* node);//Function R_POST declarations (Recursive post order)
	void			I_POST();//Function I_POST declarations (Iterative post order)
	void			I_LEVEL();//Function I_LEVEL declarations (Iterative level order)
	AlphabetNode*	R_Search(AlphabetNode* node, char alphabet);//Function R_Search declarations (Recursive Search)
};

#endif
