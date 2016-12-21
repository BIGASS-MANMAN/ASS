#pragma once
#include<iostream>
using namespace std;

template <typename T>
class Stack		// Stack class
{

private:
	T* stack;
	int top, capacity;

public:
	Stack(int stackCapacity = 10);		// If no stack capacity is given, the capacity is 10
	bool IsEmpty() const;
	T& Top() const;
	void Push(const T& x);
	void Pop();
	void ChangeSizeID(T*&a, const int oldsize, const int newsize);
};


template<typename T>
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1) throw "Stack capacity must be above 0";
	stack = new T[capacity];		// Dynamic allocate stack with size of "capacity"
	top = -1;

}

template<typename T>
bool Stack<T>::IsEmpty() const		// Check if the stack is empty
{
	return top == -1;
}

template<typename T>
T & Stack<T>::Top() const
{
	if (IsEmpty()) throw "Stack is empty";
	return stack[top];
}

template<typename T>
void Stack<T>::Push(const T & x)	// Push of stack
{
	if (top == capacity - 1)
	{
		ChangeSizeID(stack, capacity, 2 * capacity);
		capacity = capacity * 2;
	}
	stack[++top] = x;
}

template<typename T>
void Stack<T>::Pop()	// Pop of stack
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete.";
	top--;
}

template<typename T>
void Stack<T>::ChangeSizeID(T *& a, const int oldsize, const int newsize)
{
	if (newsize <0) throw "New length must be >=0";
	T* newArr = new T[newsize]; // 새로운배열 
	copy(a, a + oldsize, newArr);
	T* temp = a;
	a = newArr;
	delete[] temp; //이전 메모리를 제거 
}