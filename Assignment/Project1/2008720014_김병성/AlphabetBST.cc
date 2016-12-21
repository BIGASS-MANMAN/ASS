#include "AlphabetBST.h"



AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;
}


AlphabetBST::~AlphabetBST()
{
	/* You must fill here */

}

void AlphabetBST::Rec_preorder_Print()
{
	Rec_preorder_Print(root);
}

void AlphabetBST::Rec_preorder_Print(AlphabetNode * currentNode)
{
	if (currentNode) {
		ofstream FILEOUT;
		FILEOUT.open("log.txt", ios::app);

		FILEOUT << currentNode->GetAlphabet() << endl;
		Rec_preorder_Print(currentNode->GetLeft());
		Rec_preorder_Print(currentNode->GetRight());

		FILEOUT.close();
	}
}

void AlphabetBST::Iter_preorder_Print()
{
	ofstream FILEOUT;
	FILEOUT.open("log.txt", ios::app);

	FILEOUT.close();
}

void AlphabetBST::Rec_inorder_Print()
{
	Rec_inorder_Print(root);
}

void AlphabetBST::Rec_inorder_Print(AlphabetNode * currentNode)
{
	if (currentNode) {
		ofstream FILEOUT;
		FILEOUT.open("log.txt", ios::app);

		Rec_inorder_Print(currentNode->GetLeft());
		FILEOUT << currentNode->GetAlphabet() << endl;
		Rec_inorder_Print(currentNode->GetRight());

		FILEOUT.close();
	}
}

void AlphabetBST::Iter_inorder_Print()
{
}

void AlphabetBST::Rec_postorder_Print()
{
	Rec_postorder_Print(root);
}

void AlphabetBST::Rec_postorder_Print(AlphabetNode * currentNode)
{
	if (currentNode) {
		ofstream FILEOUT;
		FILEOUT.open("log.txt", ios::app);

		Rec_postorder_Print(currentNode->GetLeft());
		Rec_postorder_Print(currentNode->GetRight());
		FILEOUT << currentNode->GetAlphabet() << endl;

		FILEOUT.close();
	}
}

void AlphabetBST::Iter_postorder_Print()
{
}

void AlphabetBST::Iter_level_Print()
{
}


int AlphabetBST::GetWordCnt()
{
	return WordCnt;
}

AlphabetNode * AlphabetBST::Getroot()
{
	return root;
}

void AlphabetBST::Insert(AlphabetNode * node)
{	
	AlphabetNode * p = root, * pp = nullptr;
	while (p) {
		pp = p;
		if (p->GetAlphabet() < node->GetAlphabet())
			p = p->GetRight();
		else if (p->GetAlphabet() > node->GetAlphabet())
			p = p->GetLeft();
	}

	if(root)
		if(node->GetAlphabet() > pp->GetAlphabet()) pp->SetRight(node);
		else
			pp->SetLeft(node);
	else root = node;
} // RUN

bool	AlphabetBST::Print(char * order) {
	ofstream FILEOUT;
	FILEOUT.open("log.txt", ios::app);

	if(!strcmp(order, "R_PRE")) {

	}
	else if (!strcmp(order, "I_PRE")) {

	}
	else if (!strcmp(order, "R_IN")) {

	}
	else if (!strcmp(order, "I_IN")) {

	}
	else if (!strcmp(order, "R_POST")) {

	}
	else if (!strcmp(order, "I_POST")) {

	}
	else if (!strcmp(order, "I_LEVEL")) {

	}
	return true;
} // PRINT

AlphabetNode *	AlphabetBST::Search(char alpabet) {
	return nullptr;
} // LOAD, MOVE, TEST, SEARCH, UPDATE

bool	AlphabetBST::Save() {
	return 0;
} // SAVE
