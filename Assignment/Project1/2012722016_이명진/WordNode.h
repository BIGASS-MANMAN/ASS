#ifndef _WORDNODE_H_
#define _WORDNODE_H_

#include <utility>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>	
#include <cstdlib>

#define SIZE_64 64
#define SIZE_32 32
#define FIRST_WORD 0
#define TEXTFILE_NUM 3
#define D_LOAD 10
#define D_ADD 11
#define D_MOVE 12
#define D_SAVE 13
#define D_TEST 14
#define D_SEARCH 15
#define D_PRINT 16
#define D_UPDATE 17
#define D_ERROR 18
#define D_EXIT 19
#define R_PRE 20
#define I_PRE 21
#define R_IN 22
#define I_IN 23
#define R_POST 24
#define I_POST 25
#define I_LEVEL 26
#define ALPHABET_CNT 27
#define TO_MEMORIZE 0
#define MEMORIZING 1
#define MEMORIZED 2
#define MAX_WORD 100
#define E_LOAD 100
#define E_ADD 200
#define E_MOVE 300
#define E_SAVE 400
#define E_TEST 500
#define E_SEARCH 600
#define E_PRINT 700
#define E_UPDATE 800
#define E_FILE 900

using namespace std;

class WordNode
{
private:
	std::pair<char *, char *> wordmean;
	//char word[32];
	//char mean[32];
	WordNode * pLeft;	// BST Left Pointer
	WordNode * pRight;	// BST Right Pointer
	WordNode * pNext;	// Queue Next Pointer
public:
	WordNode();
	WordNode(char* word, char* mean);
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

#endif
