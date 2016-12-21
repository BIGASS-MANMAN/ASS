#include "WordBST.h"



WordBST::WordBST() //constructor
{
	root = '\0'; //initialization
	pHead = NULL;
}


WordBST::~WordBST() //destructor
{
	WordNode * pWork = root;
	while (pWork != NULL)
	{
		StackPush(pWork->GetLeft());
		StackPush(pWork->GetRight());
		delete pWork; //delete Node
		pWork = StackPop(); //stackpop
	}
}

void	WordBST::Insert(WordNode * node)	//Insert Node
{
	WordNode * pWork, *pTemp;
	if (root == NULL) //WordBST is empty
		root = node;
	else
	{
		pWork = root;
		while (pWork != NULL) //until pWork is last node
		{
			pTemp = pWork;
			if (strcmp(pWork->GetWord(), node->GetWord()) > 0)
				pWork = pWork->GetLeft();
			else if (strcmp(pWork->GetWord(), node->GetWord()) < 0)
				pWork = pWork->GetRight();
		}
		if (strcmp(pTemp->GetWord(), node->GetWord()) > 0)
			pTemp->SetLeft(node);
		else if (strcmp(pTemp->GetWord(), node->GetWord()) < 0)
			pTemp->SetRight(node);
	}
}

WordNode *	WordBST::Delete(char * word) //Delete Node
{
	WordNode * pWork, *pTemp;
	if (root == NULL) //tree is empty
		return 0;
	else
	{
		pWork = root;
		while (pWork != NULL)//until pWork is last node
		{
			pTemp = pWork;
			if (strcmp(pWork->GetWord(), word) > 0)
				pWork = pWork->GetLeft();
			else if (strcmp(pWork->GetWord(), word) < 0)
				pWork = pWork->GetRight();
			else if (strcmp(pWork->GetWord(), word) == 0)
				break;
		}
		if (pWork == NULL)
			return 0;
		if (pWork->GetLeft() == NULL && pWork->GetRight() == NULL)//leaf
		{
			if (pWork == root)
				root = NULL;
			else if (pTemp->GetLeft() == pWork)
				pTemp->SetLeft(NULL);
			else if (pTemp->GetRight() == pWork)
				pTemp->SetRight(NULL);
			return pWork;
		}
		else if (pWork->GetLeft() == NULL)//right
		{
			if (pWork == root)
				root = pWork->GetRight();
			else if (pTemp->GetLeft() == pWork)
				pTemp->SetLeft(pWork->GetRight());
			else if (pTemp->GetRight() == pWork)
				pTemp->SetRight(pWork->GetRight());
			return pWork;
		}
		else if (pWork->GetRight() == NULL)//left
		{
			if (pWork == root)
				root = pWork->GetLeft();
			else if (pTemp->GetLeft() == pWork)
				pTemp->SetLeft(pWork->GetLeft());
			else if (pTemp->GetRight() == pWork)
				pTemp->SetRight(pWork->GetLeft());
			return pWork;
		}
		else//2 degree
		{
			pTemp = pWork;
			WordNode * pPrev = pWork;
			char temp[2][32];
			strcpy(temp[0], pTemp->GetWord());
			strcpy(temp[1], pTemp->GetMean());
			pWork = pWork->GetLeft();
			while (pWork->GetRight() != NULL)
			{
				pPrev = pWork;
				pWork = pWork->GetRight();
			}
			pTemp->SetWord(pWork->GetWord());
			pTemp->SetMean(pWork->GetMean());
			if (pPrev == pTemp)
				pPrev->SetLeft(pWork->GetLeft());
			else
				pPrev->SetRight(pWork->GetLeft());
			pWork->SetWord(temp[0]);
			pWork->SetMean(temp[1]);
			return pWork; //Delete pWork
		}
	}
}

WordNode *	WordBST::Search(char * word)	//Search Word
{
	WordNode * pWork;
	if (root == NULL)  //tree is empty
		return 0;
	else
	{
		pWork = root;
		while (pWork != NULL)  //until pWork is last node
		{
			if (strcmp(pWork->GetWord(), word) > 0)
				pWork = pWork->GetLeft();
			else if (strcmp(pWork->GetWord(), word) < 0)
				pWork = pWork->GetRight();
			else if (strcmp(pWork->GetWord(), word) == 0)
				return pWork;
		}
		if (pWork == NULL)  //pWork is last node
			return 0;
	}
}

bool	WordBST::Print(char * order) //Print WordBST
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	if (strcmp(order, "R_PRE") == 0)  //recursive Preorder
	{
		Preorder(root);  //recursive
		flog.close();
		return 1;
	}
	else if (strcmp(order, "I_PRE") == 0)  //Interative Preorder
	{
		int num = 0;
		WordNode * pWork = root;
		while (pWork != NULL)  //until pWork is last node
		{
			if (num != 1)
				flog << pWork->GetWord() << " " << pWork->GetMean() << endl;
			if (pWork->GetLeft() != NULL && num != 1)
			{
				StackPush(pWork);
				pWork = pWork->GetLeft();
				num = 0;
				continue;
			}
			if (pWork->GetRight() != NULL)
			{
				pWork = pWork->GetRight();
				num = 0;
				continue;
			}
			pWork = StackPop();  //stacek pop
			num = 1;
		}
		flog.close();
		return 1;  //success
	}
	else if (strcmp(order, "R_IN") == 0)  //recursive Inorder
	{
		Inorder(root);  //recursive
		flog.close();
		return 1;
	}
	else if (strcmp(order, "I_IN") == 0)  //Interative Inorder
	{
		int num = 0;
		WordNode * pWork = root;
		while (pWork != NULL)  //until pWork is last node
		{
			if (pWork->GetLeft() != NULL && num != 1)
			{
				StackPush(pWork);
				pWork = pWork->GetLeft();
				num = 0;
				continue;
			}
			flog << pWork->GetWord() << " " << pWork->GetMean() << endl;
			if (pWork->GetRight() != NULL)
			{
				pWork = pWork->GetRight();
				num = 0;
				continue;
			}
			pWork = StackPop();  //Stack pop
			num = 1;
		}
		flog.close(); //file close
		return 1;  //success
	}
	else if (strcmp(order, "R_POST") == 0)  //recursive Postorder
	{
		Postorder(root);  //recursive
		flog.close();
		return 1;
	}
	else if (strcmp(order, "I_POST") == 0)  //Interative Postorder
	{
		int num = 0;
		char temp[32];
		WordNode * pWork = root;
		while (pWork != NULL) //until pWork is last node
		{
			if (pWork->GetLeft() != NULL && num == 0)
			{
				StackPush(pWork);
				pWork = pWork->GetLeft();
				num = 0;
				continue;
			}
			if (pWork->GetRight() != NULL && num != 2)
			{
				StackPush(pWork);
				pWork = pWork->GetRight();
				num = 0;
				continue;
			}
			flog << pWork->GetWord() << " " << pWork->GetMean() << endl;
			strcpy(temp, pWork->GetWord());
			pWork = StackPop();
			if (pWork == NULL)
				break;
			if (strcmp(pWork->GetWord(), temp) > 0)
				num = 1;
			else
				num = 2;
		}
		flog.close();
		return 1; //success
	}
	else if (strcmp(order, "I_LEVEL") == 0) //Interative Levelorder
	{
		Queue q;
		WordNode * pWork = root;
		while (pWork != NULL)
		{
			flog << pWork->GetWord() << " " << pWork->GetMean() << endl;
			if (pWork->GetLeft() != NULL)
				q.Push(pWork->GetLeft());
			if (pWork->GetRight() != NULL)
				q.Push(pWork->GetRight());
			pWork = q.Pop();
		}
		flog.close();
		return 1;
	}
}

bool	WordBST::Save() //Save wordBST
{
	ofstream fout; //write file
	fout.open("memorizing_word.txt", ios::app); //file open

	if (!fout) //file is not open
	{
		ofstream flog;
		flog.open("log.txt",ios::app);
		flog << "400" << endl;
		flog.close();
		return 0;  //Error
	}

	int num = 0;
	WordNode * pWork = root;
	while (pWork != NULL)  //until pWork is last node
	{
		if (num != 1)
			fout << pWork->GetWord() << " " << pWork->GetMean() << endl;
		if (pWork->GetLeft() != NULL && num != 1)
		{
			StackPush(pWork);
			pWork = pWork->GetLeft();
			num = 0;
			continue;
		}
		if (pWork->GetRight() != NULL)
		{
			pWork = pWork->GetRight();
			num = 0;
			continue;
		}
		pWork = StackPop();
		num = 1;
	}
	fout.close(); //file close
	return 1;
}

void	WordBST::Preorder(WordNode * node) //preorder
{
	if (node != NULL)
	{
		ofstream flog;
		flog.open("log.txt", ios::app);
		flog << node->GetWord() << " " << node->GetMean() << endl;
		flog.close();
		Preorder(node->GetLeft());
		Preorder(node->GetRight());
	}
}

void	WordBST::Inorder(WordNode * node) //Inorder
{
	if (node != NULL)
	{
		Inorder(node->GetLeft());
		ofstream flog;
		flog.open("log.txt", ios::app);
		flog << node->GetWord() << " " << node->GetMean() << endl;
		flog.close();
		Inorder(node->GetRight());
	}
}

void	WordBST::Postorder(WordNode * node) //Postorder
{
	if (node != NULL)
	{
		Postorder(node->GetLeft());
		Postorder(node->GetRight());
		ofstream flog;
		flog.open("log.txt", ios::app);
		flog << node->GetWord() << " " << node->GetMean() << endl;
		flog.close();
	}
}

void	WordBST::StackPush(WordNode * node) //StackPush
{
	if (node == NULL)
		return;
	node->SetNext(NULL);
	if (pHead == NULL)
		pHead = node;
	else
	{
		node->SetNext(pHead);
		pHead = node;
	}
}

WordNode *	WordBST::StackPop()  //Stackpop
{
	if (pHead == NULL)
		return 0;
	else
	{
		WordNode * pWork = pHead;
		pHead = pHead->GetNext();
		return pWork;
	}
}
