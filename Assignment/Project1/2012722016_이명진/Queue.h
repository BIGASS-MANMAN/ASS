#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "WordNode.h"
#include "Manager.h"
#include "AlphabetNode.h"
class Manager;
class WordNode;
class AlphabetNode;
class Queue
{
public:
	int nodeCnt;
	WordNode * pHead;
	AlphabetNode *alpHead;
public:
	Queue();
	~Queue();

	WordNode*	Get_Head() { return pHead; }
	bool		alisempty();
	void		alPush(AlphabetNode *node);
	bool		IsEmpty();
	AlphabetNode* alPop();
	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();						// MOVE
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Print(WordNode* pCur);
	bool		Save();								// SAVE
	int			GetNodeCnt();
};

template<class T>
class Stack
{
private:
	T* stack;
	int top;
	int capacity;
public:
	Stack(int stackCapapcity = 10);                //make a size of the first 10
	bool isempty() const;                          //the number of stack element 0 return true
	T &Top() const;								   //return top element in stack
	void Push(const T& item);                      //insert at top in stack
	void Pop();                                    //delete top element in stack
};

template<class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity)      //make stack array size is 10
{
	if (capacity < 1)
		throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template<class T>
inline bool Stack<T>::isempty() const { return top == -1; }

template<class T>
inline T& Stack<T>::Top() const                                    //return to top in stack
{
	if (isempty())
		throw "Stack is empty";
	return stack[top];
}

template<class T>
void Stack<T>::Push(const T& x)                                    //insert x in stack
{
	if (top == capacity - 1)
	{
		//ChangeSize1D(stack, capacity, 2 * capacity);
		//capacity *= 2;
		T* stack1;
		stack1 = new T[capacity * 2];
		for (int i = 0; i < capacity; i++)
			stack1[i] = stack[i];
		capacity *= 2;
		delete[]stack;
		stack = stack1;
	}
	stack[++top] = x;
}

template<class T>
void Stack<T>::Pop()												//delete in stack that top
{
	if (isempty())
		throw "Stack is empty.Cannot delete";
	stack[top--].~T();                                             //destructor for T
}
#endif
