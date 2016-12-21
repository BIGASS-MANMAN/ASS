#include "AlphabetBST.h"
#include <iostream>
using namespace std;

AlphabetBST::AlphabetBST()
{
	root = '\0';

	/* Alphabet into the BST */
	char arr[26] = { 'P','H','X','D','L','T','Z','B','F','J','N','R','V','Y','A','C','E','G','I','K','M','O','Q','S','U','W' };
	for (int i = 0; i < 26; i++) {
		AlphabetNode*pNew;
		pNew = new AlphabetNode;
		pNew->SetAlphabet(arr[i]);
		Insert(pNew);
	}
}

void Postorder_Destructor(AlphabetNode * pCur) {
	if (pCur) { // if pCur is not NULL,
		Postorder_Destructor(pCur->GetLeft()); // input the pCur's Left Node to tihs Recursive function
		Postorder_Destructor(pCur->GetRight()); // input the pCur's Right Node to tihs Recursive function
		delete pCur; // delete the pCur
	}
}

AlphabetBST::~AlphabetBST()
{
	Postorder_Destructor(root); // input the root Node to Recursive destruction function
}

void AlphabetBST::Insert(AlphabetNode*node) {
	AlphabetNode*pCur = root, *pp = NULL; // pp is the parent of pCur
	
	while (pCur) {
		pp = pCur;
		if (node->GetAlphabet() < pCur->GetAlphabet())
			pCur = pCur->GetLeft();
		else if (node->GetAlphabet() > pCur->GetAlphabet())
			pCur = pCur->GetRight();
		else {
			pCur->SetAlphabet(node->GetAlphabet());
			return;
		}
	}
	//node = new AlphabetNode;
	if (root != NULL)
		if (node->GetAlphabet() < pp->GetAlphabet())
			pp->SetLeft(node);
		else
			pp->SetRight(node);
	else
		root = node;
}

AlphabetNode* AlphabetBST::Search(char alphabet) {

	AlphabetNode * pWork;
	pWork = root;

	char pWork_alpha;

	if (pWork == NULL)
		return NULL;
	
	while (1)
	{
		pWork_alpha = pWork->GetAlphabet();

		// if alphabet that to search is little alphabet, but same with alpha
		if (pWork_alpha < alphabet)
		{
			if (alphabet - pWork_alpha == 32) // sucess to search alphabet.
				return pWork;
		}
		else if (pWork_alpha == alphabet) // sucess to search alphabet.
			return pWork;

		// compare.
		if (strcasecmp(&pWork_alpha, &alphabet) > 0)
		{
			if (pWork->GetLeft() == NULL)
				return NULL;

			pWork = pWork->GetLeft();
		}
		else if (strcasecmp(&pWork_alpha, &alphabet) < 0)
		{
			if (pWork->GetRight() == NULL)
				return NULL;

			pWork = pWork->GetRight();
		}
	}
}

bool AlphabetBST::Save() 
{
	// reset textfile.
	ofstream reset;
	reset.open("memorizing_word.txt");
	reset.close();

	if (root != NULL) // node exist in BST
	{
		Preorder_Save(root);
		return true;
	}
	else // no node in BST
		return false;
}

void AlphabetBST::Inorder(AlphabetNode*pCur, char*order) {
	if (pCur) { // if pCur is not NULL,
		Inorder(pCur->GetLeft(), order); // input pCur->Left to this recursive function
		pCur->GetBST()->Print(order); // Print BST
		Inorder(pCur->GetRight(), order); // input pCur->Right to this recursive function
	}
}
void AlphabetBST::Preorder(AlphabetNode*pCur, char*order) {
	if (pCur) { // if pCur is not NULL
		pCur->GetBST()->Print(order); // Print BST
		Preorder(pCur->GetLeft(), order); // input pCur->Left to this recursive function
		Preorder(pCur->GetRight(), order); // input pCur->Right to this recursive function
	}
}
void  AlphabetBST::Postorder(AlphabetNode*pCur, char*order) {
	if (pCur) { // if pCur is not NULL
		Postorder(pCur->GetLeft(), order); // input pCur->Left to this recursive function
		Postorder(pCur->GetRight(), order); // input pCur->Right to this recursive function
		pCur->GetBST()->Print(order); // Print BST
	}
}
void AlphabetBST::NONR_Inorder(char*order) {
	Stack<AlphabetNode*>s; // declare stack s.
	AlphabetNode*pCur = root;

	while (1) {
		while (pCur) { // if pCur is not NULL
			s.Push(pCur); // pCur into stack s.
			pCur = pCur->GetLeft(); // pCur move to pCur's left child.
		}
		if (s.IsEmpty())
			return; // if stack is empty, return.

		pCur = s.Top(); // pCur is Top of stack s
		s.Pop(); // Pop node that in stack s

		pCur->GetBST()->Print(order); // Print BST

		pCur = pCur->GetRight(); // pCur move to pCur's right child.
	}
}
void AlphabetBST::NONR_Preorder(char*order) {
	Stack<AlphabetNode*>s; // declare stack s.
	AlphabetNode*pCur = root;

	while (1) {  // repeat, exit when meet return
		while (pCur) {
			pCur->GetBST()->Print(order);
			s.Push(pCur);
			pCur = pCur->GetLeft();
		}
		if (s.IsEmpty())return;
		pCur = s.Top();
		s.Pop();

		pCur = pCur->GetRight();
	}
}
void AlphabetBST::NONR_Postorder(char*order) {
	Stack<AlphabetNode*>s;
	AlphabetNode * pCur = root;
	s.Push(pCur);

	AlphabetNode * pPrev = NULL;

	while (s.IsEmpty() != true)
	{
		pCur = s.Top();
		
		if (pPrev == NULL || pPrev->GetLeft() == pCur || pPrev->GetRight() == pCur) { // // pCur is child of pPrev OR First time(pPrev==NULL)
			if (pCur->GetLeft())
				s.Push(pCur->GetLeft());
			else if (pCur->GetRight())
				s.Push(pCur->GetRight());
			else { // no child
				pCur->GetBST()->Print(order);
				s.Pop();
			}
		}
		if (pCur->GetLeft() == pPrev&&pCur->GetLeft() != NULL) { // pPrev is Leftchild of pCur
			if (pCur->GetRight())
				s.Push(pCur->GetRight());
			else {
				pCur->GetBST()->Print(order);
				s.Pop();
			}
		}
		if (pCur->GetRight() == pPrev && pCur->GetRight() != NULL) { // pPrev is Rightchild of pCur
			pCur->GetBST()->Print(order);
			s.Pop();
		}
		pPrev = pCur;
	}
}

bool AlphabetBST::Print(char * order) {

	if (strcmp("R_PRE", order) == 0) {
		Preorder(root, order);
	}
	else if (strcmp("I_PRE", order) == 0) {
		NONR_Preorder(order);
	}
	else if (strcmp("R_IN", order) == 0) {
		Inorder(root, order);
	}
	else if (strcmp("I_IN", order) == 0) {
		NONR_Inorder(order);
	}
	else if (strcmp("R_POST", order) == 0) {
		Postorder(root, order);

	}
	else if (strcmp("I_POST", order) == 0) {
		NONR_Postorder(order);
	}
	else if (strcmp("I_LEVEL", order) == 0) { // Level Order.
		Queue1<AlphabetNode*>q;
		AlphabetNode*pCur = root;
		while (pCur) {
			pCur->GetBST()->Print(order); // Print BST

			if (pCur->GetLeft()) q.Push(pCur->GetLeft()); //if pCur's left is not NULL, Push pCur's left child to queue.
			if (pCur->GetRight()) q.Push(pCur->GetRight()); //if pCur's right is not NULL, Push pCur's right child to queue.
			if (q.IsEmpty()) return true; // if no node in queue, return true.
			pCur = q.Front(); // pCur point the queue q's front
			q.Pop(); // Pop node of queue q.
		}
	}
	else {
		return false;
	}
}

void AlphabetBST::Preorder_Save(AlphabetNode * t)
{
	if (t != NULL)
	{
		ofstream fout;
		fout.open("memorizing_word.txt", ios::app);
		t->GetBST()->Save(); // BST Save.
		fout.close();

		Preorder_Save(t->GetLeft()); // input t->Left to this recursive function
		Preorder_Save(t->GetRight());  // input t->Right to this recursive function
	}
}

