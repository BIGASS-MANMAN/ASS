#include "WordBST.h"
#include <string.h>
#include <fstream>

#include <iostream>
using namespace std;



WordBST::WordBST()
{
	root = '\0';
}


WordBST::~WordBST()
{
	/* You must fill here */
	DestroyTree(root);
}

/*delete node from leaves of the tree in recursive*/
void WordBST::DestroyTree(WordNode* node)
{
	if(node != '\0')
	{
		DestroyTree(node->GetLeft());
		DestroyTree(node->GetRight());
		delete node;
	}
}

/*if there isn't root, parameter is root*/
void WordBST::Insert(WordNode* node)
{
	if(root == '\0')
	{
		root = node;
	}
	else
	{
		Insert(root, node);
	}
}

/*set node's information and execute Insert() function*/
void WordBST::Insert(const char* word, const char* mean)
{
	WordNode* node = new WordNode();
	node->SetWord(word);
	node->SetMean(mean);
	Insert(node);
}

/*compare word and insert into tree */
void WordBST::Insert(WordNode* root, WordNode* node)
{
	if(strcmp(root->GetWord(),node->GetWord())>0)
	{
		if(root->GetLeft() != '\0')
			Insert(root->GetLeft(),node);
		else		//if it is null
			root->SetLeft(node);
	}
	else
	{
		if(root->GetRight() != '\0')
			Insert(root->GetRight(),node);
		else		//if it is null
			root->SetRight(node);
	}
}

WordNode* WordBST::Delete(const char* word)
{
	return Delete(root, word);
}

/*Just in case of root*/
WordNode* WordBST::Delete(WordNode* node, const char* word)
{
	if(strcmp(node->GetWord(),word) == 0)
	{
		if((node->GetLeft() == '\0') && (node->GetRight() == '\0'))
		{
			root = '\0';
			return node;
		}
		else if((node->GetLeft() != '\0') && (node->GetRight() == '\0'))
		{
			WordNode* pCur = node->GetLeft();
			WordNode* prev = pCur;
			while(pCur->GetRight() != '\0')
			{
				prev = pCur;
				pCur = pCur->GetRight();
			}
			if(prev == pCur)
			{
				pCur->SetRight(node->GetRight());
				root = pCur;
				node->SetLeft('\0');				//clear node's links
				node->SetRight('\0');
				return node;
			}
			else
			{
				prev->SetRight(pCur->GetLeft());
				pCur->SetLeft(node->GetLeft());
				root = pCur;
				node->SetLeft('\0');
				node->SetRight('\0');
				return node;
			}
		}
		else if((node->GetLeft() == '\0') && (node->GetRight() != '\0'))
		{
			WordNode* pCur = node->GetRight();
			WordNode* prev = pCur;
			while(pCur->GetLeft() != '\0')
			{
				prev = pCur;
				pCur = pCur->GetLeft();
			}
			if(prev = pCur)
			{
				root = pCur;
				node->SetLeft('\0');
				node->SetRight('\0');
				return node;
			}
			else
			{
				prev->SetLeft(pCur->GetRight());
				pCur->SetRight(node->GetRight());
				root = pCur;
				node->SetLeft('\0');
				node->SetRight('\0');
				return node;
			}
		}
		else
		{
			WordNode* pCur = node->GetLeft();
			WordNode* prev = pCur;
			while(pCur->GetRight() != '\0')
			{
				prev = pCur;
				pCur = pCur->GetRight();
			}
			if(prev = pCur)
			{
				pCur->SetRight(node->GetRight());
				root = pCur;
				node->SetLeft('\0');
				node->SetRight('\0');
				return node;
			}
			else
			{
				prev->SetRight(pCur->GetLeft());
				pCur->SetLeft(node->GetLeft());
				pCur->SetRight(node->GetRight());
				root = pCur;
				node->SetLeft('\0');
				node->SetRight('\0');
				return node;
			}
		}
	}
	else
	{
		WordNode* result;
		if(strcmp(node->GetWord(), word) > 0)
			result = Delete(node, node->GetLeft(), word);
		else
			result = Delete(node, node->GetRight(),word);

		return result;
	}
}

/*except root, Delete function needs parent node to linke child's child node,
Delete function is function to make node's link all free and return it*/
WordNode* WordBST::Delete(WordNode* parent, WordNode* child, const char* word)
{
	if(child != '\0')
	{
		if(strcmp(child->GetWord(), word) == 0)
		{
			if((child->GetLeft() == '\0') && (child->GetRight() == '\0'))
			{
				if(parent->GetLeft() == child)
					parent->SetLeft('\0');
				else
					parent->SetRight('\0');
				return child;
			}
			else if((child->GetLeft() != '\0') && (child->GetRight() == '\0'))
			{
				WordNode* pCur = child->GetLeft();
				WordNode* prev = pCur;
				while(pCur->GetRight() != '\0')
				{
					prev = pCur;
					pCur = pCur->GetRight();	//move into biggest node in child's left child
				}
				if(prev == pCur)			//if there is no child
				{
					pCur->SetRight(child->GetRight());
					parent->SetLeft(pCur);
					child->SetLeft('\0');
					child->SetRight('\0');
					return child;
				}
				else						//if thre is child
				{
					prev->SetRight(pCur->GetLeft());
					pCur->SetLeft(child->GetLeft());
					pCur->SetRight(child->GetRight());
					parent->SetLeft(pCur);
					child->SetLeft('\0');
					child->SetRight('\0');
					return child;
				}
			}
			else if((child->GetLeft() == '\0') && (child->GetRight() != '\0'))
			{
				WordNode* pCur = child->GetRight();
				WordNode* prev = pCur;
				while(pCur->GetLeft() != '\0')
				{
					prev = pCur;
					pCur = pCur->GetLeft();
				}
				if(prev == pCur)
				{
					pCur->SetLeft(child->GetLeft());
					parent->SetRight(pCur);
					child->SetLeft('\0');
					child->SetRight('\0');
					return child;
				}
				else
				{
					prev->SetLeft(pCur->GetRight());
					pCur->SetRight(child->GetRight());
					pCur->SetLeft(child->GetLeft());
					parent->SetRight(pCur);
					child->SetLeft('\0');
					child->SetRight('\0');
					return child;
				}
			}
			else
			{
				WordNode* pCur = child->GetLeft();
				WordNode* prev = pCur;
				while(pCur->GetRight()!='\0')
				{
					prev = pCur;
					pCur = pCur->GetRight();
				}
				if(prev == pCur)
				{
					pCur->SetRight(child->GetRight());
					parent->SetLeft(pCur);
					child->SetLeft('\0');
					child->SetRight('\0');
					return child;
				}
				else
				{
					prev->SetRight(pCur->GetLeft());
					pCur->SetLeft(child->GetLeft());
					pCur->SetRight(child->GetRight());
					parent->SetLeft(pCur);
					child->SetLeft('\0');
					child->SetRight('\0');
					return child;
				}
			}
		}
		else
		{
			if(strcmp(child->GetWord(), word) > 0)
				return Delete(child,child->GetLeft(), word);
			else
				return Delete(child,child->GetRight(), word);
		}
	}
	else
	{
		return '\0';
	}
}

WordNode* WordBST::Search(const char* word)
{
	return Search(root, word);
}

/*search function in use of recursive function*/
WordNode* WordBST::Search(WordNode* node, const char* word)
{
	if(node != '\0')
	{
		if(strcmp(node->GetWord(), word) == 0)
			return node;
		else
		{
			if(strcmp(node->GetWord(), word) > 0)
				return Search(node->GetLeft(), word);
			else
				return Search(node->GetRight(), word);
		}
	}
	else
		return '\0';
}

/*there are many printing way*/
bool WordBST::Print(const char* order)
{
	if(root == '\0')
		return false;
	else 
	{
		if(strcmp(order, "R_PRE") == 0)
		{
			Print_pr_re(root);
		}
		else if(strcmp(order, "I_PRE") == 0)
		{
			Print_pr_it(root);
		}
		else if(strcmp(order, "R_IN") == 0)
		{
			Print_In_re(root);
		}
		else if(strcmp(order, "I_IN") == 0)
		{
			Print_In_it(root);
		}
		else if(strcmp(order, "R_POST") == 0)
		{
			Print_po_re(root);
		}
		else if(strcmp(order, "I_POST") == 0)
		{
			Print_po_it(root);
		}
		else if(strcmp(order, "I_LEVEL") == 0)
		{
			Print_Level();
		}
		else
		{
			return false;
		}
		return true;
	}
}

/*printing nodes in recursive function*/
void WordBST::Print_In_re(WordNode* node)
{
	if(node != '\0')
	{
		Print_In_re(node->GetLeft());
		ofstream fout;
		fout.open("log.txt",ios::app);
		fout << node->GetWord() << "	" << node->GetMean() << endl;
		cout << node->GetWord() << "	" << node->GetMean() << endl;
		fout.close();
		Print_In_re(node->GetRight());
	}
}

/*printing nodes in interative traversal with stack*/
void WordBST::Print_In_it(WordNode* node)
{
	if(node == '\0')
		return;
	WordNode* ptr;
	mStack* stack = new mStack();
	ofstream fout;
	fout.open("log.txt",ios::app);
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
		fout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
		cout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
		ptr = ptr->GetRight();
	}
	fout.close();
	delete stack;
	return;
}

/*print node in postorder using recursive*/
void WordBST::Print_po_re(WordNode* node)
{
	if(node != '\0')
	{
		Print_po_re(node->GetLeft());
		Print_po_re(node->GetRight());
		ofstream fout;
		fout.open("log.txt",ios::app);
		fout << node->GetWord() << "	" << node->GetMean() << endl;
		cout << node->GetWord() << "	" << node->GetMean() << endl;
		fout.close();
	}
}

/*printing nodes in postorder with using stack*/
void WordBST::Print_po_it(WordNode* node)
{
	if(node == '\0')
		return;
	WordNode* ptr = node;
	WordNode* ptr2 = node;
	mStack* stack = new mStack();
	ofstream fout;
	fout.open("log.txt",ios::app);

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
				fout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
				cout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
				ptr2 = ptr;
				if(stack->GetHead() == '\0') return;
				ptr = stack->Pop();
			}
			stack->Push(ptr);
			ptr = ptr->GetRight();
			ptr2 = ptr;
		}
	}
	fout.close();
	delete stack;
	return;
}

/*printing node in preorder with recursive*/
void WordBST::Print_pr_re(WordNode* node)
{
	if(node != '\0')
	{
		ofstream fout;
		fout.open("log.txt",ios::app);
		fout << node->GetWord() << "	" << node->GetMean() << endl;
		cout << node->GetWord() << "	" << node->GetMean() << endl;
		fout.close();
		Print_pr_re(node->GetLeft());
		Print_pr_re(node->GetRight());
	}
}

/*printing nodes in preorder with iterative traversal using stack*/
void WordBST::Print_pr_it(WordNode* node)
{
	if(node == '\0')
		return;
	WordNode* ptr = node;
	WordNode* ptr2 = node;
	mStack* stack = new mStack();
	ofstream fout;
	fout.open("log.txt",ios::app);

	while((ptr != '\0') || (stack->GetHead() != '\0'))
	{
		if(ptr != '\0')
		{
			fout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
			cout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
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

	fout.close();
	delete stack;
	return;
}

/*it can check node's height*/
int WordBST::Height(WordNode* node)
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

/*printing nodes in levelorder*/
void WordBST::Print_Level()
{
	int h = Height(root);
	int i;
	for(i=1;i<=h;i++)
		Print_Given_Level(root,i);
}

/*printing nodes in levelorder with height value*/
void WordBST::Print_Given_Level(WordNode* node, int level)
{
	if(node == '\0')
		return;
	if(level==1)
	{
		ofstream fout;
		fout.open("log.txt",ios::app);
		fout << node->GetWord() << "	" << node->GetMean() << endl;
		cout << node->GetWord() << "	" << node->GetMean() << endl;
		fout.close();
	}
	else if(level>1)
	{
		Print_Given_Level(node->GetLeft(),level-1);
		Print_Given_Level(node->GetRight(),level-1);
	}
}

/*function saving data into memorizing_word.txt
I used stack*/
bool WordBST::Save()
{
	if(root == '\0')
		return false;
	else
	{
		WordNode* ptr = root;
		WordNode* ptr2 = root;
		mStack* stack = new mStack();
		ofstream fout;
		fout.open("memorizing_word.txt",ios::trunc);

		while((ptr != '\0') || (stack->GetHead() != '\0'))
		{
			if(ptr != '\0')
			{
				fout << ptr->GetWord() << "	" << ptr->GetMean() << endl;
				stack->Push(ptr);
				ptr = ptr->GetLeft();
			}
			else
			{
				ptr = stack->Pop();
				while((ptr->GetRight() == '\0') || (ptr->GetRight() == ptr2))
				{
					ptr2 = ptr;
					if(stack->GetHead() == '\0') return true;
					ptr = stack->Pop();
				}
				stack->Push(ptr);
				ptr = ptr->GetRight();
				ptr2 = ptr;
			}
	}

	fout.close();
	delete stack;
	return true;
	}
		return true;
}

////////////////////////////////////////////////////////////////////////////////////

/*stack for iterative traversal tree*/
mStack::mStack(void)
{
	pHead = '\0';
}

mStack::~mStack(void)
{
	WordNode* ptr = pHead;
	if(ptr != NULL)
	{
		for(WordNode* p = pHead;p != NULL; p = p->GetNext())
		{
			delete ptr;
			ptr = p;
		}
	}
}

/*node sticks into tail of stack*/
void mStack::Push(WordNode* node)
{
	if(pHead == '\0')
		pHead = node;
	else
	{
		WordNode* pCur = pHead;
		for(pCur = pHead; pCur->GetNext() != '\0'; pCur = pCur->GetNext())
		{}
		pCur->SetNext(node);
	}
}

/*node returned with clear link*/
WordNode* mStack::Pop()
{
	if(pHead == '\0')
		return '\0';
	else
	{
		WordNode* pCur = pHead;
		WordNode* prev = pCur;
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

/*just for prevention I prepared getter*/
WordNode* mStack::GetHead()
{
	return pHead;
}
