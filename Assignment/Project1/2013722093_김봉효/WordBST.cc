#include "WordBST.h"
#include "Stack.h"
#include"Queue.h"
#include<cstring>
#include<string.h>
#include<iostream>
#include<fstream>
using namespace std;
WordBST::WordBST()
{
	root = '\0';
}


WordBST::~WordBST()
{
	Dellocate(root);
	root = 0;
}

bool WordBST::IsEmpty() // if WordBST is empty return 1
{
	if (root == NULL)
		return 1;
	return 0;
}
void WordBST::Print(WordNode* p)
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	// print word, mean
	cout << p->GetWord() << " ";
	cout << p->GetMean() << endl;
	flog << p->GetWord() << " " << p->GetMean() << endl;
	flog.close();
}

void WordBST::R_Preorder(WordNode* p) // Recursive pre-order
{
	if (p) {
		Print(p);
		R_Preorder(p->GetLeft());
		R_Preorder(p->GetRight());
	}
}

void WordBST::R_Inorder(WordNode* p) // Recursive in-order
{
	if (p) {
		R_Inorder(p->GetLeft());
		Print(p);
		R_Inorder(p->GetRight());
	}
}

void WordBST::R_Postorder(WordNode* p) // Recursive post-order
{
	if (p) {
		R_Postorder(p->GetLeft());
		R_Postorder(p->GetRight());
		Print(p);
	}
}

void WordBST::I_Preorder() // Interative pre-order
{
	if (IsEmpty())
		return;
	WordNode* cur = root, *left=0, *right=0;
	Stack<WordNode*> s;
	s.Push(cur); // push root
	while (1) { // while stack is not empty
		if (s.IsEmpty()) break; 
		else {
			cur = s.Top();
			s.Pop();
			if (cur != NULL) {
				Print(cur);

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
}

void WordBST::I_Inorder() // Interative in-order
{
	if (IsEmpty()) return; // if tree is empty : exception handling
	WordNode* cur = root;
	Stack<WordNode*> s;
	while (1) {
		for (; cur != NULL; cur = cur->GetLeft()) { // move to the leftmost child
			s.Push(cur);
		}
		if (s.IsEmpty()) break;
		else { // visit right child
			cur = s.Top();
			s.Pop();
			if (cur) {
				Print(cur);
				cur = cur->GetRight();
				
			}
		}
	}
}
void WordBST::I_Postorder() // Interative post-order
{
	if (IsEmpty()) return; // if tree is empty : exception handling
	WordNode* cur = root;
	Stack<WordNode*> s;
	s.Push(root);
	while (1) { // while stack is not empty
		if (s.IsEmpty()) break;
				while(cur->GetLeft()!=NULL && cur->GetLeft()->visit==0){ // move to the left
					cur = cur->GetLeft();
					s.Push(cur);
				}
				while (cur->GetRight() != NULL && cur->GetRight()->visit==0) { // move to the right
					cur = cur->GetRight();
					s.Push(cur);
				}
				// visit
				cur = s.Top();
				s.Pop();
				Print(cur); 
				cur->visit = 1; // if cur->visit=1 cur is already visited node

				if(!s.IsEmpty())
				cur = s.Top();
				
	}
	SetVisitZero(root);
}
void WordBST::R_Preorder_save(WordNode* p) { // Recursive pre-order to save function
	int e = 0;
	if (p) {
		save_node(p); // save p in file
		R_Preorder_save(p->GetLeft());
		R_Preorder_save(p->GetRight());
	}
}


void WordBST::I_Levelorder()  // Interative Level-order
{
	if (IsEmpty()) return; // if tree is empty : exception handling
	Queue q;
	WordNode* cur = root, *left=0, *right=0;
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
		Print(cur); // visit
		q.Pop();
		cur = q.pHead; // cur = q.peek()
	}
}
void WordBST::Insert(WordNode* node)
{
	WordNode *p = root, *pp = 0;
	if (node == NULL) return; // exception handling
	if (IsEmpty()) { // if AlphabetBST is empty
		root = node;
		return;
	}
	while (p) { // find parent node where you want to insert
		pp = p;
		if (strcmp(p->GetWord(), node->GetWord())<0)
			p = p->GetRight();
		else if (strcmp(p->GetWord(), node->GetWord()) > 0)
			p = p->GetLeft();
		else
			return; // already node is in the tree
	}

	// insert the node as pp's child
	if (strcmp(pp->GetWord(), node->GetWord()) < 0) {
		pp->SetRight(node);
		
	}
	else {
		pp->SetLeft(node);
	}
}

WordNode* WordBST::Delete(char* word)
{
	WordNode *cur = root, *parent = 0;
	while (cur && strcmp(word,cur->GetWord())!=0) { // search
		parent = cur;
		if (strcmp(word, cur->GetWord()) < 0)
			cur = cur->GetLeft();
		else
			cur = cur->GetRight();
	}
	if (cur == 0) return NULL; // not found

	if (cur->GetLeft() == 0 && cur->GetRight() == 0) {
		if (parent) {
			if (parent->GetLeft() == cur)
				parent->SetLeft(0);
			if (parent->GetRight() == cur)
				parent->SetRight(0);
		}
		else
			root = 0;
		return parent;
	}
	WordNode *prevprev = cur, *prev = cur->GetLeft(), *curr = cur->GetLeft()->GetRight();
	if (cur->GetLeft() != 0) {
		prevprev = cur;
		prev = cur->GetRight();
		curr = cur->GetRight()->GetLeft();
		while (curr) {
			prevprev = prev;
			prev = curr;
			curr = curr->GetLeft();
		}
		cur->SetWord(prev->GetWord());
		cur->SetMean(prev->GetMean());
		if (prevprev == cur) prevprev->SetRight(prev->GetRight());
		else prevprev->SetLeft(prev->GetRight());
		return prev;
	}
	

	// degree 2 node and only right child
	prevprev = cur;
	prev = cur->GetLeft();
	curr = cur->GetLeft()->GetRight();
	while (curr) {
		prevprev = prev;
		prev = curr;
		curr = curr->GetRight();
	} 
	cur->SetWord(prev->GetWord());
	cur->SetMean(prev->GetMean());
	if (prevprev == cur) prevprev->SetLeft(prev->GetLeft());
	else prevprev->SetRight(prev->GetLeft());
	
	return prev;
}

WordNode* WordBST::Search(char* word) // search
{
	WordNode* p = root;
	if (IsEmpty()) {// exception handling
		return NULL;
	}
	if (strcasecmp(p->GetWord(),word)==0)
		return p;
	while (p) {
		if (strcasecmp(p->GetWord(), word) == 0)
			return p;
		if (strcasecmp(word,p->GetWord())>0)
			p = p->GetRight();
		else
			p = p->GetLeft();

	}
	return NULL;
}

bool WordBST::Print(char* order)
{
	
	// function decision in accordance with the input char* order
	if (strcmp(order, "R_PRE") == 0) {
		R_Preorder(root);
	}
	else if (strcmp(order, "I_PRE") == 0) {
		I_Preorder();
	}
	else if (strcmp(order, "R_IN") == 0) {
		R_Inorder(root);
	}
	else if (strcmp(order, "I_IN") == 0) {
		I_Inorder();
	}
	else if (strcmp(order, "R_POST") == 0) {
		R_Postorder(root);
	}
	else if (strcmp(order, "I_POST") == 0) {
		I_Postorder();
	}
	else if (strcmp(order, "I_LEVEL") == 0) {
		I_Levelorder();
	}
	else { // error : input char* order is wrong
		ofstream flog;
		flog.open("log.txt", ios::app);
		cout << "======== ERROR ========" << endl;
		cout << "700";
		cout << "======================\n" << endl;
		flog << "======== ERROR ========\n" << "700" << "======================\n"<<endl;
		flog.close();
		return 0;
	}
	return 1;
}

void WordBST::save_node(WordNode* p) {
	ofstream f;
	f.open("memorizing_word.txt",ios::app);
	ofstream flog;
	flog.open("log.txt",ios::app);
	if (!f.is_open())
	{
		cout << "======= ERROR ========" << endl;
		cout << "100" << endl;
		cout << "======================\n" << endl;
		flog << "======= ERROR ========" << endl;
		flog << "100" << endl;
		flog << "======================\n" << endl;
		return;
	}
	if (Search(p->GetWord()) != NULL) { // write word, mean in file
		f << p->GetWord() << " " << p->GetMean() << endl;
	}
	f.close();
}
bool WordBST::Save()
{
	R_Preorder_save(root); // save in pre-order
		return 1;
}

void WordBST::Dellocate(WordNode* p) {
	if (p) {
		Dellocate(p->GetLeft());
		Dellocate(p->GetRight());
		delete p->GetWord();
		delete p->GetMean();
		delete p;
	}
}

void WordBST::SetVisitZero(WordNode* p) {
	if (p) {
		SetVisitZero(p->GetLeft());
		SetVisitZero(p->GetRight());
		p->visit = 0;
	}
}
