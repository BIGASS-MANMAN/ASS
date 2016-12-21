#pragma once
#include "WordNode.h"
#include <iostream>
using namespace std;

class Stack
{
private:
	int count; // = 스택에 존재하는 노드 수
	WordNode* top; // = 가장 위에 있는 노드
	WordNode* list; // = 가장 아래에 있는 노드
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


