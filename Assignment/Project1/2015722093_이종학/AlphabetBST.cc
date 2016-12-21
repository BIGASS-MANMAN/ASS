#include "AlphabetBST.h"



AlphabetBST::AlphabetBST() //constructor
{
	root = '\0';  //initialization
	WordCnt = 0;
	pHead = NULL;
}

AlphabetBST::~AlphabetBST() //destructor
{
	AlphabetNode * pWork = root;
	while (pWork != NULL) //until pWork is last Node
	{
		StackPush(pWork->GetLeft());
		StackPush(pWork->GetRight());
		delete pWork; //delete Node
		pWork = StackPop();
	}
}

void AlphabetBST::Insert(AlphabetNode * node) //Insert Alphabet BST
{
	AlphabetNode * pWork, *pTemp;
	if (root == NULL) //Alphabet BST is empty
		root = node;
	else
	{
		pWork = root;
		while (pWork != NULL) //until pWork is last Node
		{
			pTemp = pWork;
			if (pWork->GetAlphabet() > node->GetAlphabet())  //pWork alphabet is larger than node alphabet
				pWork = pWork->GetLeft();
			else if (pWork->GetAlphabet() < node->GetAlphabet()) //pWork alphabet is smaller than node alphabet
				pWork = pWork->GetRight();
		}
		if (pTemp->GetAlphabet() > node->GetAlphabet())  //pWork alphabet is larger than node alphabet
			pTemp->SetLeft(node);
		else if (pTemp->GetAlphabet() < node->GetAlphabet()) //pWork alphabet is smaller than node alphabet
			pTemp->SetRight(node);
	}
}

bool AlphabetBST::Print(char * order) //alphabetBST list Print
{
	ofstream flog; //write file
	flog.open("log.txt", ios::app); //file open
	if (strcmp(order, "R_PRE") == 0) //command is R_PRE (Recursive PRE_ORDER)
	{
		flog << "======== PRINT ========" << endl;
		Preorder(root); //recursive
		flog << "====================\n" << endl;
		return 1; //Success
	}
	else if (strcmp(order, "I_PRE") == 0) //command is I_PRE (Interative PRE_ORDER)
	{
		int num = 0;
		AlphabetNode * pWork = root;
		flog << "======== PRINT ========" << endl;
		while (pWork != NULL) //until pWork is last node
		{
			if (num != 1)
				pWork->GetBST()->Print(order);
			if (pWork->GetLeft() != NULL && num != 1) //pWork Left is exist
			{
				StackPush(pWork); //Stack
				pWork = pWork->GetLeft();
				num = 0;
				continue;
			}
			if (pWork->GetRight() != NULL) //pWork Right is exist
			{
				pWork = pWork->GetRight();
				num = 0;
				continue;
			}
			pWork = StackPop(); //parents
			num = 1;
		}
		flog << "====================\n" << endl;
		return 1; //Success
	}
	else if (strcmp(order, "R_IN") == 0) //command is R_IN(Recursive INORDER)
	{
		flog << "======== PRINT ========" << endl;
		Inorder(root); //recursive
		flog << "====================\n" << endl;
		return 1; //Success
	}
	else if (strcmp(order, "I_IN") == 0) //command is I_IN(Interative INORDER)
	{
		int num = 0;
		AlphabetNode * pWork = root;
		flog << "======== PRINT ========" << endl;
		while (pWork != NULL) //until pWork is last Node
		{
			if (pWork->GetLeft() != NULL && num != 1) //pWork Left is exist
			{
				StackPush(pWork); //Stack Push
				pWork = pWork->GetLeft();
				num = 0;
				continue;
			}
			pWork->GetBST()->Print(order);
			if (pWork->GetRight() != NULL) //pWork Right is exist
			{
				pWork = pWork->GetRight();
				num = 0;
				continue;
			}
			pWork = StackPop(); //Stack Pop
			num = 1;
		}
		flog << "====================\n" << endl;
		return 1; //Success
	}
	else if (strcmp(order, "R_POST") == 0)  //command is R_POST(recursive POSTORDER)
	{
		flog << "======== PRINT ========" << endl;
		Postorder(root); //recursive
		flog << "====================\n" << endl;
		return 1; //success
	}
	else if (strcmp(order, "I_POST") == 0) //command is I_POST(Interative POSTORDER)
	{
		int num = 0;
		char temp;
		AlphabetNode * pWork = root;
		flog << "======== PRINT ========" << endl;
		while (pWork != NULL) //until pWork is last Node
		{
			if (pWork->GetLeft() != NULL && num == 0) //pWork left is exist
			{
				StackPush(pWork); //stack push
				pWork = pWork->GetLeft();
				num = 0;
				continue;
			}
			if (pWork->GetRight() != NULL && num != 2) //pWork right is exist
			{
				StackPush(pWork);
				pWork = pWork->GetRight();
				num = 0;
				continue;
			}
			pWork->GetBST()->Print(order);
			temp = pWork->GetAlphabet();
			pWork = StackPop(); //Stack POP
			if (pWork == NULL) //pWork is empty
				break;
			if (pWork->GetAlphabet() > temp)
				num = 1;
			else
				num = 2;
		}
		flog << "====================\n" << endl;
		return 1; //Success
	}
	else if (strcmp(order, "I_LEVEL") == 0) //command is I_LEVEL (Interative LEVELORDER)
	{
		AlphabetNode * pWork = root;
		flog << "======== PRINT ========" << endl;
		while (pWork != NULL) //until pWork is last Node
		{
			pWork->GetBST()->Print(order);
			if (pWork->GetLeft() != NULL)
				QueuePush(pWork->GetLeft()); //Queue Push
			if (pWork->GetRight() != NULL)
				QueuePush(pWork->GetRight());
			pWork = QueuePop(); //Queue Pop
		}
		flog << "====================\n" << endl;
		return 1; //Success
	}
	flog.close(); //file close
}

AlphabetNode * AlphabetBST::Search(char alphabet)
{
	AlphabetNode * pWork;
	if (root == NULL) //root is empty
		return 0; //Error
	else
	{
		pWork = root;
		while (pWork != NULL) //until pWork is last node
		{
			if (pWork->GetAlphabet() > alphabet)
				pWork = pWork->GetLeft();
			else if (pWork->GetAlphabet() < alphabet)
				pWork = pWork->GetRight();
			else if (pWork->GetAlphabet() == alphabet)
				return pWork; //Search is pWork Word
		}
		if (pWork == NULL)
			return 0; //Error
	}
}

bool AlphabetBST::Save()
{
	ofstream fout; //Write file
	fout.open("memorizing_word.txt", ios::trunc); //file open

	if (!fout) //file dose not open
	{
		cout << "400" << endl;
		return 0; //Error
	}
	fout.close(); //file close

	int num = 0;
	AlphabetNode * pWork = root;
	while (pWork != NULL) //until pWork is last node
	{
		if (num != 1)
			if (pWork->GetBST()->Save() == 0) //Save fail
				return 0; //Error
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
	return 1;
}

void	AlphabetBST::Preorder(AlphabetNode * node) //Preorder
{
	char temp[32] = "R_PRE";
	if (node != NULL)
	{
		node->GetBST()->Print(temp);
		Preorder(node->GetLeft());
		Preorder(node->GetRight());
	}
}

void	AlphabetBST::Inorder(AlphabetNode * node) //Inorder
{
	char temp[32] = "R_IN";
	if (node != NULL)
	{
		Inorder(node->GetLeft());
		node->GetBST()->Print(temp);
		Inorder(node->GetRight());
	}
}

void	AlphabetBST::Postorder(AlphabetNode * node) //Postorder
{
	char temp[32] = "R_POST";
	if (node != NULL)
	{
		Postorder(node->GetLeft());
		Postorder(node->GetRight());
		node->GetBST()->Print(temp);
	}
}

void	AlphabetBST::StackPush(AlphabetNode * node) //StackPush
{
	if (node == NULL) //node is not exist
		return; //Error
	node->SetNext(NULL);
	if (pHead == NULL) //Alphabet BST is empty
		pHead = node;
	else
	{
		node->SetNext(pHead);
		pHead = node;
	}
}

AlphabetNode *	AlphabetBST::StackPop() //StackPop
{
	if (pHead == NULL) //Stack is empty
		return 0; //Error
	else
	{
		AlphabetNode * pWork = pHead;
		pHead = pHead->GetNext();
		return pWork;
	}
}

void	AlphabetBST::QueuePush(AlphabetNode * node) //QueuePush
{
	AlphabetNode *pWork;

	if (node == NULL) //node is empty
		return; //Error
	pWork = pHead;
	node->SetNext(NULL);
	if (pHead == NULL) //Queue is empty
	{
		pHead = node;
	}
	else
	{
		while (pWork->GetNext() != NULL)
		{
			pWork = pWork->GetNext();
		}
		pWork->SetNext(node);
	}
}

AlphabetNode *	AlphabetBST::QueuePop() //QueuePop
{
	AlphabetNode *pWork;

	if (pHead == NULL) //Queue is empty
	{
		return 0;
	}
	pWork = pHead;
	pHead = pWork->GetNext();

	return pWork;
}
