#ifndef _WORDBST_H_
#define _WORDBST_H_
#define default_value 100

#include "WordNode.h"
#include <fstream>
#include <string.h>
#pragma execution_character_set("utf-8")

// The stack generic class
template< class T > class Stack
{
public:
	Stack(int = default_value);//default constructor
	~Stack()//destructor
	{
		delete[] values;
	}
	bool push(T);
	T pop();
	T top();
	bool empty();
	bool isFull();
	int size();
private:
	int total;
	T *values;
	int index;

};

// The stack constructor
template< class T > Stack<T>::Stack(int x) :
	total(x),//ctor
	values(new T[total]),
	index(-1)
{ /*empty*/
}

// If the stack is full
template< class T > bool Stack<T>::isFull()
{
	if ((index + 1) == total)
		return 1;
	else
		return 0;
}

// The stack's data size
template< class T > int Stack<T>::size()
{
	return index + 1;
}


template< class T > bool Stack<T>::push(T x)
{
	bool b = 0;
	if (!Stack<T>::isFull())
	{
		index += 1;
		values[index] = x;
		b = 1;
	}
	return b;
}

template< class T > bool Stack<T>::empty()
{
	if (index == -1)//is empty
		return 1;
	else
		return 0; //is not empty
}

template< class T > T Stack<T>::pop()
{
	T val = NULL;
	if (!Stack<T>::empty())
	{
		val = values[index];
		index -= 1;
	}
	else
	{
		cerr << "Stack is Empty : ";
	}
	return val;

}

template< class T > T Stack<T>::top()
{
	T val = NULL;
	if (!Stack<T>::empty())
	{
		val = values[index];
	}
	else
	{
		cerr << "Stack is Empty : ";
	}
	return val;
}

// The Queue Class
template< class T > class myQueue
{
public:
	myQueue(int = default_value);//default constructor
	~myQueue()//destructor
	{
		delete[] values;
	}
	bool push(T);
	T pop();
	bool empty();
	bool isFull();
	T front();
public:
	int size;
	T *values;
	int head;
	int back;
};

// The Queue constructor
template< class T > myQueue<T>::myQueue(int x) :
	size(x),//ctor
	values(new T[size]),
	head(0),
	back(0)
{ /*empty*/
}

template< class T > bool myQueue<T>::isFull()
{
	if ((back + 1) % size == head)
		return 1;
	else
		return 0;
}

template< class T > bool myQueue<T>::push(T x)
{
	bool b = 0;
	if (!myQueue<T>::isFull())
	{
		values[back] = x;
		back = (back + 1) % size;
		b = 1;
	}
	return b;
}

template< class T > bool myQueue<T>::empty()
{
	if (back == head)//is empty
		return 1;
	else
		return 0; //is not empty
}

template< class T > T myQueue<T>::pop()
{
	T val = NULL;
	if (!myQueue<T>::empty())
	{
		val = values[head];
		head = (head + 1) % size;
	}
	else
	{
		cerr << "Queue is Empty : ";
	}
	return val;

}

template< class T > T myQueue<T>::front()
{
	T val = NULL;
	if (!myQueue<T>::empty())
	{
		val = values[head];
	}
	else
	{
		cerr << "Queue is Empty : ";
	}
	return val;
}

class WordBST
{
public:
	WordNode * root;
	int count;

public:
	WordBST();
	~WordBST();

	WordNode *	getRoot();
	void		setRoot(WordNode * node);
	WordNode *	Insert(WordNode * node);
	WordNode *	Delete(char * word);
	WordNode *	DeleteImp(WordNode * root, char * word);
	WordNode *	Search(char * word);
	bool		Print(char * order);
	bool		Save();
	WordNode * findMin(WordNode * root);
	WordNode * findMax(WordNode * root);
	void		recursivePreorder(WordNode * root);
	void		iterativePreorder(WordNode * root);
	void		recursiveInorder(WordNode * root);
	void		iterativeInorder(WordNode * root);
	void		recursivePostorder(WordNode * root);
	void		iterativePostorder(WordNode * root);
	void		Levelorder(WordNode * root);
	int			getCount();
	void		releaseTree(WordNode * root);
};

#endif
