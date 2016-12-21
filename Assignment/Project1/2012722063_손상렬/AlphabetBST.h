#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"
#pragma execution_character_set("utf-8")
#include <string.h>

#define MAX_WORD 100

class AlphabetBST
{
public:
	AlphabetNode * root;
	int WordCnt;

public:
	AlphabetBST();
	~AlphabetBST();

	AlphabetNode *	getRoot();
	void			setRoot(AlphabetNode * node);
	AlphabetNode *	Insert(AlphabetNode * node);
	AlphabetNode *	Search(char alpabet);
	bool			Print(char * order);
	bool			Save();
	AlphabetNode *	findMin(AlphabetNode * root);
	AlphabetNode *	findMax(AlphabetNode * root);
	void			recursivePreorder(AlphabetNode * root);
	void			iterativePreorder(AlphabetNode * root);
	void			recursiveInorder(AlphabetNode * root);
	void			iterativeInorder(AlphabetNode * root);
	void			recursivePostorder(AlphabetNode * root);
	void			iterativePostorder(AlphabetNode * root);
	void			Levelorder(AlphabetNode * root);
	void			releaseTree(AlphabetNode * root);
};

#endif
