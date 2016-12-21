#include "AlphabetBST.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string.h>

using namespace std;

// Constructor of AlphabetBST
AlphabetBST::AlphabetBST()
{
	// Initialize root and WordCnt
	root = '\0'; // to NULL
	WordCnt = 0; // to 0
	
	// Insert AlphabetNode in the following order P->H-> ... ->U->W
	char* p = "PHXDLTZBFJNRVYACEGIKMOQSUW";
	while (*p != NULL) { // Loop until last alphabet
		AlphabetNode* node = new AlphabetNode; // Create node for new AlphabetNode 
		node->SetAlphabet(*p);				   // And set node's alphabet to p
		Insert(node); // Insert node
		p++; // move to next alphabet
	}
}

// Destructor of AlphabetBST
AlphabetBST::~AlphabetBST()
{ // Driver
	deleteTree(root);
}

void AlphabetBST::deleteTree(AlphabetNode * currentNode)
{ // WorkHorse
	// delete all nodes by postOrder
	if (currentNode)
	{
		deleteTree(currentNode->GetLeft()); 
		deleteTree(currentNode->GetRight());
		delete currentNode;
	}
}

// Insert new AlphabetNode
void AlphabetBST::Insert(AlphabetNode * node)
{
	// Start from root
	AlphabetNode *currentNode = root;
	AlphabetNode *parentNode = currentNode;

	// If tree is empty
	if (!root) {
		root = node; // Set root to node 
		return;		 // and exit func
	}

	// Move currentNode to right position
	while (currentNode) {
		parentNode = currentNode; // save parent node of currentNode
		if (currentNode->GetAlphabet() > node->GetAlphabet())
			currentNode = currentNode->GetLeft();
		else
			currentNode = currentNode->GetRight();
	}
	// Insert node
	if (parentNode->GetAlphabet() > node->GetAlphabet())
		parentNode->SetLeft(node);
	else
		parentNode->SetRight(node);
}

// Print Tree in order
bool AlphabetBST::Print(char * order, ofstream& logfile)
{
	int i; // value for handles order
	for (i = 0; i < sizeof(printOrders) / sizeof(char*); i++) // check all orders
		if (!strcmp(printOrders[i], order))
			switch (i) {
			case 0: // R_PRE
				preOrder(root,order, logfile);
				return false;
			case 1: // I_PRE
				NR_preOrder(order, logfile);
				return false;
			case 2: // R_IN
				inOrder(root, order, logfile);
				return false;
			case 3: // I_IN
				NR_inOrder(order, logfile);
				return false;
			case 4: // R_POST
				postOrder(root, order, logfile);
				return false;
			case 5: // I_POST
				NR_postOrder(order, logfile);
				return false;
			case 6: // I_LEVEL
				levelOrder(order, logfile);
				return false;
			}
	// If nothing matched return true;
	return true;
}

// Search specific AlphabetNode which equals word passed by parameter
AlphabetNode * AlphabetBST::Search(char alpabet)
{
	// Start from root;
	AlphabetNode* currentNode = root;
	alpabet = toupper(alpabet);
	while (currentNode) {
		// compare currentNode's Word and word

		if (currentNode->GetAlphabet() == alpabet) // if same
			return currentNode;					   // then return it;
		else if (currentNode->GetAlphabet() < alpabet) // else if currentNode's alphabet smaller than alphabet 
			currentNode = currentNode->GetRight();	   // then currentNode goes right subtree
		else										   // else
			currentNode = currentNode->GetLeft();	   // then currentNode goes left subtree
	}
	return NULL; // If there are no AlphaNode which equals alphabet then return NULL;
}

void AlphabetBST::Save(AlphabetNode * node)
{
	ofstream memorizing("memorizing_word.txt");

	stack<AlphabetNode*> s; // Stack for AlphabetNodes
	AlphabetNode* currentNode = node; // Start from root

									  // Loop until traversal all nodes
	while (1) {
		while (currentNode) {
			// Visit( Call the node's Print func with order) currentNode
			currentNode->GetBST()->Save(memorizing);

			// If currentNode has right child
			if (currentNode->GetRight())
				s.push(currentNode->GetRight()); // then push all rightmost nodes

			currentNode = currentNode->GetLeft(); // currentNode goes left subtree
		}
		// If stack is empty then exit func;
		if (s.empty()) return;

		// currentNode is top of stack
		currentNode = s.top();
		s.pop(); // and pop stack
	}

	memorizing.close();
}

// Traversal tree preOrder recursively  
void AlphabetBST::preOrder(AlphabetNode * currentNode, char * order, ofstream& logfile)
{
	// Visit parent->left child->right child
	if (currentNode) {
		currentNode->GetBST()->Print(order, logfile);
		preOrder(currentNode->GetLeft(), order, logfile);
		preOrder(currentNode->GetRight(), order, logfile);
	}
}

// Traversal tree preOrder iteratively
void AlphabetBST::NR_preOrder(char * order, ofstream& logfile)
{
	stack<AlphabetNode*> s; // Stack for AlphabetNodes
	AlphabetNode* currentNode = root; // Start from root

	// Loop until traversal all nodes
	while (1) {
		while (currentNode) {
			// Visit( Call the node's Print func with order) currentNode
			currentNode->GetBST()->Print(order, logfile);

			// If currentNode has right child
			if (currentNode->GetRight())
				s.push(currentNode->GetRight()); // then push all rightmost nodes
			
			currentNode = currentNode->GetLeft(); // currentNode goes left subtree
		}
		// If stack is empty then exit func;
		if (s.empty()) return;

		// currentNode is top of stack
		currentNode = s.top();
		s.pop(); // and pop stack
	}
}

// Traversal tree inOrder recursively
void AlphabetBST::inOrder(AlphabetNode * currentNode, char * order, ofstream& logfile)
{
	// Visit left child->parent->right child
	if (currentNode) {
		inOrder(currentNode->GetLeft(), order, logfile);
		currentNode->GetBST()->Print(order, logfile);
		inOrder(currentNode->GetRight(), order, logfile);
	}
}

// Traversal tree inOrder iteratively
void AlphabetBST::NR_inOrder(char * order, ofstream& logfile)
{
	stack<AlphabetNode*> s; // Stack for AlphabetNodes
	AlphabetNode* currentNode = root; // Start from root

	// Loop until traversal all nodes
	while (1) {
		// Push all leftmost nodes
		while (currentNode) {
			s.push(currentNode);
			currentNode = currentNode->GetLeft();
		}
		// If stack is empty then exit func;
		if (s.empty()) return;

		// currentNode is top of stack
		currentNode = s.top();
		s.pop(); // and pop stack

		// Visit( Call the node's Print func with order) currentNode
		currentNode->GetBST()->Print(order, logfile);
		currentNode = currentNode->GetRight(); // currentNode goes right subtree
	}
}

// Traversal tree postOrder recursively 
void AlphabetBST::postOrder(AlphabetNode * currentNode, char * order, ofstream& logfile)
{
	// Visit left child->right child->parent
	if (currentNode) {
		postOrder(currentNode->GetLeft(), order, logfile);
		postOrder(currentNode->GetRight(), order, logfile);
		currentNode->GetBST()->Print(order, logfile);
	}
}

// Traversal tree postOrder iteratively 
void AlphabetBST::NR_postOrder(char * order, ofstream& logfile)
{
	stack<AlphabetNode*> s; // Stack for WordNodes
	AlphabetNode* currentNode = root; // Start from root
	
	// Loop until traversal all nodes
	do {
		// push all leftmost nodes & each node's right child
		while (currentNode) {
			if (currentNode->GetRight())
				s.push(currentNode->GetRight());
			s.push(currentNode);
			currentNode = currentNode->GetLeft();
		}
		// currentNode is top of stack
		currentNode = s.top();
		s.pop(); // and pop stack

		// if currentNode isn't NULL and s isn't empty and top of s equals currentNode's right child
		if (currentNode->GetRight() && !s.empty() && s.top() == currentNode->GetRight()) {
			// then replace top of s with currentNode
			s.pop();
			s.push(currentNode);

			currentNode = currentNode->GetRight(); // currentNode goes right subtree
		}
		else {
			// Visit( Call the node's Print func with order) currentNode
			currentNode->GetBST()->Print(order, logfile);
			currentNode = NULL; // Set currentNode to NULL
		}
	} while (!s.empty());
}

// Traversal tree levelOrder iteratively 
void AlphabetBST::levelOrder(char * order, ofstream& logfile)
{
	queue<AlphabetNode*> q; // Queue for AlphabetNodes
	AlphabetNode *currentNode = root; // Stack for WordNodes

	// Loop until traversal all nodes
	while (currentNode) {

		// Visit( Call the node's Print func with order) currentNode
		currentNode->GetBST()->Print(order,logfile);

		// If currentNode has children then push them to q
		if (currentNode->GetLeft()) q.push(currentNode->GetLeft());
		if (currentNode->GetRight()) q.push(currentNode->GetRight());
		
		// If stack is empty then exit func;
		if (q.empty()) return;
		
		// currentNode is front of queue
		currentNode = q.front();
		q.pop(); // and pop stack
	}
}
