#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

template<class T>
class Stack {
public:
	Stack(int stackCapacity = 100);
	bool IsEmpty() const;// true=empty, false=not
	T& Top() const; // return top function
	void Push(const T&item); // insert node to top
	void Pop(); // delete node at top
private:
	T*stack;
	int top; // top's point
	int capacity; // stack's capacity
};

template <class T>
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity) { // make stack that have stackcapacity 100.
	if (capacity < 1)throw "Stack capacity must be > 0"; // classify the Error(no node in stack) by throw.
	stack = new T[capacity]; // dynamic allocation
	top = -1; // initiallize the top to -1.
}

template <class T>
inline bool Stack<T>::IsEmpty() const { // check the stack is empty or not.
	return top == -1; //if top is -1, the stack is empty.
}
template <class T>
inline T&Stack<T>::Top() const { // return node that top of the stack.
	if (IsEmpty())throw "Stack is empty"; // classify the Error(no node in stack) by throw.
	return stack[top]; // return top node
}

template <class T>
void ChangeSizeID(T*&k, int old, int new1) { // declare the function that use in Push that change the size of stack.
	if (new1 < 0) throw "Size is <0"; // classify the Error(new1 < 0) by throw.
	T * temp = new T[new1]; //dynamic allocation that size is new number
	
	int num = 0;

	if (old > new1) // previous size is bigger than new size,
		num = new1; // num is new size
	else
		num = old; // num is old size
	
	memcpy(temp, k, sizeof(T)*num); // 
	delete[]k; // delete k
	k = temp;
}
template <class T>
void Stack<T>::Push(const T&x) {
	if (top == capacity - 1) { // if stack is full
		ChangeSizeID(stack, capacity, 2 * capacity); // change size of stack
		capacity *= 2; // size up as double
	}
	stack[++top] = x; // input x to stack.
}
template <class T>
void Stack<T>::Pop() {
	if (IsEmpty())throw "Stack is empty. Cannot delete"; // classify the Error(no node in stack) by throw.
	stack[top--].~T(); // reduce the top, destruct T
}

template <class T>
class Queue1 {
public:
	Queue1(int queueCapacity = 100); // make queue that size 100
	bool IsEmpty() const;
	T& Front() const; // return front node
	T&Rear() const;// return rear node
	void Push(const T&item); // insert node to tail
	void Pop(); // delete node
private:
	T*queue;
	int front; // front point
	int rear; // rear point
	int capacity; // queue's capacity
};

template <class T>
Queue1<T>::Queue1(int queueCapacity) :capacity(queueCapacity) {
	if (capacity < 1)throw "Queue capacity must be>0"; // classify the Error(if capacity of queue is smaller than zero) by throw.
	queue = new T[capacity]; // dynamic allocation
	front = rear = 0; // reset front, rear to 0
}

template <class T>
inline bool Queue1<T>::IsEmpty() const {
	return front == rear; // check the queue by compare front with rear
}
template <class T>
inline T&Queue1<T>::Front() const { // function that guide the point of the front
	if (IsEmpty())throw "Queue is empty. No front element"; // classify the Error(no node in queue) by throw.
	return queue[(front + 1) % capacity]; //return position
}
template <class T>
inline T&Queue1<T>::Rear() const { // function that guide the point of the rear
	if (IsEmpty)throw "Queue is empty. No rear element"; // classify the Error(no node in queue) by throw.
	return queue[rear]; // return position
}
template <class T>
void Queue1<T>::Push(const T &x) {
	if ((rear + 1) % capacity == front) { // if queue is full
		T*newQueue1 = new T[2 * capacity]; // dynamic allocation size to double
		int start = (front + 1) % capacity; // number that use to compare.
		if (start < 2)  // if the start < 2
			memcpy(newQueue1, queue + start, sizeof(T)*(capacity - 1));// copy queue to new queue
		//copy(queue + start, queue + start + capacity - 1, newQueue1);
		else {
			memcpy(newQueue1, queue + start, sizeof(T)*(capacity - start));// copy queue to new queue
			memcpy(newQueue1 + capacity - start, queue, sizeof(T)*(rear + 1));// copy queue to new queue
			//copy(queue + start, queue + capacity, newQueue1);
			//copy(queue, queue + rear + 1, newQueue1 + capacity - start);
		}

		/* change all */
		front = 2 * capacity - 1;
		rear = capacity - 2;
		capacity *= 2;

		delete[]queue; // delete existing queue
		queue = newQueue1; // queue is new queue
	}
	rear = (rear + 1) % capacity;
	queue[rear] = x; // into x to rear of queue.
}

template <class T>
void Queue1<T>::Pop() {
	if (IsEmpty())throw "Queue is empty. cannot delete."; // classify the Error(no node in queue) by throw.
	front = (front + 1) % capacity;

	queue[front].~T(); // destruct T
}


class WordBST
{
public:
	WordNode * root;	// Word BST Root

public:
	WordBST();
	~WordBST();

	void Insert(WordNode * node)
	{
		if (root == NULL) // first input
		{
			root = node;
		}
		else
		{
			WordNode * pWork;
			pWork = root;

			while (1) // insert
			{
				if (strcasecmp(node->GetWord(), pWork->GetWord()) < 0) // new node < exist node
				{
					if (pWork->GetLeft() == NULL)
					{
						pWork->SetLeft(node);
						break;
					}
					else
						pWork = pWork->GetLeft();
				}
				else if (strcasecmp(node->GetWord(), pWork->GetWord()) > 0) // new node > exist node
				{
					if (pWork->GetRight() == NULL)
					{
						pWork->SetRight(node);
						break;
					}
					else
						pWork = pWork->GetRight();
				}
				else // new node = exist node
				{
					pWork->SetLeft(node); // set left.
					break;
				}
			}
		}
	}

	WordNode * Delete(char * word)
	{
		WordNode * pP=root; // parent of node that to delete
		WordNode * pDel; // node that to delete
		int direction = 0; // direction of parent to child

		pDel = Search(word); // search word

		if (pDel == NULL) // fail to search
			return NULL;

		while (1) // find the parent
		{
			if (strcasecmp(pP->GetWord(), pDel->GetWord()) > 0) // smaller than parent
			{
				if (pP->GetLeft() == pDel)
				{
					direction = 1; // set direction to 1
					break;
				}
				else
					pP = pP->GetLeft();
			}
			else if (strcasecmp(pP->GetWord(), pDel->GetWord()) < 0) // bigger than parent
			{
				if (pP->GetRight() == pDel)
				{
					direction = 2; // set direction to 2
					break;
				}
				else
					pP = pP->GetRight();
			}
			else // same with parent
			{
				if (pDel == root) // if delete root,
				{
					pP = NULL; // parent is NULL
					break;
				}
			}
		}

		/* 4 cases to delete Node in BST */
		if ((pDel->GetLeft() == NULL) && (pDel->GetRight()==NULL)) // if delete leaf
		{
			if (direction = 1) // if delete node is parent's left child
			{
				pP->SetLeft(NULL);
				return pDel;
			}
			else if (direction = 2) // if delete node is parent's right child
			{
				pP->SetRight(NULL);
				return pDel;
			}
			else // if delete node is root,
				return root;
		}
		else if ((pDel->GetLeft() != NULL) && (pDel->GetRight()==NULL)) // delete node have only left child
		{
			WordNode * pWork;
			WordNode * pP_pWork; // pareant of pWork.
			pP_pWork = pDel;
			pWork = pDel->GetLeft();

			while (1) // find biggest node
			{
				if (pWork->GetRight() != NULL) // if pWork have Right child
				{
					pP_pWork = pWork;
					pWork = pWork->GetRight();
				}
				else
					break;
			} // pWork = node that use to replace

			if (pDel->GetLeft() != pWork) // if pDel have Left child
			{
				if (pWork->GetLeft() != NULL)
					pP_pWork->SetRight(pWork->GetLeft()); // parent of pWork's right child is pWork's left child
				else
					pP_pWork->SetRight(NULL);

				pWork->SetLeft(pDel->GetLeft()); // replace Node's left chile is pDel's left child
			}

			pWork->SetRight(pDel->GetRight()); // replace Node's right chile is pDel's right child

			if (direction == 1) // if pDel is left child of parent,
				pP->SetLeft(pWork);
			else if (direction == 2) // if pDel is right child of parent,
				pP->SetRight(pWork);
			else // if pDel is root,
				root = pWork;

			return pDel;
		}
		else if ((pDel->GetLeft() == NULL) && (pDel->GetRight() != NULL)) // delete node have only right child
		{
			/* same with first case, so skip the comment */
			WordNode * pWork;
			WordNode * pP_pWork;
			pP_pWork = pDel;
			pWork = pDel->GetRight();

			while (1) // find the biggest node
			{
				if (pWork->GetLeft() != NULL)
				{
					pP_pWork = pWork;
					pWork = pWork->GetLeft();
				}
				else
					break;
			} // pWork = replacement

			if (pDel->GetRight() != pWork)
			{
				if (pWork->GetRight() != NULL)
					pP_pWork->SetLeft(pWork->GetRight());
				else
					pP_pWork->SetLeft(NULL);

				pWork->SetRight(pDel->GetRight());
			}
			pWork->SetLeft(pDel->GetLeft());

			if (direction == 1)
				pP->SetLeft(pWork);
			else if (direction == 2)
				pP->SetRight(pWork);
			else
				root = pWork;

			return pDel;
		}
		else if ((pDel->GetLeft() != NULL) && (pDel->GetRight() != NULL))  // delete node have two child
		{
			WordNode * pWork;
			WordNode * pP_pWork;
			pP_pWork = pDel;
			pWork = pDel->GetLeft();

			while (1)
			{
				if (pWork->GetRight() != NULL)
				{
					pP_pWork = pWork;
					pWork = pWork->GetRight();
				}
				else
					break;
			}

			if (pDel->GetLeft() != pWork)
			{
				if (pWork->GetLeft() != NULL)
					pP_pWork->SetRight(pWork->GetLeft());
				else
					pP_pWork->SetRight(NULL);

				pWork->SetLeft(pDel->GetLeft());
			}

			pWork->SetRight(pDel->GetRight());

			if (direction == 1)
				pP->SetLeft(pWork);
			else if (direction == 2)
				pP->SetRight(pWork);
			else
				root = pWork;

			return pDel;
		}
	}

	WordNode * Search(char * word) // search the word in BST
	{
		WordNode * pWork;
		pWork = root;

		if (pWork == NULL)
			return NULL;

		while (1)
		{
			if (strcasecmp(pWork->GetWord(), word) > 0) // if pWork's word > word to find,
			{
				if (pWork->GetLeft() == NULL)
					return NULL; 

				pWork = pWork->GetLeft();
			}
			else if (strcasecmp(pWork->GetWord(), word) < 0) // if pWork's word < word to find,
			{
				if (pWork->GetRight() == NULL)
					return NULL;

				pWork = pWork->GetRight();
			}
			else  // if pWork's word = word to find,
				return pWork;
		}
	}

	bool Save() // save BST to text file
	{
		if (root != NULL) // if node exist in BST
		{
			Preorder_Save(root);
			return true;
		}
		else // no node in BST
			return false;
	}

	void Preorder_Save(WordNode * t) // Save to Preorder,
	{
		if (t != NULL)
		{
			ofstream fout;
			fout.open("memorizing_word.txt", ios::app); // file open,
			fout << t->GetWord() << "," << t->GetMean() << endl; // write to file,
			fout.close(); // file close,

			Preorder_Save(t->GetLeft()); // input t->Left to this recursive function
			Preorder_Save(t->GetRight());  // input t->Right to this recursive function
		}
	}

	void Inorder(WordNode*pCur) {
		if (pCur) { // if pCur is not NULL,
			ofstream foutin;
			foutin.open("log.txt", ios::app);
			Inorder(pCur->GetLeft());  // input t->Left to this recursive function

			foutin << pCur->GetWord() << " " << pCur->GetMean() << endl;
			cout << pCur->GetWord() << " " << pCur->GetMean() << endl;

			Inorder(pCur->GetRight());  // input t->Right to this recursive function

			foutin.close();
		}
	}
	void Preorder(WordNode*pCur) {
		if (pCur) { // if pCur is not NULL,
			ofstream foutpre;
			foutpre.open("log.txt", ios::app);
			cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
			foutpre << pCur->GetWord() << " " << pCur->GetMean() << endl;
			Preorder(pCur->GetLeft());
			Preorder(pCur->GetRight());
			foutpre.close();
		}
	}
	void Postorder(WordNode*pCur) {
		if (pCur) { // if pCur is not NULL,
			ofstream foutpost;
			foutpost.open("log.txt", ios::app);
			Postorder(pCur->GetLeft());
			Postorder(pCur->GetRight());
			cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
			foutpost << pCur->GetWord() << " " << pCur->GetMean() << endl;
			foutpost.close();
		}
	}
	void NONR_Inorder() { // none recursive Inorder
		Stack<WordNode*>s; // declare stack s.
		WordNode*pCur = root;
		ofstream foutin1;
		foutin1.open("log.txt", ios::app);

		while (1) { // repeat, exit when meet return
			while (pCur) { // repeat, exit when pCur is NULL
				s.Push(pCur); // pCur into stack s.
				pCur = pCur->GetLeft(); // pCur move to pCur's left child.
			}
			if (s.IsEmpty())
				return; // if stack is empty, return.

			pCur = s.Top(); // pCur is Top of stack s
			s.Pop(); // Pop node that in stack s
			cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
			foutin1 << pCur->GetWord() << " " << pCur->GetMean() << endl;

			pCur = pCur->GetRight(); // pCur move to pCur's right child.
		}

		foutin1.close();
	}
	void NONR_Preorder() {
		Stack<WordNode*>s;
		WordNode*pCur = root;
		ofstream foutpre1;
		foutpre1.open("log.txt", ios::app);

		while (1) {  // repeat, exit when meet return
			while (pCur) {
				cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
				foutpre1 << pCur->GetWord() << " " << pCur->GetMean() << endl;

				s.Push(pCur); // pCur into stack s.
				pCur = pCur->GetLeft();
			}
			if (s.IsEmpty())return; // if no node in stack, return.

			pCur = s.Top();
			s.Pop();
					
			pCur = pCur->GetRight();
		}
		foutpre1.close();
	}
	void NONR_Postorder() {
		Stack<WordNode*>s; // declare stack s
		WordNode * pCur = root;
		ofstream foutpost1;
		foutpost1.open("log.txt", ios::app);

		s.Push(pCur); // pCur push to stack s
		WordNode * pPrev = NULL;

		if (root == NULL) // if no node in stack,
			return;

		while (s.IsEmpty() != true)
		{
			pCur = s.Top();
			
			if (pPrev == NULL || pPrev->GetLeft() == pCur || pPrev->GetRight() == pCur) { // pCur is child of pPrev OR First time(pPrev==NULL)
				if (pCur->GetLeft())
					s.Push(pCur->GetLeft());
				else if (pCur->GetRight())
					s.Push(pCur->GetRight());
				else { // no child
					cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
					foutpost1 << pCur->GetWord() << " " << pCur->GetMean() << endl;
					s.Pop();
				}
			}
			if (pCur->GetLeft() == pPrev && pCur->GetLeft() != NULL) { // pPrev is Leftchild of pCur
				if (pCur->GetRight())
					s.Push(pCur->GetRight());
				else {
					cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
					foutpost1 << pCur->GetWord() << " " << pCur->GetMean() << endl;
					s.Pop();
				}
			}
			if (pCur->GetRight() == pPrev && pCur->GetRight() != NULL) { // pPrev is Rightchild of pCur
				cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
				foutpost1 << pCur->GetWord() << " " << pCur->GetMean() << endl;
				s.Pop();
			}
			pPrev = pCur;
		}
		foutpost1.close();
	}
	
	bool Print(char * order)
	{
		if (strcmp("R_PRE", order) == 0) {
			Preorder(root);
		}
		else if (strcmp("I_PRE", order) == 0) {
			NONR_Preorder();
		}
		else if (strcmp("R_IN", order) == 0) {
			Inorder(root);
		}
		else if (strcmp("I_IN", order) == 0) {
			NONR_Inorder();
		}
		else if (strcmp("R_POST", order) == 0) {
			Postorder(root);

		}
		else if (strcmp("I_POST", order) == 0) {
			NONR_Postorder();
		}
		else if (strcmp("I_LEVEL", order) == 0) { // Level Order.
			Queue1<WordNode*>q; // declare the queue q.
			WordNode*pCur = root;
			ofstream foutlev;
			foutlev.open("log.txt", ios::app);

			while (pCur) { // repeat if pCur is not NULL
				cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
				foutlev << pCur->GetWord() << " " << pCur->GetMean() << endl;

				if (pCur->GetLeft()) q.Push(pCur->GetLeft()); //if pCur's left is not NULL, Push pCur's left child to queue.
				if (pCur->GetRight()) q.Push(pCur->GetRight()); //if pCur's right is not NULL, Push pCur's right child to queue.
				if (q.IsEmpty())return true; // if no node in queue, return true.

				pCur = q.Front(); // pCur point the queue q's front
				q.Pop(); // Pop node of queue q.
			}

			foutlev.close();
		}
		else {
			return false;
		}
	}

};

#endif
