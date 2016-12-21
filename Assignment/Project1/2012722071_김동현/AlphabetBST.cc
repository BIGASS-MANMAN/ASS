#include "AlphabetBST.h"

AlphabetBST::AlphabetBST()
{
	root = NULL;
	WordCnt = 0;
}
AlphabetBST::~AlphabetBST()
{
	root = NULL;
	WordCnt = 0;
}

AlphabetNode * AlphabetBST::Search(char alphabet)
{
	//find same alphabet
	Stack<AlphabetNode *> pp;
	AlphabetNode * pCur = root;
	AlphabetNode * out = new AlphabetNode();
	pp.Push(pCur);

	while (!pp.IsEmpty())
	{
		if (pCur)
		{
			pp.Push(pCur);
			pCur = pCur->GetLeft();
		}
		else
		{
			pCur = pp.Top();
			pp.Pop();
			if (pCur->GetAlphabet() == alphabet) out = pCur;
			pCur = pCur->GetRight();
		}
	}

	return out;
}

void AlphabetBST::Insert(AlphabetNode * node)//This function make Alphabet Tree
{
	AlphabetNode * pCur = root;
	AlphabetNode * pVur = NULL;
	if (!root)
	{
		root = new AlphabetNode();			
	        root = node;
		return ;	
	}
	while (1)//find empty space to put new node
	{
		if (node->GetAlphabet() == pCur->GetAlphabet()) break;
		else if (node->GetAlphabet() > pCur->GetAlphabet())//When current alphabet is lower than root alphabet
		{   //pVur get currentnode and pCur move to left child, if pCur is empty pVur get leftchild and break
			if (pCur -> GetRight() == NULL)
			{

				pCur->SetRight(node); break;
			}
			else
			{
				pCur = pCur -> GetRight();
			}

		}
		else//When current alphabet is upper than root alphabet
		{   //pVur get currentnode and pCur move to right child, if pCur is empty pVur get leftright and break
			if (pCur -> GetLeft() == NULL)
			{
				pCur->SetLeft(node); break;
			}
			else
			{
				pCur = pCur->GetLeft();
			}
		}
	}
}


AlphabetNode * AlphabetBST::ItInorder(char  fword, AlphabetNode * currentnode)
{   //find same alphabet
	Stack<AlphabetNode *> pp;
	AlphabetNode * out = new AlphabetNode();
	pp.Push(currentnode);
	while (1)
	{
		if (currentnode)
		{
			pp.Push(currentnode);
			currentnode = currentnode->GetLeft();
		}
		else
		{
			currentnode = pp.Top();
			pp.Pop();
			if (currentnode->GetAlphabet() == fword) out = currentnode;
			currentnode = currentnode->GetRight();
		}

		if(pp.IsEmpty() == true)
		break;
	}
	return out;
}

bool AlphabetBST::Save()
{
	ofstream fout;
	fout.open("MEMORIZING", ios::trunc);
	char standard = 97;

	if (fout == NULL)
	{
		return false;
	}
	else
	{	
		AlphabetNode * pCur;
		WordBST * bst;

		char(*words)[64];

		
		while (standard != 123)
		{
			pCur = ItInorder(standard, root);
			bst = pCur->GetBST();
			if (bst->root == NULL)
			{
				standard += 1;
				continue;
			}
			words = bst->Expressword(bst->root);
			for (int i = 0; i < 100; i++)
			{
				if (words[i] == NULL)
					break;
				fout << words[i] << endl;
			}
			standard += 1;
		}
	}
	return true;
}

bool AlphabetBST::Print(char * order)
{
	int dicision = 0;

	if (strcmp(order, "R_IN") == 0)
		dicision = 1;
	if (strcmp(order, "I_IN") == 0)
		dicision = 2;
	if (strcmp(order, "R_PRE") == 0)
		dicision = 3;
	if (strcmp(order, "I_PRE") == 0)
		dicision = 4;
	if (strcmp(order, "R_POST") == 0)
		dicision = 5;
	if (strcmp(order, "I_POST") == 0)
		dicision = 6;
	if (strcmp(order, "I_LEVEL") == 0)
		dicision = 7;
	switch (dicision)
	{
	case 1:
		Inorder(root);
		break;
	case 2:
		preorder(root);
		break;
	case 3:
		postorder(root);
		break;
	case 4:
		IterativeInorder(root);
		break;
	case 5:
		Iterativepreorder(root);
		break;
	case 6:
		Iterativepostorder(root);
		break;
	case 7:
		Levelorder(root);
		break;
	}
	return false;
}

void AlphabetBST::Inorder(AlphabetNode * currentnode)
{
	if (currentnode)
	{
		char arr[256] = {"R_IN"};
		Inorder(currentnode->GetLeft());
		Visit(arr, currentnode);
		Inorder(currentnode->GetRight());
	}
}

void AlphabetBST::preorder(AlphabetNode * currentnode)
{
	if (currentnode)
	{
		char arr[256] = {"I_IN"};
		Visit(arr, currentnode);
		preorder(currentnode->GetLeft());
		preorder(currentnode->GetRight());
	}
}

void AlphabetBST::postorder(AlphabetNode * currentnode)
{
	if (currentnode)
	{
		postorder(currentnode->GetLeft());
		postorder(currentnode->GetRight());
		char arr[256] = {"R_PRE"};
		Visit(arr, currentnode);
	}
}

void AlphabetBST::IterativeInorder(AlphabetNode * currentnode)
{
	//find same word
	Stack<AlphabetNode *> pp;
	AlphabetNode * pCur = root;
	pp.Push(pCur);

	while (!pp.IsEmpty() || pCur)
	{
		if (pCur)
		{
			pp.Push(pCur);
			pCur = pCur->GetLeft();
		}
		else
		{
			pCur = pp.Top();
			pp.Pop();
			char arr[256] = {"I_PRE"};
			Visit(arr, currentnode);
			pCur = pCur->GetRight();
		}
	}
}

void AlphabetBST::Iterativepreorder(AlphabetNode * currentnode)
{
	Stack<AlphabetNode*> s;
	while (1)
	{
		while (currentnode)
		{
			s.Push(currentnode);
			currentnode = currentnode->GetLeft();
		}
		if (s.IsEmpty())
			return;
		currentnode = s.Top();
		char arr[256] = {"R_POST"};
		Visit(arr, currentnode);
		s.Pop();

		currentnode = currentnode->GetRight();
	}
}

void AlphabetBST::Iterativepostorder(AlphabetNode * currentnode)
{
	if (currentnode == NULL)
		return;

	Stack<AlphabetNode* > stack, result;
	AlphabetNode * pNew;

	do {
		stack.Push(currentnode);
		AlphabetNode* pCur = stack.Top();
		result.Push(pCur);
		stack.Pop();

		if (pCur->GetLeft() != NULL)
			stack.Push(pCur->GetLeft());

		if (pCur->GetLeft() != NULL)
			stack.Push(pCur->GetLeft());

	} while (stack.IsEmpty());

	while (result.IsEmpty()) {

		pNew = result.Top();
		char arr[256] = {"I_POST"};
		Visit(arr, currentnode);
		result.Pop();
	}
}

void AlphabetBST::Levelorder(AlphabetNode * currentnode)
{
	queue<AlphabetNode *> Q;

	if (root == NULL)
		return;

	Q.push(currentnode);

	while (!Q.empty())
	{
		AlphabetNode * node = Q.front();
		Q.pop();

		char arr[256] = {"I_LEVEL"};
		Visit(arr, node);

		if (node->GetLeft())
		{
			Q.push(node->GetLeft());
		}
		if (node->GetRight())
		{
			Q.push(node->GetRight());
		}
	}
}

void AlphabetBST::Visit(char * n, AlphabetNode * node)
{
	WordBST *bst = node->GetBST();
	bst->Print(n);
}
