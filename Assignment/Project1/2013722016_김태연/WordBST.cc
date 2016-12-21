#include "WordBST.h"
#include <iostream>
#include <fstream>
using namespace std;



WordBST::WordBST() // WordBST constructor
{
	root = '\0';
}
WordBST::~WordBST() // WordBST destructor
{
	Stack s1, s2;
	WordNode* temp1 = NULL;
	WordNode* temp2 = NULL;

	s1.Push(root);

	while (!s1.isEmpty()) // delete by postorder traversal
	{
		temp1 = s1.Pop();
		s2.Push(temp1);

		if (temp1->GetLeft())
			s1.Push(temp1->GetLeft());
		if (temp1->GetRight())
			s1.Push(temp1->GetRight());
	}
	while (!s2.isEmpty())
	{
		temp2 = s2.Pop();
		delete temp2;
	}

}

void	WordBST::Insert(WordNode * node)// LOAD, MOVE
{
	WordNode *p = root, *pp = NULL;

	while (p) { // while p is not NULL
		pp = p; // pp is p's parent at end of loop
		if (strcmp(node->GetWord(), p->GetWord()) < 0) p = p->GetLeft();
		else if (strcmp(node->GetWord(), p->GetWord()) > 0) p = p->GetRight();
		else // look for place to insert
		{
			p->SetWord(node->GetWord()); p->SetMean(node->GetMean());
			return;
		}
	}
		p = new WordNode(); // dynamic allocation
		p->SetWord(node->GetWord()); p->SetMean(node->GetMean()); // set word and mean

		if (root != NULL) // when root is not NULL
			if (strcmp(p->GetWord(), pp->GetWord()) < 0) pp->SetLeft(p);
			else pp->SetRight(p); // insert
		else root = p; // when root is NULL, insert p to root
		
}
WordNode * WordBST::Delete(char * word)// TEST
{
	WordNode *p = root, *q = NULL; 
	while (p && strcmp(p->GetWord(), word)) // look for node to delete
	{
		q = p;
		if (strcmp(p->GetWord(), word) > 0) p = p->GetLeft();
		else p = p->GetRight();
	}

	if (p == NULL) // when fail to searching node to delete
		return p;
	

	else if (p->GetLeft() == 0 && p->GetRight() == 0) // when node to delete has 2 children
	{
		if (q == NULL) root = NULL;
		else if (q->GetLeft() == p) q->SetLeft(NULL);
		else q->SetRight(NULL);
		return p;
	}

	else if (p->GetLeft() == 0) // when node to delete has only right child
	{
		if (q == 0) root = p->GetRight();
		else if (q->GetLeft() == p) q->SetLeft(p->GetRight());
		else q->SetRight(p->GetRight());
		return p;
	}

	else if (p->GetRight() == 0) // when node to delete has only left child
	{
		if (q == 0) root = p->GetLeft();
		else if (q->GetLeft() == p) q->SetLeft(p->GetLeft());
		else q->SetRight(p->GetLeft());
		return p;
	}

	else // when node to delete has 2 children
	{
		WordNode *prevprev = p, *prev = p->GetRight(),
			*curr = p->GetRight()->GetLeft();

		while (curr) {
			prevprev = prev;
			prev = curr;
			curr = curr->GetLeft();
		}

		p->SetWord(prev->GetWord());
		p->SetMean(prev->GetMean());
		if (prevprev == p) prevprev->SetRight(prev->GetRight());
		else prevprev->SetLeft(prev->GetRight());
		return prev;
	}
}
WordNode *	WordBST::Search(char * word)// ADD, TEST, SEARCH, UPDATE
{
	WordNode *p = root;

	while (p) { // while p is not NULL
		if (strcmp(p->GetWord(), word) > 0) p = p->GetLeft(); // binary search
		else if (strcmp(p->GetWord(), word) < 0) p = p->GetRight();
		else return p;
	}
	return NULL;
}

bool	WordBST::Save()// SAVE
{
	ofstream fin_2;
	fin_2.open("memorizing_word.txt", ios::app);
	WordNode* currentNode = root;
	Stack(s);
	if (currentNode == NULL) { // if currnetNode is NULL
		return 0;
	}
	while (currentNode) { // while currentNode is not NULL
		fin_2 << currentNode->GetWord() << "\t" << currentNode->GetMean() << endl;
		if (currentNode->GetRight()) s.Push(currentNode->GetRight());
		if (currentNode->GetLeft())  s.Push(currentNode->GetLeft());
		if (s.isEmpty()) { // if stack is empty
			fin_2.close();
			return 1;
		}
		currentNode = s.Pop();
	}
	return 1;
}

void WordBST::Visit(WordNode*currentNode) { // Visit Function
	ofstream fout; fout.open("log.txt", ios::app);
	fout << currentNode->GetWord() << " " << currentNode->GetMean() << endl;
	cout << currentNode->GetWord() << " " << currentNode->GetMean() << endl;
	fout.close();
}

void WordBST::Preorder(WordNode* currentNode) // Reculsive preorder
{
	if (currentNode) {
		Visit(currentNode);
		Preorder(currentNode->GetLeft());
		Preorder(currentNode->GetRight());
	}
}

void WordBST::Inorder(WordNode* currentNode)// Reculsive inorder
{
	if (currentNode) {
		Inorder(currentNode->GetLeft());
		Visit(currentNode);
		Inorder(currentNode->GetRight());
	}
}

void WordBST::Postorder(WordNode* currentNode)// Reculsive postorder
{
	if (currentNode) {
		Postorder(currentNode->GetLeft());
		Postorder(currentNode->GetRight());
		Visit(currentNode);
	}
}

void WordBST::NonrecInorder(WordNode* currentNode) { // Nonreculsive inorder
	Stack s;

	while (1) {
		while (currentNode) {
			s.Push(currentNode);
			currentNode = currentNode->GetLeft();
		}
		if (s.isEmpty())return;
		currentNode = s.getTop();
		s.Pop();
		Visit(currentNode);
		currentNode = currentNode->GetRight();
	}
}

void WordBST::NonrecPreorder(WordNode* currentNode) { // Nonreculsive preorder
	Stack(s);
	currentNode = root;
	while (currentNode) {
		Visit(currentNode);
		if (currentNode->GetRight()) s.Push(currentNode->GetRight());
		if (currentNode->GetLeft())  s.Push(currentNode->GetLeft());
		if (s.isEmpty())return;

		currentNode = s.Pop();
	}
}

void WordBST::NonrecPostorder(WordNode* currentNode) { // Nonreculsive postorder
	Stack s1, s2;
	WordNode* temp1 = NULL;
	WordNode* temp2 = NULL;

	s1.Push(root);

	while (!s1.isEmpty())
	{
		temp1 = s1.Pop();
		s2.Push(temp1);

		if (temp1->GetLeft())
			s1.Push(temp1->GetLeft());
		if (temp1->GetRight())
			s1.Push(temp1->GetRight());
	}
	while (!s2.isEmpty())
	{
		temp2 = s2.Pop();
		Visit(temp2);
	}
}

void WordBST::LevelOrder(WordNode* currentNode) { // levelorder traversal
	Queue q;

	while (currentNode) {
		Visit(currentNode);
		if (currentNode->GetLeft())q.Push(currentNode->GetLeft());
		if (currentNode->GetRight())q.Push(currentNode->GetRight());
		if (q.IsEmpty())return;
		currentNode = q.GetpHead();
		q.Pop();

	}
}

bool   WordBST::Print(char * order)// PRINT
{
	if (!strcmp(order, "R_PRE")) // print by reculsive preorder
	{
		Preorder(root);
		return true;
	}
	else if (!strcmp(order, "R_IN")) // print by reculsive inorder
	{
		Inorder(root);
		return true;
	}
	else if (!strcmp(order, "R_POST")) // print by reculsive postorder
	{
		Postorder(root);
		return true;
	}
	else if (!strcmp(order, "I_LEVEL")) // print by level order traversal
	{
		LevelOrder(root);
		return true;
	}

	else if (strcmp(order, "I_PRE") == 0) // print by nonreculsive preorder
	{
		NonrecPreorder(root);
		return true;
	}
	else if (strcmp(order, "I_IN") == 0) // print by nonreculsive inorder
	{
		NonrecInorder(root);
		return true;
	}
	else if (strcmp(order, "I_POST") == 0) // print by nonreculsive postorder
	{
		NonrecPostorder(root);
		return true;
	}
	else
		return false;
}