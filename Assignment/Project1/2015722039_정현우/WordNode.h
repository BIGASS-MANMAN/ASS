#ifndef _WORDNODE_H_
#define _WORDNODE_H_

#include <iostream>
#include <utility>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string.h>
using namespace std;

class WordNode
{
public:
	std::pair<char *, char *> wordmean;
	//char word[32];
	//char mean[32];
	WordNode * pLeft;	// BST Left Pointer
	WordNode * pRight;	// BST Right Pointer
	WordNode * pNext;	// Queue Next Pointer

public:
	WordNode();
	~WordNode();

	char *		GetWord();					// Get Word
	char *		GetMean();					// Get Word Mean
	WordNode *	GetLeft();					// Get BST Left Pointer
	WordNode *	GetRight();					// Get BST Right Pointer
	WordNode *	GetNext();					// Get Queue Next Pointer

	void		SetWord(char * word);		// Set Word
	void		SetMean(char * mean);		// Set Word Mean
	void		SetLeft(WordNode * node);	// Set BST Left Pointer
	void		SetRight(WordNode * node);	// Set BST Right Pointer
	void		SetNext(WordNode * node);	// Set Queue Next Pointer
};


template<class K>		 // Stack class for Interative order print
class Stack				 //class Stack
{
public:
	K *Array[100];		 // class array
public:
	Stack();
	~Stack();
	void push(K * node); //stack's Push Function
	K * pop();			 //stack's pop Function
	bool empty();		 //stack's empty Function
	K * top();			 //stack's top Function
};

template<class K>
Stack<K>::Stack()
{
	for (int i = 0; i < 100; i++)
		Array[i] = NULL; // all of Array is NULL in start position
}

template<class K>
Stack<K>::~Stack()
{}									//course all stack is pop in order, then destroyer need not
template<class K>
void Stack<K>::push(K * node) {		//stack's push Function
	if (Array[0] == NULL)			//if head == Null, head set
		Array[0] = node;			
	else							//else Array's last is node
	{
		int i = 0;
		while (Array[i] != NULL)
			i++;
		Array[i] = node;
	}
}
template<class K>
K * Stack<K>::pop() {						//stack's pop
	int i = 0;
	while (Array[i] != NULL && i != 101)	//go to last of Array
		i++;
	K *node = NULL;
	if(i==0)
		return NULL;
	node = Array[i - 1];
	Array[i - 1] = NULL;					//pop top node of the stack
	return node;							//return that node
}
template<class K>
bool Stack<K>::empty() {					//stack's empty Function
	int i = 0;
	if (Array[i] == NULL)					//if Array is exit : return 0 else return 1
		return 1;
	else
		return 0;
}
template<class K>
K * Stack<K>::top() {						//return top of the Array
	int i = 0;
	while (Array[i] != NULL && i != 101)
		i++;
	return Array[i - 1];
}

#endif
