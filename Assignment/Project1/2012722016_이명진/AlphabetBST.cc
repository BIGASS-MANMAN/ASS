#include "AlphabetBST.h"

AlphabetBST::AlphabetBST()
{
	AlphabetNode* pNew = NULL;
	char AlpArr[ALPHABET_CNT] = "phxdltzbfjnrvyacegikmoqsuw";
	root = NULL;
	WordCnt = 0;
	//allocate alphabet node bst
	for(int i=0; i<ALPHABET_CNT-1; i++)
	{
		pNew = new AlphabetNode;
		pNew->SetAlphabet(AlpArr[i]);
		Insert(pNew);
	}	
}
AlphabetBST::~AlphabetBST()
{
	//recursive deallocate
	Destroy(root);
}
void AlphabetBST::Destroy(AlphabetNode* node)
{
	if (node != NULL)
	{
		//finding all left from node
		Destroy(node->GetLeft());
		//find all right from node
		Destroy(node->GetRight());
		delete node;
	}
}
void AlphabetBST::Insert(AlphabetNode* node)
{
	AlphabetNode* pCur = root;
	AlphabetNode* pPre = NULL;

	if (root == NULL)
	{
		root = node;
		return;
	}

	while (pCur)
	{
		pPre = pCur;
		//move node to left child
		if (pCur->GetAlphabet() > node->GetAlphabet())
			pCur = pCur->GetLeft();
		//move node to Right child
		else if (pCur->GetAlphabet() < node->GetAlphabet())
			pCur = pCur->GetRight();
		else
		{
			//no matching
			delete node;
			return;
		}
	}
	
	//set left if new node is smaller
	if (node->GetAlphabet() < pPre->GetAlphabet())
		pPre->SetLeft(node);
	//set right if new node is bigger
	else
		pPre->SetRight(node);
}
bool AlphabetBST::Print(char * order)
{
	if (strcmp("R_PRE", order) == 0)//go to preorder
	{
		preorder();
		return true;
	}
	else if (strcmp("I_PRE", order) == 0)//go to Nonrecpreorder
	{
		Nonrecpreorder();
		return true;

	}
	else if (strcmp("R_IN", order) == 0)//go to Inorder
	{
		Inorder();
		return true;
	}
	else if (strcmp("I_IN", order) == 0)//go to NonrecInorder
	{
		NonrecInorder();
		return true;
	}
	else if (strcmp("R_POST", order) == 0)//go to postorder
	{
		postorder();
		return true;
	}
	else if (strcmp("I_POST", order) == 0)//go to Nonrecpostorder
	{
		Nonrecpostorder();
		return true;
	}
	else if (strcmp("I_LEVEL", order) == 0)//go to Levelorder
	{
		Levelorder();
		return true;
	}
	else
		return false;
}
AlphabetNode* AlphabetBST::Search(char alpabet)
{
	AlphabetNode* pCur = root;
	if (root == NULL)
		return NULL;
	while (pCur)
	{
		//make alphabets lower capital
		if (alpabet >= 'A' && alpabet <= 'Z')
			alpabet += 32;
		//get left child if data is smaller
		if (alpabet < pCur->GetAlphabet())
			pCur = pCur->GetLeft();
		//get right child if data is bigger
		else if (alpabet > pCur->GetAlphabet())
			pCur = pCur->GetRight();
		//if data is same. return
		else
			return pCur;
	}
	return NULL;
}
bool AlphabetBST::Save()
{
	WordBST *bst;
	Stack<AlphabetNode*> s;                          //stack variable declaration
	AlphabetNode *currentNode = root;

	if (root == '\0')
		return false;

	while (1)
	{
		while (currentNode)                          //roop that currentnode is not null
		{
			bst = currentNode->GetBST();             //go to BST
			bst->Save();
			s.Push(currentNode);                      // push in stack
			currentNode = currentNode->GetLeft();
		}
		if (s.isempty()) break;                       //when stack is empty, go out the function
		currentNode = s.Top();                       //currentnode point to top node in stack
		s.Pop();                                     //pop top node in stack                   
		currentNode = currentNode->GetRight();       //go to rightchild
	}
	return true;
}

void AlphabetBST::preorder()
{
	preorder(root);
}
void AlphabetBST::preorder(AlphabetNode *currentNode)
{
	WordBST *bst;
	if (currentNode) {
		bst = currentNode->GetBST();
		bst->Print("R_PRE");
		preorder(currentNode->GetLeft());//go to leftside
		preorder(currentNode->GetRight()); // go to rightside
	}
}
void AlphabetBST::Nonrecpreorder()
{
	WordBST *bst;
	Stack<AlphabetNode*> s;                          //stack variable declaration
	AlphabetNode *currentNode = root;
	while (1)
	{
		while (currentNode)                          //roop that currentnode is not null
		{
			bst = currentNode->GetBST();             //go to BST
			bst->Print("I_PRE");
			s.Push(currentNode);                      // push in stack
			currentNode = currentNode->GetLeft();
		}
		if (s.isempty()) return;                       //when stack is empty, go out the function
		currentNode = s.Top();                       //currentnode point to top node in stack
		s.Pop();                                     //pop top node in stack                   
		currentNode = currentNode->GetRight();       //go to rightchild
	}
}
void AlphabetBST::Inorder()
{
	Inorder(root);
}
void AlphabetBST::Inorder(AlphabetNode *currentNode)
{
	WordBST *bst;
	if (currentNode) {
		Inorder(currentNode->GetLeft());//go to leftside
		bst = currentNode->GetBST();
		bst->Print("R_IN");
		Inorder(currentNode->GetRight()); // go to rightside
	}
}
void AlphabetBST::NonrecInorder()
{
	WordBST *bst;
	Stack<AlphabetNode*> s;                          //stack variable declaration
	AlphabetNode *currentNode = root;
	while (1)
	{
		while (currentNode)                          //roop that currentnode is not null
		{
			s.Push(currentNode);                      // push in stack
			currentNode = currentNode->GetLeft();
		}
		if (s.isempty()) return;                       //when stack is empty, go out the function
		currentNode = s.Top();                       //currentnode point to top node in stack
		s.Pop();                                     //pop top node in stack
		bst = currentNode->GetBST();
		bst->Print("I_IN");                        //go to BST
		currentNode = currentNode->GetRight();       //go to rightchild
	}
}
void AlphabetBST::postorder()
{
	postorder(root);
}
void AlphabetBST::postorder(AlphabetNode *currentNode)
{
	WordBST *bst;
	if (currentNode) {

		postorder(currentNode->GetLeft());//go to leftside
		postorder(currentNode->GetRight()); // go to rightside
		bst = currentNode->GetBST();
		bst->Print("R_POST");
	}
}
void AlphabetBST::Nonrecpostorder()
{
	WordBST *bst;
	Stack<AlphabetNode*> s;                          //stack variable declaration

	while (1)
	{
		if (!root) return;

		s.Push(root);//root insert in stack
		AlphabetNode *prev = NULL;

		while (!s.isempty())//break if stack is empty
		{
			AlphabetNode *curr = s.Top();//curr is point top of stack
			if (!prev || prev->GetLeft() == curr || prev->GetRight() == curr)
			{//prev is null or left of prev is same curr or right of prev is same curr
				if (curr->GetLeft())//if it have left of curr
					s.Push(curr->GetLeft());//push in stack
				else if (curr->GetRight())//if it have not left of curr and have right of curr
					s.Push(curr->GetRight());//push in stack
			}
			else if (curr->GetLeft() == prev)//left of curr is same prev
			{//it is prev is already push
				if (curr->GetRight())
					s.Push(curr->GetRight());
			}
			else
			{
				bst = curr->GetBST();//get bst of currentNode 
				bst->Print("I_POST");
				s.Pop();
			}
			prev = curr;
		}
		if (s.isempty())
			break;
	}
}
void AlphabetBST::Levelorder()
{
	Queue q;                          //queue variable declaration
	AlphabetNode *currentNode = root;
	WordBST *bst;

	if (currentNode == NULL)
		return;

	while (currentNode)                          //roop that currentnode is not null
	{
		bst = currentNode->GetBST();
		if (bst->root != NULL)
		{
			bst->Print("I_LEVEL");
		}//print

		if (currentNode->GetLeft())
			q.alPush(currentNode->GetLeft());     //leftchild push
		if (currentNode->GetRight())
			q.alPush(currentNode->GetRight());   //rightchild push
		
		if (q.alisempty())
			return;
		currentNode = q.alPop();
	}
}