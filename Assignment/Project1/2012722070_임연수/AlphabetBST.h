#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_
/************************************************************/
/*This is AlphabetBST.h that structred BST					*/
/*Also, It is definition about AlphabetBST Class			*/
/************************************************************/
#include "AlphabetNode.h"

#define MAX_WORD	100	// Maximum MEMORIZING Words
#define LETTER		26
/*initial string about each ordering						*/
#define PRESTR		"phdbacfegljiknmoxtrqsvuwzy" 
#define	INSTR		"abcdefghijklmnopqrstuvwxyz"
#define POSTSTR		"acbegfdikjmonlhqsruwvtyzxp"
#define LEVSTR		"phxdltzbfjnrvyacegikmoqsuw"

class AlphabetBST
{
public:
	/*MEMBER VARIABLE*/
	AlphabetNode * root;
	int WordCnt;
	
	/*MEMBER FUNCTION driven PRINT()*/
	bool R_PRE(AlphabetNode *node, char *order);
	bool R_IN(AlphabetNode *node, char *order);
	bool R_POST(AlphabetNode *node, char *order);
	bool I_PRE(char *order, bool save=false);
	bool I_IN(char *order);
	bool I_POST(char *order);
	bool I_LEVEL(char *order);

public:
	/*CONSTRUCTOR, DESTRUCTOR*/
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);	// run
	bool			Print(char *order);				// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();	
	/*CHECK SIZE*/
	bool			isEmpty();						// SAVE
	bool			isFull();
	/*CHECK WORDCNT*/
	void			incCnt();
	void			decCnt();
	int				getCnt();
};

#endif
