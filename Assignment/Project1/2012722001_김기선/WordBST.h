#ifndef _WORDBST_H_		//prevent header crash
#define _WORDBST_H_

#include "WordNode.h"	//include header

class WordBST		//declare wordBST class
{
public:		//assume private member//
	/*member variable*/
	WordNode * root;   // Word BST Root
	int leaf_WordCnt;   //for speed up
	/*member func (traversal)*/
	void Visit(WordNode* pCur);	//print node data
	void R_PRE(WordNode* pCur);	//Reculsive Preorder
	void I_PRE();				//Iterative Preoder
	void R_IN(WordNode* pCur);	//Reculsive Inorder
	void I_IN();				//Iterative Inorder
	void R_POST(WordNode* pCur);//Reculsive Postorder
	void I_POST();				//Iterative Postorder
	void I_LEVEL();				//Iterative Levelorder

public:	////public member////
	WordBST();	//constructor
	~WordBST();	//destructor
	/*BST interface func*/
	void      Insert(WordNode * node);         // LOAD, MOVE
	WordNode *   Delete(char * word);            // TEST
	WordNode *   Search(char * word);            // ADD, TEST, SEARCH, UPDATE
	bool      Print(const char * order);		//PRINT
	bool      Save();                        // SAVE
};
/*alphabet bst's queue*/
class queue_word
{
private:	//private member variable//
	WordNode* pHead;	//Head
	WordNode* pTail;	//Tail

public:		//public member variable//
	queue_word()	////constructor////
	{
		pHead = NULL;	//set null
		pTail = NULL;
	}

	~queue_word() ////destructor ////
	{	//delete all node in queue
		WordNode* pCur = pTail;		//for move
		WordNode* pTemp = pTail;	//for delete

		if (pHead == NULL)
			return;

		while (1)
		{
			if (pCur == NULL)
				return;

			pTemp = pCur;			//save node
			pCur = pCur->GetNext();//move next
			delete pTemp;			//delete node
		}
	}

	void push(WordNode* pNew)	////push func////
	{
		if (pHead == NULL)		//first push case
		{
			pHead = pNew;
			pTail = pNew;
			return;
		}
		pNew->SetNext(pTail);	//pNew's pointer set
		pTail = pNew;			//pTail set

		return;
	}

	void pop()	////pop func////
	{
		WordNode* pCur = pTail;   //walker
		if (pHead == NULL)      ////except 1////
			return;            //state empty

		if (pHead == pTail)      ////except 2////
		{                  //state only one node exist
			pHead = NULL;      //pop!
			pTail = NULL;
			return;
		}

		while (1)
		{
			if (pCur->GetNext() == pHead)   //point
			{
				pCur->SetNext(NULL);      //pop!
				pHead = pCur;
				return;
			}
			pCur = pCur->GetNext();      //move next
		}
	}

	bool empty()	////is empty? func////
	{
		if (pHead == NULL)	//return head exist
			return true;
		else
			return false;
	}

	WordNode* front()	////front func////
	{
		if (pHead != NULL)
			return pHead;
		else
			return NULL;
	}
};

/*alphabet bst's stack*/
class stack_word
{
private:
	WordNode* pTop;   //pointer

public:
	stack_word()   //constructor//
	{
		pTop = NULL;   //NULL initialize
	}

	~stack_word() //destructor//
	{            //delete stack
		WordNode* pTemp = pTop;		//walker

		while (1)	//roop
		{
			if (pTop == NULL)	//stop point
				return;

			pTemp = pTop;		   //go top
			pTop = pTop->GetNext();//move
			delete pTemp;		   //delete pTemp
		}
	}

	void push(WordNode* pNew)	//push func//
	{
		if (pTop == NULL)	//first push case
			pTop = pNew;	//set top
		else
		{
			pNew->SetNext(pTop);	//new set
			pTop = pNew;			//set top
		}


		return;//exit func
	}

	void pop()
	{
		if (pTop == NULL)//exception
			return;      //stack is empty

		WordNode* pTemp = pTop; //walker
		pTemp = pTemp->GetNext();   //save temp
		pTop->SetNext(NULL);      //pop
		pTop = pTemp;            //set
	}

	bool empty()	//is empty? func//
	{
		if (pTop == NULL)	//return pTop exist 
			return true;
		else
			return false;
	}

	WordNode* top()	//return top func//
	{
		if (pTop != NULL)
			return pTop;
		else
			return NULL;
	}

};



#endif

