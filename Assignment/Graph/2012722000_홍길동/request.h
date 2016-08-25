#pragma once
#include "node.h"

class request
{
private:
	node* ShortestPath;
	int index;
	char from, to;
	int badwidth;
	request* S_Next;
	request* F_Next;
	request* LF_S_Next;//If linkFail contain this edge, Insert LF linked list
	request* LF_F_Next;
public:
	request();
	request(int Index, char From, char To, int Bandwidth);
	void setShortPath(node* path, int count, node* adjList);

	void setS_Next(request* pNext);
	void setF_Next(request* pNext);
	void setLF_S_Next(request* pNext);
	void setLF_F_Next(request* pNext);
	request* getS_Next();
	request* getF_Next();
	request* getLF_S_Next();
	request* getLF_F_Next();

	char getFrom();
	char getTo();
	int getIndex();
	int getBandwidth();

	node* getShortPath();
};