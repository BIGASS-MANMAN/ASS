#include "AlphabetBST.h"
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;



AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;
	Insert('P');
	Insert('H');
	Insert('X');
	Insert('D');
	Insert('L');
	Insert('T');
	Insert('Z');
	Insert('B');
	Insert('F');
	Insert('J');
	Insert('N');
	Insert('R');
	Insert('V');
	Insert('Y');
	Insert('A');
	Insert('C');
	Insert('E');
	Insert('G');
	Insert('I');
	Insert('K');
	Insert('M');
	Insert('O');
	Insert('Q');
	Insert('S');
	Insert('U');
	Insert('W');
}


AlphabetBST::~AlphabetBST()
{
	/* You must fill here */
	DestroyAlphaTree(root);
}


void AlphabetBST::DestroyAlphaTree(AlphabetNode* node)
{
	if(node != '\0')
	{
		DestroyAlphaTree(node->GetLeft());
		DestroyAlphaTree(node->GetRight());
		delete node;
	}
}

void AlphabetBST::Insert(AlphabetNode* node)
{
	if(root == '\0')
		root = node;
	else
		Insert(root, node);
}

void AlphabetBST::Insert(char alphabet)
{
	AlphabetNode* node = new AlphabetNode();
	node->SetAlphabet(alphabet);
	Insert(node);
}

void AlphabetBST::Insert(AlphabetNode* root, AlphabetNode* node)
{
	if(root->GetAlphabet() > node->GetAlphabet())
	{
		if(root->GetLeft() != '\0')
			Insert(root->GetLeft(), node);
		else
			root->SetLeft(node);
	}
	else
	{
		if(root->GetRight() != '\0')
			Insert(root->GetRight(), node);
		else
			root->SetRight(node);
	}
}

bool AlphabetBST::Print(const char* order)
{
	if(strcmp(order, "R_PRE") == 0)
	{
		Print_pr_re(root,order);
		return true;
	}
	else if(strcmp(order, "I_PRE") == 0)
	{
		Print_pr_it(root,order);
		return true;
	}
	else if(strcmp(order, "R_IN") == 0)
	{
		Print_In_re(root,order);
		return true;
	}
	else if(strcmp(order, "I_IN") == 0)
	{
		Print_In_it(root,order);
		return true;
	}
	else if(strcmp(order, "R_POST") == 0)
	{
		Print_po_re(root,order);
		return true;
	}
	else if(strcmp(order, "I_POST") == 0)
	{
		Print_po_it(root,order);
		return true;
	}
	else if(strcmp(order, "I_LEVEL") == 0)
	{
		Print_Level(order);
		return true;
	}
	else
		return false;
}

void AlphabetBST::Print_In_re(AlphabetNode* node, const char* order)
{
	if(node!=NULL)
	{
		Print_In_re(node->GetLeft(),order);
		node->GetBST()->Print(order);
		Print_In_re(node->GetRight(),order);
	}
}

void AlphabetBST::Print_In_it(AlphabetNode* node,const char* order)
{
	if(node == '\0')
		return;
	AlphabetNode* ptr;
	aStack* stack = new aStack();
	ptr = node;
	while(1)
	{
		while(ptr != '\0')
		{
			stack->Push(ptr);
			ptr = ptr->GetLeft();
		}
		ptr = stack->Pop();
		if(ptr == '\0') break;
		ptr->GetBST()->Print(order);
		ptr = ptr->GetRight();
	}
	delete stack;
	return;
}

void AlphabetBST::Print_po_re(AlphabetNode* node, const char* order)
{
	if(node!=NULL)
	{
		Print_po_re(node->GetLeft(),order);
		Print_po_re(node->GetRight(),order);
		node->GetBST()->Print(order);
	}
}

void AlphabetBST::Print_po_it(AlphabetNode* node,const char* order)
{
	if(node == '\0')
		return;
	AlphabetNode* ptr = node;
	AlphabetNode* ptr2 = node;
	aStack* stack = new aStack();

	while((ptr != '\0') || (stack->GetHead() != '\0'))
	{
		if(ptr != '\0')
		{
			stack->Push(ptr);
			ptr = ptr->GetLeft();
		}
		else
		{
			ptr = stack->Pop();
			while((ptr->GetRight() == '\0') || (ptr->GetRight() == ptr2))
			{
				ptr->GetBST()->Print(order);
				ptr2 = ptr;
				if(stack->GetHead() == '\0') return;
				ptr = stack->Pop();
			}
			stack->Push(ptr);
			ptr = ptr->GetRight();
			ptr2 = ptr;
		}
	}
	delete stack;
	return;
}

void AlphabetBST::Print_pr_re(AlphabetNode* node, const char* order)
{
	if(node!=NULL)
	{
		node->GetBST()->Print(order);
		Print_pr_re(node->GetLeft(),order);
		Print_pr_re(node->GetRight(),order);
	}
}

void AlphabetBST::Print_pr_it(AlphabetNode* node,const char* order)
{
	if(node == '\0')
		return;
	AlphabetNode* ptr = node;
	AlphabetNode* ptr2 = node;
	aStack* stack = new aStack();

	while((ptr != '\0') || (stack->GetHead() != '\0'))
	{
		if(ptr != '\0')
		{
			ptr->GetBST()->Print(order);
			stack->Push(ptr);
			ptr = ptr->GetLeft();
		}
		else
		{
			ptr = stack->Pop();
			while((ptr->GetRight() == '\0') || (ptr->GetRight() == ptr2))
			{
				ptr2 = ptr;
				if(stack->GetHead() == '\0') return;
				ptr = stack->Pop();
			}
			stack->Push(ptr);
			ptr = ptr->GetRight();
			ptr2 = ptr;
		}
	}
	delete stack;
	return;
}

int AlphabetBST::Height(AlphabetNode* node)
{
	if(node == '\0')
		return 0;
	else
	{
		int lheight = Height(node->GetLeft());
		int rheight = Height(node->GetRight());

		if(lheight > rheight)
			return (lheight+1);
		else
			return (rheight+1);
	}
}

void AlphabetBST::Print_Level(const char* order)
{
	int h = Height(root);
	int i;
	for(i=1;i<=h;i++)
		Print_Given_Level(root,i,order);
}

void AlphabetBST::Print_Given_Level(AlphabetNode* node, int level,const char* order)
{
	if(node == '\0')
		return;
	if(level==1)
	{
		node->GetBST()->Print(order);
	}
	else if(level>1)
	{
		Print_Given_Level(node->GetLeft(),level-1,order);
		Print_Given_Level(node->GetRight(),level-1,order);
	}
}


AlphabetNode* AlphabetBST::Search(char alphabet)
{
	return Search(root, alphabet);
}

AlphabetNode* AlphabetBST::Search(AlphabetNode* node ,char alphabet)
{
	if(node != '\0')
	{
		if(node->GetAlphabet() == alphabet)
			return node;
		else
		{
			if(node->GetAlphabet() > alphabet)
				return Search(node->GetLeft(), alphabet);
			else
				return Search(node->GetRight(), alphabet);
		}
	}
	else
		 return '\0';
}

bool AlphabetBST::Save()
{
	if(root=='\0')
		return false;
	ofstream fout;
	fout.open("memorizing_word.txt",ios::trunc);
	fout.close();
	Save(root);
	return true;
}

void AlphabetBST::Save(AlphabetNode* node)
{
	if(node!=NULL)
	{
		Save(node->GetLeft());
		node->GetBST()->Save();
		Save(node->GetRight());
	}
}


////////////////////////////////////////////////////////////////////////////////////

aStack::aStack(void)
{
	pHead = '\0';
}

aStack::~aStack(void)
{
	AlphabetNode* ptr = pHead;
	if(ptr != NULL)
	{
		for(AlphabetNode* p = pHead;p != NULL; p = p->GetNext())
		{
			delete ptr;
			ptr = p;
		}
	}
}

void aStack::Push(AlphabetNode* node)
{
	if(pHead == '\0')
		pHead = node;
	else
	{
		AlphabetNode* pCur = pHead;
		for(pCur = pHead; pCur->GetNext() != '\0'; pCur = pCur->GetNext())
		{}
		pCur->SetNext(node);
	}
}

AlphabetNode* aStack::Pop()
{
	if(pHead == '\0')
		return '\0';
	else
	{
		AlphabetNode* pCur = pHead;
		AlphabetNode* prev = pCur;
		for(pCur = pHead; pCur->GetNext() != '\0'; pCur = pCur->GetNext())
		{
			prev = pCur;
		}
		if(prev == pCur)
			pHead = '\0';
		else
			prev->SetNext('\0');
		return pCur;
	}
}

AlphabetNode* aStack::GetHead()
{
	return pHead;
}

