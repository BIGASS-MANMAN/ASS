#include "WordBST.h"
#include "Queue.h"
#include<cstring>
#include<iostream>
#include<fstream>
using namespace std;
WordBST::WordBST()
{
	root = '\0';
}


WordBST::~WordBST()
{
	Queue queue;									// Defining Queue is queue
	if (!root)return;								// Is not Correct root, then return
	WordNode* p = root, *pp = 0;					// current wordNode pointer p is root and pointer pp is 0
	while (p) {										// repetition
		if(p->GetLeft())queue.Push(p->GetLeft());	// condition repetition,If wordNode p is pointing Getting Left, push the p is pointing GetLeft
		if(p->GetRight())queue.Push(p->GetRight());	// condition repetition,If wordNode p is pointing Getting Right, push the p is pointing GetRight
		delete p;									// Delete p
		p = queue.Pop();							// pointer p is queue pop
	}
}



void		WordBST::Insert(WordNode * node)			// LOAD, MOVE
{
	WordNode* p = root, *pp = 0;						// current wordNode pointer p is root and pointer pp is 0
	int  cmp;											// Defining int cmp, for compare
	if (!root) {										// Is not Correct root
		root = node;									// root value is Node
		return;											
	}
	while (p) {											// Repetition
		cmp = strcmp(node->GetWord(), p->GetWord());	// comparing string node and p
		if (cmp < 0) {									// Condition compare
			pp = p;										// Defined pp is p
			p = p->GetLeft();							// If correct condition, then p is pointing GetLeft
		}
		else if (cmp > 0) {								// Another condition compare
			pp = p;										// Defined pp is p
			p = p->GetRight();							// If correct condition, them p is pointing GerRight
		}
		else {											// The other condition compare
			delete node;								// node Deleting
			return;
		}
	}
	if (strcmp(node->GetWord(), pp->GetWord()) < 0)pp->SetLeft(node);	// Compare String node and pp
	else pp->SetRight(node);											// pp is pointing SetRight
}
WordNode *	WordBST::Delete(char * word)				// TEST
{
	WordNode* p = root, *pp = 0;						// Node pointer p is root, pp is 0
	if (!root)return 0;									// Is not Correct root
	while (p) {											// Repetition
		if (strcmp(word, p->GetWord()) < 0) {			// string compare are word and pointer p
			pp = p;										// pointer pp is p
			p = p->GetLeft();							// pointer p is getleft
		}
		else if (strcmp(word, p->GetWord()) > 0) {		// Another condition
			pp = p;										// pointer pp is p
			p = p->GetRight();							// pointer p is getright
		}
		else break;										// out of repetition
	}
	if (!p)return 0;									// is not correct p then end function
	WordNode *prev = 0, *prevprev = 0, *prevchild = 0;	// prev:replace wordnode which is deleted / prevprev:parent of prev / prevchild:child node of prev
	if(p->GetLeft()){									// If condition, p is pointing get leftchild
		prevprev = p;									// set prevprev
		prev = p->GetLeft();							// prev is left child of p
		while (prev->GetRight()) {						// Repetition
			prevprev = prev;							// prevprev is prev 
			prev = prev->GetRight();					// prev is pointing getright
		}
		if(prev->GetLeft())prevchild = prev->GetLeft();	// set prevchild if prev has left child
		if(p != prevprev){								// if prevprev is not p
			prev->SetLeft(p->GetLeft());				// set prev left child
			prev->SetRight(p->GetRight());				// set prev right child
			prevprev->SetRight(prevchild);				// set prevprev right child
		}
		else	prev->SetRight(p->GetRight());			// prevprev set right
	}
	else if(p->GetRight()){								// Another condition if p pointing getright
		prevprev = p;									// prevprev set p
		prev = p->GetRight();							// prev is p to pointion getright
		while (prev->GetLeft()) {						// repetiton condition for prev is pointing getleft
			prevprev = prev;							// prevprev set prev
			prev = prev->GetLeft();						// prev is pointion getleft
		}
		if(prev->GetRight())prevchild = prev->GetRight();// set prevchild if prev has right child
		if(p != prevprev){
			if(prevchild)prevprev->SetLeft(prevchild);
			prev->SetRight(p->GetRight());
			prev->SetLeft(p->GetLeft());
			prevprev->SetLeft(prevchild);
		}
		else prev->SetLeft(p->GetLeft());
	}
	if (pp) {											// If condition
		if (p == pp->GetLeft())pp->SetLeft(prev);		// If p is eq pp pointed getleft, then pp pointing setleft
		else pp->SetRight(prev);						// or pp is pointing setright
	}
	else root = prev;
	return p;											// Return value is p
}
WordNode *	WordBST::Search(char * word)				// ADD, TEST, SEARCH, UPDATE
{
	WordNode* p = root;													// node pointer p is root
	if (!root)return 0;													// is not correct root, end of function
	while (p) {															// repetition
		if (strcmp(word, p->GetWord()) < 0)p = p->GetLeft();			// If comparing word and pointer p left
		else if (strcmp(word, p->GetWord()) > 0)p = p->GetRight();		// or oomparing word and pointer p right
		else return p;													// or return value p
	}
	return 0;															// end of function
}
bool		WordBST::Print(char * order)							// PRINT
{
		if		(!strcmp(order, "R_PRE"))	R_Preorder(root);		// If condition compare order
		else if (!strcmp(order, "R_IN"))	R_Inorder(root);		// or condition compare order
		else if (!strcmp(order, "R_POST"))	R_Postorder(root);		// or condition compare order
		else if (!strcmp(order, "I_PRE"))	I_Preorder();			// or condition compare order
		else if (!strcmp(order, "I_IN"))	I_Inorder();			// or condition compare order
		else if (!strcmp(order, "I_POST"))	I_Postorder();			// or condition compare order
		else if (!strcmp(order, "I_LEVEL")) I_LEVEL();				// or condition compare order
		else return 0;												// or end of function
		return 1;													// return value is 1
}
bool		WordBST::Save()								// SAVE
{
	Queue queue;													// Queueu is define queue
	WordNode * p = root;											// wordnode pointer p set root
	Stack stack;													// Stack is define stack
	ofstream fout;													// out of file stream fout
	if (!root)return 0;												// Is not correct root, then end of function
	fout.open("memorizing_word.txt", ios_base::app);				// file open
	if (!fout.is_open())return 0;									// end of function for file is not open
	while (1) {														// repetition
		while (p) {													// Twin repetition
			if (p->GetRight())stack.Push(p->GetRight());			// If condition to p pointing getright, data stacking push to p pointing getright
			fout << p->GetWord() << "\t" << p->GetMean() << endl;	// print file
			p = p->GetLeft();										// p set point get letf
		}
		if (!stack.pHead)break;										// is not, out of repetition
		p = stack.Pop();											// p poped stack
	}
	fout.close();													// print file close
	return 1;														// return value is 1
}

void		WordBST::R_Preorder(WordNode* node)						
{
	ofstream fout;													// open file stream fout
	fout.open("log.txt", ios_base::app);							// file open
	if (!fout.is_open())return;										// is not open
	if (node) {														// If condition node
		fout << node->GetWord() << "\t" << node->GetMean() << endl;	// print inner file
		R_Preorder(node->GetLeft());								// Preorder node pointing getleft
		R_Preorder(node->GetRight());								// Preorder node pointing getright
	}
	fout.close();													// file stream close
}

void		WordBST::R_Inorder(WordNode * node)
{
	ofstream fout;													// open file stream fout
	fout.open("log.txt", ios_base::app);							// file open
	if (!fout.is_open())return;										// is not open
	if (node) {														// If condition node
		R_Inorder(node->GetLeft());									// Inorder node pointing getleft
		fout << node->GetWord() << "\t" << node->GetMean() << endl;	// print inner file
		cout << node->GetWord() << "\t" << node->GetMean() << endl;
		R_Inorder(node->GetRight());								// Inorder node pointing getright
	}
	fout.close();													// file stream close
}

void		WordBST::R_Postorder(WordNode * node)
{
	ofstream fout;													// open file stream fout
	fout.open("log.txt", ios_base::app);							// file open
	if (!fout.is_open())return;										// is not open
	if (node) {														// If condition node
		R_Postorder(node->GetLeft());								// postorder node pointing getleft
		R_Postorder(node->GetRight());								// postorder node pointing getright
		fout << node->GetWord() << "\t" << node->GetMean() << endl;	// print inner file
		cout << node->GetWord() << "\t" << node->GetMean() << endl;
	}
	fout.close();													// file stream close
}

void		WordBST::I_Preorder()									// preorder traversal
{
	WordNode * p = root;											// wordnode point p set root
	Stack stack;													// Defined Stack is stack
	ofstream fout;													// open file stream fout
	fout.open("log.txt", ios_base::app);							// open file
	if (!fout.is_open())return;										// is not open
	while(1){														// repetition
		while (p) {													// twin pepetition
			if (p->GetRight())stack.Push(p->GetRight());			// If condition p pointed get right, then stack push
			fout << p->GetWord() << "\t" << p->GetMean() << endl;	// print inner file
			cout << p->GetWord() << "\t" << p->GetMean() << endl;
			p = p->GetLeft();										// p set getleft
		}
		if (!stack.pHead)break;;									// is not, out of repetition
		p = stack.Pop();											// p is stack pop
	}	
	fout.close();													// file stream close
}

void		WordBST::I_Inorder()									// inorder traversal
{
	WordNode * p = root;											// wordnode point p set root
	Stack stack;													// Defined Stack is stack
	ofstream fout;													// open file stream fout
	fout.open("log.txt", ios_base::app);							// open file
	if (!fout.is_open())return;										// is not open
	while(1){														// repetiton
		while (p) {													// twin repetiton
			stack.Push(p);											// stack push
			p = p->GetLeft();										// p pointing getleft
		}
		if (!stack.pHead)break;;									// is not stack head
		p = stack.Pop();											// p is stack pop
		fout << p->GetWord() << "\t" << p->GetMean() << endl;		// print inner file
		cout << p->GetWord() << "\t" << p->GetMean() << endl;
		p = p->GetRight();											// p set p pointing getright
	}
	fout.close();													// file stream close
}

void		WordBST::I_Postorder()									// postorder traversal
{		
	WordNode * p = root;											// wordnode point p is root
	Stack stack;													// Defined Stack is stack
	ofstream fout;													// open file stream is fout
	fout.open("log.txt", ios_base::app);							// open file
	if (!fout.is_open())return;										// is not open
	while(1) {														// repetition
		while (p) {													// twin repetition
			if (p->GetRight())stack.Push(p->GetRight());			// If condition is p pointing getright
			stack.Push(p);											// Stack push
			p = p->GetLeft();										// p set p point getleft
		}
		if (!stack.pHead)break;										// is not stack head
		p = stack.Pop();											// p is stack pop
		if (p->GetRight() == stack.Top() && p->GetRight()) {		// if condition, p pointed getright
			stack.Pop();											// stack pop
			stack.Push(p);											// stack push
			p = p->GetRight();										// p set p pointing get right
		}
		else {														// or
			fout << p->GetWord() << "\t" << p->GetMean() << endl;	// print inner file
			cout << p->GetWord() << "\t" << p->GetMean() << endl;
			p = 0;													// p set 0
		}
	}
	fout.close();													// file close
}

void		WordBST::I_LEVEL()										// levelorder traversal
{
	WordNode * p = root;											// wordnode pointer p set root
	ofstream fout;													// open file stream fout
	fout.open("log.txt", ios_base::app);							// open file
	if (!fout.is_open())return;										// is not open
	Queue queue;													// Define Queue is queue
	while (p) {														// repetition
		if (p->GetLeft())queue.Push(p->GetLeft());					// If condition p pointing get left then, queue push left
		if (p->GetRight())queue.Push(p->GetRight());				// If condition p pointing get right then, queue push right
		fout << p->GetWord() << "\t" << p->GetMean() << endl;		// print inner file
		cout << p->GetWord() << "\t" << p->GetMean() << endl;
		p = queue.Pop();											// p set queue pop
	}
	fout.close();													// file close

}
