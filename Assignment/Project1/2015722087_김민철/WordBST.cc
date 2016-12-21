#include "WordBST.h"

void Postorder_Destructor_Word(WordNode*pCur) {
	if (pCur) { // if pCur is not NULL,
		Postorder_Destructor_Word(pCur->GetLeft()); // input the pCur's Left Node to tihs Recursive function
		Postorder_Destructor_Word(pCur->GetRight()); // input the pCur's Right Node to tihs Recursive function
		delete pCur; // delete the pCur
	}
}

WordBST::WordBST()
{
	root = '\0'; // set root to NULL
}

WordBST::~WordBST()
{
	Postorder_Destructor_Word(root);  // input the root Node to Recursive destruction function
}

