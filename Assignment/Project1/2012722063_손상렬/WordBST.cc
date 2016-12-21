#include "WordBST.h"

// Constructor
WordBST::WordBST()
{
	root = '\0';
	count = 0;
}

// Destructor
WordBST::~WordBST()
{
	releaseTree(root);
}

// The tree released function.
void WordBST::releaseTree(WordNode * root)
{
	if (root == NULL)
		return;

	// If there is child node, the recursive function will execute.
	if (root->GetRight() != NULL)
	{
		releaseTree(root->GetRight());
	}
	if (root->GetLeft() != NULL)
	{
		releaseTree(root->GetLeft());
	}

	// All the child node will be null.
	root->SetLeft(NULL);
	root->SetRight(NULL);

	// Exception Handling
	if (root != NULL)
	{
		delete root;
	}
}

// Find the min node based on root node.
WordNode * WordBST::findMin(WordNode * root)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->GetLeft())
	{
		return findMin(root->GetLeft());
	}
	else
	{
		return root;
	}
}

// Find the max node based on root node.
WordNode * WordBST::findMax(WordNode * root)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->GetRight())
	{
		findMax(root->GetRight());
	}
	else
	{
		return root;
	}
}

// The node inserting function.
WordNode * WordBST::Insert(WordNode * node)
{
	WordNode * temp = root;
	// if the node is the BST's root node.
	if (temp == NULL)
	{
		count++;
		return node;
	}

	while (temp != NULL)
	{
		// If the inserted node's alphabet is larger than root.
		if (strcmp(node->GetWord(), temp->GetWord()) > 0)
		{
			if (temp->GetRight() == NULL)
			{
				temp->SetRight(node);
				break;
			}
			temp = temp->GetRight();
		}
		else if (strcmp(node->GetWord(), temp->GetWord()) < 0)
		{
			if (temp->GetLeft() == NULL)
			{
				temp->SetLeft(node);
				break;
			}
			temp = temp->GetLeft();
		}
	}
	return root;
}

// The deleting function.
WordNode * WordBST::Delete(char * word)
{
	return DeleteImp(root, word);
}

// The deleting function.
WordNode * WordBST::DeleteImp(WordNode * root, char * word)
{
	WordNode * temp;
	if (root == NULL)
	{
		count--;
		return NULL;
	}
	if (strcmp(word, root->GetWord()) > 0)
	{
		root->SetRight(DeleteImp(root->GetRight(), word));
	}
	else if (strcmp(word, root->GetWord()) < 0)
	{
		root->SetLeft(DeleteImp(root->GetLeft(), word));
	}
	else
	{
		if (root->GetLeft())
		{
			temp = findMax(root->GetLeft());
			root->SetWord(temp->GetWord());
			root->SetMean(temp->GetMean());
			root->SetLeft(DeleteImp(root->GetLeft(), temp->GetWord()));
		}
		else if (root->GetRight())
		{
			temp = findMin(root->GetRight());
			root->SetWord(temp->GetWord());
			root->SetMean(temp->GetMean());
			root->SetRight(DeleteImp(root->GetRight(), temp->GetWord()));
		}
		else
		{
			temp = root;
			free(temp);
			return NULL;
		}
	}
	return root;
}

// the Word searching function.
WordNode * WordBST::Search(char * word)
{
	WordNode * temp = root;

	// the alphabet searching function.
	while (temp != NULL)
	{
		if (strcmp(word, temp->GetWord()) > 0)
		{
			temp = temp->GetRight();
		}
		else if (strcmp(word, root->GetWord()) < 0)
		{
			temp = temp->GetLeft();
		}
		else
		{
			return root;
		}
	}
	return NULL;
}

// The recursive pre-order function.
void WordBST::recursivePreorder(WordNode * root)
{
	// log writing.
	ofstream out("log.txt", ios::app);
	if (root == NULL)
	{
		return;
	}
	cout << root->GetWord() << " " << root->GetMean() << endl;
	out << root->GetWord() << " " << root->GetMean() << endl;
	recursivePreorder(root->GetLeft());
	recursivePreorder(root->GetRight());
}

// The iterative pre-order function.
void WordBST:: iterativePreorder(WordNode * root)
{
	// log writing.
	ofstream out("log.txt", ios::app);
	// Set a stack instance.
	Stack<WordNode *> stack;
	stack.push(root);
	// Until all the node chekced
	while (stack.size() > 0)
	{
		WordNode * current = stack.top();
		stack.pop();
		cout << current->GetWord() << " " << current->GetMean() << endl;
		out << current->GetWord() << " " << current->GetMean() << endl;
		WordNode * temp = current->GetRight();
		if (temp != NULL)
			stack.push(temp);
		temp = current->GetLeft();
		if (temp != NULL)
			stack.push(temp);
	}
}

// The recursive in-order function.
void WordBST::recursiveInorder(WordNode * root)
{
	ofstream out("log.txt", ios::app);
	if (root == NULL)
	{
		return;
	}
	recursiveInorder(root->GetLeft());
	cout << root->GetWord() << " " << root->GetMean() << endl;
	out << root->GetWord() << " " << root->GetMean() << endl;
	recursiveInorder(root->GetRight());
}

// The iterative in-order function.
void WordBST::iterativeInorder(WordNode * root)
{
	ofstream out("log.txt", ios::app);
	Stack<WordNode *> stack;
	WordNode * current = root;
	while (1)
	{
		while (current != NULL)
		{
			stack.push(current);
			current = current->GetLeft();
		}
		if (stack.size() != 0)
		{
			current = stack.top();
			stack.pop();
		}
		if (current == NULL)
			break;
		cout << current->GetWord() << " " << current->GetMean() << endl;
		out << current->GetWord() << " " << current->GetMean() << endl;
		current = current->GetRight();
	}
}

// The recursive post-order function.
void WordBST::recursivePostorder(WordNode * root)
{
	ofstream out("log.txt", ios::app);
	if (root == NULL)
	{
		return;
	}
	recursivePostorder(root->GetLeft());
	recursivePostorder(root->GetRight());
	cout << root->GetWord() << " " << root->GetMean() << endl;
	out << root->GetWord() << " " << root->GetMean() << endl;
}

// The iterative post-order function.
void WordBST::iterativePostorder(WordNode * root)
{
	ofstream out("log.txt", ios::app);
	if (!root)
		return;
	Stack<WordNode *> stack;
	stack.push(root);
	WordNode * prev = NULL;
	while (!stack.empty())
	{
		WordNode * current = stack.top();
		if (!prev || prev->GetLeft() == current || prev->GetRight() == current)
		{
			if (current->GetLeft())
			{
				stack.push(current->GetLeft());
			}
			else if (current->GetRight())
			{
				stack.push(current->GetRight());
			}
		}
		else if (current->GetLeft() == prev)
		{
			if (current->GetRight())
			{
				stack.push(current->GetRight());
			}
		}
		else
		{
			cout << current->GetWord() << " " << current->GetMean() << endl;
			out << current->GetWord() << " " << current->GetMean() << endl;
			stack.pop();
		}
		prev = current;
	}
}

// The queue levelorder function.
void WordBST::Levelorder(WordNode * root)
{
	// Set a queue instance
	ofstream out("log.txt", ios::app);
	myQueue<WordNode *> queue;
	if (root)
	{
		queue.push(root);
	}
	// Until all the stack data is empty.
	while (!queue.empty())
	{
		WordNode * temp = queue.front();
		queue.pop();
		cout << temp->GetWord() << " " << temp->GetMean() << endl;
		out << temp->GetWord() << " " << temp->GetMean() << endl;
		if (temp->GetLeft())
		{
			queue.push(temp->GetLeft());
		}
		if (temp->GetRight())
		{
			queue.push(temp->GetRight());
		}
	}
}

// The function that returns the root.
WordNode * WordBST::getRoot()
{
	return root;
}

// The function that sets a root node.
void WordBST::setRoot(WordNode * node)
{
	root = node;
}

// Print function.
bool WordBST::Print(char * order)
{
	if (strcmp(order, "R_PRE") == 0)
	{
		recursivePreorder(getRoot());
		return true;
	}
	else if(strcmp(order, "I_PRE") == 0)
	{
		iterativePreorder(getRoot());
		return true;
	}
	else if (strcmp(order, "R_IN") == 0)
	{
		recursiveInorder(getRoot());
		return true;
	}
	else if (strcmp(order, "I_IN") == 0)
	{
		iterativeInorder(getRoot());
		return true;
	}
	else if (strcmp(order, "R_POST") == 0)
	{
		recursivePostorder(getRoot());
		return true;
	}
	else if (strcmp(order, "I_POST") == 0)
	{
		iterativePostorder(getRoot());
		return true;
	}
	else if (strcmp(order, "R_LEVEL") == 0)
	{
		Levelorder(getRoot());
		return true;
	}
	else
	{
		return false;
	}
}

// The saving function.
bool WordBST::Save()
{
	if (root == NULL)
		return false;
	ofstream outFile("memorizing_word.txt", ios::app);
	Stack<WordNode *> stack;
	stack.push(root);
	while (stack.size() > 0)
	{
		WordNode * current = stack.top();
		stack.pop();
		outFile << current->GetWord() << " " << current->GetMean() << endl;
		WordNode * temp = current->GetRight();
		if (temp != NULL)
			stack.push(temp);
		temp = current->GetLeft();
		if (temp != NULL)
			stack.push(temp);
	}
	outFile.close();
	return true;
}

// return all count.
int	WordBST::getCount()
{
	return count;
}