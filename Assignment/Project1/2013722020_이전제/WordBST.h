#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"
#include <fstream>
using namespace std;

class WordBST
{
public:
	WordNode * root;	// Word BST Root

public:
	WordBST();
	~WordBST();
	
	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);							// PRINT
	bool		Save();								// SAVE
	bool        IsEmpty();
	void        destruc(WordNode* node);
	void        Pre_Save(WordNode* node);
	WordNode * GetRoot();
	void       SetRoot(WordNode *);
	void R_PRE(WordNode* node);    //member fucntions 
	void R_IN(WordNode* node);
	void R_POST(WordNode* node);
	void I_PRE(WordNode* node);
	void I_IN(WordNode* node);
	void I_POST(WordNode* node);
	void I_LEVEL(WordNode* node);
};


class My_Stack        //my stack
{
private:
	//memeber value and function
	WordNode* pHead;
	WordNode* pUnder;
	WordNode* pTop;

public:
	My_Stack();
	~My_Stack();
	void SetHead(WordNode * node);
	void SetUnder(WordNode * node);
	WordNode * GetUnder();
	WordNode * GetHead();
	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();						// MOVE
	bool        IsEmpty();
	WordNode * Top();
};

class My_Queue     //my queue
{
private:
	WordNode* pHead;
	WordNode* pTail;
	WordNode* pNext;
public:
	My_Queue();
	~My_Queue();
	void SetHead(WordNode * node);
	void SetNext(WordNode * node);
	void SetTail(WordNode * node);
	WordNode * GetNext();
	WordNode * GetHead();
	WordNode*  GetTail();
	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();						// MOVE
	bool        IsEmpty();
	
		
};





# endif