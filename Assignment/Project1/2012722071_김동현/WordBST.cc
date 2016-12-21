#include "WordBST.h"


WordBST::WordBST()
{
	root = NULL;
}


WordBST::~WordBST()
{
	root = NULL;
}



void WordBST::Define(WordNode * getnode, WordNode * givenode)//declare this function to define nodes Word and Mean
{
	getnode->SetWord(givenode->GetWord());
	getnode->SetMean(givenode->GetMean());
}

WordNode * WordBST::Search(char * word)// this Search function is based by iterative Inorder
{
	//find same word and return that node
	Stack<WordNode *> pp;// get stack variable
	WordNode * pCur = root;
	WordNode * out = new WordNode();
	pp.Push(pCur);//push current node

	while (!pp.IsEmpty() || pCur)// if current node  or stack is empty escape while function
	{
		if (pCur)// if current node is not null
		{
			pp.Push(pCur);
			pCur = pCur->GetLeft();
		}
		else// if current node is null
		{
			pCur = pp.Top();//go to Parents node
			pp.Pop();//pop previous node
			if (pCur->GetWord() == word) out = pCur;//if currentnode and word is same
			pCur = pCur->GetRight();
		}
	}

	return out;//return node

}

bool WordBST::Save()
{
	return true;
}

void WordBST::Insert(WordNode * node)// make Wordtree in Alphabet Tree
{
	WordNode * pCur = root;
	if(root == NULL)
	{
		root = node;
		return;
	}
	while (1)
	{	// if currentnode is bigger than seek node
		if (strcmp(pCur->GetWord(), node->GetWord()) > 0)
		{
			if (pCur->GetLeft() == NULL)
			{
				pCur->SetLeft(node);
				return;
			}
			pCur = pCur->GetLeft();
		}//if currentnode is smaller than seek node
		else if (strcmp(pCur->GetWord(), node->GetWord()) < 0)
		{
			if (pCur->GetRight() == NULL)
			{
				pCur->SetRight(node);
				return;
			}
			pCur = pCur->GetRight();
		}//if currentnode is same with seek node
		else
		{
			pCur->SetMean(node->GetMean());
			return;
		}
	}
}

bool WordBST::Print(char * order)
{
	//variable dicision get order and switch to number
	int dicision = 0;
	//switching order to number
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
	//start functions 
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

void WordBST::Inorder(WordNode * currentnode)//enter the tree by inorder
{  
	if (currentnode)
	{
		Inorder(currentnode->GetLeft());
		Visit(currentnode);
		Inorder(currentnode->GetRight());;
	}
}

void WordBST::preorder(WordNode * currentnode)//enter the tree by preorder
{
	if (currentnode)
	{
		Visit(currentnode);
		preorder(currentnode->GetLeft());
		preorder(currentnode->GetRight());
	}
}

void WordBST::postorder(WordNode * currentnode)//enter the tree by postorder
{
	if (currentnode)
	{
		postorder(currentnode->GetLeft());
		postorder(currentnode->GetRight());
		Visit(currentnode);
	}
}

void WordBST::IterativeInorder(WordNode * currentnode)//enter the tree by Iterativeinorder
{
	//find same word
	Stack<WordNode *> pp;// declare stack variable
	WordNode * pCur = root;
	pp.Push(pCur);//push current node

	while (!pp.IsEmpty() || pCur)//if currentnode or stack is empty, escape while function
	{
		if (pCur)//if pCur is not null, push current node and get left
		{
			pp.Push(pCur);
			pCur = pCur->GetLeft();
		}
		else// if pCur is null, pCur get Top of pp and before node is pop
		{
			pCur = pp.Top();
			pp.Pop();
			Visit(currentnode);
			pCur = pCur->GetRight();
		}
	}
}

void WordBST::Iterativepreorder(WordNode * currentnode)//enter the tree by Iterativepreorder
{
	Stack<WordNode*> pp;
	while (1)
	{
		while (currentnode)
		{
			Visit(currentnode);
			pp.Push(currentnode);
			currentnode = currentnode->GetLeft();
		}
		if (pp.IsEmpty())
			return;
		currentnode = pp.Top();
		pp.Pop();

		currentnode = currentnode->GetRight();
	}
}

void WordBST::Iterativepostorder(WordNode* root)//enter the tree by Iterativepostorder
{
	if (root == NULL)
		return;

	Stack<WordNode* > stack, result;// postorder get 2 stack variable, first stack variable make stack and seconde stack make pop
	WordNode * pNew;
	// we use do_while 
	do {
		stack.Push(root);//push current node
		WordNode* pCur = stack.Top();// pCur get Parents node
		result.Push(pCur);//push pCur by result
		stack.Pop();
		// if left side of pCur is not null, push left side
		if (pCur->GetLeft() != NULL)
			stack.Push(pCur->GetLeft());
		// if right side of pCur is not null, push right side
		if (pCur->GetLeft() != NULL)
			stack.Push(pCur->GetLeft());

	} while (stack.IsEmpty());//when stack is empty, escape while function

	while (result.IsEmpty()) {//when result stack is empty, escape while function

		pNew = result.Top();
		Visit(pNew);//print pNew
		result.Pop();
	}

}

void WordBST::Levelorder(WordNode * currentnode)//enter the tree by Levelorder
{
	queue<WordNode *> Q;// Q is queue variable

	if (root == NULL)
		return;

	Q.push(currentnode);//push current node

	while (!Q.empty())
	{
		WordNode * node = Q.front();
		Q.pop();

		Visit(node);

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

void WordBST::Visit(WordNode * currentnode)
{
	cout << currentnode->GetWord() << " " << currentnode->GetMean() << endl;//print current node's Word and Mean
}

WordNode* WordBST::Delete(char* word)
{
	WordNode* p = root;
	WordNode* q = NULL;      //q is parent of p

	while (p&&strcmp(p->GetWord(), word) != 0) {      //Find the word that you want to delete
		q = p;
		if (strcmp(p->GetWord(), word) < 0)
			p = p->GetRight();
		else
			p = p->GetLeft();
	}

	if (p == NULL)
		return NULL;      //No find node

	if (p->GetLeft() == NULL && p->GetRight() == NULL) {      //The delete node is leaf node
		if (q == NULL)
			root = NULL;

		else if (q->GetLeft() == p)
			q->SetLeft(NULL);
		else
			q->SetRight(NULL);

		return p;
	}

	else if (p->GetLeft() == NULL) {   //The delete node that have only right the child
									   //It is replaced by the smallest value in the right subtree
		WordNode* prevprev = p;
		WordNode* prev = p->GetRight();
		WordNode* curr = p->GetRight()->GetLeft();

		while (curr != NULL) {
			prevprev = prev;
			prev = curr;
			curr = curr->GetLeft();
		}

		p->SetWord(prev->GetWord());
		p->SetMean(prev->GetMean());

		if (prevprev == p)
			prevprev->SetRight(prev->GetRight());
		else
			prevprev->SetLeft(prev->GetRight());

		return prev;
	}

	else if (p->GetRight() == NULL || (p->GetLeft() != NULL && p->GetRight() != NULL)) {   //The delete node that have only left the child
																						   //or when both the left child and right child
																						   //It is replaced by the biggest value in the left subtree
		WordNode* prevprev = p;
		WordNode* prev = p->GetLeft();
		WordNode* curr = p->GetLeft()->GetRight();

		while (curr != NULL) {
			prevprev = prev;
			prev = curr;
			curr = curr->GetRight();
		}

		p->SetWord(prev->GetWord());
		p->SetMean(prev->GetMean());

		if (prevprev == p)
			prevprev->SetLeft(prev->GetLeft());
		else
			prevprev->SetRight(prev->GetLeft());

		return prev;
	}
	return NULL;
}
