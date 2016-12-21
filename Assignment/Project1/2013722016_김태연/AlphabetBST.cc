#include "AlphabetBST.h"
#include <iostream>
#include <fstream>

using namespace std;

AlphabetBST::AlphabetBST() // AlphabetBST constructor
{
	root = '\0'; // Initialization
	WordCnt = 0; // Initialization
	arr = new char[64]; // dynamic allocation

	AlphabetNode P, H, X, D, L, T, Z, B, F, J, N, R, V, Y, A, C, E, G, I, K, M, O, Q, S, U, W;
	//Set BST
	P.SetAlphabet('p');
	P.Setsample("p");
	H.SetAlphabet('h');
	H.Setsample("h");
	X.SetAlphabet('x');
	X.Setsample("x");
	D.SetAlphabet('d');
	D.Setsample("d");
	L.SetAlphabet('l');
	L.Setsample("l");
	T.SetAlphabet('t');
	T.Setsample("t");
	Z.SetAlphabet('z');
	Z.Setsample("z");
	B.SetAlphabet('b');
	B.Setsample("b");
	F.SetAlphabet('f');
	F.Setsample("f");
	J.SetAlphabet('j');
	J.Setsample("j");
	N.SetAlphabet('n');
	N.Setsample("n");
	R.SetAlphabet('r');
	R.Setsample("r");
	V.SetAlphabet('v');
	V.Setsample("v");
	Y.SetAlphabet('y');
	Y.Setsample("y");
	A.SetAlphabet('a');
	A.Setsample("a");
	C.SetAlphabet('c');
	C.Setsample("c");
	E.SetAlphabet('e');
	E.Setsample("e");
	G.SetAlphabet('g');
	G.Setsample("g");
	I.SetAlphabet('i');
	I.Setsample("i");
	K.SetAlphabet('k');
	K.Setsample("k");
	M.SetAlphabet('m');
	M.Setsample("m");
	O.SetAlphabet('o');
	O.Setsample("o");
	Q.SetAlphabet('q');
	Q.Setsample("q");
	S.SetAlphabet('s');
	S.Setsample("s");
	U.SetAlphabet('u');
	U.Setsample("u");
	W.SetAlphabet('w');
	W.Setsample("w");
	Insert(&P); // Insert Alphabets to BST
	Insert(&H);
	Insert(&X);
	Insert(&D);
	Insert(&L);
	Insert(&T);
	Insert(&Z);
	Insert(&B);
	Insert(&F);
	Insert(&J);
	Insert(&N);
	Insert(&R);
	Insert(&V);
	Insert(&Y);
	Insert(&A);
	Insert(&C);
	Insert(&E);
	Insert(&G);
	Insert(&I);
	Insert(&K);
	Insert(&M);
	Insert(&O);
	Insert(&Q);
	Insert(&S);
	Insert(&U);
	Insert(&W);
}


AlphabetBST::~AlphabetBST() // AlphabetBST destructor
{
	delete arr; // delete
	
	Stack s1, s2; // Stack instance
	AlphabetNode* temp1 = NULL; // temp1, temp2 initialization
	AlphabetNode* temp2 = NULL;

	s1.Push(root->Getsample()); // push sample to Stack

	while (!s1.isEmpty()) // while stack is not empty
	{
		temp1 = Search(s1.Pop()->GetWord()[0]); // temp = stack1's top
		s2.Push(temp1->Getsample()); //  push temp1's sample to stack2

		if (temp1->GetLeft()) // Is there temp1's leftchild?
			s1.Push(temp1->GetLeft()->Getsample()); // push temp1's left child's sample to temp1
		if (temp1->GetRight())
			s1.Push(temp1->GetRight()->Getsample()); // push temp1's right child's sample to temp1
	}
	while (!s2.isEmpty()) // while stack2 is not empty
	{
		temp2 = Search(s2.Pop()->GetWord()[0]); // temp2 = stack2's top
		delete temp2; // delete temp2
	}
}

void AlphabetBST::Insert(AlphabetNode * node) { // AlphabetBST Insert Function
	AlphabetNode *p = root, *pp = NULL; // AlphabetNode* p, * pp initialization

	while (p) { // while p is not NULL
		pp = p; // pp is p's parent when loop's end
		if (node->GetAlphabet() < p->GetAlphabet()) p = p->GetLeft(); // look for place to insert
		else if (node->GetAlphabet() > p->GetAlphabet()) p = p->GetRight(); // look for place to insert
		else
		{
			p->SetAlphabet(node->GetAlphabet()); // Alphabet of input node set in Alphabet  of p node
			return;
		}
	}
		p = new AlphabetNode(); // dynamic allocation
		p->SetAlphabet(node->GetAlphabet()); // SetAlphabet of p
		p->Setsample(node->Getsample()->GetWord()); // Setsample of p

		if (root != NULL) // when root is not NULL
			if (p->GetAlphabet() < pp->GetAlphabet()) pp->SetLeft(p);
			else pp->SetRight(p);
		else root = p;
}


AlphabetNode * AlphabetBST::Search(char alpabet) { // AlphabetBST Search Function
	AlphabetNode * temp = root; // temp is root
	while (temp) // while temp is not NULL
	{
		if (temp->GetAlphabet() == alpabet) // look for searching alphabet
			return temp;	
		else if (temp->GetAlphabet() > alpabet) // look for searching alphabet
			temp = temp->GetLeft();
		else
			temp = temp->GetRight(); // look for searching alphabet
	}
	return NULL;  // when search failed
}

void AlphabetBST::Visit(AlphabetNode* currentNode) { // AlphabetBST Visit Function
	currentNode->GetBST()->Print(arr);
}
void AlphabetBST::Preorder(AlphabetNode* currentNode) // Reculsive Preorder
{   
	if (currentNode) {
		Visit(currentNode);
		Preorder(currentNode->GetLeft());
		Preorder(currentNode->GetRight());
	}
}
void AlphabetBST::Inorder(AlphabetNode* currentNode) // Reculsive Inorder
{
	if(currentNode) {
		Inorder(currentNode->GetLeft());
		Visit(currentNode);
		Inorder(currentNode->GetRight());
	}
}
void AlphabetBST::Postorder(AlphabetNode* currentNode) // Reculsive Postorder
{
	if (currentNode) {
		Postorder(currentNode->GetLeft());
		Postorder(currentNode->GetRight());
		Visit(currentNode); // visit last
	}
}
void AlphabetBST::NonrecPreorder(AlphabetNode* currentNode) { // Nonreculsive Preorder
	Stack(s);
	currentNode = root;
	while (currentNode) {
		Visit(currentNode); // visit first
		if (currentNode->GetRight()) s.Push(currentNode->GetRight()->Getsample());
		if (currentNode->GetLeft())  s.Push(currentNode->GetLeft()->Getsample());
		if (s.isEmpty())return;

		currentNode = Search(s.Pop()->GetWord()[0]);
	}
}

void AlphabetBST::NonrecPostorder(AlphabetNode* currentNode) { // Nonreculsive Postorder
	Stack s1, s2; // Stack for noncrepostorder
	AlphabetNode* temp1 = NULL; // AlphabetNode*temp1,*temp2
	AlphabetNode* temp2 = NULL;

	s1.Push(root->Getsample()); // push root's sample to stack1

	while (!s1.isEmpty()) // while stack1 is not empty
	{
		temp1 = Search(s1.Pop()->GetWord()[0]);
		s2.Push(temp1->Getsample());

		if (temp1->GetLeft())
			s1.Push(temp1->GetLeft()->Getsample());
		if (temp1->GetRight())
			s1.Push(temp1->GetRight()->Getsample());
	}
	while (!s2.isEmpty()) // while stack2 is not empty
	{
		temp2 = Search(s2.Pop()->GetWord()[0]);
		Visit(temp2);
	}
}

void AlphabetBST::LevelOrder(AlphabetNode* currentNode) { // Levelorder traversal
	Queue q; // Queue instance

	while (currentNode) { // while current is not NULL
		Visit(currentNode); // Visit currentNode
		if (currentNode->GetLeft())q.Push(currentNode->GetLeft()->GetBST()->root); // push to queue
		if (currentNode->GetRight())q.Push(currentNode->GetRight()->GetBST()->root); // push to queue
		if (q.IsEmpty())return; // when queue is empty, return
		currentNode = Search(q.GetpHead()->GetWord()[0]);
		q.Pop(); // pop
	}
}

void AlphabetBST::NonrecInorder(AlphabetNode* currentNode) { // Nonreculsive Inorder
	Stack s; // Stack instance

	while (1) { 
		while (currentNode) {	 // while currentnode is not NULL	
				s.Push(currentNode->Getsample()); // push currentNode's sample to stack
			currentNode = currentNode->GetLeft(); // move to left child
		}
		if (s.isEmpty())return; // when stack is empty, return
		currentNode = Search(s.getTop()->GetWord()[0]);
		s.Pop(); // pop 
		Visit(currentNode); // visit currentNode
		currentNode = currentNode->GetRight(); // move to right child
	}
}

bool AlphabetBST::Save() { // Save Function
	Stack(s); // stack instance
	AlphabetNode * currentNode = root; // currentNode = root
	if (currentNode == NULL) { // if currentNode is NULL
		return 0; // return 
	}

	while (currentNode) { // while currnetNode is not NULL
		currentNode->GetBST()->Save(); // WordBST Save
		if (currentNode->GetRight()) s.Push(currentNode->GetRight()->Getsample());
		if (currentNode->GetLeft())  s.Push(currentNode->GetLeft()->Getsample());
		if (s.isEmpty()) { // when stack is empty,return 
			return 1;
		}
		currentNode = Search(s.Pop()->GetWord()[0]);
	}
	return 1;
}

bool AlphabetBST::Print(char* order) { // Print Function

	strcpy(arr, order); // copy order to arr

	if (strcmp(order, "R_PRE") == 0) // print by reculsive preorder
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		fout << "======== PRINT ========" << endl;
		fout.close();
		cout << "======== PRINT ========" << endl;
		Preorder(root);
		cout << "=======================" << endl;
		ofstream fout1;
		fout1.open("log.txt", ios::app);
		fout1 << "=======================" << endl;
		fout1.close();
		return true;
	}
	else if (strcmp(order, "R_IN") == 0)// print by reculsive inorder
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		fout << "======== PRINT ========" << endl;
		fout.close();
		cout << "======== PRINT ========" << endl;
		Inorder(root);
		cout << "=======================" << endl;
		ofstream fout1;
		fout1.open("log.txt", ios::app);
		fout1 << "=======================" << endl;
		fout1.close();
		return true;
	}
	else if (strcmp(order, "R_POST") == 0)// print by reculsive postorder
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		fout << "======== PRINT ========" << endl;
		fout.close();
		cout << "======== PRINT ========" << endl;
		Postorder(root);
		cout << "=======================" << endl;
		ofstream fout1;
		fout1.open("log.txt", ios::app);
		fout1<< "=======================" << endl;
		fout1.close();
		return true;
	}
	else if (strcmp(order, "I_LEVEL") == 0)// print by levelorder
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		fout << "======== PRINT ========" << endl;
		fout.close();
		cout << "======== PRINT ========" << endl;
		LevelOrder(root);
		cout << "=======================" << endl;
		ofstream fout1;
		fout1.open("log.txt", ios::app);
		fout1 << "=======================" << endl;
		fout1.close();
		return true;
	}
	else if (strcmp(order, "I_PRE") == 0)// print by nonreculsive preorder
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		fout << "======== PRINT ========" << endl;
		fout.close();
		cout << "======== PRINT ========" << endl;
		NonrecPreorder(root);
		cout << "=======================" << endl;
		ofstream fout1;
		fout1.open("log.txt", ios::app);
		fout1 << "=======================" << endl;
		fout1.close();
		return true;
	}
	else if (strcmp(order, "I_IN") == 0)// print by nonreculsive inorder
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		fout << "======== PRINT ========" << endl;
		fout.close();
		cout << "======== PRINT ========" << endl;
		NonrecInorder(root);
		cout << "=======================" << endl;
		ofstream fout1;
		fout1.open("log.txt", ios::app);
		fout1 << "=======================" << endl;
		fout1.close();
		return true;
	}
	else if (strcmp(order, "I_POST") == 0)// print by nonreculsive postorder
	{
		ofstream fout;
		fout.open("log.txt", ios::app);
		fout << "======== PRINT ========" << endl;
		fout.close();
		cout << "======== PRINT ========" << endl;
		NonrecPostorder(root);
		cout << "=======================" << endl;
		ofstream fout1;
		fout1.open("log.txt", ios::app);
		fout1 << "=======================" << endl;
		fout1.close();
		return true;
	}
	else
		return false;

}
int AlphabetBST::GetWordCnt() // GetWordCnt Function
{
	return WordCnt;
}
void  AlphabetBST::GetWordCntPlus() // GetWordCntPlus Function
{
	WordCnt++;
}