#include "AlphabetBST.h"

// Constructor
AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;
}

// Destructor
AlphabetBST::~AlphabetBST()
{
	if (root != NULL)
		releaseTree(root);
}

// The tress released function.
void AlphabetBST::releaseTree(AlphabetNode * root)
{
	if(root == NULL)
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
AlphabetNode * AlphabetBST::findMin(AlphabetNode * root)
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
AlphabetNode * AlphabetBST::findMax(AlphabetNode * root)
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
AlphabetNode * AlphabetBST::Insert(AlphabetNode * node)
{
	AlphabetNode * temp = root;

	if (temp == NULL)
		return node;

	while (temp != NULL)
	{
		// If the inserted node's alphabet is larger than root.
		if (node->GetAlphabet() > temp->GetAlphabet())
		{
			if (temp->GetRight() == NULL)
			{
				temp->SetRight(node);
				break;
			}
			temp = temp->GetRight();
		}
		else if (node->GetAlphabet() < temp->GetAlphabet())
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

// the alphabet searching function.
AlphabetNode * AlphabetBST::Search(char alpabet)
{
	AlphabetNode * temp = root;

	while (temp != NULL)
	{
		// if alphabet is
		if (alpabet > temp->GetAlphabet())
			temp = temp->GetRight();
		else if (alpabet < temp->GetAlphabet())
			temp = temp->GetLeft();
		// If finding the alphabet node.
		else
			return temp;
	}
}

// The recursive pre-order function.
void AlphabetBST::recursivePreorder(AlphabetNode * root)
{
	if (root == NULL)
	{
		return;
	}
	root->GetBST()->recursivePreorder(root->GetBST()->getRoot());
	recursivePreorder(root->GetLeft());
	recursivePreorder(root->GetRight());
}

// The iterative pre-order function.
void AlphabetBST::iterativePreorder(AlphabetNode * root)
{
	// Set a stack instance.
	Stack<AlphabetNode *> stack;
	stack.push(root);
	// Until all the node chekced
	while (stack.size() > 0)
	{
		AlphabetNode * current = stack.top();
		stack.pop();
		root->GetBST()->iterativePreorder(root->GetBST()->getRoot());
		AlphabetNode * temp = current->GetRight();
		if (temp != NULL)
			stack.push(temp);
		temp = current->GetLeft();
		if (temp != NULL)
			stack.push(temp);
	}
}

// The recursive in-order function.
void AlphabetBST::recursiveInorder(AlphabetNode * root)
{
	if (root == NULL)
	{
		return;
	}
	recursiveInorder(root->GetLeft());
	root->GetBST()->recursiveInorder(root->GetBST()->getRoot());
	recursiveInorder(root->GetRight());
}

// The iterative in-order function.
void AlphabetBST::iterativeInorder(AlphabetNode * root)
{
	// Set a stack instance.
	Stack<AlphabetNode *> stack;
	AlphabetNode * current = root;
	// Until all the node chekced
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
		root->GetBST()->iterativeInorder(root->GetBST()->getRoot());
		current = current->GetRight();
	}
}

// The recursive post-order function.
void AlphabetBST::recursivePostorder(AlphabetNode * root)
{
	if (root == NULL)
	{
		return;
	}
	recursivePostorder(root->GetLeft());
	recursivePostorder(root->GetRight());
	root->GetBST()->recursivePostorder(root->GetBST()->getRoot());
}

// The iterative post-order function.
void AlphabetBST::iterativePostorder(AlphabetNode * root)
{
	if (!root)
		return;
	// Set a stack instance.
	Stack<AlphabetNode *> stack;
	stack.push(root);
	AlphabetNode * prev = NULL;
	// Until all the node chekced
	while (!stack.empty())
	{
		AlphabetNode * current = stack.top();
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
			root->GetBST()->iterativePostorder(root->GetBST()->getRoot());
			stack.pop();
		}
		prev = current;
	}
}

// The queue levelorder function.
void AlphabetBST::Levelorder(AlphabetNode * root)
{
	// Set a queue instance
	myQueue<AlphabetNode *> queue;
	if (root)
	{
		queue.push(root);
	}
	// Until all the stack data is empty.
	while (!queue.empty())
	{
		AlphabetNode * temp = queue.front();
		queue.pop();
		root->GetBST()->Levelorder(root->GetBST()->getRoot());
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
AlphabetNode * AlphabetBST::getRoot()
{
	return root;
}

// The function that sets a root node.
void AlphabetBST::setRoot(AlphabetNode * node)
{
	root = node;
}

// Print function.
bool AlphabetBST::Print(char * order)
{
	if (strcmp(order, "R_PRE") == 0)
	{
		recursivePreorder(getRoot());
		return true;
	}
	else if (strcmp(order, "I_PRE") == 0)
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
bool AlphabetBST::Save()
{
	// Make the memorizing_word.txt text file.
	ofstream outFile("memorizing_word.txt");
	outFile.close(); // The initative.

	// Set the stack instance
	Stack<AlphabetNode *> stack;
	stack.push(root);
	int count = 0;
	while (stack.size() > 0)
	{
		AlphabetNode * current = stack.top();
		stack.pop();
		if (current->GetBST()->Save())
			count++;
		AlphabetNode * temp = current->GetRight();
		if (temp != NULL)
			stack.push(temp);
		temp = current->GetLeft();
		if (temp != NULL)
			stack.push(temp);
	}
	if (count == 0)
		return false;
	return true;
}
