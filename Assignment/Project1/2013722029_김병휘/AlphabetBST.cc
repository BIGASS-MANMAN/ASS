#define _CRT_SECURE_NO_WARNINGS
#include "AlphabetBST.h"
#include "Queue.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;

	char initial[] = "PHXDLTZBFJNRVYACEGIKMOQSUW"; // Level order
	for (int i = 0; i < 26; i++) {
		AlphabetNode* node = new AlphabetNode();	// generate alphabet node
		node->SetAlphabet(initial[i]);				// set alphabet
		this->Insert(node);							// insert node
	}
}

AlphabetBST::~AlphabetBST()
{
	// delete from leaf nodes to root node
	char initial[] = "ACBEGFDIKJMONLHQSRUWVTYZXP";
	for (int i = 0; i < 26; i++) delete Search(initial[i]);
}

// run
void AlphabetBST::Insert(AlphabetNode * node)
{
	if (!root) // this node is first
	{
		root = node; // this node is root
		return;
	}
	else
	{
		AlphabetNode* newNode = root;

		for (;;)
		{
			if (newNode->GetAlphabet() <= node->GetAlphabet())			// this node is larger than current node
			{
				if (newNode->GetRight() == '\0')						// this node has no right child
				{
					newNode->SetRight(node);							// set this node as right child
					return;
				}
				else
				{
					newNode = newNode->GetRight();						// move right
					continue;
				}
			}
			else if (newNode->GetAlphabet() > node->GetAlphabet())		// this node is lower than current node
			{
				if (newNode->GetLeft() == '\0')							// this node has no left child
				{
					newNode->SetLeft(node);								// set this node as left child
					return;
				}
				else
				{
					newNode = newNode->GetLeft();						// move left
					continue;
				}
			}
			else
				return;
		}
	}
}

// PRINT
bool AlphabetBST::Print(char * order)
{
	if (WordCnt <= 0) return false; // word doesn't exist in tree
	else
	{
		char *alpha_order = new char[26 + 1]; // alphabet series of traversal order

		if (!strcmp(order, "R_PRE") || !strcmp(order, "I_PRE"))			// Preorder Traversal
		{
			strcpy(alpha_order, "PHDBACFEGLJIKNMOXTRQSVUWZY");			// copy order
		}
		else if (!strcmp(order, "R_IN") || !strcmp(order, "I_IN"))		// Inorder Traversal
		{
			strcpy(alpha_order, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");			// copy order
		}
		else if (!strcmp(order, "R_POST") || !strcmp(order, "I_POST"))	// Postorder Traversal
		{
			strcpy(alpha_order, "ACBEGFDIKJMONLHQSRUWVTYZXP");			// copy order
		}
		else if (!strcmp(order, "I_LEVEL"))								// Level order Traversal
		{
			strcpy(alpha_order, "PHXDLTZBFJNRVYACEGIKMOQSUW");			// copy order
		}
		else return false;												// it's not correct order

		ofstream output("log.txt", ios::app); // output file

		if (output.is_open()) // file is open well
		{
			// print the result with the following order
			output << "======== PRINT ========" << endl;
			for (int i = 0; i < 26; i++)
			{
				Search(alpha_order[i])->GetBST()->Print(order);
			}


//			output.close();
			delete alpha_order;
			return true;
		}
		else // file is not open
			return false;
	}
}

// LOAD, MOVE, TEST, SEARCH, UPDATE
AlphabetNode* AlphabetBST::Search(char alpabet)
{
	AlphabetNode* temp = root;

	char capital = alpabet; // make capital

	if ('a' <= capital && capital <= 'z') // is lower character
		capital -= 'a' - 'A'; // convert
	else if ('A' <= capital && capital <= 'Z'); // is capital
	else
		return '\0'; // it's not alphabet

	for (; temp;) // until finding node
	{
		if (temp->GetAlphabet() < capital) // alphabet is more higher
			temp = temp->GetRight(); // go to the right
		else if (temp->GetAlphabet() > capital) // alphabet is more lower
			temp = temp->GetLeft(); // go to the left
		else // find the node
			return temp; // return node
	}

	return '\0'; // cannot find the node
}

// SAVE
bool AlphabetBST::Save()
{
	ofstream flush("memorizing_word.txt");					// for renew save file
	flush.close();

	if (!root) return false;								// bst is empty
	AlphabetNode *top = 0, *lastRight = 0, *p, *q, *r, *r1;	// deepest node, highest parent node of top that has two children

	p = q = root;											// start from root

	for (;;)
	{
		for (;;)											// start to go down
		{
			if ((!p->GetLeft()) && (!p->GetRight()))		// p is leaf node
			{
				p->GetBST()->Save();						// save words
				break;										// start to go up
			}
			if (!p->GetLeft())								// p has only right child
			{
				p->GetBST()->Save();						// save words
				r = p->GetRight(); p->SetRight(q);			// make current node's right pointer pointing its parent node
				q = p; p = r;								// go down to this right child
			}
			else											// p has only left child
			{
				p->GetBST()->Save();						// save words
				r = p->GetLeft(); p->SetLeft(q);			// make current node's left pointer pointing its parent node
				q = p; p = r;								// go down to this left child
			}
		}

		AlphabetNode* av = p;								// deepeset node
		for (;;)
		{
			if (p == root) return true;						// traversal is done
			if (!q->GetLeft())								// parent node has only right child
			{
				r = q->GetRight(); q->SetRight(p);			// restore link
				p = q; q = r;								// go up to parent node
			}
			else if (!q->GetRight())						// parent node has only left child
			{
				r = q->GetLeft(); q->SetLeft(p);			// restore link
				p = q; q = r;								// go up to parent node
			}
			else if (q == lastRight)						// left and right sub tree traversal is done
			{
				r = top; lastRight = r->GetLeft();			// set lastRight node as its parent node
				top = r->GetRight();						// set top node as the deepest node of the parent node of lastRight
				r->SetLeft(0); r->SetRight(0);				// restore link, i.e. it has no child originally
				r = q->GetRight(); q->SetRight(p);			// restore link
				p = q; q = r;								// go up to its parent node
			}
			else											// only left sub tree traversal is done
			{
				av->SetLeft(lastRight); av->SetRight(top);	// set the left child of the deepest node as previous lastRight and right as top
				top = av; lastRight = q;					// update new top and lastRight, i.e. child lastRight and its deepest node
				r = q->GetLeft(); q->SetLeft(p);			// restore link
				r1 = q->GetRight(); q->SetRight(r);			// move to the right sub tree
				p = r1;										// set current node as the first node of the right sub tree
				break;										// restart to go down
			}
		}
	}
}