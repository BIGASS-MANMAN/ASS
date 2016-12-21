#include"Stack.h"

template<typename T>
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1) throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template<typename T>
Stack<T>::~Stack()
{

}

template<typename T>
bool Stack<T>::IsEmpty() const
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
void Stack<T>::Push(const T & x)
{
	if (top == capacity - 1)
	{
		ChangeSizeID(stack, capacity, 2 * capacity);
		capacity = capacity * 2;
	}
	stack[++top] = x;
}


template<typename T>
void Stack<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty. Cannot delete.";
	top--;
}

template<typename T>
void Stack<T>::ChangeSizeID(T *& a, const int oldsize, const int newsize)
{
	if (newsize <0) throw "New length must be >=0";
	T* newArr = new T[newsize];
	copy(a, a + oldsize, newArr);
	T* temp = a;
	a = newArr;
	delete[] temp;
}
