#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"
#include <ctype.h>
#include <fstream>
#include <iostream>
#include "Queue.h"
#include <queue>


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
	bool			Print(char * order);		// PRINT
	AlphabetNode *	Search(char alpabet);	       // LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
	AlphabetNode * 	ItInorder(char  fword, AlphabetNode * currentnode);
	void			Inorder(AlphabetNode * currentnode);
	void			preorder(AlphabetNode * currentnode);
	void			postorder(AlphabetNode * currentnode);
	void			IterativeInorder(AlphabetNode * currentnode);
	void			Iterativepreorder(AlphabetNode * currentnode);
	void			Iterativepostorder(AlphabetNode * currentnode);
	void			Levelorder(AlphabetNode * currentnode);
	void			Visit(char* n, AlphabetNode * currentnode);




};

#endif
