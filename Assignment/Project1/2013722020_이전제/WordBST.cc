#include "WordBST.h"
#include <cstring>   //including haeader
#include <iostream>
using namespace std;

WordBST::WordBST()  //constructor 
{
	root = '\0';
}


WordBST::~WordBST() //dstructor using recursive
{
	destruc(root);
}

void     WordBST::destruc(WordNode* node)  //while node is not NULL, delete
{
	if (node == NULL)
	{
		return;
	}

	if (node->GetRight() != NULL)
	{
		destruc(node->GetRight());
	}
	if (node->GetLeft() != NULL)
	{
		destruc(node->GetLeft());
	}
	node->SetLeft(NULL);
	node->SetRight(NULL);

	if (node != NULL)
	{
		delete node;
	}
}


WordNode * WordBST::GetRoot()
{
	return root;
}

void       WordBST::SetRoot(WordNode * Root)
{
	root = Root;
}


void	    WordBST::Insert(WordNode * node)  //push 
{
	if (root==NULL)                           //if root is NULL, node is root
	{
		root = node; 
		return;
	}
		WordNode* current = root;             //current is root

		for (;;)                      // while 
		{
			if (strcmp(current->GetWord(), node->GetWord()) <= 0)			
			{
				if (current->GetRight() == NULL)    //node's word is bigger than current's word
				{
					current->SetRight(node);		//node is current right child						
					return;
				}
				else
				{
					current = current->GetRight();			//current is current right child			
					continue;
				}
			}
			else if (strcmp(current->GetWord(), node->GetWord()) > 0)	//if current's word is bigger than node's word
			{
				if (current->GetLeft() == NULL)						//if current's left child is NULL
				{
					current->SetLeft(node);								//current's left child is node
					return;
				}
				else                                        //else current = current's left child
				{
					current = current->GetLeft();							
					continue;
				}
			}
			else
			{                 //exception handling
				return;
			}
		}
	}// LOAD, MOVE
WordNode *	WordBST::Delete(char * word)				// TEST
{
       
	WordNode *p = root, *q = 0;		               //p is root , q is null							
	while (p && strcmp(word, p->GetWord()))		  //p is not null and word is not eqaul to p's word				
	{
		q = p;													//q is p's parent
		if (strcmp(word, p->GetWord()) < 0) p = p->GetLeft();	//if p's word bigger than word, p = p's left child
		else p = p->GetRight();									 //else p is p's right child
	}
	if (!p) return NULL;										//if p is NULL, reutrn NULL;
 
	if (p->GetLeft() ==NULL && p->GetRight() == NULL)		//p is no child
	{
		if (q == NULL) root = NULL;							//if p's parent is null, root is null
		else if (q->GetLeft() == p) q->SetLeft(NULL);		//else q's left child is p, q's left child is null		
		else q->SetRight(NULL);								 //else q's right child is null
		return p;                                            //return p
	}
 
	if (p->GetLeft() == NULL)			  //only left child has							
	{
		if (q == NULL) root = p->GetRight();					//if q is null, root is p's right child	
		else if (q->GetLeft() == p) q->SetLeft(p->GetRight());	 //else q's left child is p, p's left child is p's right child
		else q->SetRight(p->GetRight());						//else q's right child is p's right child
		return p;												 //return p
	}
 
	if (p->GetRight() == NULL)		//only right child has									
	{
		if (q == NULL) root = p->GetLeft();				//if q is null, root is p's left child				
		else if (q->GetLeft() == p) q->SetLeft(p->GetLeft());	//else q's left child is p, p's left child is p's left child
		else q->SetRight(p->GetLeft());							//else q's right child is p's left child					
		return p;												 //return p											
	}
 
																
	WordNode *prevprev = p, *prev = p->GetLeft(),	//node's has two child 		
		*curr = p->GetLeft()->GetRight();						
 
	while (curr)	     //while curr is not null, prevprev is prev, prev is current, current is currnet's right child							
	{
		prevprev = prev;
		prev = curr;
		curr = curr->GetRight();
	}
 
	
                           //To declared new word node for storing data and retuning
	WordNode *del = new WordNode();							
	del->SetWord(p->GetWord());						//to input data		
	del->SetMean(p->GetMean());								
 
	p->SetWord(prev->GetWord());					//To connecting data		
	p->SetMean(prev->GetMean());

	if (prevprev == p) prevprev->SetLeft(prev->GetRight());	//if prevprev is p , prevprev's left child is prev's right child
	else prevprev->SetRight(prev->GetRight());			//else prevprev right child is prev's right child
	delete prev;												//delete prev and return del
	return del;		

}

WordNode * WordBST::Search(char * word)				// ADD, TEST, SEARCH, UPDATE
{
	WordNode * current = root;
	while (current)
	{
		if (strcmp(word, current->GetWord()) < 0)  current = current->GetLeft();  //if current's word bigger than word, currnt go to left
		else if (strcmp(word, current->GetWord()) > 0) current = current->GetRight(); //if word bigger than current's word, currnet go to right
		else  {
                  return current;  //else return current
                         }

	}
      return '\0';
}
bool		WordBST::Print(char * order)						// PRINT
{

	if (strcmp(order, "R_PRE") == 0)   //called R_PRE fucntion
	{
		if (root != NULL)
		{
			R_PRE(root);
			return true;
		}
		else return false;
	}
	else if (strcmp(order, "I_PRE") == 0) //called I_PRE fucntion
	{
		if (root != NULL)
		{
			I_PRE(root);
			return true;
		}
		return false;
	}
	else if (strcmp(order, "R_IN") == 0) //called R_IN fucntion
	{
		if (root != NULL)
		{
			R_IN(root);
			return true;
		}
		else return  false;

	}
	else if (strcmp(order, "I_IN") == 0) //called I_IN fucntion
	{
		if (root != NULL)
		{
			I_IN(root);
			return true;
		}
		else false;
	}
	else if (strcmp(order, "R_POST") == 0) //called R_POST fucntion
	{
		if (root != NULL)
		{
			R_POST(root);
			return true;
		}
		return false;
	}
	else if (strcmp(order, "I_POST") == 0) //called I_POST fucntion
	{
		if (root != NULL)
		{
			I_POST(root);
			return true;
		}
		return false;
	}
	else if (strcmp(order, "I_LEVEL") == 0) //called I_LEVEL fucntion
	{
		if (root != NULL)
		{
			I_LEVEL(root);
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}

	return false;
}
bool		WordBST::Save()								// SAVE
{
	if (root == NULL)
	{
		return false;
	}
	
		Pre_Save(root);
		return true;
	
}

void       WordBST::Pre_Save(WordNode* current)  // Save by using recursive method 
{
	if (current == NULL)
	{
		return;
	}

	ofstream ouf;
	ouf.open("memorizing_word.txt",ios_base::app);
	ouf << current->GetWord() << "	" << current->GetMean() << endl;
     Pre_Save(current->GetLeft());         //save data by preorder recursive traveral
	Pre_Save(current->GetRight());
	ouf.close();
}
bool         WordBST::IsEmpty()  //check bst
{
	WordNode * current = root;
	if (current == NULL)
	{
		return true;  //empty is true
	}
	else
	{
		return false; //else false
	}
}

void            WordBST::R_PRE(WordNode * node)// print by using recursive method 
{
	ofstream ouf;
	ouf.open("log.txt", ios_base::app);
	if (node == NULL)
	{
		return;
	}
	ouf << node->GetWord() << "	" << node->GetMean() << endl;
	R_PRE(node->GetLeft());
	R_PRE(node->GetRight());
	ouf.close();
}


void WordBST::R_IN(WordNode* node)// print by using recursive method 
{
	ofstream ouf;
	ouf.open("log.txt", ios_base::app);
	if (node == NULL)
	{
		return;
	}
	R_IN(node->GetLeft());
	ouf << node->GetWord() << "	" << node->GetMean() << endl;
	R_IN(node->GetRight());
	ouf.close();
}
void WordBST::R_POST(WordNode* node)// print by using recursive method 
{
	ofstream ouf;
	ouf.open("log.txt", ios_base::app);
	if (node == NULL)
	{
		return;
	}
	R_POST(node->GetLeft());
	R_POST(node->GetRight());
	ouf << node->GetWord() << "	" << node->GetMean() << endl;
	ouf.close();
}
void WordBST::I_PRE(WordNode* node)	// print by using iterative method 
{
	ofstream ouf;
	ouf.open("log.txt", ios_base::app);  //using my stack
	My_Stack st;
	WordNode * current = NULL;
	WordNode* temp = NULL;
	current = node;  //root
	if (current == NULL)
	{
		ouf.close();
		return;     
	}
	st.Push(current);
	
	
	while (st.IsEmpty()==false)           //if it is not empty, pop the stack;s top value and checking about there has childs
	{
		WordNode* cour = st.Top();
		ouf << cour->GetWord() << "	" << cour->GetMean() << endl;
		
		st.Pop();
		if (cour->GetRight() != NULL)      
		{
			st.Push(cour->GetRight());
		}

		if (cour->GetLeft() != NULL)
		{
			st.Push(cour->GetLeft());
		}
	}
	ouf.close();
	return;
}

void WordBST::I_IN(WordNode* node)	// print by using iterative method 
{
	ofstream ouf;
	ouf.open("log.txt", ios_base::app);   //open fild
	My_Stack st;
	WordNode * current = NULL;
	WordNode* temp = NULL;             //using my_stack
	current = node; 
	if (current == NULL)
	{
		ouf.close();
		return;      //exception handling
	}

	while (1)       //while infinitely,
	{
		while (current)			//if current is not null,
		{
			st.Push(current);
			current = current->GetLeft();   //push on stack and go to left child
		}
		if (st.IsEmpty()) return;          //If stack is empty, return 
		current = st.Top();					// current is stack's top value and pop the value
		st.Pop();
		ouf << current->GetWord() << "	" << current->GetMean() << endl;
		current = current->GetRight();        // now current is current's right child
	}
	
	ouf.close();                        // close the fild and return 
	return;
}
void WordBST::I_POST(WordNode* node)	// print by using iterative method 
{
	ofstream ouf;
	ouf.open("log.txt", ios_base::app);
	My_Stack child;                  //it is using two stack child and parent
	My_Stack parent;
	WordNode*  prev = NULL;
	WordNode * current = node; //root
	WordNode * temp = NULL;
	
	if (current == NULL)
	{
		ouf.close();
		return;     
	}

	child.Push(current);              //push the value on child stack

	while (!child.IsEmpty())        //if child stack is not empty
	{
		current = child.Top();
		parent.Push(current);          //current is child stack's top value and push on parent stack
		child.Pop();
		if (current->GetLeft()) child.Push(current->GetLeft());     //child stack is poped and checking childs
		if (current->GetRight()) child.Push(current->GetRight());
	}
	while (!parent.IsEmpty())           //parent stacks has value in post order , and then print the value
	{
		ouf << parent.Top()->GetWord() << "	" << parent.Top()->GetMean() << endl;
		parent.Pop();
	}

	ouf.close();       // closed the file and return 
	return;
}


void WordBST::I_LEVEL(WordNode* node)	// print by using iterative method 
{
	ofstream ouf;
	ouf.open("log.txt", ios_base::app);
	if (node == NULL)                   //open fild
	{
		ouf.close(); return;
	}
	My_Queue qu;                       //using my queue
	qu.Push(node);                     //push the root value

	while (qu.IsEmpty() == false)        //if queue is not empty,
	{
		WordNode* current = qu.GetHead();      //current is get head and print value
		ouf << current->GetWord() << "	" << current->GetMean() << endl;
		qu.Pop();                                //popend and check childs

		if (current->GetLeft() != NULL) qu.Push(current->GetLeft());

		if (current->GetRight() != NULL) qu.Push(current->GetRight());
	}
	
	ouf.close();     //closd the fild and return 
	return;
}

My_Stack::My_Stack()  //stack constructor
{
	pHead = NULL;
	pUnder = NULL;
	pTop = NULL;
}
My_Stack::~My_Stack() //stack destructor
{
	while (IsEmpty() == false)
	{
		Pop();
	}
}
void My_Stack::SetHead(WordNode * node) // using for member value
{
	pHead = node;
}

void My_Stack::SetUnder(WordNode * node)
{
	pUnder = node;
}
WordNode * My_Stack::GetUnder()
{
	return pUnder;
}
WordNode * My_Stack::GetHead()
{
	return pHead;
}



void	My_Stack::Push(WordNode * node)    // push
{
	WordNode* current = this->GetHead();   // current is get head
	WordNode* temp = NULL;
	if (current == NULL)          //if current is head, insert the value
	{
		temp = new WordNode;
		temp->SetWord(node->GetWord());
		temp->SetMean(node->GetMean());
		if (node->GetLeft() != NULL)temp->SetLeft(node->GetLeft());
		if (node->GetRight() != NULL)temp->SetRight(node->GetRight());
		pHead = temp;  pTop = temp;      //temp is head and top
		return;
	}
	else
	{
		while (current->GetNext() != NULL)      //else, find the top and connect to new node
		{
			current = current->GetNext();
		}
		temp = new WordNode;
		temp->SetWord(node->GetWord());
		temp->SetMean(node->GetMean());
		if (node->GetLeft() != NULL)temp->SetLeft(node->GetLeft());
		if (node->GetRight() != NULL)temp->SetRight(node->GetRight());
		current->SetNext(temp);  pTop = temp;      //top is new node
		return;
	}
	return;
}				// LOAD, ADD


WordNode *	My_Stack::Pop()          
{
	if (pTop == NULL) return NULL;
	WordNode* current = this->GetHead();
	WordNode * del = NULL;
	WordNode * temp = NULL;
	if (current->GetNext()==NULL)       // if only one value had, head and top null
	{
		pTop = NULL; pHead = NULL;
		return current;
	}
	while (current->GetNext() != pTop)  //else it is found the top and poping
	{
		current = current->GetNext();
	}

	del = Top();
	current->SetNext(NULL);
	pTop = current;
	return del;

}						// MOVE
bool      My_Stack::IsEmpty()  //check empty
{
	if (pHead == NULL || pTop == NULL)
	{
		return true;
	}
	return false;

}

WordNode * My_Stack::Top()  //return pTop
{
	if (pTop == NULL)
	{
		return NULL;
	}
	return pTop;
}


My_Queue::My_Queue()  //constructor 
{
	pHead = NULL;
	pTail = NULL;
	pNext = NULL;
}
My_Queue::~My_Queue() //destructor
{
	WordNode * current = this->pHead;
	while (IsEmpty() == false)
	{
		Pop();
	}
}
void My_Queue::SetHead(WordNode * node)  //using for memeber value
{
	pHead = node;
}
void My_Queue::SetTail(WordNode * node)
{
	pTail = node;
}
void My_Queue::SetNext(WordNode * node)
{
	pNext = node;
}
WordNode * My_Queue::GetNext()
{
	return pNext;
}
WordNode * My_Queue::GetHead()
{
	return pHead;
}
WordNode * My_Queue::GetTail()
{
	return pTail;
}


void My_Queue::Push(WordNode * node)    // push
{
	WordNode* current = this->GetHead();	  // current is get head
	WordNode* temp = NULL;
	if (current == NULL)		//if current is head, insert the value
	{
		temp = new WordNode;
		temp->SetWord(node->GetWord());
		temp->SetMean(node->GetMean());
		if (node->GetLeft() != NULL)temp->SetLeft(node->GetLeft());
		if (node->GetRight() != NULL)temp->SetRight(node->GetRight());
		pHead = temp;  pTail = temp;		  //temp is head and tail
		return;
	}
	else
	{													//else, find the tail and connect to new node
		while (current->GetNext() != NULL)
		{
			current = current->GetNext();
		}
		temp = new WordNode;
		temp->SetWord(node->GetWord());
		temp->SetMean(node->GetMean());
		if (node->GetLeft() != NULL)temp->SetLeft(node->GetLeft());
		if (node->GetRight() != NULL)temp->SetRight(node->GetRight());
		current->SetNext(temp);  pTail = temp;			  //tail is new node
		return;
	}

	return;
}
bool My_Queue::IsEmpty()      //check empty
{
	if (pHead == NULL || pTail == NULL)
	{
		return true;
	}
	return false;
}

WordNode * My_Queue::Pop()
{
	if (pTail == NULL || pHead==NULL) return NULL;
	WordNode* current = this->GetHead();		
	WordNode * del = NULL;
	WordNode * temp = NULL;
	if (current->GetNext() == NULL)		// if only one value had, head and top null
	{
		pTail = NULL; pHead = NULL;
		return current;
	}

	temp = current->GetNext(); //else, head points next node and cutting connection
	pHead = temp;
	current->SetNext(NULL);
	return temp;                   //return poped node

}
