#include "WordBST.h"
#include "Queue.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

WordBST::WordBST()
{
	root = '\0';
}

WordBST::~WordBST()
{
	// Delete root node until tree is empty
	for (; root != '\0';) delete this->Delete(root->GetWord());
}

// LOAD, MOVE
void WordBST::Insert(WordNode * node)
{

	if (!root) // tree is empty
	{
		root = node; // this node becomes root
		return;
	}
	else
	{
		WordNode* newNode = root;

		for (;;) {
			if (strcmp(newNode->GetWord(), node->GetWord()) <= 0)			// this node is larger than current node
			{
				if (newNode->GetRight() == '\0')							// this node has no right child
				{
					newNode->SetRight(node);								// set this node as right child
					return;
				}
				else
				{
					newNode = newNode->GetRight();							// move right
					continue;
				}
			}
			else if (strcmp(newNode->GetWord(), node->GetWord()) > 0)		// this node is lower than current node
			{
				if (newNode->GetLeft() == '\0')								// this node has no left child
				{
					newNode->SetLeft(node);									// set this node as left child
					return;
				}
				else
				{
					newNode = newNode->GetLeft();							// move left
					continue;
				}
			}
			else
				return;
		}
	}
}

// TEST
WordNode* WordBST::Delete(char * word)
{
	WordNode *p = root, *q = 0;									// p == current node, q == parent node
	while (p && strcmp(word, p->GetWord()))						// until finding node
	{
		q = p;													// update previous node
		if (strcmp(word, p->GetWord()) < 0) p = p->GetLeft();	// go to the left if this word is bigger
		else p = p->GetRight();									// go to the right if this word is lower
	}
	if (!p) return '\0';										// cannot find the node

	if (p->GetLeft() == 0 && p->GetRight() == 0)				// in case p is left node
	{
		if (q == 0) root = 0;									// root = 0 if p is root and leaf node
		else if (q->GetLeft() == p) q->SetLeft(0);				// if p is left node of q
		else q->SetRight(0);									// if p is right node of q
		return p;
	}

	if (p->GetLeft() == 0)										// in case p only has right child
	{
		if (q == 0) root = p->GetRight();						// next root is the right child of previous root
		else if (q->GetLeft() == p) q->SetLeft(p->GetRight());	// if p is the left child of q, q points what p did on right
		else q->SetRight(p->GetRight());						// if p is the right child of q, q points what p did on left
		return p;												// return node
	}

	if (p->GetRight() == 0)										// in case p only has left child
	{
		if (q == 0) root = p->GetLeft();						// next root is the left child of previous root
		else if (q->GetLeft() == p) q->SetLeft(p->GetLeft());	// if p is the left child of q, q points what p did on left
		else q->SetRight(p->GetLeft());							// if p is the right child of q, q points what p did on right
		return p;												// return node
	}

																// p has left and right child, find the biggest node in left sub tree
	WordNode *prevprev = p, *prev = p->GetLeft(),				// prevprev: parent node of delete node
		*curr = p->GetLeft()->GetRight();						// prev: delete node, curr: child node of delete node

	while (curr)												// update prevprev, prev, curr
	{
		prevprev = prev;
		prev = curr;
		curr = curr->GetRight();
	}

	// curr is 0, prev is the node to be deleted, prevprev is prev's
	// parent, prev->leftChild is 0

	WordNode *delNode = new WordNode();							// node for return
	delNode->SetWord(p->GetWord());								// set word
	delNode->SetMean(p->GetMean());								// set mean

	p->SetWord(prev->GetWord());								// copy node's word in delete node
	p->SetMean(prev->GetMean());								// copy node's mean in delete node
	if (prevprev == p) prevprev->SetLeft(prev->GetLeft());		// if parent's left child has no right child, parent points what child did on right
	else prevprev->SetRight(prev->GetLeft());					// else, parent points what child did on right
	delete prev;												// delete the biggest node in left sub tree
	return delNode;												// return delete node
}

// ADD, TEST, SEARCH, UPDATE
WordNode* WordBST::Search(char * word)
{
	if (!root) return '\0';									// tree is empty
	else
	{
		WordNode* temp = root;								// from root,

		for (; temp != '\0';) {								// until temp is not NULL
			if (strcmp(temp->GetWord(), word) < 0)			// the word is higher
				temp = temp->GetRight();					// go to the right
			else if (strcmp(temp->GetWord(), word) > 0)		// the word is lower
				temp = temp->GetLeft();						// go to the left
			else
				return temp;								// find and return node
		}

		return '\0';										// cannot find the node
	}
}

/* ***************************************************************************** */
bool Print_R_PRE(WordNode* node)
{
	ofstream output("log.txt", ios::app);

	if (output.is_open()) // file is open
	{
		if (!node)
			return true; // escape condition
		else {
			output << node->GetWord() << " " << node->GetMean() << endl;	// print word and mean
			Print_R_PRE(node->GetLeft());									// print left sub tree
			Print_R_PRE(node->GetRight());									// print right sub tree

			output.close();													// file close
			return true;
		}
	}
	else
		return false;
}

bool Print_I_PRE(WordNode* root)
{
	ofstream output("log.txt", ios::app);										// output file

	if (output.is_open())														// file is open
	{
		if (!root)																// tree is empty
		{
			output.close();														// output close
			return false;
		}
		WordNode *top = 0, *lastRight = 0, *p, *q, *r, *r1;						// deepest node, highest parent node of top that has two children

		p = q = root;															// start from root

		for (;;)
		{
			for (;;)															// start to go down
			{
				if ((!p->GetLeft()) && (!p->GetRight()))						// p is leaf node
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					break;														// start to go up
				}
				if (!p->GetLeft())												// p has only right child
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					r = p->GetRight(); p->SetRight(q);							// make current node's right pointer pointing its parent node
					q = p; p = r;												// go down to this right child
				}
				else															// p has only left child
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					r = p->GetLeft(); p->SetLeft(q);							// make current node's left pointer pointing its parent node
					q = p; p = r;												// go down to this left child
				}
			}

			WordNode* av = p;													// deepeset node
			for (;;)
			{
				if (p == root)													// traversal is done
				{
					output.close();												// output close
					return true;
				}
				if (!q->GetLeft())												// parent node has only right child
				{
					r = q->GetRight(); q->SetRight(p);							// restore link
					p = q; q = r;												// go up to parent node
				}
				else if (!q->GetRight())										// parent node has only left child
				{
					r = q->GetLeft(); q->SetLeft(p);							// restore link
					p = q; q = r;												// go up to parent node
				}
				else if (q == lastRight)										// left and right sub tree traversal is done
				{
					r = top; lastRight = r->GetLeft();							// set lastRight node as its parent node
					top = r->GetRight();										// set top node as the deepest node of the parent node of lastRight
					r->SetLeft(0); r->SetRight(0);								// restore link, i.e. it has no child originally
					r = q->GetRight(); q->SetRight(p);							// restore link
					p = q; q = r;												// go up to its parent node
				}
				else															// only left sub tree traversal is done
				{
					av->SetLeft(lastRight); av->SetRight(top);					// set the left child of the deepest node as previous lastRight and right as top
					top = av; lastRight = q;									// update new top and lastRight, i.e. child lastRight and its deepest node
					r = q->GetLeft(); q->SetLeft(p);							// restore link
					r1 = q->GetRight(); q->SetRight(r);							// move to the right sub tree
					p = r1;														// set current node as the first node of the right sub tree
					break;														// restart to go down
				}
			}
		}
	}
	else
		return false;
}

bool Print_R_IN(WordNode* node)
{
	ofstream output("log.txt", ios::app);

	if (output.is_open()) // fhile is open
	{
		if (!node)
			return true; // escape condition
		else {
			Print_R_IN(node->GetLeft());									// print left sub tree
			output << node->GetWord() << " " << node->GetMean() << endl;	// print word and mean
			Print_R_IN(node->GetRight());									// print right sub tree

			output.close();													// file close
			return true;
		}
	}
	else
		return false;
}

bool Print_I_IN(WordNode* root)
{
	ofstream output("log.txt", ios::app);										// output file

	if (output.is_open())														// file is open
	{
		if (!root)																// tree is empty
		{
			output.close();														// output close
			return false;
		}
		WordNode *top = 0, *lastRight = 0, *p, *q, *r, *r1;						// deepest node, highest parent node of top that has two children

		p = q = root;															// start from root

		for (;;)
		{
			for (;;)															// start to go down
			{
				if ((!p->GetLeft()) && (!p->GetRight()))						// p is leaf node
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					break;														// start to go up
				}
				if (!p->GetLeft())												// p has only right child
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					r = p->GetRight(); p->SetRight(q);							// make current node's right pointer pointing its parent node
					q = p; p = r;												// go down to this right child
				}
				else															// p has only left child
				{
					r = p->GetLeft(); p->SetLeft(q);							// make current node's left pointer pointing its parent node
					q = p; p = r;												// go down to this left child
				}
			}

			WordNode* av = p;													// deepeset node
			for (;;)
			{
				if (p == root)													// traversal is done
				{
					output.close();												// output close
					return true;
				}
				if (!q->GetLeft())												// parent node has only right child
				{
					r = q->GetRight(); q->SetRight(p);							// restore link
					p = q; q = r;												// go up to parent node
				}
				else if (!q->GetRight())										// parent node has only left child
				{
					r = q->GetLeft(); q->SetLeft(p);							// restore link
					p = q; q = r;												// go up to parent node
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
				}
				else if (q == lastRight)										// left and right sub tree traversal is done
				{
					r = top; lastRight = r->GetLeft();							// set lastRight node as its parent node
					top = r->GetRight();										// set top node as the deepest node of the parent node of lastRight
					r->SetLeft(0); r->SetRight(0);								// restore link, i.e. it has no child originally
					r = q->GetRight(); q->SetRight(p);							// restore link
					p = q; q = r;												// go up to its parent node
				}
				else															// only left sub tree traversal is done
				{
					output << q->GetWord() << " " << q->GetMean() << endl;		// save word
					av->SetLeft(lastRight); av->SetRight(top);					// set the left child of the deepest node as previous lastRight and right as top
					top = av; lastRight = q;									// update new top and lastRight, i.e. child lastRight and its deepest node
					r = q->GetLeft(); q->SetLeft(p);							// restore link
					r1 = q->GetRight(); q->SetRight(r);							// move to the right sub tree
					p = r1;														// set current node as the first node of the right sub tree
					break;														// restart to go down
				}
			}
		}
	}
	else
		return false;
}

bool Print_R_POST(WordNode* node)
{
	ofstream output("log.txt", ios::app);

	if (output.is_open()) // file is open
	{
		if (!node)
			return true; // escape condition
		else {
			Print_R_POST(node->GetLeft());									// print left sub tree
			Print_R_POST(node->GetRight());									// print right sub tree
			output << node->GetWord() << " " << node->GetMean() << endl;	// print word and mean

			output.close();													// file close
			return true;
		}
	}
	else
		return false;
}

bool Print_I_POST(WordNode* root)
{
	ofstream output("log.txt", ios::app);										// output file

	if (output.is_open())														// file is open
	{
		if (!root)																// tree is empty
		{
			output.close();														// output close
			return false;
		}
		WordNode *top = 0, *lastRight = 0, *p, *q, *r, *r1;						// deepest node, highest parent node of top that has two children

		p = q = root;															// start from root

		for (;;)
		{
			for (;;)															// start to go down
			{
				if ((!p->GetLeft()) && (!p->GetRight()))						// p is leaf node
				{
					break;														// start to go up
				}
				if (!p->GetLeft())												// p has only right child
				{
					r = p->GetRight(); p->SetRight(q);							// make current node's right pointer pointing its parent node
					q = p; p = r;												// go down to this right child
				}
				else															// p has only left child
				{
					r = p->GetLeft(); p->SetLeft(q);							// make current node's left pointer pointing its parent node
					q = p; p = r;												// go down to this left child
				}
			}

			WordNode* av = p;													// deepeset node
			for (;;)
			{
				if (p == root)													// traversal is done
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					output.close();												// output close
					return true;
				}
				if (!q->GetLeft())												// parent node has only right child
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					r = q->GetRight(); q->SetRight(p);							// restore link
					p = q; q = r;												// go up to parent node
				}
				else if (!q->GetRight())										// parent node has only left child
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					r = q->GetLeft(); q->SetLeft(p);							// restore link
					p = q; q = r;												// go up to parent node
				}
				else if (q == lastRight)										// left and right sub tree traversal is done
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					r = top; lastRight = r->GetLeft();							// set lastRight node as its parent node
					top = r->GetRight();										// set top node as the deepest node of the parent node of lastRight
					r->SetLeft(0); r->SetRight(0);								// restore link, i.e. it has no child originally
					r = q->GetRight(); q->SetRight(p);							// restore link
					p = q; q = r;												// go up to its parent node
				}
				else															// only left sub tree traversal is done
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					av->SetLeft(lastRight); av->SetRight(top);					// set the left child of the deepest node as previous lastRight and right as top
					top = av; lastRight = q;									// update new top and lastRight, i.e. child lastRight and its deepest node
					r = q->GetLeft(); q->SetLeft(p);							// restore link
					r1 = q->GetRight(); q->SetRight(r);							// move to the right sub tree
					p = r1;														// set current node as the first node of the right sub tree
					break;														// restart to go down
				}
			}
		}
	}
	else
		return false;
}

bool Print_I_LEVEL(WordNode* root)
{
	ofstream output("log.txt", ios::app);

	Queue q_temp; // for level order
	WordNode* currentNode = root; // start from root

	if (output.is_open()) // file is open
	{
		while (currentNode) // until current Node becomes NULL
		{
			output << currentNode->GetWord() << " " << currentNode->GetMean() << endl; // print word
			if (currentNode->GetLeft()) q_temp.Push(currentNode->GetLeft()); // push left child of current node
			if (currentNode->GetRight()) q_temp.Push(currentNode->GetRight()); // push right child of current node
			if (!q_temp.pHead) // traversal is done if queue is empty
			{
				output.close();
				return true;
			}
			currentNode = q_temp.Pop(); // get next level node
		}
	}
	else
		return false;
}
/* ******************************************************************************* */

// PRINT
bool WordBST::Print(char * order)
{
	if (!strcmp(order, "R_PRE"))		// Recursive Preorder Traversal
	{
		return Print_R_PRE(root);
	}
	else if (!strcmp(order, "I_PRE"))	// Iterative Preorder Traversal
	{
		return Print_I_PRE(root);
	}
	else if (!strcmp(order, "R_IN"))	// Recursive Inorder Traversal
	{
		return Print_R_IN(root);
	}
	else if (!strcmp(order, "I_IN"))	// Iterative Inorder Traversal
	{
		return Print_I_IN(root);
	}
	else if (!strcmp(order, "R_POST"))	// Recursive Postorder Traversal
	{
		return Print_R_POST(root);
	}
	else if (!strcmp(order, "I_POST"))	// Iterative Postorder Traversal
	{
		return Print_I_POST(root);
	}
	else if (!strcmp(order, "I_LEVEL"))	// Iterative Level order Traversal
	{
		return Print_I_LEVEL(root);
	}
	else return false;					// wrong order
}



// SAVE
bool WordBST::Save()
{
	ofstream output("memorizing_word.txt", ios::app);

	if (output.is_open())														// file is open
	{
		if (!root)																// tree is empty
		{
			output.close();														// output close
			return false;
		}
		WordNode *top = 0, *lastRight = 0, *p, *q, *r, *r1;						// deepest node, highest parent node of top that has two children

		p = q = root;															// start from root

		for (;;)
		{
			for (;;)															// start to go down
			{
				if ((!p->GetLeft()) && (!p->GetRight()))						// p is leaf node
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					break;														// start to go up
				}
				if (!p->GetLeft())												// p has only right child
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					r = p->GetRight(); p->SetRight(q);							// make current node's right pointer pointing its parent node
					q = p; p = r;												// go down to this right child
				}
				else															// p has only left child
				{
					output << p->GetWord() << " " << p->GetMean() << endl;		// save word
					r = p->GetLeft(); p->SetLeft(q);							// make current node's left pointer pointing its parent node
					q = p; p = r;												// go down to this left child
				}
			}

			WordNode* av = p;													// deepeset node
			for (;;)
			{
				if (p == root)													// traversal is done
				{
					output.close();												// output close
					return true;
				}
				if (!q->GetLeft())												// parent node has only right child
				{
					r = q->GetRight(); q->SetRight(p);							// restore link
					p = q; q = r;												// go up to parent node
				}
				else if (!q->GetRight())										// parent node has only left child
				{
					r = q->GetLeft(); q->SetLeft(p);							// restore link
					p = q; q = r;												// go up to parent node
				}
				else if (q == lastRight)										// left and right sub tree traversal is done
				{
					r = top; lastRight = r->GetLeft();							// set lastRight node as its parent node
					top = r->GetRight();										// set top node as the deepest node of the parent node of lastRight
					r->SetLeft(0); r->SetRight(0);								// restore link, i.e. it has no child originally
					r = q->GetRight(); q->SetRight(p);							// restore link
					p = q; q = r;												// go up to its parent node
				}
				else															// only left sub tree traversal is done
				{
					av->SetLeft(lastRight); av->SetRight(top);					// set the left child of the deepest node as previous lastRight and right as top
					top = av; lastRight = q;									// update new top and lastRight, i.e. child lastRight and its deepest node
					r = q->GetLeft(); q->SetLeft(p);							// restore link
					r1 = q->GetRight(); q->SetRight(r);							// move to the right sub tree
					p = r1;														// set current node as the first node of the right sub tree
					break;														// restart to go down
				}
			}
		}
	}
	else
		return false;
}
