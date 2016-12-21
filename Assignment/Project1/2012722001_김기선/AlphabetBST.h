#ifndef _ALPHABETBST_H_		//prevent header crash
#define _ALPHABETBST_H_

#include "AlphabetNode.h"	//include header

#define MAX_WORD 100		//define max word

class AlphabetBST			//declare class (bst)
{
public:	////assumed private member////
	/*member variable*/
	AlphabetNode * root;	//bst's root
	int WordCnt;			//saved word number count

	/*BST TRAVERSAL*/
	void Visit(AlphabetNode* pCur, const char* order);	////for print func
	bool Visit(AlphabetNode* pCur);						////for save func
	void R_PRE(AlphabetNode* pCur);	//Reculsive Preorder
	void I_PRE();					//Iterative Preoder
	void R_IN(AlphabetNode* pCur);	//Reculsive Inorder
	void I_IN();					//Iterative Inorder
	void R_POST(AlphabetNode* pCur);//Reculsive Postorder
	void I_POST();					//Iterative Postorder
	void I_LEVEL();					//Iterative Levelorder

public:	////public member////
	AlphabetBST();	//constructor
	~AlphabetBST();	//destructor

	/*BST interface func*/
	void         Insert(AlphabetNode * node);   // run
	bool         Print(const char * order);     // PRINT
	AlphabetNode *   Search(char alpabet);      // LOAD, MOVE, TEST, SEARCH, UPDATE
	bool         Save();						// SAVE

	/*WordCnt value interface func*/
	void wordcnt_up();		//num up
	void wordcnt_down();	//num down
	int getWordCnt();		//return num
};

/*alphabet bst's queue*/
class queue_alp	
{
private:	//private member variable//
	AlphabetNode* pHead;	//Head
	AlphabetNode* pTail;	//Tail

public:		//public member variable//
	queue_alp()	////constructor////
	{
		pHead = NULL;	//set null
		pTail = NULL;
	}

	~queue_alp() ////destructor ////
	{	//delete all node in queue
		AlphabetNode* pCur = pTail;		//for move
		AlphabetNode* pTemp = pTail;	//for delete

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

	void push(AlphabetNode* pNew)	////push func////
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
		AlphabetNode* pCur = pTail;   //walker
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

	AlphabetNode* front()	////front func////
	{
		if (pHead != NULL)
			return pHead;
		else
			return NULL;
	}
};


/*alphabet bst's stack*/
class stack_alp
{
private:
	AlphabetNode* pTop;   //pointer

public:
	stack_alp()   //constructor//
	{
		pTop = NULL;   //NULL initialize
	}

	~stack_alp() //destructor//
	{            //delete stack
		AlphabetNode* pTemp = pTop;		//walker

		while (1)	//roop
		{
			if (pTop == NULL)	//stop point
				return;

			pTemp = pTop;		   //go top
			pTop = pTop->GetNext();//move
			delete pTemp;		   //delete pTemp
		}
	}

	void push(AlphabetNode* pNew)	//push func//
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

	void pop()	//pop func//
	{
		if (pTop == NULL)//exception
			return;      //stack is empty

		AlphabetNode* pTemp = pTop; //walker
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

	AlphabetNode* top()	//return top func//
	{
		if (pTop != NULL)	//return pTop
			return pTop;
		else
			return NULL;
	}

};
#endif

