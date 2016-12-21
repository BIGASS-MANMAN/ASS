#ifndef _STACK_H_
#define _STACK_H_

#include<iostream>

using namespace std;

template <typename T>
class Stack
{

private:
	T* stack;
	int top, capacity;

public:
	Stack(int stackCapacity = 10);
	~Stack();

	bool IsEmpty() const;
	T& Top() const;
	void Push(const T& x);
	void Pop();
	void ChangeSizeID(T*&a, const int oldsize, const int newsize);
};

#endif

