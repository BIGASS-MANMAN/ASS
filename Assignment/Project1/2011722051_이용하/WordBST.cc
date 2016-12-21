#include "WordBST.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

void strchange(char * a);  // change big letter to small letter
int mystrcmp(char * a, char * b);  // string compare ignoring the case of character

WordBST::WordBST() // WordBST's constructor
{
	root = '\0';
}

WordBST::~WordBST() // WordBST's destructor
{
	WordNode * Stack[100] = { 0 };
	int pos = -1;
	WordNode * pCur = new WordNode;
	pCur = root; // store root in pCur
	int sig = 0;
	while (pCur != NULL)
	{
		Stack[++pos] = pCur; // storing pCur in Stack
		pCur = pCur->GetLeft(); // pCur stores pCur's left node
	}
	while (1)
	{
		if (sig == 1)
		{
			while (pCur != NULL)
			{
				Stack[++pos] = pCur; // storing pCur in Stack
				pCur = pCur->GetLeft(); // pCur stores pCur's left node
			}
		}
		if (pos == -1)
			return;
		pCur = Stack[pos];
		if (pCur->GetRight() != NULL && pCur->GetCount() == 0)
		{
			pCur->SetCount(1); // it's count is changed to 1
			pCur = pCur->GetRight(); // pCur stores pCur's right node
			sig = 1; // signal is changed to 1
			continue;
		}
		else
		{
			Stack[pos] = NULL; // Stack's data is deleted
			pos--; // position is substracted by 1
			delete pCur; // delete the node
			sig = 0; // signal is changed to 1
			continue;
		}
	}
}

void WordBST::Insert(WordNode * node) // WordBST's Insert function
{
	WordNode * pNew = new WordNode;
	pNew->SetWord(node->GetWord());
	pNew->SetMean(node->GetMean());

	if (root == NULL)
		root = pNew;
	else
	{
		WordNode * pCur = new WordNode;
		pCur = root;
		while (1)
		{
			if (strcmp(pCur->GetWord(), pNew->GetWord()) >= 0) // if pCur's word is bigger than pNew's word
			{
				if (pCur->GetLeft() == NULL) // if pCur's leftnode is not presented
				{
					pCur->SetLeft(pNew); // pCur's leftnode is pNew
					break;
				}
				else
				{
					pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
					continue;
				}
			}
			else if (strcmp(pCur->GetWord(), pNew->GetWord()) < 0) // if pCur's word is smaller than pNew's word
			{
				if (pCur->GetRight() == NULL) // if pCur's rightnode is not presented
				{
					pCur->SetRight(pNew); // pCur's rightnod eis pNew
					break;
				}
				else
				{
					pCur = pCur->GetRight(); // store pCur's rightnode in pCur
					continue;
				}
			}
		}
	}
}

WordNode * WordBST::Delete(char * word)
{
	WordNode * p = new WordNode;
	WordNode * pp = new WordNode;
	WordNode * sp = new WordNode;
	WordNode * spp = new WordNode;
	WordNode * temp = new WordNode;

	p = root;
	pp = NULL;

	while (1)
	{
		if (p != NULL)
		{
			if (mystrcmp(p->GetWord(), word) == 0) // if word in WordBST
				break;
			pp = p;

			if (mystrcmp(p->GetWord(), word) > 0) // if word is bigger than p
				p = p->GetLeft(); // move p to the left
			else
				p = p->GetRight(); // move p to the right
		}
		else
			break;
	}
	if (p != NULL)
	{
		if (p->GetLeft() == NULL && p->GetRight() == NULL) // if deleting node has no node
		{
			if (p == root) // if p is root
			{
				temp->SetWord(p->GetWord()); // temp's word is p's word
				temp->SetMean(p->GetMean()); // temp's mean is p's mean
				root = NULL; // store NULL in root
				delete p; // delete node p
				return temp; // return tempnode
			}
			else
			{
				temp->SetWord(p->GetWord()); // temp's word is p's word
				temp->SetMean(p->GetMean()); // temp's mean is p's mean
				if (pp->GetLeft() == p) // pp's leftnode is p
					pp->SetLeft(NULL); // store NULL in pp's leftnode 
				else if (pp->GetRight() == p) // pp's rightnode is p
					pp->SetRight(NULL); // store NULL in pp's rightnode
				delete p; // delete node p
				return temp; // return tempnode
			}
		}
		else if (p->GetLeft() != NULL && p->GetRight() == NULL)  // if deleting p has a leftnode
		{
			if (p == root)  // if p is root
			{
				temp->SetWord(p->GetWord());  // temp's word is p's word
				temp->SetMean(p->GetMean());  // temp's mean is p's mean
				root = p->GetLeft(); // store p's leftnode in root
				delete p; // delete node p
				return temp; // return tempnode
			}
			else
			{
				temp->SetWord(p->GetWord()); // temp's word is p's word
				temp->SetMean(p->GetMean()); // temp's mean is p's mean
				spp = p; // store p in spp
				sp = p->GetLeft(); // store p's leftnode in sp
				while (sp->GetRight() != NULL)  // if sp has a rightnode
				{
					spp = sp; // store sp in spp
					sp = sp->GetRight(); // store sp's rightnode in sp
				}
			}
			if (sp->GetLeft() != NULL) // if sp has a leftnode 
			{
				p->SetWord(sp->GetWord()); // store sp's word in p
				p->SetMean(sp->GetMean()); // store sp's mean in p
				spp->SetRight(NULL); // store NULL in spp's rightnode
				spp->SetRight(sp->GetLeft()); // store sp's leftnode in spp's rightnode
			}
			else
			{
				p->SetWord(sp->GetWord()); // store sp's word in p
				p->SetMean(sp->GetMean()); // store sp's mean in p
			}
			delete sp; // delete sp node
			return temp; // return tempnode
		}
		else if (p->GetLeft() == NULL && p->GetRight() != NULL) // if deleting p has a rightnode
		{
			if (p == root) // if p is root
			{
				temp->SetWord(p->GetWord()); // temp's word is p's word
				temp->SetMean(p->GetMean()); // temp's word is p's mean
				root = p->GetRight(); // store p's rightnode in root
				delete p; // delete node p
				return temp; // return tempnode
			}
			else
			{
				temp->SetWord(p->GetWord()); // temp's word is p's word
				temp->SetMean(p->GetMean()); // temp's word is p's mean
				spp = p; // store p in spp
				sp = p->GetRight(); // store p's rightnode in sp
				while (sp->GetLeft() != NULL) // if sp has a leftnode
				{
					spp = p; // store p in spp
					sp = p->GetLeft(); // store sp's leftnode in sp
				}
				if (sp->GetRight() != NULL) // if sp has a rightnode 
				{
					p->SetWord(sp->GetWord()); // store sp's word in p
					p->SetMean(sp->GetMean()); // store sp's mean in p
					spp->SetLeft(NULL); // store NULL in spp's leftnode
					spp->SetLeft(sp->GetRight()); // store sp's rightnode in spp's leftnode
					p->SetRight(NULL); // store NULL in p's rightnode
				}
				else
				{
					p->SetWord(sp->GetWord()); // store sp's word in p
					p->SetMean(sp->GetMean()); // store sp's mean in p
				}
				delete sp; // delete sp node
				return temp; // return tempnode
			}
		}
		else // if deleting p has two nodes
		{
			if (p == root) // if p is root
			{
				temp->SetWord(p->GetWord()); // temp's word is p's word
				temp->SetMean(p->GetMean()); // temp's word is p's mean
				root = p->GetLeft(); // store p's leftnode in root
				delete p; // delete p node
				return temp; // return tempnode
			}
			else
			{
				temp->SetWord(p->GetWord()); // temp's word is p's word
				temp->SetMean(p->GetMean()); // temp's word is p's mean
				spp = p; // store p in spp
				sp = p->GetLeft(); // store p's leftnode in sp
				while (sp->GetRight() != NULL) // if sp has a rightnode 
				{
					spp = sp; // store sp in spp
					sp = sp->GetRight(); // store sp's rightnode in sp
				}
				if (sp->GetLeft() != NULL) // if sp has a leftnode
				{
					p->SetWord(sp->GetWord()); // sp's word in p
					p->SetMean(sp->GetMean()); // sp's mean in p
					spp->SetRight(NULL); // store NULL in spp's rightnode 
					spp->SetRight(sp->GetLeft()); // store sp's leftnode in spp's rightnode
				}
				else
				{
					p->SetWord(sp->GetWord()); // store sp's word in p
					p->SetMean(sp->GetMean()); // store sp's mean in p
				}
				delete sp; // delete sp node
				return temp; // return tempnode
			}
		}
	}
	else // no word in WordBST
		return 0; // return 0
}

WordNode * WordBST::Search(char * word) // search function in WordBST
{
	WordNode * pCur = new WordNode;
	pCur = root;
	if (root == NULL) // No root
		return 0;
	else
	{
		while (pCur != NULL)
		{
			if (mystrcmp(word, pCur->GetWord()) == 0) // found
				return pCur; // return node
			else
			{
				if (mystrcmp(word, pCur->GetWord()) > 0) // word > node
				{
					pCur = pCur->GetRight(); // move to right pointer
					continue;
				}
				else if (mystrcmp(word, pCur->GetWord()) < 0) // word < node
				{
					pCur = pCur->GetLeft(); // move to left pointer
					continue;
				}
			}
		}
		return 0; // Not found
	}
}

bool WordBST::Print(char * order)
{
	if (strcmp(order, "R_IN") == 0) // recursive inorder
		R_IN(order);
	else if (strcmp(order, "R_PRE") == 0) // recursive pre order
		R_PRE(order);
	else if (strcmp(order, "R_POST") == 0) // recursive post order
		R_POST(order);
	else if (strcmp(order, "I_LEVEL") == 0) // iterative level order
		I_LEVEL(order);
	else if (strcmp(order, "I_IN") == 0) // iterative inorder
		I_IN(order);
	else if (strcmp(order, "I_POST") == 0) // iterative post order
		I_POST(order);
	else if (strcmp(order, "I_PRE") == 0) // iterative pre order
		I_PRE(order);
	else // error code
	{
		ofstream log;
		log.open("log.txt", ios::app); // log.txt open
		cout << "======== ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
		log << "======== ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
		log.close(); // close log file
		return 0;
	}
	return 1;
}

bool WordBST::Save() // save function in WordBST
{
	ofstream fout;
	fout.open("memorizing_word.txt", ios::app); // open text file
	WordNode * Stack[100] = { 0 }; // assign WordNode type's array named Stack for WordBST's storing WordNode
	int pos = -1;  // assign pos for representing array's position
	WordNode * pCur = new WordNode; // assign pCur for storing WordBST's WordNode
	pCur = root; // store root in pCur
	if (root == NULL)
		return 0; // No node in WordBST
	Stack[++pos] = pCur; // store pCur in Stack
	while (pos != -1)
	{
		pCur = Stack[pos]; // Stack is popped in pCur
		fout << pCur->GetWord() << " " << pCur->GetMean() << endl; // save pCur's word and mean in textfile
		Stack[pos] = NULL; // store NULL in stack
		pos--; // pos is substracted by 1 
		if (pCur->GetRight())
			Stack[++pos] = pCur->GetRight(); // store pCur's rightnode in stack
		if (pCur->GetLeft())
			Stack[++pos] = pCur->GetLeft(); // store pCur's leftnode in stack
	}
	fout.close(); // close log file
	return 1;
}

void WordBST::R_IN(char * order) // recursive inorder
{
	R_IN(root, order);
}

void WordBST::R_IN(WordNode * Node, char * order) // recursive inorder
{
	if (Node)
	{
		R_IN(Node->GetLeft(), order); // input leftnode in R_IN
		Visit(Node, order); // visit
		R_IN(Node->GetRight(), order); // input rightnode in R_IN
	}
}

void WordBST::R_PRE(char * order) // recursive pre order
{
	R_PRE(root, order);
}

void WordBST::R_PRE(WordNode * Node, char * order) // recursive pre order
{
	if (Node)
	{
		Visit(Node, order); // visit
		R_PRE(Node->GetLeft(), order); // input leftnode in R_PRE
		R_PRE(Node->GetRight(), order); // input rightnode in R_PRE
	}
}

void WordBST::R_POST(char * order) // recursive post order
{
	R_POST(root, order);
}

void WordBST::R_POST(WordNode * Node, char * order) // recursive post order
{
	if (Node)
	{
		R_POST(Node->GetLeft(), order); // input leftnode in R_POST
		R_POST(Node->GetRight(), order); // input rightnode in R_POST
		Visit(Node, order); // visit
	}
}

void WordBST::I_IN(char * order) // I_IN function in WordBST
{
	WordNode * Stack[100] = { 0 };  // assign WordNode type's array named Stack for WordBST's storing WordNode
	int pos = -1; // assign pos for representing array's position
	WordNode * pCur = new WordNode; // assign pCur for storing WordBST's WordNode
	pCur = root; // store root in pCur
	while (1)
	{
		while (pCur)
		{
			Stack[++pos] = pCur; // store pCur in Stack
			pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
		}
		if (pos == -1) // if no node in stack
			return; // break loop
		pCur = Stack[pos]; // Stack is popped in pCu
		Stack[pos] = NULL; // store NULL in Stack
		pos--; // pos is substracted by 1 
		Visit(pCur, order); // call Visit
		pCur = pCur->GetRight(); // store pCur's rightnode in pCur
	}
}
void WordBST::I_POST(char * order) // I_POST function in WordBST
{
	WordNode * Stack[100] = { 0 }; // assign WordNode type's array named Stack for WordBST's storing WordNode
	int pos = -1; // assign pos for representing array's position
	WordNode * pCur = new WordNode; // assign pCur for storing WordBST's WordNode
	pCur = root; // store root in pCur
	int sig = 0; // assign sig for signal in this function
	while (pCur)
	{
		Stack[++pos] = pCur; // Stack is pushed in pCur
		pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
	}
	while (1)
	{
		if (sig == 1) // if signal is 1
		{
			while (pCur)
			{
				Stack[++pos] = pCur; // Stack is pushed in pCur
				pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
			}
		}
		if (pos == -1) // if no node is in WordBST
			return; // break loop
		pCur = Stack[pos]; // Stack is popped is in pCur
		if (pCur->GetRight() != NULL && pCur->GetCount() == 0) // if pCur has a rightnode
		{
			pCur->SetCount(1); // pCur's count is changed to 1
			pCur = pCur->GetRight(); // store pCur's rightnode in pCur
			sig = 1; // sig is changed to 1
			continue; // continue loop
		}
		else
		{
			Stack[pos] = NULL; // store NULL in Stack
			pos--; // pos is substracted by 1 
			Visit(pCur, order); // call VIsit
			sig = 0; // sig is changed to 0
			continue; // continue loop
		}
	}
	SetZero_IN(); // call SetZero_IN
}
void WordBST::I_PRE(char * order) // I_PRE function in WordBST
{
	WordNode * Stack[100] = { 0 }; // assign WordNode type's array named Stack for WordBST's storing WordNode
	int pos = -1; // assign pos for representing array's position
	if (root == NULL) // if no node in WordBST
		return; // break loop
	WordNode * pCur = new WordNode; // assign pCur for storing WordBST's WordNode
	pCur = root; // store root in pCur
	Stack[++pos] = pCur; // Stack is pushed in pCur
	while (pos != -1)
	{
		pCur = Stack[pos]; // Stack is popped in pCur
		Visit(pCur, order); // call Visit
		Stack[pos] = NULL; // store NULL in Stack
		pos--; // pos is substracted by 1 
		if (pCur->GetRight()) // if pCur has a rightnode
			Stack[++pos] = pCur->GetRight(); // store pCur's rightnode in Stack
		if (pCur->GetLeft()) // if pCur has a leftnode
			Stack[++pos] = pCur->GetLeft(); // store pCur's leftnode in Stack
	}
}

void WordBST::I_LEVEL(char * order) // I_LEVEL function in WordBST
{
	WordNode * Queue[100] = { 0 }; // assign WordNode type's array named Queue for WordBST's storing WordNode
	int pos = 0; // assign pos for representing array's position
	int front = 0; // queue's front position
	WordNode * Node = new WordNode; // assign Node for storing WordBST's WordNode
	Node = root; // store root in Node
	while (Node)
	{
		Visit(Node, order); // call Visit
		if (Node->GetLeft()) // if Node has a leftnode
			Queue[pos++] = Node->GetLeft(); // store Node's leftnode in Queue
		if (Node->GetRight()) // if Node has a rightnode
			Queue[pos++] = Node->GetRight(); // store Node's rightnode in Queue
		if (pos == front) // if no node is in queue
			return; // break loop
		Node = Queue[front]; // Queue's popped in Node
		Queue[front] = NULL; // store NULL in Queue
		front++; // add 1 to front
	}
}
void WordBST::Visit(WordNode * node, char * order)
{
	ofstream log;
	log.open("log.txt", ios::app); // log.txt open
	cout << node->GetWord() << "/" << node->GetMean() << endl; // print
	log << node->GetWord() << "/" << node->GetMean() << endl; // print
	log.close(); // close log file
}

int WordBST::GetWordCount() // GetWordCount function in WordBST
{
	int cnt = 0; // assign cnt for storing count
	WordNode * Stack[100] = { 0 }; // assign WordNode type's array named Stack for WordBST's storing WordNode
	int pos = -1;// assign pos for representing array's position
	WordNode * pCur = new WordNode; // assign pCur for storing WordBST's WordNode
	pCur = root; // store root in pCur
	while (1)
	{
		while (pCur)
		{
			Stack[++pos] = pCur; // Stack is pushed in pCur
			pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
		}
		if (pos == -1) // if no node is in Stack
			break; // break loop
		pCur = Stack[pos]; // Stack's popped in Node
		Stack[pos] = NULL; // store NULL in Stack
		pos--; // pos is substracted by 1
		cnt++; // cnt is added by 1
		pCur = pCur->GetRight(); // store pCur's rightnode in pCur
	}
	return cnt; // return count
}

void WordBST::SetZero_IN() // SetZero_IN function in WordBST
{
	WordNode * Stack[100] = { 0 }; // assign WordNode type's array named Stack for WordBST's storing WordNode
	int pos = -1; // assign pos for representing array's position
	WordNode * pCur = new WordNode; // assign pCur for storing WordBST's WordNode
	pCur = root; // store root in pCur
	while (1)
	{
		while (pCur)
		{
			Stack[++pos] = pCur; // Stack is pushed in pCur
			pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
		}
		if (pos == -1) // if no node is in Stack
			return; // break loop
		pCur = Stack[pos]; // Stack's popped in Node
		Stack[pos] = NULL; // store NULL in Stack
		pos--; // pos is substracted by 1 
		pCur->SetCount(0); // pCur's count is changed to 0
		pCur = pCur->GetRight(); // store pCur's rightnode in pCur
	}
}
