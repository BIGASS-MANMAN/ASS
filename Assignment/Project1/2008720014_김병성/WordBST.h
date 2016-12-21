#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"

template <class T>
class Stack
{
private:
	T *stack;
	int top;
	int capacity;
public:
	Stack(int stackCapacity = 50); 
	bool IsEmpty() const;
	T& Top() const;
	void Push(const T& item);
	void Pop();
	~Stack() { delete stack; }
};

class WordBST
{
public:
	WordNode * root;	// Word BST Root

public:
	WordBST();
	~WordBST();

	void Rec_preorder_Print();
	void Rec_preorder_Print(WordNode * currentNode);
	void Iter_preorder_Print();

	void Rec_inorder_Print();
	void Rec_inorder_Print(WordNode * currentNode);
	void Iter_inorder_Print();

	void Rec_postorder_Print();
	void Rec_postorder_Print(WordNode * currentNode);
	void Iter_postorder_Print();

	void Iter_level_Print();

	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);				// PRINT
	bool		Save();								// SAVE
};

#endif
