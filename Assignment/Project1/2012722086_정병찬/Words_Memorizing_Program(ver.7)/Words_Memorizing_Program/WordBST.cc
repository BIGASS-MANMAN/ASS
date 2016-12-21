#include "WordBST.h"
#include"Stack.h"
#include"Queue.h"



WordBST::WordBST()
{
	root = '\0';		// Initialize the "root" to NULL in constructor
}

WordBST::~WordBST()
{
}

void WordBST::Insert(WordNode * node)		// Inserts a word node in word BST
{
	WordNode*p = root, *pp = 0;
	while (p)		// Finds where to put the node in word BST
	{
		pp = p;
		if (strcmp(node->GetWord(), p->GetWord()) < 0)
			p = p->GetLeft();
		else if (strcmp(node->GetWord(), p->GetWord()) > 0)
			p = p->GetRight();
		else
		{
			p->SetMean(node->GetMean());
			return;
		}
	}
	// Insert the word node
	p = new WordNode;
	p->SetWord(node->GetWord());
	p->SetMean(node->GetMean());
	if (root)
	{
		if (strcmp(p->GetWord(), pp->GetWord()) < 0)
			pp->SetLeft(p);
		else
			pp->SetRight(p);
	}
	else root = p;
}

WordNode * WordBST::Delete(char * word)		// Delete the node in word BST
{
	WordNode *p = root, *q = 0, *temp = 0, *temp2 = 0;
	while (p && strcmp(word, p->GetWord()))      // Find which node to delete
	{
		q = p;		// "q" becomes the parent of the node that is to be deleted
		if (strcmp(word, p->GetWord()) < 0) p = p->GetLeft();
		else p = p->GetRight();
	}

	if (p == 0)		// If the node is not found
	{
		cout << "입력된 Key를 가진 노드가 존재하지 않습니다." << endl;
		return NULL;
	}
	else if (p->GetLeft() == 0 && p->GetRight() == 0)   // If it is a leaf node
	{
		if (q == 0) root = 0;
		else if (q->GetLeft() == p) q->SetLeft(0);
		else q->SetRight(0);
		delete p;
	}

	else if (p->GetLeft() == 0)   // If the node has only right child
	{
		temp = p;
		temp2 = p->GetRight();
		if (q == 0) root = temp->GetRight();	// If the root is to be deleted
		else if (q->GetLeft() == temp)			// If the node is left child of "q"
		{
			temp = temp->GetRight();
			while (temp->GetLeft()) { temp = temp->GetLeft(); }
			q->SetLeft(temp);
			temp->SetRight(temp2);
		}
		else if (q->GetRight() == temp)		// If the node is right child of "q"
		{
			temp = temp->GetRight();
			while (temp->GetLeft()) { temp = temp->GetLeft(); }
			q->SetRight(temp);
			temp->SetRight(temp2);
		}
		delete p;
	}

	else if (p->GetRight() == 0)     // If the node has only left child
	{
		temp = p;
		temp2 = p->GetLeft();
		if (q == 0) root = temp->GetLeft();
		else if (q->GetLeft() == temp)		// If the node is left child of "q"
		{
			temp = temp->GetLeft();
			while (temp->GetRight()) { temp = temp->GetRight(); }
			q->SetLeft(temp);
			temp->SetLeft(temp2);
		}
		else if (q->GetRight() == temp)		// If the node is right child of "q"
		{
			temp = temp->GetLeft();
			while (temp->GetRight()) { temp = temp->GetRight(); }
			q->SetRight(temp);
			temp->SetLeft(temp2);
		}
		delete p;
	}

	else	// If the node has both left and right child
	{      // Find the node with smallest value in right sub-tree
		temp = p;
		temp2 = p->GetRight();
		if (q == 0)
		{
			temp = temp->GetRight();
			while (temp->GetLeft()) { temp = temp->GetLeft(); }
			root = temp;
			root->SetRight(temp2);
		}
		else if (q->GetLeft() == temp)		// If the node is left child of "q"
		{
			temp = temp->GetRight();
			while (temp->GetLeft()) { temp = temp->GetLeft(); }
			q->SetLeft(temp);
			temp->SetLeft(temp2);
		}
		else if (q->GetRight() == temp)		// If the node is right child of "q"
		{
			temp = temp->GetRight();
			while (temp->GetLeft()) { temp = temp->GetLeft(); }
			q->SetRight(temp);
			temp->SetLeft(temp2);
		}
		delete p;
	}
}

WordNode * WordBST::Search(char * word)
{
	WordNode* cur = root;
	if (root == NULL) return NULL;
	while (cur)		// Search the node without using recursive function
		{
			if (strcmp(word, cur->GetWord()) < 0) cur = cur->GetLeft();
			else if (strcmp(word, cur->GetWord()) > 0) cur = cur->GetRight();
			else return cur;
		}
	return NULL;

}

bool WordBST::Print(char * order)
{
	if (!strcmp(order, "R_PRE"))
	{
		R_PRE(root);		// Print the nodes in pre-order using recursive function
		return true;
	}
	else if (!strcmp(order, "I_PRE"))
	{
		I_PRE();			// Print the nodes in pre-order without using recursive function
		return true;
	}
	else if (!strcmp(order, "R_IN"))
	{
		R_IN(root);			// Print the nodes in in-order using recursive function
		return true;
	}
	else if (!strcmp(order, "I_IN"))
	{
		I_IN();				// Print the nodes in in-order without using recursive function
		return true;
	}
	else if (!strcmp(order, "R_POST"))
	{
		R_POST(root);		// Print the nodes in post-order using recursive function
		return true;
	}
	else if (!strcmp(order, "I_POST"))
	{
		I_POST();			// Print the nodes in post-order without using recursive function
		return true;
	}
	else if (!strcmp(order, "I_LEVEL"))
	{
		I_LEVEL();			// Print the nodes in level-order without using recursive function
		return true;
	}
	else return false;


}

void WordBST::R_PRE(WordNode * cur)		// Print first, then get to left and right child
{
	
	if (cur == NULL) return;

	cout << cur->GetWord() << " " << cur->GetMean() << endl;
	R_PRE(cur->GetLeft());
	R_PRE(cur->GetRight());
}

void WordBST::I_PRE()
{
	Stack<WordNode*> s;
	WordNode* cur = root;
	if (cur == NULL) return;
	s.Push(cur);

	while (!s.IsEmpty())	// Use loop instead of recursive function
	{
		cur = s.Top();
		cout << cur->GetWord() << " " << cur->GetMean() << endl;
		s.Pop();
		if (cur->GetRight())
			s.Push(cur->GetRight());
		if (cur->GetLeft())
			s.Push(cur->GetLeft());
	}

}

void WordBST::R_IN(WordNode * cur)		// Get to left child first, then print. And get to right child
{
	
	if (cur == NULL) return;


	R_IN(cur->GetLeft());
	cout << cur->GetWord() << " " << cur->GetMean() << endl;
	R_IN(cur->GetRight());
}

void WordBST::I_IN()
{
	Stack<WordNode*> s;
	WordNode* cur = root;
	if (cur == NULL) return;
	while (1)			// Use loop instead of using recursive function
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
		cout << cur->GetWord() << " " << cur->GetMean() << endl;
		cur = cur->GetRight();
	}
}

void WordBST::R_POST(WordNode * cur)		// Get to left and right child first, then print
{
	
	if (cur == NULL) return;
	R_POST(cur->GetLeft());
	R_POST(cur->GetRight());
	cout << cur->GetWord() << " " << cur->GetMean() << endl;
}

void WordBST::I_POST()
{
	Stack<WordNode*> s1;
	Stack<WordNode*> s2;
	WordNode* cur1 = root;
	WordNode* cur2 = NULL;
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
			cout << cur2->GetWord() << " " << cur2->GetMean() << endl;
		}
	}
}

void WordBST::I_LEVEL()		// Level-order without recursive function
{
	Queue q;
	WordNode* cur = root;
	if (cur == NULL) return;
	while (cur)
	{
		cout << cur->GetWord() << " " << cur->GetMean() << endl;
		if (cur->GetLeft()) q.Push(cur->GetLeft());
		if (cur->GetRight()) q.Push(cur->GetRight());
		if (q.IsEmpty()) return;
		cur = q.Front();
		q.Pop();
	}
}

bool WordBST::Save()
{
	if(root == NULL)
		return false;
	Stack<WordNode*> s;
	WordNode* cur = root;	// put root in cur

	s.Push(cur);		// Push from the root

	ofstream fout;
	fout.open("memorizing_word.txt", ios::app);
	while (!s.IsEmpty())		// Until the end of stack, put the word and meaning in file 
	{
		cur = s.Top();
		fout << cur->GetWord() << " " << cur->GetMean() << endl;
		s.Pop();
		if (cur->GetRight())
			s.Push(cur->GetRight());
		if (cur->GetLeft())
			s.Push(cur->GetLeft());
	}

	fout.close();
	return true;
}

WordNode * WordBST::Getroot()
{
	return root;
}

int WordBST::Bst_count()		// Counts the number of nodes in BST
{
	int count = 0;
	Stack<WordNode*> s;
	WordNode* cur = root;
	if (cur == NULL) return 0;
	s.Push(cur);

	while (!s.IsEmpty())
	{
		cur = s.Top();
		count++;
		s.Pop();
		if (cur->GetRight())
			s.Push(cur->GetRight());
		if (cur->GetLeft())
			s.Push(cur->GetLeft());
	}
	return count;
}