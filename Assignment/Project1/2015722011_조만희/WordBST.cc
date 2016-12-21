#include "WordBST.h"

#include <iostream>
#include <fstream>
#include <stack>
#include <string.h>
#include "Queue.h"

using namespace std;

// Constructor of WordBST
WordBST::WordBST()
{
	// Initialize root to NULL
	root = '\0';
}

// Destructor of WordBST
WordBST::~WordBST()
{
	// Delete Tree
	deleteTree(root);
}

// Recursive destroyer of Tree
void WordBST::deleteTree(WordNode * currentNode)
{
	// Delete all node by postOrder
	// Because in postOrder, deleted node doesn't affect other node
	if (currentNode)
	{
		deleteTree(currentNode->GetLeft());
		deleteTree(currentNode->GetRight());
		delete currentNode;
	}
}

// Insert WordNode to Tree
void WordBST::Insert(WordNode * node)
{
	// Declare current & parent nodes and set to root
	WordNode *currentNode = root;
	WordNode *parentNode = currentNode;

	if (!root) { // if Tree is empty
		root = node; // Set tree to node 
		return;
	}

	// Move currentNode to right position 
	while (currentNode) {
		parentNode = currentNode;
		if (strcmp(currentNode->GetWord(), node->GetWord()) == 1)
			currentNode = currentNode->GetLeft();
		else
			currentNode = currentNode->GetRight();
	}

	// Insert new WordNode
	if (strcmp(parentNode->GetWord(), node->GetWord()) == 1)
		parentNode->SetLeft(node);
	else
		parentNode->SetRight(node);
}

// Delete WordNode
WordNode * WordBST::Delete(char * word)
{
	// Set deleteNode to WordNode which equals word passed by parameter
	WordNode* deleteNode = Search(word);
	// currentNode is deleteNode;
	WordNode* currentNode = deleteNode;

	// Find node which will replace deletenode
	if (currentNode->GetLeft()) // If deleteNode has left child
		while (currentNode->GetLeft())
			currentNode = currentNode->GetLeft(); // Then curretNode is max value in left subtree
	else if (currentNode->GetRight()) // Else if deleteNode has only right child
		while (currentNode->GetRight())
			currentNode = currentNode->GetRight(); // Then currentNode is min value in right subtree

	// Replace data & delete currentNode
	deleteNode->SetWord(currentNode->GetWord());
	deleteNode->SetMean(currentNode->GetMean());
	currentNode = NULL;
	
	// Return replaced node
	return deleteNode;
}

// Search specific WordNode which equals word passed by parameter
WordNode * WordBST::Search(char * word)
{
	// Start from root;
	WordNode* currentNode = root;
	int cmp; // value for compare
	while (currentNode) {
		cmp = strcmp(currentNode->GetWord(), word); // compare currentNode's Word and word
		if (!cmp) // if same 
			return currentNode;					   // then return it;
		else if (cmp < 0)						   // else if currentNode's Word smaller than word 
			currentNode = currentNode->GetRight(); // then currentNode goes right subtree
		else									   // else
			currentNode = currentNode->GetLeft();  // then currentNode goes left subtree
	}
	return NULL; // If there are no AlphaNode which equals alphabet then return NULL;
}

// Print Tree in order
bool WordBST::Print(char * order, ofstream& logfile)
{
	int i; // value for handles order
	for (i = 0; i < sizeof(printOrders) / sizeof(char*); i++) // check all orders
		if (!strcmp(printOrders[i], order))
			switch (i) {
			case 0: // R_PRE
				preOrder(root ,logfile);
				return false;
			case 1: // I_PRE
				NR_preOrder(logfile);
				return false;
			case 2: // R_IN
				inOrder(root, logfile);
				return false;
			case 3: // I_IN
				NR_inOrder(logfile);
				return false;
			case 4: // R_POST
				postOrder(root, logfile);
				return false;
			case 5: // I_POST
				NR_postOrder(logfile);
				return false;
			case 6: // I_LEVEL
				levelOrder(logfile);
				return false;
			}
	// If nothing matched return true;
	return true;
}

void WordBST::Save(std::ofstream& memorizing)
{
	
	stack<WordNode*> s; // Stack for WordNodes
	WordNode* currentNode = root; // Start from root

								  // Loop until traversal all nodes
	while (1) {
		while (currentNode) {
			// Visit( Print Word & Mean) currentNode
			memorizing << currentNode->GetWord() << "\t" << currentNode->GetMean() << endl;
			
			// If currentNode has right child
			if (currentNode->GetRight())
				s.push(currentNode->GetRight());  // then push all rightmost nodes

			currentNode = currentNode->GetLeft(); // currentNode goes left subtree
		}
		// If stack is empty then exit func;
		if (s.empty()) {  return; }

		// currentNode is top of stack
		currentNode = s.top();
		s.pop(); // and pop stack
	}
	
}

// Traversal tree preOrder recursively 
void WordBST::preOrder(WordNode* currentNode, ofstream& logfile)
{
	
	// Visit parent->left child->right child
	if (currentNode) {
		cout << currentNode->GetWord()  << "\t" << currentNode->GetMean() << endl;
		logfile << currentNode->GetWord() << "\t" << currentNode->GetMean() << endl;
		
		preOrder(currentNode->GetLeft(), logfile);
		preOrder(currentNode->GetRight(), logfile);
	}
}

// Traversal tree preOrder iteratively 
void WordBST::NR_preOrder(ofstream& logfile)
{
	stack<WordNode*> s; // Stack for WordNodes
	WordNode* currentNode = root; // Start from root
	
	// Loop until traversal all nodes
	while (1) {
		while (currentNode) {
			// Visit( Print Word & Mean) currentNode
			cout << currentNode->GetWord()  << "\t" << currentNode->GetMean() << endl;
			logfile << currentNode->GetWord() << "\t" << currentNode->GetMean() << endl;
			// If currentNode has right child
			if (currentNode->GetRight())
				s.push(currentNode->GetRight());  // then push all rightmost nodes

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
void WordBST::inOrder(WordNode* currentNode, ofstream& logfile)
{
	// Visit left child->parent->right child
	if (currentNode) {
		preOrder(currentNode->GetLeft(), logfile);
		cout << currentNode->GetWord()  << "\t" << currentNode->GetMean() << endl;
		logfile << currentNode->GetWord() << "\t" << currentNode->GetMean() << endl;
		preOrder(currentNode->GetRight(), logfile);
	}
}

// Traversal tree inOrder iteratively
void WordBST::NR_inOrder(ofstream& logfile)
{
	stack<WordNode*> s; // Stack for WordNodes
	WordNode* currentNode = root; // Start from root
	
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

		// Visit( Print Word & Mean) currentNode
		cout << currentNode->GetWord()  << "\t" << currentNode->GetMean() << endl;
		logfile << currentNode->GetWord() << "\t" << currentNode->GetMean() << endl;
		
		currentNode = currentNode->GetRight(); // currentNode goes right subtree
	}
}

// Traversal tree postOrder recursively 
void WordBST::postOrder(WordNode* currentNode, ofstream& logfile)
{
	// Visit left child->right child->parent
	if (currentNode) {
		postOrder(currentNode->GetLeft(),logfile);
		postOrder(currentNode->GetRight(), logfile);
		cout << currentNode->GetWord()  << "\t" << currentNode->GetMean() << endl;
		logfile << currentNode->GetWord() << "\t" << currentNode->GetMean() << endl;
	}
}

// Traversal tree postOrder iteratively 
void WordBST::NR_postOrder(ofstream& logfile)
{
	stack<WordNode*> s; // Stack for WordNodes
	WordNode* currentNode = root; // Start from root

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
			// Visit( Print Word & Mean) currentNode
			cout << currentNode->GetWord()  << "\t" << currentNode->GetMean() << endl;
			logfile << currentNode->GetWord() << "\t" << currentNode->GetMean() << endl;
			currentNode = NULL; // Set currentNode to NULL
		}
	} while (!s.empty()); 
}

// Traversal tree levelOrder iteratively 
void WordBST::levelOrder(ofstream& logfile)
{
	Queue q; // Queue for WordNodes
	WordNode *currentNode = root; // Stack for WordNodes

	// Loop until traversal all nodes
	while (currentNode) {
		// Visit( Print Word & Mean) currentNode
		cout << currentNode->GetWord()  << "\t" << currentNode->GetMean() << endl;
		logfile << currentNode->GetWord() << "\t" << currentNode->GetMean() << endl;
		
		// If currentNode has children then push them to q
		if (currentNode->GetLeft()) q.Push(currentNode->GetLeft());
		if (currentNode->GetRight()) q.Push(currentNode->GetRight());

		// If stack is empty then exit func;
		if (q.Empty()) return;

		// currentNode is front of queue
		currentNode = q.Front();
		q.Pop(); // and pop stack
	}
}

