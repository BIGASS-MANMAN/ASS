#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"
#include <cstring>

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

	AlphabetNode*	Get(AlphabetNode* node,char alpa);	//find same node

	void R_PRE(AlphabetNode* n,char * order);		//recursive pre-order
	void R_IN(AlphabetNode* n,char * order);		//recursive in-order
	void R_POST(AlphabetNode* n,char * order);		//recursive post-order
	void I_PRE(char * order);						//iterative pre-order
	void I_IN(char * order);						//iterative  in-order
	void I_POST(char * order);						//iterative post-order
	void I_LEVEL(char * order);						//iterative level-order
	
	void SetWordCnt()					//set WorcCNT
	{
		if(WordCnt!=MAX_WORD)
			WordCnt++;
	}					
	int	GetWordCnt(){return WordCnt;}	//get WordCnt
	
	void Remove(AlphabetNode* n);		//Removing AlphabetBST
};

#endif
