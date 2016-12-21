#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
private:
	AlphabetNode * root;	// Root of ALPHABETBST
	int WordCnt;			// The number of words of MEMORIZING
	struct Stack {			// STACK data structure
		AlphabetNode * pHead = '\0';			// Pointer pp set 0
		bool IsEmpty() {						// Empty Discriminant Function //
			if (!pHead)return 1;				// is Stack empty, return true //
			return 0;							// end of function
		}
		AlphabetNode * Top() {					// AlphabetNode class pointer Top
			return pHead;						// return pHead
		}				
		void Push(AlphabetNode * node) {		// Insert function
			node->SetNext(pHead);				// node pointing setnext
			pHead = node;						// pHead set node
		}
		AlphabetNode * Pop() { AlphabetNode * p = pHead;	// AlphabetNode class pointer pop 
		pHead = pHead->GetNext();							// pHead set pHead pointing getnext 
		p->SetNext(0);										// p pointing setnext 
		return p;											// return p
		}
	};
	struct Queue {										// Queue data structure
		AlphabetNode * pHead = '\0', *pTail = '\0';		// Alphabet node pointer pHead set NULL, pointer pTail set NULL
		bool IsEmpty() {								// Empty Discriminant Function
			if (!pHead)return 1;						// is not pHead
			else return 0;								// or end of function
		}
		void Push(AlphabetNode * node) {				// Queue push
			if (IsEmpty()) {							// if node is empty
				pHead = node;							// pHead set node
				pTail = node;							// pTail set node
				return;									// return 
			}
			else pTail->SetNext(node);					// or pTail pointing setnext
			pTail = node;								// pTail set node
		} 
		AlphabetNode * Pop() {							// AlphabetNode pointer pop
			AlphabetNode * p = pHead;					// AlphabetNode Pointer p set pHead
			if (!IsEmpty()) {							// If AlphabetNode is not empty, 
				pHead = pHead->GetNext();				// phead set pointing getnext
				p->SetNext(0);							// p pointing setnext
				return p;								// return p
			}
			return 0;									// end of function
		}
	};

public:
	AlphabetBST();		// Constructor
	~AlphabetBST();		// Destructor

	void			Insert(AlphabetNode * node);		// run
	bool			Print(char * order);				// PRINT
	AlphabetNode *	Search(char alpabet);				// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();								// SAVE
	void			Insert(WordNode * node);			// node insert function
	WordNode *		Search(char * node);				// node Search function
	WordNode *		Delete(WordNode * node);			// node Delete function
	bool			IsFull();							// Full Check
	bool			IsEmpty();							// Empty Check

	void			R_Preorder(AlphabetNode * node);	// Preorder traversal using Recursion
	void			R_Inorder(AlphabetNode * node);		// Inorder traversal using Recursion
	void			R_Postorder(AlphabetNode * node);	// Postorder traversal using Recursion
	void			I_Preorder();						// Preorder traversal using Iterator				
	void			I_Inorder();						// Inorder traversal using Iterator					
	void			I_Postorder();						// Postorder traversal using Iterator					
	void			I_LEVEL();							// Levelorder traversal using Iterator
};

#endif
