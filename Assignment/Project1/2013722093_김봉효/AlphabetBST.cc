#include "AlphabetBST.h"
#include"Stack.h"
#include"Alpha_Queue.h"
#include"Alpha_Queue.cc"
#include<iostream>
#include<cstring>
using namespace std;
AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;
}

AlphabetBST::~AlphabetBST()
{
	Dellocate(root);
}
void	AlphabetBST::R_Preorder(AlphabetNode* p, char *word) {
	if (p) {
		p->GetBST()->Print(word);
		R_Preorder(p->GetLeft(),word);
		R_Preorder(p->GetRight(),word);
	}
}// Recursive Pre-order
void	AlphabetBST::R_Inorder(AlphabetNode* p, char* word) {
	if (p) {
		R_Preorder(p->GetLeft(), word);
		p->GetBST()->Print(word);
		R_Preorder(p->GetRight(), word);
	}
}// Recursive In-order
void	AlphabetBST::R_Postorder(AlphabetNode* p, char* word) {
	if (p) {
		R_Preorder(p->GetLeft(), word);
		p->GetBST()->Print(word);
		R_Preorder(p->GetRight(), word);
	}
}// Recursive Post-order

void	AlphabetBST::I_Preorder(char* word) {
	if (IsEmpty()) return;
	AlphabetNode* cur = root, *left = 0, *right = 0;
	Stack<AlphabetNode*> s;
	s.Push(cur); // push root
	while (1) { // while stack is not empty
		if (s.IsEmpty()) break;
		else {
			cur = s.Top();
			s.Pop();
			if (cur != NULL) {
				cur->GetBST()->Print(word);

				if (cur->GetRight() != NULL) { // move to the right child
					right = cur->GetRight();
					s.Push(right);
				}
				if (cur->GetLeft() != NULL) { // move to the left child
					left = cur->GetLeft();
					s.Push(left);
				}
			}
		}
	}

}// Iterative Pre-order
void	AlphabetBST::I_Inorder(char* word) {
	if (IsEmpty()) return; // if tree is empty : exception handling
	AlphabetNode* cur = root;
	Stack<AlphabetNode*> s;
	while (1) {
		for (; cur != NULL; cur = cur->GetLeft()) { // move to the leftmost child
			s.Push(cur);
		}
		if (s.IsEmpty()) break;
		else { // visit right child
			cur = s.Top();
			s.Pop();
			if (cur) {
				cur->GetBST()->Print(word);
				cur = cur->GetRight();
			}
		}
	}
}// Iterative In-order
void	AlphabetBST::I_Postorder(char* word) {
	if (IsEmpty()) return; // if tree is empty : exception handling
	AlphabetNode* cur = root;
	Stack<AlphabetNode*> s;
	s.Push(root);
	while (1) { // while stack is not empty
		if (s.IsEmpty()) break;
		while (cur->GetLeft() != NULL && cur->GetLeft()->visit == 0) { // move to the left
			cur = cur->GetLeft();
			s.Push(cur);
		}
		while (cur->GetRight() != NULL && cur->GetRight()->visit == 0) { // move to the right
			cur = cur->GetRight();
			s.Push(cur);
		}
		// visit
		cur = s.Top();
		s.Pop();
		if (cur->GetBST() == NULL) {
			cout << "======== ERROR ========" << endl;
			cout << "700" << endl;
			cout << "=======================\n" << endl;
		}
		cur->GetBST()->Print(word);
		cur->visit = 1; // if cur->visit=1 cur is already visited node

		if (!s.IsEmpty())
			cur = s.Top();

	}
	SetVisitZero(root);
}// Iterative Post-order
void	AlphabetBST::I_Levelorder(char* word) {
	if (IsEmpty()) return; // if tree is empty : exception handling
	Alpha_Queue q;
	AlphabetNode* cur = root, *left = 0, *right = 0;
	q.Push(root);
	while (1) { // while q is not empty
		if (q.IsEmpty()) break;
		if (cur->GetLeft() != NULL) { // move to the left
			left = cur->GetLeft();
			q.Push(left); // push left
		}
		if (cur->GetRight() != NULL) { // move to the right
			right = cur->GetRight();
			q.Push(right); // push right
		}
		cur->GetBST()->Print(word); // visit
		q.Pop();
		cur = q.pHead; // cur = q.peek()
	}
}
void AlphabetBST::Insert(AlphabetNode * node)
{

	if (node == NULL) return; // exception handling
	if (IsEmpty()) { // if AlphabetBST is empty
		root = node;
		return;
	}
	
	AlphabetNode *p = root, *pp = 0;
	while (p) { // find parent node where you want to insert
		pp = p;
		if (node->GetAlphabet() > p->GetAlphabet())
			p = p->GetRight();
		else if (node->GetAlphabet() < p->GetAlphabet())
			p = p->GetLeft();
		else
			return; // already node is in the tree
	}

	// insert the node as pp's child
	if (node->GetAlphabet() > pp->GetAlphabet())
		pp->SetRight(node);
	else
		pp->SetLeft(node);
}

bool AlphabetBST::Print(char * order)
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	if (root == 0)
		return 0;
	// function decision in accordance with the input char* order
	if (strcmp(order, "R_PRE") == 0) {
		cout << "======== PRINT ========" << endl;
		flog << "======== PRINT ========" << endl;
		R_Preorder(root, order);
		cout << "=====================\n" << endl;
		flog << "=====================\n" << endl;
	}
	else if (strcmp(order, "I_PRE") == 0) {
		cout << "======== PRINT ========" << endl;
		flog << "======== PRINT ========" << endl;
		I_Preorder(order);
		cout << "=====================\n" << endl;
		flog << "=====================\n" << endl;
	}
	else if (strcmp(order, "R_IN") == 0) {
		cout << "======== PRINT ========" << endl;
		flog << "======== PRINT ========" << endl;
		R_Inorder(root, order);
		cout << "=====================\n" << endl;
		flog << "=====================\n" << endl;
	}
	else if (strcmp(order, "I_IN") == 0) {
		cout << "======== PRINT ========" << endl;
		flog << "======== PRINT ========" << endl;
		I_Inorder(order);
		cout << "=====================\n" << endl;
		flog << "=====================\n" << endl;
	}
	else if (strcmp(order, "R_POST") == 0) {
		cout << "======== PRINT ========" << endl;
		flog << "======== PRINT ========" << endl;
		R_Postorder(root, order);
		cout << "=====================\n" << endl;
		flog << "=====================\n" << endl;
	}
	else if (strcmp(order, "I_POST") == 0) {
		cout << "======== PRINT ========" << endl;
		flog << "======== PRINT ========" << endl;
		I_Postorder(order);
		cout << "=====================\n" << endl;
		flog << "=====================\n" << endl;
	}
	else if (strcmp(order, "I_LEVEL") == 0) {
		cout << "======== PRINT ========" << endl;
		flog << "======== PRINT ========" << endl;
		I_Levelorder(order);
		cout << "=====================\n" << endl;
		flog << "=====================\n" << endl;
	}
	else  // error : input char* order is wrong
	{
		return 0;
		flog.close();
	}
	flog.close();
	return 1;
}

AlphabetNode* AlphabetBST::Search(char alpabet)
{
	AlphabetNode* p = root;
	if (IsEmpty()) {
		return p;
	}
	if (p->GetAlphabet() == alpabet)
		return p;
	while (p) {
		if (p->GetAlphabet() == alpabet)
			return p;
		if (alpabet > p->GetAlphabet())
			p = p->GetRight();
		else
			p = p->GetLeft();
		
	}
	return NULL;
}
void AlphabetBST::R_Preorder_save(AlphabetNode* p) {
	if (p) {
		p->GetBST()->Save();
		R_Preorder_save(p->GetLeft());
		R_Preorder_save(p->GetRight());
	}
}
bool AlphabetBST::Save()  // pre-order
{
	ofstream fin;
	fin.open("memorizing_word.txt",ios::trunc);
	fin.close();
	R_Preorder_save(root);
	return 1;
}

bool AlphabetBST::IsEmpty() const
{
	if (root == NULL)
		return 1;
	return 0;
}

void AlphabetBST::Dellocate(AlphabetNode* p) {
	while (p) {
		Dellocate(p->GetLeft());
		Dellocate(p->GetRight());
		if(p->GetBST())
		p->GetBST()->~WordBST();
		p = NULL;
	}
}
void AlphabetBST::SetVisitZero(AlphabetNode* p)
{
	if (p) {
		SetVisitZero(p->GetLeft());
		SetVisitZero(p->GetRight());
		p->visit = 0;
	}
}
