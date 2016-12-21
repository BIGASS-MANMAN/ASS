#include "WordBST.h"
/************************************************************/
/*This is WordBST.cc that structred BST						*/
/*Also, It is declaration about WordBST Class				*/
/************************************************************/
WordBST::WordBST()
{
/* Constructor init root to '\0'						 	*/
	root = '\0';
}


WordBST::~WordBST()
{
/* Destructor free the memoary about WordNode Objects		*/
	root->~WordNode();
}

void WordBST::Insert(WordNode * node)
{
/* It is the insertion about Binary Search Tree Structure.		*/
/* If BST is empty, assign node to root.						*/
/* If not, Insert the node as proper child(compare as Word).	*/	
	if(root==NULL) {
		root=node;
		return;
	}
	
	WordNode *pCur = root, *ppCur;
	while(pCur!=NULL) {
		ppCur=pCur;
		pCur = strcmp(pCur->GetWord(),node->GetWord())<0 ? pCur->GetRight() : pCur->GetLeft();
	}
	strcmp(ppCur->GetWord(),node->GetWord())<0 ? ppCur->SetRight(node) : ppCur->SetLeft(node);
}

WordNode *	WordBST::Delete(char * word) {
/* Delete works to returns word in data structures.				*/
/* First, check whether parameter word exists in this			*/ 
/* Andthen, do Deletion.										*/
/*	in degree 2, replace MINIMUM KEY in right subtree			*/
/*	in degree 1, replace MIN/MAXIMUM KEy in left/right subtree	*/
/*	no degree, just returns that								*/
	WordNode *pCur = root;
	WordNode *ppCur = '\0';
	WordNode *temp = '\0';
	WordNode *ppTemp = '\0';
	char tWord[32]={0}, tMean[32]={0};
	int flag;

	if(!this->Search(word)) return NULL; 
	
	while(flag = strcmp(pCur->GetWord(),word)) {
		ppCur = pCur;
		pCur = flag>0 ? pCur->GetLeft() : pCur->GetRight();
	} // pCur is deletion Node, ppCur is pCur's parent Node.
	if(pCur->GetLeft()) {
		ppTemp = pCur;
		temp = pCur->GetLeft();

		while(temp->GetRight()) {
			ppTemp=temp;
			temp = temp->GetRight();
		}
		if(ppTemp==pCur) ppTemp->SetLeft(temp->GetLeft());
		else ppTemp->SetRight(temp->GetLeft());
		strcpy(tWord,pCur->GetWord());
		strcpy(tMean,pCur->GetMean());

		pCur->SetVoca(temp->GetWord(),temp->GetMean());

		temp->SetVoca(tWord,tMean);
		temp->SetLeft(NULL);
		temp->SetRight(NULL);
		return temp;
	}
	
	else if(!pCur->GetLeft() && pCur->GetRight()) {
		ppTemp = pCur;
		temp = pCur->GetRight();

		while(temp->GetLeft()) {
			ppTemp=temp;
			temp = temp->GetLeft();
		}
		if(ppTemp==pCur) ppTemp->SetRight(temp->GetRight());
		else ppTemp->SetLeft(temp->GetRight());
		strcpy(tWord,pCur->GetWord());
		strcpy(tMean,pCur->GetMean());

		pCur->SetVoca(temp->GetWord(),temp->GetMean());
		temp->SetVoca(tWord,tMean);
		temp->SetLeft(NULL);
		temp->SetRight(NULL);
		return temp;
	}	

	else { // no degree
		if(!ppCur) root=NULL;
		else ppCur->GetLeft() == pCur ? ppCur->SetLeft(NULL) : ppCur->SetRight(NULL);
		pCur->SetLeft(NULL);
		pCur->SetRight(NULL);
		return pCur;
	}

}

bool WordBST::Print(char *order) {
/* It is the Traversal about Binary Search Tree Structure.						*/
/* In order, there are 4 case : Pre-Order, In-Order, Post-Order, Level_Order.	*/
/* In technical method, there are 2 case : Iteratively, Recursively.			*/
	const char *orderMode[7] = {"I_PRE","I_IN","I_POST","I_LEVEL","R_PRE","R_IN","R_POST"};
	short int op=-1;
	// with string constants and opcode, easily can call one of print-methods
   	// using switch statements.	

	for(int i=0;i<7;i++) if(!strcmp(order,orderMode[i])) op = i; 
	
	switch(op) {
	case 0: return I_PRE();			// in case "I_PRE"
	case 1: return I_IN();			// in case "I_IN"
	case 2: return I_POST();		// in case "I_POST"
	case 3: return I_LEVEL();		// in case "I_LEVEL" 
	case 4: return R_PRE(root);		// in case "R_PRE"
	case 5:	return R_IN(root);		// in case "R_IN"
	case 6:	return R_POST(root);	// in case "R_POST"
	default: return false;
	}
}

WordNode * WordBST::Search(char * word) {
/* It is the Search about Binary Search Tree Structure.					*/
/* It can implement using strcmp()										*/
	WordNode *pCur = root;
	int flag;
	while(pCur) {
		flag = strcmp(pCur->GetWord(),word);
		if(!flag) return pCur;
		pCur = flag>0 ? pCur->GetLeft() : pCur->GetRight();
	}
	return NULL;
}

bool WordBST::Save() {
/* It is the Save about Binary Search Tree Structure.				*/
/* I implemented this using PRINT() with Save option(=true)			*/  
	return I_PRE(true);		
}

void WordBST::VISIT(WordNode *node) {
	ofstream log(LOG_FILENAME,ios::app);
	log<<node->GetWord()<<"\t"<<node->GetMean()<<"\n";
	log.close();
}
/****************************************************************/
/* TRAVESAL ORDERING SECTION CALLED BY PRINT()					*/
bool WordBST::R_PRE(WordNode *node) {
/* Recursive Pre-order Traversal */
/* VISIT -> LEFT -> RIGHT		 */
	if(!node) return false;
	VISIT(node);
	R_PRE(node->GetLeft());
	R_PRE(node->GetRight());
}

bool WordBST::R_IN(WordNode *node) {
/* Recursive In-order Traversal	 */
/* LEFT -> VISIT -> RIGHT		 */
	if(!node) return false;
	R_IN(node->GetLeft());
	VISIT(node);
	R_IN(node->GetRight());
}

bool WordBST::R_POST(WordNode *node) {
/* Recursive Post-order Traversal */
/* LEFT -> RIGHT -> VISIT		  */
	if(!node) return false;
	R_POST(node->GetLeft());
	R_POST(node->GetRight());
	VISIT(node);
}

bool WordBST::I_PRE(bool save) {
/* Iterative Pre-order Traversal						*/
/* PUSH left-side wordNode in Stack & VISIT. Go RiGHT	*/ 
	WordNode *currentNode = root;
	Queue s;

	if(!root) return false;
	ofstream f(MEMORIZING_FILENAME,ios::app);
	if(!f) return false;

	while(true) {
		while(currentNode) {
			if(save) f<<currentNode->GetWord()<<"\t"<<currentNode->GetMean()<<endl;
			else VISIT(currentNode);
			s.Push(currentNode);
			currentNode=currentNode->GetLeft();
		}
		if(s.isEmpty()) {
			f.close();
			return true;
		}
		else currentNode = s.top();
		s.Pop_back();
		currentNode = currentNode->GetRight();
	}
}

bool WordBST::I_IN() {
/* Iterative In-order Traversal							*/
/* Push Left-side Nodes in Stack. VISIT&POP. GO RIGHT	*/ 
	WordNode *currentNode = root;
	Queue s;
	if(!root) return false;
	while(true) {
		while(currentNode) {
			s.Push(currentNode);
			currentNode=currentNode->GetLeft();
		}
		if(s.isEmpty()) return true;
		else currentNode = s.top();
		VISIT(currentNode);
		s.Pop_back();
		currentNode = currentNode->GetRight();
	}
}

bool WordBST::I_POST() {
/* Iterative Post-order Traversal   */
/* PUSH Left-side Nodes in Stack	*/ 
	WordNode *currentNode = root;
	WordNode *temp = NULL;
	Queue s;
	if(!root) return false;
	while(true) {
		while(currentNode) {
			s.Push(currentNode);
			currentNode=currentNode->GetLeft();
		}
		if(s.isEmpty()) return true;
		currentNode = s.top();
		if(!currentNode->GetRight()) { // if not RightChild,
			// VISIT, and then do loop.
			VISIT(currentNode);
			while(true) {
				temp = currentNode; 
				s.Pop_back(); 
				if(s.isEmpty()) return true;
				currentNode = s.top(); // pop_back (pop rear), and then assign currentNode 
				if(currentNode->GetRight() == temp) { // compare that temp is parent's rightChild 
					VISIT(currentNode);
				}
				else {
					currentNode=NULL; 
					break;
				}
			}
		}
		else {
			//GO RIGHT.
			currentNode = currentNode->GetRight();
		}
	}
}

bool WordBST::I_LEVEL() {
/* Iterative Level-order Traversal  */
/* It can impelment using queue		*/

	WordNode *currentNode = root;
	Queue wordQ;
	WordNode *temp;
	if(!root) return false;
	wordQ.Push(root);
	while(1) {
		temp = wordQ.Pop();
		if(!temp) break;
		VISIT(temp);
		if(temp->GetLeft()) wordQ.Push(temp->GetLeft());
		if(temp->GetRight()) wordQ.Push(temp->GetRight());
	}
}
/****************************************************************/
