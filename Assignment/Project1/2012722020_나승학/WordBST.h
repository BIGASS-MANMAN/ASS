#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"

class WordBST
{
private:
	WordNode * root;								// Word BST Root
	void R_Preorder(WordNode * node);				// Preorder traversal using Recursion
	void R_Inorder(WordNode * node);				// Inorder traversal using Recursion
	void R_Postorder(WordNode * node);				// Postorder traversal using Recursion
	void I_Preorder();								// Preorder traversal
	void I_Inorder();								// Inorder traversal using Iterator
	void I_Postorder();								// Postorder traversal using Iterator
	void I_LEVEL();									// Levelorder traversal using Iterator
	struct Stack {									// Stack Data structure
		WordNode * pHead = '\0';					// WordNode pointer pHead set NULL
		WordNode * Top() {							// WordNOde pointer Top
			return pHead;							// return pHead
		}
		void Push(WordNode * node) {				// node insert function
			node->SetNext(pHead);					// node pointing setNext
			pHead = node;							// pHead set node
		}
		WordNode * Pop() {							// node delete function 
			WordNode * p = pHead;					// WordNode Pointer P set pHead;
			pHead = pHead->GetNext();			    // p set p pointing getright
			p->SetNext(0);							// p pointing setnext
			return p;								// return p
		}
	};
	
public:
	WordBST();										// Constructor
	~WordBST();										// Destructor

	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);				// PRINT
	bool		Save();								// SAVE
};

#endif
