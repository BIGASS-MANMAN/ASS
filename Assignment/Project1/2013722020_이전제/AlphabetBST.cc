#include "AlphabetBST.h"      //include header
#include <iostream>
using namespace std;


AlphabetBST::AlphabetBST()   //constructor with ordering alphabet
{
	root = '\0';
	WordCnt = 0;
	Making('P');
	Making('H');
	Making('X');
	Making('D');
	Making('L');
	Making('T');
	Making('Z');
	Making('B');
	Making('F');
	Making('J');
	Making('N');
	Making('R');
	Making('V');
	Making('Y');
	Making('A');
	Making('C');
	Making('E');
	Making('G');
	Making('I');
	Making('K');
	Making('M');
	Making('O');
	Making('Q');
	Making('S');
	Making('U');
	Making('W');
}


AlphabetBST::~AlphabetBST()
{
	destruc(root);    //destructor

}
void     AlphabetBST::destruc(AlphabetNode* node)
{
	if (node == NULL)        //destructing by using recursive 
	{
		return;
	}
	if (node->GetRight() != NULL)
	{
		destruc(node->GetRight());
	}
	if (node->GetLeft() != NULL)
	{
		destruc(node->GetLeft());
	}
	node->SetLeft(NULL);
	node->SetRight(NULL);

	if (node != NULL)
	{
		delete node;
	}
}

bool         AlphabetBST::IsEmpty()  //check bst empty
{
	AlphabetNode* current = root;
	if (current == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
AlphabetNode *AlphabetBST::GetRoot() //retrun root;
{
	return root;
}

void			AlphabetBST::Insert(AlphabetNode * node)	//push 
{
	if (!root)    //if root is NULL, node is root
	{
		root = node; 
		return;
	}
	else
	{
		AlphabetNode* newNode = root;

		for (;;)
		{
			if (newNode->GetAlphabet() <= node->GetAlphabet())			 //current is root
			{
				if (newNode->GetRight() == NULL)						  // while 
				{
					newNode->SetRight(node);							//node's alphabet is bigger than current's alpha
					return;
				}
				else
				{
					newNode = newNode->GetRight();						//current is current right child	
					continue;
				}
			}
			else if (newNode->GetAlphabet() > node->GetAlphabet())	//if current's alpha is bigger than node's alpha
			{
				if (newNode->GetLeft() == NULL)							//if current's left child is NULL
				{
					newNode->SetLeft(node);								//current's left child is node
					return;
				}
				else
				{
					newNode = newNode->GetLeft();						//else current = current's left child
					continue;
				}
			}
			else
			{
				return;   //exception handling
			}
		}
	}
}

bool			AlphabetBST::Print(char * order)  //print bst						
{
	ofstream ouf;
	ouf.open("log.txt", ios::app);
	if (this->GetWordCnt() == 0)
	{
		return false;   //empty bst
	}

	if (strcmp(order, "R_PRE") == 0)  //called print 
	{
		ouf << "======== PRINT ========" << endl;
		R_PRE(root);
		ouf << "=======================" << endl << endl;
		ouf.close();
		return true;
	}
	else if (strcmp(order, "I_PRE") == 0)  //called print 
	{
		ouf << "======== PRINT ========" << endl;
		I_PRE(root);
		ouf << "=======================" << endl << endl;
		ouf.close();
		return true;
	}
	else if (strcmp(order, "R_IN") == 0)  //called print 
	{
		ouf << "======== PRINT ========" << endl;
		R_IN(root);
		ouf << "=======================" << endl << endl;
		ouf.close();
		return true;
	}
	else if (strcmp(order, "I_IN") == 0)  //called print 
	{
		ouf << "======== PRINT ========" << endl;
		I_IN(root);
		ouf << "=======================" << endl << endl;
		ouf.close();
		return true;
	}
	else if (strcmp(order, "R_POST") == 0)  //called print 
	{
		ouf << "======== PRINT ========" << endl;
		R_POST(root);
		ouf << "=======================" << endl << endl;
		ouf.close();
		return true;
	}
	else if (strcmp(order, "I_POST") == 0)  //called print 
	{
		ouf << "======== PRINT ========" << endl;
		I_POST(root);
		ouf << "=======================" << endl << endl;
		ouf.close();
		return true;
	}
	else if (strcmp(order, "I_LEVEL") == 0)  //called print 
	{
		ouf << "======== PRINT ========" << endl;
		I_LEVEL(root);
		ouf << "=======================" << endl << endl;
		ouf.close();
		return true;
	}
	else
	{
		ouf.close();     //exception handling
		return false;
	}

	return false;
}


AlphabetNode *	AlphabetBST::Search(char alpabet)			// LOAD, MOVE, TEST, SEARCH, UPDATE
{
	if (!alpabet) return 0;         
	AlphabetNode * current = NULL;
	current = this->root;     //current is root

	if (current == NULL)
	{
		return NULL;    //bst is hasn't
	}
	while (current)     //while current is not null, searcing node by comparing
	{
		if (alpabet > current->GetAlphabet())
		{
			current = current->GetRight();
		}
	    else if (alpabet < current->GetAlphabet())
		{
			current = current->GetLeft();
		}
		else return current; //return node
	}
	return NULL;
}

bool			AlphabetBST::Save()							// SAVE
{
	if (root != NULL)
	{
		ofstream ouf;
		ouf.open("memorizing_word.txt");
		Pre_save(root);                                   //save by using pre_order traveral
		ouf.close();
		return true;
	}
	else
	{
		return false;
	}
}
void		AlphabetBST::Pre_save(AlphabetNode * current)
{
	if (current == NULL)
	{
		return;
	}

	current->GetBST()->Save(); //save data by preorder recursive traveral
	Pre_save(current->GetLeft());
	Pre_save(current->GetRight());
}

bool            AlphabetBST::R_PRE(AlphabetNode * node)
{

	if (node == NULL)
	{
		return true;
	}
	char method[6] = "R_PRE";        //recursive pre order
	node->GetBST()->Print(method);   //visit
	R_PRE(node->GetLeft());
	R_PRE(node->GetRight());
	return true;
}


bool AlphabetBST::R_IN(AlphabetNode* node)
{
	char method[5] = "R_IN";     //recursive in order
	if (node == NULL)
	{
		return true;
	}
	R_IN(node->GetLeft());  
	node->GetBST()->Print(method);  //vist
	R_IN(node->GetRight());
	return true;
}
bool AlphabetBST::R_POST(AlphabetNode* node)
{
	char  method[7] = "R_POST";    //recursive post order
	if (node == NULL)
	{
		return true;
	}
	R_POST(node->GetLeft());
	R_POST(node->GetRight());
	node->GetBST()->Print(method);   //visit
	return true;
}
void  AlphabetBST::Making(char alpha)
{
	AlphabetNode* current = NULL;   //making alphabet node tree
	current = new AlphabetNode;
	current->SetAlphabet(alpha);
	Insert(current);
}

int       AlphabetBST::GetWordCnt()  //get informaiton about node number in bst
{
	return WordCnt;
}

void AlphabetBST::WordCount(int check)
{
	if (check == 1)
	{
		WordCnt++;    //counting number of node in bst
		return;
	}
	else if (check == 2)
	{
		WordCnt--;
		return;
	}
	else
	{
		return;
	}
}

bool AlphabetBST::I_PRE(AlphabetNode* node)
{
	char  method[6] = {"I_PRE"  } ;   //Iterative pre order traveral
	this->Search('P')->GetBST()->Print(method);
	this->Search('H')->GetBST()->Print(method);
	this->Search('D')->GetBST()->Print(method);
	this->Search('B')->GetBST()->Print(method);
	this->Search('A')->GetBST()->Print(method);
	this->Search('C')->GetBST()->Print(method);
	this->Search('F')->GetBST()->Print(method);
	this->Search('E')->GetBST()->Print(method);
	this->Search('G')->GetBST()->Print(method);
	this->Search('L')->GetBST()->Print(method);
	this->Search('J')->GetBST()->Print(method);
	this->Search('I')->GetBST()->Print(method);
	this->Search('K')->GetBST()->Print(method);
	this->Search('N')->GetBST()->Print(method);
	this->Search('M')->GetBST()->Print(method);
	this->Search('O')->GetBST()->Print(method);
	this->Search('X')->GetBST()->Print(method);
	this->Search('T')->GetBST()->Print(method);
	this->Search('R')->GetBST()->Print(method);
	this->Search('Q')->GetBST()->Print(method);
	this->Search('S')->GetBST()->Print(method);
	this->Search('V')->GetBST()->Print(method);
	this->Search('U')->GetBST()->Print(method);
	this->Search('W')->GetBST()->Print(method);
	this->Search('Z')->GetBST()->Print(method);
	this->Search('Y')->GetBST()->Print(method);
	return true;
}
bool AlphabetBST::I_IN(AlphabetNode* node)
{
	char method[5] = "I_IN"; //Iterative in order traveral
	
	this->Search('A')->GetBST()->Print(method);
	this->Search('B')->GetBST()->Print(method);
	this->Search('C')->GetBST()->Print(method);
	this->Search('D')->GetBST()->Print(method);
	this->Search('E')->GetBST()->Print(method);
	this->Search('F')->GetBST()->Print(method);
	this->Search('G')->GetBST()->Print(method);
	this->Search('H')->GetBST()->Print(method);
	this->Search('I')->GetBST()->Print(method);
	this->Search('J')->GetBST()->Print(method);
	this->Search('K')->GetBST()->Print(method);
	this->Search('L')->GetBST()->Print(method);
	this->Search('M')->GetBST()->Print(method);
	this->Search('N')->GetBST()->Print(method);
	this->Search('O')->GetBST()->Print(method);
	this->Search('P')->GetBST()->Print(method);
	this->Search('Q')->GetBST()->Print(method);
	this->Search('S')->GetBST()->Print(method);
	this->Search('R')->GetBST()->Print(method);
	this->Search('T')->GetBST()->Print(method);
	this->Search('U')->GetBST()->Print(method);
	this->Search('V')->GetBST()->Print(method);
	this->Search('W')->GetBST()->Print(method);
	this->Search('X')->GetBST()->Print(method);
	this->Search('Y')->GetBST()->Print(method);
	this->Search('Z')->GetBST()->Print(method);
	
	return true;
}
bool AlphabetBST::I_POST(AlphabetNode* node)
{
	char method[7] = "I_POST"; //Iterative post order traveral
	this->Search('A')->GetBST()->Print(method);
	this->Search('C')->GetBST()->Print(method);
	this->Search('B')->GetBST()->Print(method);
	this->Search('E')->GetBST()->Print(method);
	this->Search('G')->GetBST()->Print(method);
	this->Search('F')->GetBST()->Print(method);
	this->Search('D')->GetBST()->Print(method);
	this->Search('I')->GetBST()->Print(method);
	this->Search('K')->GetBST()->Print(method);
	this->Search('J')->GetBST()->Print(method);
	this->Search('M')->GetBST()->Print(method);
	this->Search('O')->GetBST()->Print(method);
	this->Search('N')->GetBST()->Print(method);
	this->Search('L')->GetBST()->Print(method);
	this->Search('H')->GetBST()->Print(method);
	this->Search('Q')->GetBST()->Print(method);
	this->Search('S')->GetBST()->Print(method);
	this->Search('R')->GetBST()->Print(method);
	this->Search('U')->GetBST()->Print(method);
	this->Search('W')->GetBST()->Print(method);
	this->Search('V')->GetBST()->Print(method);
	this->Search('T')->GetBST()->Print(method);
	this->Search('Y')->GetBST()->Print(method);
	this->Search('Z')->GetBST()->Print(method);
	this->Search('X')->GetBST()->Print(method);
	this->Search('P')->GetBST()->Print(method);
	this->Search('Z')->GetBST()->Print(method);
	return true;
}

bool AlphabetBST::I_LEVEL(AlphabetNode* node)
{
	char method[8] = "I_LEVEL";    //Iterative level order traveral
	this->Search('P')->GetBST()->Print(method); 
	this->Search('H')->GetBST()->Print(method);
	this->Search('X')->GetBST()->Print(method);
	this->Search('D')->GetBST()->Print(method);
	this->Search('L')->GetBST()->Print(method);
	this->Search('T')->GetBST()->Print(method);
	this->Search('Z')->GetBST()->Print(method);
	this->Search('B')->GetBST()->Print(method);
	this->Search('F')->GetBST()->Print(method);
	this->Search('J')->GetBST()->Print(method);
	this->Search('N')->GetBST()->Print(method);
	this->Search('R')->GetBST()->Print(method);
	this->Search('V')->GetBST()->Print(method);
	this->Search('Y')->GetBST()->Print(method);
	this->Search('A')->GetBST()->Print(method);
	this->Search('C')->GetBST()->Print(method);
	this->Search('E')->GetBST()->Print(method);
	this->Search('G')->GetBST()->Print(method);
	this->Search('I')->GetBST()->Print(method);
	this->Search('K')->GetBST()->Print(method);
	this->Search('M')->GetBST()->Print(method);
	this->Search('O')->GetBST()->Print(method);
	this->Search('Q')->GetBST()->Print(method);
	this->Search('S')->GetBST()->Print(method);
	this->Search('U')->GetBST()->Print(method);
	this->Search('W')->GetBST()->Print(method);
	return true;
}

