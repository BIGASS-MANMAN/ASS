#include "AlphabetBST.h"
/************************************************************/
/*This is AlphabetBST.cc that structred BST					*/
/*Also, It is declaration about AlphabetBST Class			*/
/************************************************************/
AlphabetBST::AlphabetBST()
{
/* Constructor init all member variable to zero or '\0'  	*/
	root = '\0';
	WordCnt = 0;
}

AlphabetBST::~AlphabetBST()
{
/* Destructor free the memoary about AlphabetNode Objects 	*/
	root->~AlphabetNode();
}

void AlphabetBST::Insert(AlphabetNode * node) {
/* It is the insertion about Binary Search Tree Structure.		*/
/* If BST is empty, assign node to root.						*/
/* If not, Insert the node as proper child(compare as Word).	*/	
	AlphabetNode *data = new AlphabetNode;
	data->SetAlphabet(node->GetAlphabet());

	if(root==NULL) root=data;
	else {
		AlphabetNode *pCur = root;
		while(pCur!=NULL) {
			if((int)pCur->GetAlphabet() - (int)data->GetAlphabet() < 0) { // if CURSOR.KEY < NODE.KEY,
				if( pCur->GetRight() ) pCur=pCur->GetRight();
				else { 
					pCur->SetRight(data);
					return;
				}
			}
			else {
				if( pCur->GetLeft() ) pCur=pCur->GetLeft();
				else { 
					pCur->SetLeft(data);
					return;
				}
			}
		}
	}
}

bool AlphabetBST::Print(char *order) {
/* It is the Traversal about Binary Search Tree Structure.						*/
/* In order, there are 4 case : Pre-Order, In-Order, Post-Order, Level_Order.	*/
/* In technical method, there are 2 case : Iteratively, Recursively.			*/
	const char *orderMode[7] = {"I_PRE","I_IN","I_POST","I_LEVEL","R_PRE","R_IN","R_POST"};
	short int op=-1;
	// with string constants and opcode, easily can call one of print-methods
   	// using switch statements.	

	for(int i=0;i<7;i++) if(!strcmp(order,orderMode[i])) op = i; 
	
	switch(op) {
	case 0: return I_PRE(order);		// in case "I_PRE"
	case 1: return I_IN(order);			// in case "I_IN"
	case 2: return I_POST(order);		// in case "I_POST"
	case 3: return I_LEVEL(order);		// in case "I_LEVEL" 
	case 4: return R_PRE(root,order);	// in case "R_PRE"
	case 5:	return R_IN(root,order);	// in case "R_IN"
	case 6:	return R_POST(root,order);  // in case "R_POST"
	default: return false;
	}
}

AlphabetNode * AlphabetBST::Search(char alphabet) {
/* It is the Search about Binary Search Tree Structure.				*/
/* Letter is the ASCII-CODE value. Therefore, use value's gap		*/
	AlphabetNode *pCur = root;
	int flag;
	while(pCur) {
		flag = pCur->GetAlphabet() - alphabet;
		if(!flag) return pCur; // !flag means that zero, which it means that both ASCII CODEs are correct.
		pCur = flag>0 ? pCur->GetLeft() : pCur->GetRight(); // if positive value, CURSOR>TARGET.
	}
	return NULL;
}

bool AlphabetBST::Save() {
/* It is the Save about Binary Search Tree Structure.				*/
/* I implemented this using PRINT() with Save option(=true)			*/  
	ofstream f(MEMORIZING_FILENAME,ios::trunc);
	if(!f) return false;
	f.close();
	return I_PRE("I_PRE",true);
}

bool AlphabetBST::isEmpty() {
/* If either of WordBST have data(s), it returns false.			*/
/* to implement this, check WordCnt								*/
	return !WordCnt;
}

bool AlphabetBST::isFull() {
/* If SIZE equals CAPACITY(=100), it returns true.				*/
	return WordCnt==MAX_WORD;
}


/****************************************************************/
/* There are 3 member-function about WordCnt					*/
void AlphabetBST::incCnt() {
/* it increments WordCnt										*/
	WordCnt++;
}

void AlphabetBST::decCnt() {
/* it decrements WordCnt										*/
	WordCnt--;
}

int AlphabetBST::getCnt() {
/* it returns WordCnt											*/
	return WordCnt;
}
/****************************************************************/

/****************************************************************/
/* TRAVESAL ORDERING SECTION CALLED BY PRINT()					*/
bool AlphabetBST::R_PRE(AlphabetNode *node, char *order) {
/* Recursive Pre-order Traversal */
/* VISIT -> LEFT -> RIGHT		 */
	if(!node) return true;
	node->GetBST()->Print(order);
	R_PRE(node->GetLeft(),order);	
	R_PRE(node->GetRight(),order);
	return true;
}
bool AlphabetBST::R_IN(AlphabetNode *node, char *order) {
/* Recursive In-order Traversal */
/* LEFT -> VISIT -> RIGHT		*/
	if(!node) return true;
	R_IN(node->GetLeft(),order);
	node->GetBST()->Print(order);
	R_IN(node->GetRight(),order);
	return true;
}
bool AlphabetBST::R_POST(AlphabetNode *node, char *order) {
/* Recursive In-order Traversal */
/* LEFT -> RIGHT -> VISIT		*/
	if(!node) return true;
	R_POST(node->GetLeft(),order);	
	R_POST(node->GetRight(),order);
	node->GetBST()->Print(order);
	return true;
}

bool AlphabetBST::I_PRE(char *order, bool save) {
/* Iterative Pre-order Traversal */
	char orderTemp[27] = PRESTR;
	for(int i=0;i<LETTER;i++) {
		if(save) Search(orderTemp[i])->GetBST()->Save();
		else Search(orderTemp[i])->GetBST()->Print(order);
	} return true;
}

bool AlphabetBST::I_IN(char *order) {
/* Iterative In-order Traversal */
	char orderTemp[27] = INSTR;
	for(int i=0;i<LETTER;i++) Search(orderTemp[i])->GetBST()->Print(order);
	return true;
}
bool AlphabetBST::I_POST(char *order) {
/* Iterative Post-order Traversal */
	char orderTemp[27] = POSTSTR;
	for(int i=0;i<LETTER;i++) Search(orderTemp[i])->GetBST()->Print(order);
	return true;
}
bool AlphabetBST::I_LEVEL(char *order) {
/* Iterative Level-order Traversal */
	char orderTemp[27] = LEVSTR;
	for(int i=0;i<LETTER;i++) Search(orderTemp[i])->GetBST()->Print(order);
	return true;
}
/****************************************************************/