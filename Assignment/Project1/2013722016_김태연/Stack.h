#pragma once
#include "WordNode.h"
#include <iostream>
using namespace std;

class Stack
{
private:
	int count; // = ���ÿ� �����ϴ� ��� ��
	WordNode* top; // = ���� ���� �ִ� ���
	WordNode* list; // = ���� �Ʒ��� �ִ� ���
	WordNode* node;
public:
	Stack();
	~Stack();
	void setTop(WordNode* top);
	void Push(WordNode* newNode);
	bool isEmpty();
	WordNode* getTop();
	WordNode* Pop();
};


