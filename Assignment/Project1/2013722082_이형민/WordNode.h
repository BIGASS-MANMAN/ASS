#ifndef _WORDNODE_H_
#define _WORDNODE_H_

#include <utility>
#include <cstring>
#include <fstream>
#include <iostream>
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

template <class T>
struct Node {
	Node<T>* next;
	T* data;
	Node() { next = 0; data = 0; }
};

template <class T>
class Stack// for printing using a stack
{

public:
	Stack() {
		pHead = 0;
	}
	~Stack() {
			while (!isEmpty())
			{
				pop();
			}
	}
	void push(T* data)// stack insert
	{
		Node<T> * newNode = new Node<T>;
		if (pHead == 0)
		{
			pHead = newNode;
			newNode->data = data;
		}
		else
		{
			newNode->next = pHead;
			pHead = newNode;
			newNode->data = data;
		}
	}
	T* pop()// stack delete
	{
		if (pHead == 0)
		{
			return 0;
		}
		else
		{
			Node<T> * temp = pHead;
			T * return_data = temp->data;
			pHead = pHead->next;// phead move forward for deleting temp
			delete temp;
			return return_data;

		}
	}
	bool isEmpty() {
		if (pHead == 0)
			return 1;
		else
			return 0;
	}

private:
	Node<T> * pHead;

};

template <class T>
class LevelQueue
{
public:

	LevelQueue()
	{
		pHead = 0;
	}
	~LevelQueue()//implemented destructor 
	{
		while (!this->isEmpty())//deleting untill has no node
			pop();
	}
	void push(T* data) {
		Node<T> *temp = pHead;
		Node<T> * newNode = new Node<T>;
		if (pHead == 0)
		{
			pHead = newNode;
			pHead->data = data;
		}
		else
		{
			while (temp->next != 0)
				temp = temp->next;
			temp->next = newNode;// at the end part insert
			newNode->data = data;
			//newNode->data = data;
		}
	}
	T* pop()//Levelqueue delete
	{
		if (pHead == 0)
			return 0;
		Node<T> * temp = pHead;
		T * return_data = temp->data;
		pHead = pHead->next;//phead move foward for deleting temp
		delete temp;
		return return_data;
	}
	bool isEmpty()
	{
		if (pHead == 0)
			return 1;
		else
			return 0;
	}
	T * front()//phead
	{
		return pHead->data;

	}

private:
	Node<T> * pHead;

};

#endif
