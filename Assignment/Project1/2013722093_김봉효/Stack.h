#ifndef _STACK_H_
#define _STACK_H_
#include"WordNode.h"
template <class T>
class Stack
{
private:
	T *stack;
	int cap; // capacity : max size
	int top; // current size
public:
	int visit;
	Stack(int Scap = 30):cap(Scap) { // default : Scap=30
		if (cap < 1) throw"Stack Capacity must be > 0"; // exception handling
		visit = 0; // visit determination variable
		stack = new T[cap]; // dynamic allocation
		top = -1;
	}
	~Stack() {
		delete[] stack; // deallocation stack
	}
	bool IsEmpty() const {
		if (top == -1)
			return 1;
		return 0;
	}
	void ChangeSize() { // reallocation function
		int new_size = cap * 2; // 2
		T* temp = new T[new_size];
		for (int i = 0; i < cap; i++) {
			temp[i] = stack[i];
		}
		cap = new_size;
		delete[] stack;
		stack = temp;
	}
	void Push( T& node) {
		if (top == cap - 1) { // if stack is full
			ChangeSize(); // reallocation
		}
		stack[++top] = node; // push
	}
	void Pop() {
		if (IsEmpty()) throw"Stack is empty"; // exception handling
		stack[top--]=NULL; // pop
	}
	T Top() {
		if (IsEmpty()) throw "Stack is empty";
		return stack[top]; // return top
	}
};
#endif
