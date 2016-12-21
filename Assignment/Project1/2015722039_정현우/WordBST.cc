#include "WordBST.h"
#include "Queue.h"

using namespace std;

WordBST::WordBST()							// constructor
{	
	root = NULL; ;							//initialize root
	fo.open("memorizing_word.txt",ios::app);//open memoriziong_word.txt in fo
}

WordBST::~WordBST()							//destructor
{											//delete in Poset order
	Stack<WordNode> Astack;					//Astack for Post order
	Stack<WordNode> Bstack;					//Bstack for Post order
	WordNode * node;						//move node
	Astack.push(root);
	while (!Astack.empty())					//this work in Post order that parent is not delete while all of child is delete
	{										//while Astack don't have node loop is acting
		node = Astack.pop();				//Astack give stack's top to node
		Bstack.push(node);					//Bstack have node at top
		if (node == NULL)					//node is NULL -> end
			return;
		if (node->GetLeft())				//if node have child, Astack have that at top
			Astack.push(node->GetLeft());
		if (node->GetRight())
			Astack.push(node->GetRight());
	}
	while (!Bstack.empty())					//delete all of Bstack's node
	{
		delete Bstack.pop();
	}
	fo.close();
}
void		WordBST::Insert(WordNode * node)													// use in LOAD, MOVE / insert Word Node
{
	if (root) {																					//if root exit
		WordNode * pWork = root;
		WordNode * pWork2 = root;
		while (pWork)																			//it is pre order insert , while pWork isn't 0
		{
			pWork2 = pWork;								
			if (strcmp(pWork->GetWord(), node->GetWord()) > 0) pWork = pWork->GetLeft();		//if pWork's word is first in word dictionary then node pWork go to left
			else if (strcmp(pWork->GetWord(), node->GetWord()) < 0) pWork = pWork->GetRight();  // else if not equal , go to right
			else																				//if equal, break
				break;
		}
		if (strcmp(pWork2->GetWord(), node->GetWord()) > 0) pWork2->SetLeft(node);				//if  pWork2's word is first in word dictionary then node, node = pWork2's left child
		else if (strcmp(pWork2->GetWord(), node->GetWord()) < 0) pWork2->SetRight(node);		// else if not equal , right child
	}
	else root = node;																			//if root is NULL, root == node
}

WordNode *	WordBST::Delete(char * word)				 
{
	WordNode *pWork = root, *pPrev = NULL;				 //this work at project's roll
	while (pWork && strcmp(word, pWork->GetWord()))		 //find delete node
	{
		pPrev = pWork;
		if (strcmp(pWork->GetWord(), word) > 0)	
		{
			pWork = pWork->GetLeft();
		}
		else
		{
			pWork = pWork->GetRight();
		}
	}
	if (!pWork) return NULL;

	else if (!(pWork->GetLeft()) && !(pWork->GetRight()))	//if delete node don't has child
	{
		if (!pPrev) {										//if root is delete node, delete root
			root = NULL;
		}
		else if (pPrev->GetLeft() == pWork)					// else if node is parent's left , parent's left is NULL
		{
			pPrev->SetLeft(NULL);
		}
		else if (pPrev->GetRight() == pWork)				// else if node is parent's right, parent's right is NULL
		{
			pPrev->SetRight(NULL);
		}
		return pWork;										//return pWork
	}
	else if (!(pWork->GetLeft()))							//if delete node has only right child
	{														
		if (!pPrev) {										//if delete node is root
			root = pWork->GetRight();						//root is root's right child
		}													
		else if (pPrev->GetLeft() == pWork)					//else if node is parent's left, parent's left is NULL
			pPrev->SetLeft(pWork->GetRight());				
		else if (pPrev->GetRight() == pWork)				//else if node is parent's right, parent's right is NULL
			pPrev->SetRight(pWork->GetRight());				
		return pWork;										//return delete node
	}														
	else if (!(pWork->GetRight()))							//if delete node has only left child
	{														
		if (!pPrev) {										//if delete node is root
			root = pWork->GetLeft();						//root is root's left child
		}													
		else if (pPrev->GetLeft() == pWork)					//else if node is parent's left, parent's left is NULL
			pPrev->SetLeft(pWork->GetLeft());				
		else if (pPrev->GetRight() == pWork)				//else if node is parent's right, parent's right is NULL
			pPrev->SetRight(pWork->GetLeft());				
		return pWork;										//return delete node
	}														
	else {													//if node has 2 degree child
		WordNode *prevprev = pWork;								
		WordNode *prev = pWork->GetLeft();						
		WordNode *curr = pWork->GetLeft()->GetRight();
		while (curr)										//find delete node's biggist node little then delete node 
		{
			prevprev = prev;
			prev = curr;
			curr = curr->GetRight();						//go to curr's right child
		}
		WordNode *New = new WordNode;						//make new node
		New->SetMean(pWork->GetMean());
		New->SetWord(pWork->GetWord());
		pWork->SetWord(prev->GetWord());
		pWork->SetMean(prev->GetMean());
		if (prevprev == pWork) prevprev->SetLeft(prev->GetLeft());	//if prevprev == pWork, prev->Getleft is prevprev's left
		else prevprev->SetRight(prev->GetLeft());			//else prevprev's right child is prev's leftchild
		delete prev;										//delete prev
		return New;											//return New node
	}
}
WordNode *	WordBST::Search(char * word)				// ADD, TEST, SEARCH, UPDATE //찾은값 리턴 없을시 NULL
{														//Search node that has same word infomation with word
	WordNode *pWork = root;
														//if word is big alphabet, traslate to little alphabet and copy 
	int loop = 0;										// else just copy
	char word2[100] = { 0 };
	while (word[loop] != '\0')
	{
		if (word[loop] <= 90 && word[loop] >= 65)
		{
			word2[loop] = word[loop] + 32;
			loop++;
		}
		else
		{
			word2[loop] = word[loop];
			loop++;
		}
	}
														
	if (strcmp(word, word2) == 1)							//if word is little alphabet
	{
		while (pWork && (strcmp(word, pWork->GetWord())))	//while pWork is exit and word is same to pWork's word infomation
		{
			if (strcmp(pWork->GetWord(), word) > 0) pWork = pWork->GetLeft();//if pWork's word infomation is bigger then word, pWork is pWork's left child
			else pWork = pWork->GetRight();					//else right child
		}
		if (!pWork) return NULL;							//if cant's find return NULL
		else return pWork;									//else pWork
	}
	else													//if word isn;t little alphabet
	{
		while (pWork && (strcmp(word2, pWork->GetWord())))	//while pWork is exit and word2 is same to pWork's word infomation
		{
			if (strcmp(pWork->GetWord(), word2) > 0) pWork = pWork->GetLeft();//if pWork's word infomation is bigger then word2, pWork is pWork's left child
			else pWork = pWork->GetRight();					//else right child
		}
		if (!pWork) return NULL;							//if cant's find return NULL
		else return pWork;									//else pWork
	}
}
bool		WordBST::Print(char * order)					// PRINT
{
	WordNode *pWork = root;
	Log.open("Log.txt", ios::app);							//open log.txt
	int i=0;
	while(*(order+i) != 0)									//translate order to big alphabet
	{
		toupper((int)*(order+i));
		i++;
	}
	if (!strcmp(order, "R_PRE")) {							//find order and log.txt close
		this->Re_Preorder(pWork);
		Log.close();
		return 0;
	}
	else if (!strcmp(order, "I_PRE")) {
		this->It_Preorder(pWork);
		Log.close();
		return 0;
	}
	else if (!strcmp(order, "R_IN")) {
		this->Re_Inorder(pWork);
		Log.close();
		return 0;
	}
	else if (!strcmp(order, "I_IN")) {
		this->It_Inorder(pWork);
		Log.close();
		return 0;
	}
	else if (!strcmp(order, "R_POST")) {
		this->Re_Postorder(pWork);
		Log.close();
		return 0;
	}
	else if (!strcmp(order, "I_POST")) {
		this->It_Postorder(pWork);
		Log.close();
		return 0;
	}
	else if (!strcmp(order, "I_LEVEL")) {
		this->it_Levelorder(pWork);
		Log.close();
		return 0;
	}
	else {
		Log.close();
		return 1;
	}
}
bool		WordBST::Save()								// SAVE
{
	//Save - preorder
	Stack <WordNode> myStack;												//make stack
	WordNode *pWork = root;													//

	if (!root) return 1;													//for print error
	else
	{
		myStack.push(pWork);												//Push into stack
		while (!myStack.empty())											//until stack is empty
		{
			pWork = myStack.top();											
			myStack.pop();
			fo << pWork->GetWord() << " " << pWork->GetMean() << endl;	//Visit
			if (pWork->GetRight()) myStack.push(pWork->GetRight());			//Go Right 
			if (pWork->GetLeft()) myStack.push(pWork->GetLeft());			//Go Left
		}
	}
	return 0; //finish 
	
	
}

void		WordBST::Re_Preorder(WordNode * node)
{
	//Print - Recursive Preorder
	WordNode *pWork = node;
	if (pWork != NULL)
	{
		cout << pWork->GetWord() << " " << pWork->GetMean() << endl;		//Visit
		Log << pWork->GetWord() << " " << pWork->GetMean() << endl;		//Visit
		Re_Preorder(pWork->GetLeft());										//Go Left
		Re_Preorder(pWork->GetRight());										//Go Right
	}
}
void		WordBST::It_Preorder(WordNode * node)
{
	//Print - Iterative Preorder

	Stack<WordNode> Astack;
	WordNode *pWork = node;
	Astack.push(pWork);
	while (!Astack.empty())									//while Astack is not empty		
	{
		pWork = Astack.pop();											//pWork  = Astack's top
		cout << pWork->GetWord() << " " << pWork->GetMean() << endl;	//Print
		Log << pWork->GetWord() << " " << pWork->GetMean() << endl;		//Print to log.txt
		if (pWork == NULL)												//if pWork == NULL end  else pWork has right child, Astack push that 
			return;														//else pWork has left child, Astack push
		if (pWork->GetRight())
			Astack.push(pWork->GetRight());
		if (pWork->GetLeft())
			Astack.push(pWork->GetLeft());
	}

}
void		WordBST::Re_Inorder(WordNode * node)
{
	WordNode *pWork = node;											//recursive inorder
	if (pWork != NULL)
	{
		Re_Inorder(pWork->GetLeft()); // Left
		cout << pWork->GetWord() << " " << pWork->GetMean() << endl; // Print
		Log << pWork->GetWord() << " " << pWork->GetMean() << endl;
		Re_Inorder(pWork->GetRight()); // Right
	}
}
void		WordBST::It_Inorder(WordNode * node)					//interative inorder
{
	Stack <WordNode> myStack;
	
	WordNode *pWork = node;											//pWork is root

	if (pWork == NULL) return;

	while (pWork->GetLeft()) {										//while go to left, save all of passed node in myStack
		myStack.push(pWork);
		pWork = pWork->GetLeft();
	}

	do {															//print infomation
		cout << pWork->GetWord() << " " << pWork->GetMean() << endl;
		Log << pWork->GetWord() << " " << pWork->GetMean() << endl;
		if (pWork->GetRight())										//if pWork has right child
		{
			pWork = pWork->GetRight();								//pWork = pWork's Right child
			while (pWork->GetLeft()) {								//go to pWork's smallest node
				myStack.push(pWork);								//and save passed node in Stack
				pWork = pWork->GetLeft();
			}
		}
		else 
			pWork = myStack.pop();									//pWork is stack's top
	} while (pWork);												//while pWork is exist

	return;

}
void		WordBST::Re_Postorder(WordNode * node)
{																	//recursive postorder
	WordNode *pWork = node;
	if (pWork != NULL)
	{
		Re_Postorder(pWork->GetLeft()); // Left
		Re_Postorder(pWork->GetRight()); // Right
		cout << pWork->GetWord() << " " << pWork->GetMean() << endl;//Print
		Log << pWork->GetWord() << " " << pWork->GetMean() << endl;
	}
}
void		WordBST::It_Postorder(WordNode * node)
{														//interative Post order
	Stack<WordNode> Astack;								//Astack for Post order				
	Stack<WordNode> Bstack;								//Bstack for Post order				
	WordNode *  pWork;									//print node is pWork
	Astack.push(node);									
	while (!Astack.empty())								//while Astack don't have node ,  loop is acting
	{																
		node = Astack.pop();							//Astack give stack's top to node		
		Bstack.push(node);								//Bstack have node at top						
		if (node == NULL)								//node is NULL -> end	
			return;										//if node have child, Astack have that at top
		if (node->GetLeft())							
			Astack.push(node->GetLeft());				
		if (node->GetRight())
			Astack.push(node->GetRight());
	}
	while (!Bstack.empty())								//Print all of Bstack's node
	{
		pWork = Bstack.pop();
		cout << pWork->GetWord() << " " << pWork->GetMean() << endl;
		Log << pWork->GetWord() << " " << pWork->GetMean() << endl;
	}
}

void		WordBST::it_Levelorder(WordNode * node)
{																		//interative Level order
	Queue myQueue;
	WordNode *pWork = node;												//
	while (pWork) {														//while pWork is exit , loop is work
		cout << pWork->GetWord() << " " << pWork->GetMean() << endl;	//print pWork
		Log << pWork->GetWord() << " " << pWork->GetMean() << endl;		//print at log pWork
		if (pWork->GetLeft())myQueue.Push(pWork->GetLeft());			//save pWork's child in queue
		if (pWork->GetRight())myQueue.Push(pWork->GetRight());			//
		if (myQueue.Empty())return;										//
		pWork = myQueue.Front();										//pWork is queue's front
		myQueue.Pop();													//delete queue's node
	}
}
