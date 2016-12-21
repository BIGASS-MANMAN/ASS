#include "AlphabetBST.h"
#include "AlphabetNode.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct BST_Queue {						// Binary Search Tree Queue
	AlphabetNode* pHead = '\0';			// Alphabet node pointer phead set 0
	AlphabetNode* pTail = '\0';			// Alphabet node pointer ptail set 0
	void Push(AlphabetNode* node) {		// Alphabetnode push
		if (!pHead) {					// is not phead condition
			pHead = node;				// phead set node
			pTail = node;				// ptail set node
		}
		else {							// or
			pTail->SetNext(node);		// ptail pointing setnext
			pTail = node;				// ptail set node
		}
	}
	AlphabetNode * Pop() {				// Alphabet node pointer pop
		AlphabetNode * temp;			// Alphabet node pointer temp
		if (!pHead)return 0;			// is not phead, then end of function
		else {							// or
			temp = pHead;				// pointer temp set phead
			pHead = pHead->GetNext();	// phead set pointing getnext
			if (pHead == 0)pTail = '\0';	// If phead eq 0, then ptail set 0
			return temp;				// return temp
		}
	}
};
AlphabetBST::AlphabetBST()		// BST
{
	root = '\0';																			// initial root set NULL
	WordCnt = 0;																			// initial word current wordcnt set 0
	
	BST_Queue queue;																		// Define BST Queue , queue
	AlphabetNode * p;																		// Alphabet node pointer p
	char arr[26] = { 'p', 'h', 'x', 'd', 'l', 't', 'z', 'b', 'f', 'j', 'n', 'r', 'v',		// character array
					'y', 'a', 'c', 'e', 'g', 'i', 'k', 'm', 'o', 'q', 's', 'u', 'w' };
	for (int i = 0; i < 26; i++) {															// condition repetition
		p = new AlphabetNode;																// pointer p set dynamic allocation Alphabe node
		p->SetAlphabet(arr[i]);																// p pointing setAlphabet
		Insert(p);																			// input insert
	}
}

AlphabetBST::~AlphabetBST()								// BST
{
	BST_Queue queue;									// Define BST Queue, queue
	if (!root)return;									// is not root, return
	AlphabetNode* p = root;					// Alphabet node pointer p set root, pointer pp set 0
	while (p) {											// repetition
		if (p->GetLeft())queue.Push(p->GetLeft());		// If condition p pointed getleft, then push left
		if (p->GetRight())queue.Push(p->GetRight());	// If condition p pointed getright, then push right
		delete p;										// Delete p
		p = queue.Pop();								// p set pop
	}
}


void			AlphabetBST::Insert(AlphabetNode * node)	// run
{
	AlphabetNode* p = root, *pp = '\0';									// Alphabet node pointer p set root, pointer pp set 0
	if (!root) {														// is not root
		root = node;													// root set node
		return;															// return
	}
	while (p) {															// repetition
		if (node->GetAlphabet() < p->GetAlphabet()) {					// if node smaller than p
			pp = p;														// pp set p
			p = p->GetLeft();											// p set p pointing getleft
		}
		else if (node->GetAlphabet() > p->GetAlphabet()) {				// or node larger than p
			pp = p;														// pp set p
			p = p->GetRight();											// p set p pointing getright
		}
		else {															// or
			delete node;												// Delete node
			return;														// return
		}			
	}
	if (node->GetAlphabet() < pp->GetAlphabet())pp->SetLeft(node);		// If condition node smaller than pp, then pp pointing setleft
	else pp->SetRight(node);											// or pp pointint setright

}
bool			AlphabetBST::Print(char * order)						// PRINT
{
	if (!WordCnt)return 0;												// MEMORIZING is empty
	ofstream fout;														// open file stream fout
	fout.open("log.txt", ios_base::app);								// open file
	if (!fout.is_open() || IsEmpty())return 0;							// is not open, then end of function
	if		(!strcmp("R_PRE", order)){									// if condition
		fout << "======== PRINT ========" << endl;						// print inner file
		cout << "======== PRINT ========" << endl;
		R_Preorder(root);												// Recursive Preorder
	}
	else if (!strcmp("R_IN", order)){									// or
		fout << "======== PRINT ========" << endl;						// print inner file
		cout << "======== PRINT ========" << endl;
		R_Inorder(root);												// Recursive Inorder
	}
	else if (!strcmp("R_POST", order))	{								// or
		fout << "======== PRINT ========" << endl;						// print inner file
		cout << "======== PRINT ========" << endl;
		R_Postorder(root);												// Recursive postorder		
	}
	else if	(!strcmp("I_PRE", order)){									// or
		fout << "======== PRINT ========" << endl;						// print inner file
		cout << "======== PRINT ========" << endl;
		I_Preorder();													// Iterative preorder
	}
	else if (!strcmp("I_IN", order)){									// or
		fout << "======== PRINT ========" << endl;						// print inner file
		cout << "======== PRINT ========" << endl;
		I_Inorder();													// Iterative inorder		
	}	
	else if (!strcmp("I_POST", order)){									// or
		fout << "======== PRINT ========" << endl;						// print inner file
		cout << "======== PRINT ========" << endl;
		I_Postorder();													// Iterative postorder
	}
	else if (!strcmp("I_LEVEL", order)){								// or
		fout << "======== PRINT ========" << endl;						// print inner file
		cout << "======== PRINT ========" << endl;
		I_LEVEL();														// Iterative level-order
	}
	else {																// or
		fout.close();													// file close
		return 0;														// end of function
	}
	fout << "=======================" << endl;
	cout << "=======================" << endl;
	fout.close();														// file close
	return 1;															// return value 1
}
AlphabetNode *	AlphabetBST::Search(char alpabet)				// LOAD, MOVE, TEST, SEARCH, UPDATE
{
	AlphabetNode* p = root;										// alphabet node pointer p set root
	if (!root)return 0;											// is not root, then end of function
	while (p) {													// repetiton
		if (alpabet < p->GetAlphabet())p = p->GetLeft();		// If condition alphabet smaller than p, then p set p pointing getleft
		else if (alpabet > p->GetAlphabet())p = p->GetRight();	// or p set p pointing getright
		else return p;											// or return p
	}
	return 0;													// end of function
}
bool			AlphabetBST::Save()							// SAVE
{
	AlphabetNode * p = root;								// Alphabet node pointer p set root
	Stack stack;											// Define Stack, stack
	ofstream fout;											// open file stream fout
	fout.open("memorizing_word.txt", ios_base::out);		// open file
	fout.close();											// file close
	if (!root)return 0;										// is not root, then end of function
	while (1) {												// repetition
		while (p) {											// twin repetition
			if (p->GetRight())stack.Push(p->GetRight());	// If condition p pointed getright, then stack push
			p->GetBST()->Save();							// p pointing getbst , along save
			p = p->GetLeft();								// p set p pointing getleft
		}			
		if (!stack.pHead)break;								// is not stack phead, then out of repetition
		p = stack.Pop();									// p set stack pop
	}
	return 1;												// return value 1
}

void AlphabetBST::Insert(WordNode * node)					// BST insert
{
	AlphabetNode* temp;										// alphabet node pointer temp
	if (WordCnt == 100)return;								// if word current 

	temp = Search((node->GetWord())[0]);					// temp set search
	temp->GetBST()->Insert(node);							// temp pointing getbst, along insert
	WordCnt++;												// word current increase 1
}

WordNode *	AlphabetBST::Search(char * word)				// BST Search
{
	WordNode * node;										// word node pointer node
	node = Search(word[0])->GetBST()->Search(word);			// node set Search
	return node;											// return value node
}

WordNode * AlphabetBST::Delete(WordNode * word)								// BST Delete
{

	return Search(word->GetWord()[0])->GetBST()->Delete(word->GetWord());	// return search

}

bool	AlphabetBST::IsFull()		// IsFull
{
	if (WordCnt == 100)return 1;	// If condition word current eq 100, then return 1
	else return 0;					// or end of function
}

bool	AlphabetBST::IsEmpty()		// IsEmpty
{
	if (WordCnt == 0)return 1;		// If condition word current eq 0, then return 1
	else return 0;					// or end of function
}
void	AlphabetBST::R_Preorder(AlphabetNode * node)	// BST Recursive Preorder
{
	if (node) {											// If condition node
		node->GetBST()->Print("R_PRE");					// node pointing getbst, along print
		R_Preorder(node->GetLeft());					// Recursive preorder left
		R_Preorder(node->GetRight());					// Recursive preorder right
	}
}

void	AlphabetBST::R_Inorder(AlphabetNode * node)		// BST Recursive Inorder
{
	if (node) {											// If condition node
		R_Inorder(node->GetLeft());						// Recursive Inorder
		node->GetBST()->Print("R_IN");					// node pointing getbst, along print
		R_Inorder(node->GetRight());					// Recursive Inorder
	}
}

void	AlphabetBST::R_Postorder(AlphabetNode * node)	// BST Recursive Postorder
{		
	if (node) {											// If condition node
		R_Postorder(node->GetLeft());					// Recursive Postorder
		R_Postorder(node->GetRight());					// Recursive Postorder
		node->GetBST()->Print("R_POST");				// node pointing getbst, along print
	}
}

void	AlphabetBST::I_Preorder()							// Preorder traversal
{
	AlphabetNode * p = root;								// Alphabet node pointer p set root
	Stack stack;											// Define Stack, stack
	while (1) {												// repetition
		while (p) {											// twin repetition
			if (p->GetRight())stack.Push(p->GetRight());	// if condition p 
			p->GetBST()->Print("I_PRE");					// p pointing getbst, along print
			p = p->GetLeft();								// p set p pointing getleft
		}		
		if (!stack.pHead)return;							// If condition is not stack phead, then return
		p = stack.Pop();									// p set stack pop
	}
}

void	AlphabetBST::I_Inorder()				// Iterative Inorder
{
	AlphabetNode * p = root;					// Alphabet node pointer p set root
	Stack stack;								// Define Stack, stack
	while (1) {									// repetition
		while (p) {								// twin repetition
			stack.Push(p);						// stack push
			p = p->GetLeft();					// p set p pointint getleft
		}
		if (!stack.pHead)return;				// If condition is not phead, then return
		p = stack.Pop();						// p set stack pop
		p->GetBST()->Print("I_IN");				// p pointing getbst, along print
		p = p->GetRight();						// p set p pointing getright
	}
}

void	AlphabetBST::I_Postorder()								// Iterative postorder
{
	AlphabetNode * p = root;									// Alphabetnode pointer p set root
	Stack stack;												// Define Stack, stack
	while (1) {													// repetition
		while (p) {												// twin repetition
			if (p->GetRight())stack.Push(p->GetRight());		// If condition p pointed getright, then stack push
			stack.Push(p);										// stack push p
			p = p->GetLeft();									// p set p pointing getleft
		}
		if (stack.IsEmpty())return;								// If stack empty, then return
		p = stack.Pop();										// p set stack pop
		if (p->GetRight() == stack.Top() && p->GetRight()) {	// If condition p pointed getright eq top stack so p pointed getright
			stack.Pop();										// stack pop
			stack.Push(p);										// stack push p
			p = p->GetRight();									// p set p pointing getright
		}			
		else {													// or
			p->GetBST()->Print("I_POST");						// p pointing getbst, along print
			p = 0;												// p set 0, initialize
		}
	}
}

void	AlphabetBST::I_LEVEL()								// Iterative Levelorder
{
	Queue queue;											// Define Queue, queue
	AlphabetNode * p = root;								// alphabet node pointer p set root
		while (p) {											// repetition
			if (p->GetLeft())queue.Push(p->GetLeft());		// If condition p pointed getleft, then queue, push
			if (p->GetRight())queue.Push(p->GetRight());	// If condition p pointed getright, then queue, push
			p->GetBST()->Print("I_LEVEL");					// p pointing getbst, along print
			p = queue.Pop();								// p set queue pop
		}
}
