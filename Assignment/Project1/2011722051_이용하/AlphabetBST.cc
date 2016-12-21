#include "AlphabetBST.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

AlphabetBST::AlphabetBST() // AlphabetBST's constructor
{
	root = '\0';
	WordCnt = 0;
}


AlphabetBST::~AlphabetBST() // AlphabetBST's destructor
{
	AlphabetNode * Stack[100] = { 0 }; // assign AlphabetNode type's array named Stack for AlphabetBST's storing WordNode
	int pos = -1; // assign pos for representing array's position
	AlphabetNode * pCur = new AlphabetNode; // assign pCur for storing AlphabetBST's WordNode
	pCur = root; // store root in pCur
	int sig = 0; // assign sig for signal in postorder
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
		if (pos == -1) // if Stack is NULL
			return; // finish to operate while loop
		pCur = Stack[pos]; // Stack is popped to pCur
		if (pCur->GetRight() != NULL && pCur->GetCount() == 0) // if the node has a right node
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

void AlphabetBST::Insert(AlphabetNode * node) // AlphabetBST's Insert function
{
	AlphabetNode * pNew = new AlphabetNode;  // assign pNew for storing AlphabetBST's WordNode
	pNew->SetAlphabet(node->GetAlphabet()); // store Alphabet in pNew 
	pNew->SetLeft(NULL);
	pNew->SetRight(NULL);
	pNew->SetCount(0);

	if (root == NULL)
		root = pNew; // root is pNew
	else
	{
		AlphabetNode * pCur = new AlphabetNode; // assign pCur for storing AlphabetBST's WordNode
		pCur = root;
		while (1)
		{
			if (pCur->GetAlphabet() >= pNew->GetAlphabet()) // if pCur's alphabet is bigger than pNew's alphabet
			{
				if (pCur->GetLeft() == NULL) // if pCur's leftnode is not presented
				{
					pCur->SetLeft(pNew); // pCur's leftnode is pNew
					break;
				}
				else
				{
					pCur = pCur->GetLeft(); // pCur is pCur's leftnode
					continue;
				}
			}
			else if (pCur->GetAlphabet() < pNew->GetAlphabet()) // if pCur's alphabet is smaller than pNew's alphabet
			{
				if (pCur->GetRight() == NULL) // if pCur's rightnode is not presented
				{
					pCur->SetRight(pNew); // pCur's rightnode is pNew
					break;
				}
				else
				{
					pCur = pCur->GetRight(); // pCur is pCur's rightnode
					continue;
				}
			}
		}
	}
}

bool AlphabetBST::Print(char * order) // print function in AlphabetBST
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
	else
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

AlphabetNode * AlphabetBST::Search(char alphabet)
{
	AlphabetNode * pCur = new AlphabetNode;
	pCur = root;
	if (root == NULL)
		return 0;
	else
	{
		while (pCur != NULL)
		{
			if (alphabet == pCur->GetAlphabet()) // found
				return pCur;
			else
			{
				if (alphabet<pCur->GetAlphabet()) // word < node
				{
					pCur = pCur->GetLeft(); // move to left pointer
					continue;
				}
				else if (alphabet>pCur->GetAlphabet()) // word > node
				{
					pCur = pCur->GetRight(); // move to right pointer
					continue;
				}
			}
		}
		return 0;
	}
}

bool AlphabetBST::Save()
{
	R_PRE("SAVE"); // SAVE order
	return 1;
}

void AlphabetBST::Visit(AlphabetNode * Node, char * order)
{
	if (strcmp(order, "SAVE") == 0) // SAVE order
		Node->GetBST()->Save();
	else // print
		Node->GetBST()->Print(order);
}

void AlphabetBST::R_PRE(char * order) // recursive pre order
{
	R_PRE(root, order);
}
void AlphabetBST::R_PRE(AlphabetNode * Node, char * order) // recursive pre order
{
	if (Node)
	{
		Visit(Node, order); // visit
		R_PRE(Node->GetLeft(), order); // input left node in R_PRE
		R_PRE(Node->GetRight(), order); // input right node In R_PRE
	}
}

void AlphabetBST::R_POST(char * order) // recursive post order
{
	R_POST(root, order);
}
void AlphabetBST::R_POST(AlphabetNode * Node, char * order) // recursive post order
{
	if (Node)
	{
		R_POST(Node->GetLeft(), order); // input left node in R_POST
		R_POST(Node->GetRight(), order); // input right node In R_POST
		Visit(Node, order); // visit
	}
}

void AlphabetBST::R_IN(char * order) // recursive inorder
{
	R_IN(root, order);
}
void AlphabetBST::R_IN(AlphabetNode * Node, char * order) // recursive inorder
{
	if (Node)
	{
		R_IN(Node->GetLeft(), order); // input left node in R_IN
		Visit(Node, order); // visit
		R_IN(Node->GetRight(), order); // input right node in R_IN
	}
}

void AlphabetBST::I_LEVEL(char * order) // iterative inorder
{
	AlphabetNode * Queue[100] = { 0 };
	int pos = 0;
	int front = 0;
	if (root == NULL)
		return;
	AlphabetNode * Node = new AlphabetNode;
	Node = root; // store root in Node
	while (Node)
	{
		Visit(Node, order); // visit
		if (Node->GetLeft())
			Queue[pos++] = Node->GetLeft(); // store Node's leftnode in Queue
		if (Node->GetRight())
			Queue[pos++] = Node->GetRight(); // store Node's rightnode in Queue
		if (pos == front) // no node in the queue
			return;
		Node = Queue[front]; // pop
		Queue[front] = NULL;
		front++; // add 1 to front
	}
}

void AlphabetBST::I_PRE(char * order) // iterative pre order
{
	AlphabetNode * Stack[100] = { 0 };
	int pos = -1;
	if (root == NULL)
		return;
	AlphabetNode * pCur = new AlphabetNode;
	pCur = root; // store root in pCur
	Stack[++pos] = pCur; // push in Stack array
	while (pos != -1)
	{
		pCur = Stack[pos]; // pop
		Visit(pCur, order); // visit
		Stack[pos] = NULL;
		pos--;
		if (pCur->GetRight())
			Stack[++pos] = pCur->GetRight(); // store pCur's right node
		if (pCur->GetLeft())
			Stack[++pos] = pCur->GetLeft(); // store pCur's left node
	}
}

void AlphabetBST::I_IN(char * order) // iterative inorder
{
	AlphabetNode * Stack[100] = { 0 };
	int pos = -1;
	if (root == NULL)
		return;
	AlphabetNode * pCur = new AlphabetNode;
	pCur = root;
	while (1)
	{
		while (pCur)
		{
			Stack[++pos] = pCur; // store pCur in Stack
			pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
		}
		if (pos == -1) // if no node in stack
			return;
		pCur = Stack[pos]; // Stack is popped in pCur 
		Stack[pos] = NULL;
		pos--;
		Visit(pCur, order); // visit
		pCur = pCur->GetRight(); // store pCur's rightnode in pCur
	}
}

void AlphabetBST::I_POST(char * order) // iterative post order
{
	AlphabetNode * Stack[100] = { 0 };
	int pos = -1;
	if (root == NULL)
		return;
	AlphabetNode * pCur = new AlphabetNode;
	pCur = root;
	int sig = 0;
	while (pCur)
	{
		Stack[++pos] = pCur; // Stack is pushed in pCur
		pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
	}
	while (1)
	{
		if (sig == 1)
		{
			while (pCur)
			{
				Stack[++pos] = pCur; // Stack is pushed in pCur
				pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
			}
		}
		if (pos == -1) // if no node is in WordBST
			return;
		pCur = Stack[pos]; // Stack is popped is in pCur
		if (pCur->GetRight() != NULL && pCur->GetCount() == 0) // if pCur has a rightnode
		{
			pCur->SetCount(1); // pCur's count is changed to 1
			pCur = pCur->GetRight(); // store pCur's rightnode in pCur
			sig = 1;
			continue;
		}
		else
		{
			Stack[pos] = NULL; // store NULL in Stack
			pos--;
			Visit(pCur, order); // visit
			sig = 0;
			continue;
		}
	}
	SetZero_IN();
}

int AlphabetBST::NULL_BST() // NULL_BST function in AlphabetBST
{
	int num = 0;
	AlphabetNode * Stack[100] = { 0 };
	int pos = -1;
	AlphabetNode * pCur = new AlphabetNode;
	pCur = root;
	while (1)
	{
		while (pCur)
		{
			Stack[++pos] = pCur; // Stack is pushed in pCur
			pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
		}
		if (pos == -1) // if no node is in AlphabetBST
			break;
		pCur = Stack[pos]; // Stack is popped is in pCur
		Stack[pos] = NULL;
		pos--;
		if (pCur->GetBST()->root != NULL) // WordBST's root is not NULL
			num = 1;
		pCur = pCur->GetRight(); // store pCur's rightnode in pCur
	}
	if (num == 0)
		return 0;
	else
		return 1;
}

void AlphabetBST::SetWordCount() // SetWordCount function in AlphabetBST
{
	AlphabetNode * Stack[100] = { 0 };
	WordCnt = 0;
	int pos = -1;
	AlphabetNode * pCur = new AlphabetNode;
	pCur = root;
	while (1)
	{
		while (pCur)
		{
			Stack[++pos] = pCur; // Stack is pushed in pCur
			pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
		}
		if (pos == -1) // if no node is in Stack
			return;
		pCur = Stack[pos]; // Stack's popped in Node
		Stack[pos] = NULL;
		pos--;
		WordCnt += pCur->GetBST()->GetWordCount(); // sum of all WordBST's wordcount
		pCur = pCur->GetRight(); // store pCur's rightnode in pCur
	}
}

void AlphabetBST::SetZero_IN() // SetZero_IN function in AlphabetBST
{
	AlphabetNode * Stack[100] = { 0 };
	int pos = -1;
	AlphabetNode * pCur = new AlphabetNode;
	pCur = root;
	while (1)
	{
		while (pCur)
		{
			Stack[++pos] = pCur; // Stack is pushed in pCur
			pCur = pCur->GetLeft(); // store pCur's leftnode in pCur
		}
		if (pos == -1) // if no node is in Stack
			return;
		pCur = Stack[pos]; // Stack's popped in Node
		Stack[pos] = NULL; // store NULL in Stack
		pos--;
		pCur->SetCount(0); // pCur's count is changed to 0
		pCur = pCur->GetRight(); // store pCur's rightnode in pCur
	}
}
