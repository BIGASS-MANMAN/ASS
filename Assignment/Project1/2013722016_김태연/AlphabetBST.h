#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100   // Maximum MEMORIZING Words

class AlphabetBST
{
private:
	AlphabetNode * root;
	int WordCnt;
	char* arr;

public:
	AlphabetBST();
	~AlphabetBST();

	void         Insert(AlphabetNode * node);   // run
	bool         Print(char * order);                  // PRINT
	AlphabetNode *   Search(char alpabet);         // LOAD, MOVE, TEST, SEARCH, UPDATE
	bool         Save();                     // SAVE

	void         Visit(AlphabetNode*currentNode);
	void         Preorder(AlphabetNode* currentNode);
	void         Inorder(AlphabetNode* currentNode);
	void         Postorder(AlphabetNode* currentNode);
	void		 NonrecPreorder(AlphabetNode* currentNode);
	void		 NonrecPostorder(AlphabetNode* currentNode);
	void		 LevelOrder(AlphabetNode* currentNode);
	void		 NonrecInorder(AlphabetNode* currentNode);
	int          GetWordCnt();
	void         GetWordCntPlus();
};

#endif
