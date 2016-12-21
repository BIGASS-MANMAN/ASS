#include "WordBST.h"

WordBST::WordBST()
{
	root = NULL;
	
}
WordBST::~WordBST()
{
	Destroy(root);
}
void WordBST::Destroy(WordNode* node)
{
	if (node != NULL)
	{
		Destroy(node->GetLeft());
		Destroy(node->GetRight());
		delete node;
	}
}
WordNode* WordBST::Get_Root()
{
	return root; 
}

void WordBST::Insert(WordNode* node)
{
	WordNode* pCur = root;
	WordNode* pPre = NULL;
	if (root == NULL)
	{
		root = node;
		return;
	}
	while (pCur)
	{
		pPre = pCur;
		if ( strcmp(node->GetWord(), pCur->GetWord()) == -1)
			pCur = pCur->GetLeft();
		else if (strcmp(node->GetWord(), pCur->GetWord()) == 1)
			pCur = pCur->GetRight();
		else
		{
			delete node;
			return;
		}
	}
	
	if (strcmp(node->GetWord(), pPre->GetWord()) == -1)
		pPre->SetLeft(node);
	else
		pPre->SetRight(node);
	
}

WordNode* WordBST::Delete(char* word)
{
	WordNode* pCur = root;
	WordNode* parent = 0;

	while (strcmp(word, pCur->GetWord()) != 0)	//search the word
	{
		parent = pCur;
		if (strcmp(word, pCur->GetWord()) < 0)//if word is smaller than word of pCur, go left									
			pCur = pCur->GetLeft();
		else
			pCur = pCur->GetRight();//if word is bigger than word of pCur, go right
	}

	if (pCur == 0)	//if wordnode have not word for delete
		return 0;

	if (pCur->GetLeft() == 0 && pCur->GetRight() == 0)//if word node is leaf
	{
		if (parent == 0)
			root = 0;
		else if (parent->GetLeft() == pCur)//if it node is parent left child									
			parent->SetLeft(0);
		else//if it node is parent right child
			parent->SetRight(0);

		return pCur;
	}

	
	if (pCur->GetLeft() == 0)      //if it have a rightchild node
	{
	if (parent == 0)
	root = pCur->GetRight();
	else if (parent->GetLeft() == pCur)
	parent->SetLeft(pCur->GetRight());
	else
	parent->SetRight(pCur->GetRight());
	return pCur;
	}

	if (pCur->GetRight() == 0)   //if it have a leftchild node
	{
	if (parent == 0)
	root = pCur->GetLeft();
	else if (parent->GetLeft() == pCur)
	parent->SetLeft(pCur->GetLeft());
	else
	parent->SetRight(pCur->GetLeft());
	
	return pCur;
	}
	

	WordNode *prevprev = pCur, *prev = pCur->GetRight(), *curr = NULL;
	if (prev != NULL)
		curr = pCur->GetRight()->GetLeft(); //if node degree is 1,2

	while (curr)	//search a delete node and change node 							
	{//it is nearest word
		prevprev = prev;
		prev = curr;
		curr = curr->GetLeft();
	}
	WordNode *re = new WordNode;
	re->SetWord(pCur->GetWord());
	re->SetMean(pCur->GetMean());
	pCur->SetWord(prev->GetWord());				// change the nearest word	
	pCur->SetMean(prev->GetMean());
	if (prevprev == pCur)
		prevprev->SetRight(prev->GetRight());
	else
		prevprev->SetLeft(prev->GetRight());
	return re;
}
WordNode* WordBST::Search(char* word)
{
	int i = 0;
	WordNode* pCur = root;
	
	while (*(word + i) != '\0')
	{
		if (*(word + i) >= 'A' && *(word + i) <= 'Z')
			*(word + i) += 32;
		i++;
	}

	while (pCur)//if pCur is not empty
	{
		if (strcmp(word, pCur->GetWord()) < 0)  //search that if word is smaller than pCur word, go left
			pCur = pCur->GetLeft();
		else if (strcmp(word, pCur->GetWord()) > 0)//search that if word is bigger than pCur word, go right
			pCur = pCur->GetRight();
		else//if search to have same word,return that pCur
			return pCur;
	}

	if (pCur == NULL)//it is have not same word
		return 0;
	return NULL;
}
bool WordBST::Print(char* order)
{
	if (strcmp("R_PRE", order) == 0)//go to preorder
	{
		preorder();
		return true;
	}
	if (strcmp("I_PRE", order) == 0)//go to Nonrecpreorder
	{
		Nonrecpreorder();
		return true;
	}
	if (strcmp("R_IN", order) == 0)//go to Inorder
	{
		Inorder();
		return true;
	}
	if (strcmp("I_IN", order) == 0)//go to NonrecInorder
	{
		NonrecInorder();
		return true;
	}
	if (strcmp("R_POST", order) == 0)//go to postorder
	{
		postorder();
		return true;
	}
	if (strcmp("I_POST", order) == 0)//go to Nonrecpostorder
	{
		Nonrecpostorder();
		return true;
	}
	if (strcmp("I_LEVEL", order) == 0)//go to Levelorder
	{
		Levelorder();
		return true;
	}
	return false;
}
bool WordBST::Save()
{
	Stack<WordNode*> s;                          //stack variable declaration
	WordNode *currentNode = root;
	ofstream fout;
	fout.open("memorizing_word.txt", ios::app);

	if (root == '\0')
		return false;

	while (1)
	{
		while (currentNode)                          //roop that currentnode is not null
		{
			fout << currentNode->GetWord() << "	" << currentNode->GetMean() << endl;
			s.Push(currentNode);                      // push in stack
			currentNode = currentNode->GetLeft();
		}
		if (s.isempty()) break;                       //when stack is empty, go out the function
		currentNode = s.Top();                       //currentnode point to top node in stack
		s.Pop();                                     //pop top node in stack                   
		currentNode = currentNode->GetRight();       //go to rightchild
	}
	fout.close();
	return true;
}

void WordBST::Visit(WordNode *currentNode)//store word log.txt 
{
	ofstream fout;
	fout.open("log.txt", ios::app);
	fout << currentNode->GetWord() << "	" << currentNode->GetMean() << endl;
	fout.close();
}
void WordBST::preorder()
{
	preorder(root);
}
void WordBST::preorder(WordNode *currentNode)//preorder method
{
	if (currentNode) {
		Visit(currentNode);//print
		preorder(currentNode->GetLeft());//go to leftside
		preorder(currentNode->GetRight()); // go to rightside

	}
}
void WordBST::Nonrecpreorder()
{
	Stack<WordNode*> s;                          //stack variable declaration
	WordNode *currentNode = root;
	while (1)
	{
		while (currentNode)                          //roop that currentnode is not null
		{
			Visit(currentNode);						//print
			s.Push(currentNode);                      // push in stack
			currentNode = currentNode->GetLeft();
		}
		if (s.isempty()) return;                       //when stack is empty, go out the function
		currentNode = s.Top();                       //currentnode point to top node in stack
		s.Pop();                                     //pop top node in stack                   
		currentNode = currentNode->GetRight();       //go to rightchild
	}
}
void WordBST::Inorder()
{
	Inorder(root);
}
void WordBST::Inorder(WordNode *currentNode)
{
	if (currentNode) {
		Inorder(currentNode->GetLeft());//go to leftside
		Visit(currentNode);
		Inorder(currentNode->GetRight()); // go to rightside
	}
}
void WordBST::NonrecInorder()
{
	Stack<WordNode*> s;                          //stack variable declaration
	WordNode *currentNode = root;
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
		Visit(currentNode);                      //go to BST
		currentNode = currentNode->GetRight();       //go to rightchild
	}
}
void WordBST::postorder()
{
	postorder(root);
}
void WordBST::postorder(WordNode *currentNode)
{
	if (currentNode) {

		postorder(currentNode->GetLeft());//go to leftside
		postorder(currentNode->GetRight()); // go to rightside
		Visit(currentNode);
	}
}
void WordBST::Nonrecpostorder()
{
	Stack<WordNode*> s;                          //stack variable declaration

	while (1)
	{
		if (!root) return;

		s.Push(root);//root insert in stack
		WordNode *prev = NULL;

		while (!s.isempty())//break if stack is empty
		{
			WordNode *curr = s.Top();//curr is point top of stack
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
				Visit(curr);
				s.Pop();
			}
			prev = curr;
		}
		if (s.isempty())
			break;
	}
}
void WordBST::Levelorder()
{
	Queue q;                          //queue variable declaration
	WordNode *currentNode = root;

	while (currentNode)                          //roop that currentnode is not null
	{
		Visit(currentNode);                      //print
		if (currentNode->GetLeft()) q.Push(currentNode->GetLeft());     //leftchild push
		if (currentNode->GetRight()) q.Push(currentNode->GetRight());   //rightchild push
		if (q.IsEmpty())
			return;
		currentNode = q.Pop(); //top of queue
	}
}

