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

	void			DestroyAlphaTree(AlphabetNode* node);

	void			Insert(AlphabetNode * node);	// run
	void			Insert(char alphabet);
	void			Insert(AlphabetNode* root, AlphabetNode* node);

	bool			Print(const char * order);			// PRINT
	void			Print_In_re(AlphabetNode* node, const char* order);
	void			Print_In_it(AlphabetNode* node, const char* order);
	void			Print_po_re(AlphabetNode* node, const char* order);
	void			Print_po_it(AlphabetNode* node, const char* order);
	void			Print_pr_re(AlphabetNode* node, const char* order);
	void			Print_pr_it(AlphabetNode* node, const char* order);
	
	int				Height(AlphabetNode* node);
	void			Print_Level(const char* order);
	void			Print_Given_Level(AlphabetNode* node, int level, const char* order);

	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	AlphabetNode *	Search(AlphabetNode* node, char alphabet);
	bool			Save();							// SAVE
	void			Save(AlphabetNode* node);
};

class aStack
{
private:
	AlphabetNode* pHead;
public:
	aStack(void);
	~aStack(void);
	void		Push(AlphabetNode* node);
	AlphabetNode*	Pop();
	AlphabetNode*	GetHead();
};

#endif
