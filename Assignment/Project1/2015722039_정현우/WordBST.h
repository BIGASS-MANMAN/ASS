#ifndef _WORDBST_H_
#define _WORDBST_H_

#include <fstream>
#include "WordNode.h"
using namespace std;
class WordBST
{
private:
	WordNode*	root;	// Word BST Root
	ofstream	fo;		// Write in memorizing.txt
	ofstream	Log;	// Wirte in Log.txt
public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode*	Delete(char * word);				// TEST
	WordNode*	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);				// PRINT
	bool		Save();								// SAVE

	void Re_Preorder(WordNode * node);				//Recursive preorder
	void It_Preorder(WordNode * node);				//Interative preorder
	void Re_Inorder(WordNode * node);				//Recursive IN order
	void It_Inorder(WordNode * node);				//interative IN order
	void Re_Postorder(WordNode * node);				//Recursive Post order
	void It_Postorder(WordNode * node);				//Interative post order
	void it_Levelorder(WordNode * node);			//Interative LEVEL order
};

#endif
