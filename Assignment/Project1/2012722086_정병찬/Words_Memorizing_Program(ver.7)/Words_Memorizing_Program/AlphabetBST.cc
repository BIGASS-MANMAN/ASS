#include "AlphabetBST.h"
#include"Stack.h"
#include"Queue_BST.h"



AlphabetBST::AlphabetBST()
{
	root = '\0';	// Initialize the root to NULL
	WordCnt = 0;	// Initialize the WordCnt to 0
}

AlphabetBST::~AlphabetBST()
{
	Stack<AlphabetNode*> s;
	AlphabetNode* cur = root;
	if (cur == NULL) return;
	do
	{
		while (cur)
		{
			if (cur->GetRight())	// If there is right child of "cur" push the right child
				s.Push(cur->GetRight());
			s.Push(cur);

			cur = cur->GetLeft();		// put the left child of "cur" in "cur"
		}
		cur = s.Top();		// The top of stack is put in "cur"
		s.Pop();

		if (cur->GetRight() && s.Top() == cur->GetRight())		// If the right child of "cur" equals to the top of stack while it's not NULL
		{
			s.Pop();
			s.Push(cur);
			cur->GetRight();
		}
		else
		{
			delete cur;
			cur = NULL;
		}
	} while (!s.IsEmpty());		// Until the stack is empty
}

void AlphabetBST::Insert(AlphabetNode * node)	// This function is for inserting an alphabet node of alphabet bst
{
	AlphabetNode*p = root, *pp = 0;
	while (p)		// This loop finds where to put the node in alphabet BST
	{
		pp = p;
		if (node->GetAlphabet() < p->GetAlphabet())
			p = p->GetLeft();
		else if (node->GetAlphabet() > p->GetAlphabet())
			p = p->GetRight();
		else
		{
			p->SetAlphabet(node->GetAlphabet());
			return;
		}
	}

	p = new AlphabetNode;
	p->SetAlphabet(node->GetAlphabet());		// Set the alphabet of the node
	if (root)
	{
		if (node->GetAlphabet() < pp->GetAlphabet())
			pp->SetLeft(p);		// The node becomes left child if it is smaller
		else
			pp->SetRight(p);	// The node becomes right child if it is greater
	}
	else root = p;		// 'p' becomes the root if root does not exist yet
}

AlphabetNode * AlphabetBST::Search(char Alphabet)
{
	AlphabetNode* cur = root;
	char temp = Alphabet;
	if (Alphabet >= 'a' && Alphabet <= 'z') temp = Alphabet - 32;	// If the first character of the word is a capital letter, change it to lower case

	while (cur)		// Starting from the root, search which node matches the first character of the word without using recursive function
	{
		if (temp < cur->GetAlphabet()) cur = cur->GetLeft();
		else if (temp > cur->GetAlphabet()) cur = cur->GetRight();
		else return cur;
	}

}

bool AlphabetBST::Print(char * order)
{

	if (!strcmp(order, "R_PRE"))		// Print the nodes in pre-order using recursive function
	{
		cout << "======== PRINT ========" << endl;
		R_PRE(root, order);
		cout << "=======================" << endl;
		return true;
	}
	else if (!strcmp(order, "I_PRE"))	// Print the nodes in pre-order without using recursive function
	{
		cout << "======== PRINT ========" << endl;
		I_PRE(order);
		cout << "=======================" << endl;
		return true;
	}
	else if (!strcmp(order, "R_IN"))	// Print the nodes in in-order using recursive function
	{
		cout << "======== PRINT ========" << endl;
		R_IN(root, order);
		cout << "=======================" << endl;
		return true;
	}
	else if (!strcmp(order, "I_IN"))	// Print the nodes in in-order without using recursive function
	{
		cout << "======== PRINT ========" << endl;
		I_IN(order);
		cout << "=======================" << endl;
		return true;
	}
	else if (!strcmp(order, "R_POST"))	// Print the nodes in post-order using recursive function
	{
		cout << "======== PRINT ========" << endl;
		R_POST(root, order);
		cout << "=======================" << endl;
		return true;
	}
	else if (!strcmp(order, "I_POST"))	// Print the nodes in post-order without using recursive function
	{
		cout << "======== PRINT ========" << endl;
		I_POST(order);
		cout << "=======================" << endl;
		return true;
	}
	else if (!strcmp(order, "I_LEVEL"))	// Print the nodes in level-order without using recursive function
	{
		cout << "======== PRINT ========" << endl;
		I_LEVEL(order);
		cout << "=======================" << endl;
		return true;
	}
	else return false;

}

void AlphabetBST::R_PRE(AlphabetNode * cur, char * order)	// Print first, then get to left and right child
{
	if (cur == NULL) return;

	cur->GetBST()->Print(order);
	R_PRE(cur->GetLeft(), order);
	R_PRE(cur->GetRight(), order);
}

void AlphabetBST::I_PRE(char * order)
{
	Stack<AlphabetNode*> s;
	AlphabetNode* cur = root;
	if (cur == NULL) return;
	s.Push(cur);

	while (!s.IsEmpty())		// Use loop instead of recursive function
	{
		cur = s.Top();
		cur->GetBST()->Print(order);
		s.Pop();
		if (cur->GetRight())
			s.Push(cur->GetRight());
		if (cur->GetLeft())
			s.Push(cur->GetLeft());
	}

}

void AlphabetBST::R_IN(AlphabetNode * cur, char * order)	// Get to left child first, then print. And get to right child
{
	if (cur == NULL) return;


	R_IN(cur->GetLeft(), order);
	cur->GetBST()->Print(order);
	R_IN(cur->GetRight(), order);
}

void AlphabetBST::I_IN(char * order)
{
	Stack<AlphabetNode*> s;
	AlphabetNode* cur = root;
	if (cur == NULL) return;
	while (1)		// Use loop instead of using recursive function
	{
		while (cur)
		{
			s.Push(cur);
			cur = cur->GetLeft();
		}
		if (s.IsEmpty())
			return;
		cur = s.Top();
		s.Pop();
		cur->GetBST()->Print(order);
		cur = cur->GetRight();
	}
}

void AlphabetBST::R_POST(AlphabetNode * cur, char * order)		// Get to left and right child first, then print
{
	if (cur == NULL) return;
	R_POST(cur->GetLeft(), order);
	R_POST(cur->GetRight(), order);
	cur->GetBST()->Print(order);
}

void AlphabetBST::I_POST(char * order)
{
	Stack<AlphabetNode*> s1;
	Stack<AlphabetNode*> s2;
	AlphabetNode* cur1 = root;
	AlphabetNode* cur2 = NULL;
	if (cur1 == NULL) return;
	s1.Push(cur1);

	while (!s1.IsEmpty())		// Use loop instead of using recursive function
	{
		cur2 = s1.Top();
		s1.Pop();
		s2.Push(cur2);

		if (cur2->GetLeft())
			s1.Push(cur2->GetLeft());

		if (cur2->GetRight())
			s1.Push(cur2->GetRight());

		while (!s2.IsEmpty())
		{
			cur2 = s2.Top();
			s2.Pop();
			cur2->GetBST()->Print(order);
		}
	}
}

void AlphabetBST::I_LEVEL(char * order)		// Level-order without recursive function
{
	Queue_BST<AlphabetNode*> q;
	AlphabetNode* cur = root;
	if (cur == NULL) return;

	while (cur)
	{
		cur->GetBST()->Print(order);
		if (cur->GetLeft()) q.Push(cur->GetLeft());
		if (cur->GetRight()) q.Push(cur->GetRight());
		if (q.IsEmpty()) return;
		cur = q.Front();
		q.Pop();
	}
}

bool AlphabetBST::Save()
{
	if (root == NULL)
		return false;
	Stack<AlphabetNode*> s;
	AlphabetNode * cur = root;		// put root in cur

	s.Push(cur);		// Push from the root
	ofstream fout;
	fout.open("memorizing_word.txt", ios::trunc);
	fout.clear();
	fout.close();

	while (!s.IsEmpty())	// Until the end of stack, put the word and meaning in file 
	{
		cur = s.Top();
		cur->GetBST()->Save();
		s.Pop();
		if (cur->GetRight())
			s.Push(cur->GetRight());
		if (cur->GetLeft())
			s.Push(cur->GetLeft());
	}


	return true;
}

int AlphabetBST::Alpha_bst_count()		// Counts the number of nodes in BST
{
	int count = 0;
	Stack<AlphabetNode*> s;
	AlphabetNode* cur = root;
	if (cur == NULL) return 0;
	while (1)
	{
		while (cur)
		{
			s.Push(cur);
			cur = cur->GetLeft();
		}
		if (s.IsEmpty())
			return count;
		cur = s.Top();
		s.Pop();
		count += cur->GetBST()->Bst_count();
		cur = cur->GetRight();
	}

	return count;
}
