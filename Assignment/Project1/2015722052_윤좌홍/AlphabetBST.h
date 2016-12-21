#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "A_Stack.h"
#include "AlphabetNode.h"
#include <cstring>
#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
public:
	AlphabetNode * root;
	int WordCnt;
	char m_order[32];	//for easily input print order accessing, using member variable 
	ofstream fout_log;
public:
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);	// run
	void			Insert(WordNode * node);		//Node inserting only this function execute
	bool			Print(char * order);						// PRINT
	void			Print_Pre(AlphabetNode * node);
	void			Print_In(AlphabetNode * node);
	void			Print_Post(AlphabetNode * node); //recursive traversal function
	void			Iter_Pre(AlphabetNode * node); //Iterator traversal function
	void 			Iter_In(AlphabetNode * node);
	void			Iter_Post(AlphabetNode * node);
	void			Iter_Level(AlphabetNode * node);
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
	void			Save_Pre(AlphabetNode * node);	//pre-ordering to save traversal
	void			Delete_BST(AlphabetNode * node);//delete BST function
	int				GetWordCnt();
	void			SetWordCnt(int count);
};

#endif
