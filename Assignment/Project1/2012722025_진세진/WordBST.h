#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"

class WordBST
{
public:
	WordNode * root;	// Word BST Root

public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);			// LOAD, MOVE
	void		Insert(const char* word, const char* mean);
	void		Insert(WordNode* root, WordNode* node);

	WordNode *	Delete(const char * word);				// TEST
	WordNode *	Delete(WordNode* node, const char* word);
	WordNode *	Delete(WordNode* parent, WordNode* child, const char* word);

	WordNode *	Search(const char * word);				// ADD, TEST, SEARCH, UPDATE
	WordNode *	Search(WordNode* node, const char* word);

	bool		Print(const char * order);				// PRINT
	void		Print_In_re(WordNode* node);
	void		Print_In_it(WordNode* node);
	void		Print_po_re(WordNode* node);
	void		Print_po_it(WordNode* node);
	void		Print_pr_re(WordNode* node);
	void		Print_pr_it(WordNode* node);

	int			Height(WordNode* node);
	void		Print_Level();
	void		Print_Given_Level(WordNode* node, int level);

	bool		Save();								// SAVE

	void		DestroyTree(WordNode* node);
};

/*stack for iterative traversal*/
class mStack
{
private:
	WordNode* pHead;
public:
	mStack(void);
	~mStack(void);
	void		Push(WordNode* node);
	WordNode*	Pop();
	WordNode*	GetHead();
};

#endif
