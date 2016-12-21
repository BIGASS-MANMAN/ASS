#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "Queue.h"
#include "AlphabetBST.h"
#include "CircularLinkedList.h"
class Queue;
class AlphabetBST;
class CircularLinkedLish;
class FileClassNode
{
private:
	char* fileData[2];
	FileClassNode* pNext;
	int Opt;
	int Func;
public:
	FileClassNode();
	FileClassNode(int func);
	FileClassNode(int func, int opt);
	FileClassNode(int func, char* arg);
	FileClassNode(char* arg1, char* arg2);
	FileClassNode(int func, int opt, char* arg);
	FileClassNode(int func, char* arg1, char* arg2);
	~FileClassNode();

	FileClassNode* GetNext();
	char* GetFileData1();
	char* GetFileData2();
	int GetMoveCnt();
	int GetOpt();
	int GetFunc();

	void SetNext(FileClassNode* next);
};
class FileClass
{
private:
	ifstream fin;
	ofstream fout;
	FileClassNode * pHeadFile;
public:
	FileClass();
	~FileClass();

	bool Is_empty();
	void Push(FileClassNode* node);
	FileClassNode* Pop();

	bool Parsing_command(const char* filename);
	bool Parsing_file(const char* file_name);
	int Check_FuncFlag(char* function);
	int Check_OptionFlag(char* option);
	void Print_Logfile(bool fileSuccess, char* funcType, int Err, WordNode* node, char* preMean);
};
class Manager
{ 
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue
	FileClass File;
	FileClassNode* fileNode;
public:
	Manager();
	~Manager();

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line
	//int Parsing_Command(const char* command, char* function, char* option);
	
	bool ADD();
	bool LOAD();
	bool MOVE();
	bool SAVE();
	bool TEST();
	bool SEARCH();
	bool PRINT();
	bool UPDATE();
	//void Error(int code);
	void EXIT();
};

#endif