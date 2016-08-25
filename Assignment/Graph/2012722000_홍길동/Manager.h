#pragma once
#include "edge.h"
#include "node.h"
#include "LeftistTree.h"
#include "request.h"
#include "graph.h"
#include <fstream>
class Manager
{
private:
	ifstream m_fin1;
	ifstream m_fin2;
	ofstream m_fout;

	graph Graph;
	int** CostArray;
	node* ShortPath;
	LeftistTree LFT;
	int COUNT;
	request* S_REQ_ROOT;
	request* F_REQ_ROOT;
	request* LF_S_ROOT;
	request* LF_F_ROOT;
public:
	Manager();
	~Manager();

	void MakeEdge(char* sentence);
	node* getGraphRoot();
	node* MakeShortPath(char From, char To, node* GraphRoot);
	void MakeCostArr(node* GraphRoot);
	edge* find(int v1, int v2);

	bool ProcessRoute(char* fname);
	bool InputFileOpen1(const char* fname);
	bool InputFileOpen2(const char* fname);
	bool OutputFileOpen(const char* fname);
	void setCount(int count);

	void PRINT(node* path, node* adjList, char from);
	bool COMMAND(char* fname);
	void REQUEST(char* sentence);
	bool EOS(char* sentence);
	void LINKFAIL(char* sentence);
	void consoleprint();
};