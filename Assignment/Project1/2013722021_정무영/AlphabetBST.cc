#include "AlphabetBST.h"



AlphabetBST::AlphabetBST()
{
	root = '\0';
	for (int i = 0; i < ALPHABET; i++) Stk_or_Que[i] = '\0';
	leftHeight = 0;
	rightHeight = 0;
	numOfWords = 0;
}


AlphabetBST::~AlphabetBST()
{
	AlphabetNode* node=root;
	int i = -1;
	int j = -1;
	AlphabetNode* Stack[100];
	while (1) {
		while (node) {
			Stack[++j] = node;
			Stk_or_Que[++i] = node;
			node = node->GetRight();
		}
		if (Stk_or_Que[0] == '\0') break;
		node = Stk_or_Que[i]->GetLeft();
		Stk_or_Que[i] = '\0'; i--;
	}

	for (; j >= 0; j--) {
		delete Stack[j];
	}
}

void AlphabetBST::Insert(AlphabetNode * node) {		//Insert AlphabetNode after allocation by principle of BST
	if (!root) root = node; //set a node which first input as a root
	AlphabetNode * cur = root;		//set root
	
	while (node && !(node->GetAlphabet() == cur->GetAlphabet())) {		//BST inserting 	//except the node has same data
		if (node->GetAlphabet() < cur->GetAlphabet()) {		// case one : a alphabet of the node is smaller than alphabet of the current node 
			if (cur->GetLeft() == '\0') {		//if there is no more node, link with the parents node
				cur->SetLeft(node);
				return;
			}
			else cur = cur->GetLeft();		//go to next node
		}
		else {									// case two :  a alphabet of the node is bigger than alphabet of the current node
			if (cur->GetRight() == '\0') {		//if there is no more node, link with the parents node
				cur->SetRight(node);
				return;
			}
			else cur = cur->GetRight();		//go to next node
		}
	}
	
}	// run

bool AlphabetBST::Print(char * order) {				
	if (!strcmp(order, "r_pre")) this->R_Preorder(root);
	else if (!strcmp(order, "i_pre")) this->I_Preorder(root);
	else if (!strcmp(order, "r_in")) this->R_Inorder(root);
	else if (!strcmp(order, "i_in")) this->I_Inorder(root);
	else if (!strcmp(order, "r_post")) this->R_Postorder(root);
	else if (!strcmp(order, "i_post")) this->I_Postorder(root);
	else if (!strcmp(order, "i_lev")) this->I_Levelorder(root);
	else return false;

	return true;
}						// PRINT

AlphabetNode * AlphabetBST::Search(char alpabet) {	
	if (alpabet >= 97 || alpabet <= 112) alpabet -= 32;
	AlphabetNode * finder = root;
	while (finder) {
		if (alpabet == finder->GetAlphabet()) return finder;
		else if (alpabet< finder->GetAlphabet()) finder = finder->GetLeft();
		else finder = finder->GetRight();
	}
	return '\0';
}			// LOAD, MOVE, TEST, SEARCH, UPDATE

bool AlphabetBST::Save() {		//using Save function of AlphabetBST class
	AlphabetNode* node=root;
	int cnt = 0;
	int i = -1;
	while (1) {
		while (node) {				//Store words by preorder
			cnt+=node->GetBST()->Save();
			Stk_or_Que[++i] = node;
			node = node->GetLeft();
		}
		if (Stk_or_Que[0] == '\0') break;
		node = Stk_or_Que[i];
		Stk_or_Que[i] = '\0'; i--;
		node = node->GetRight();
	}
	if (!cnt) return false;  //if no words in bst return false
	return true;
}							// SAVE

int AlphabetBST::GetNumOfWords() {					//visit all wordBST and count the number of words
	if (root == 0) return 0;
	int sum=0;
	AlphabetNode * node = root;
	int i = -1;
	while (1) {
		while (node) {
			Stk_or_Que[++i] = node;
			node = node->GetLeft();
		}
		if (Stk_or_Que[0] == '\0') return sum;
		node = Stk_or_Que[i];
		sum += node->GetBST()->GetNum();
		Stk_or_Que[i] = '\0'; i--;
		node = node->GetRight();
	}
}

void AlphabetBST::R_Preorder(AlphabetNode * node) {		//preorder
	if (node) {
		node->GetBST()->R_Preorder();
		R_Preorder(node->GetLeft());
		R_Preorder(node->GetRight());
	}
}
void AlphabetBST::I_Preorder(AlphabetNode* node) {		//preorder
	int i = -1;
	while (1) {
		while (node) {
			node->GetBST()->I_Preorder();
			Stk_or_Que[++i] = node; 
			node = node->GetLeft();
		}
		if (Stk_or_Que[0] == '\0') return;
		node = Stk_or_Que[i];
		Stk_or_Que[i] = '\0'; i--;
		node = node->GetRight();
	}
}
void AlphabetBST::R_Inorder(AlphabetNode * node) {		//inorder
	if (node) {
		R_Inorder(node->GetLeft());
		node->GetBST()->R_Inorder();
		R_Inorder(node->GetRight());
	}
}
void AlphabetBST::I_Inorder(AlphabetNode* node) {		//inorder
	int i = -1;
	while (1) {
		while (node) {
			Stk_or_Que[++i] = node; 
			node = node->GetLeft();
		}
		if (Stk_or_Que[0] == '\0') return;
		node = Stk_or_Que[i];
		Stk_or_Que[i] = 0; i--;
		node->GetBST()->I_Inorder();
		node = node->GetRight();
	}

}
void AlphabetBST::R_Postorder(AlphabetNode * node) {		//postorder
	if (node) {
		R_Postorder(node->GetLeft());
		R_Postorder(node->GetRight());
		node->GetBST()->R_Postorder();
	}
}
void AlphabetBST::I_Postorder(AlphabetNode* node) {			//postorder
	int i = -1;
	int j = -1;
	AlphabetNode* Stack[100];
	while (1) {
		while (node) {
			Stack[++j] = node;
			Stk_or_Que[++i] = node;
			node = node->GetRight();
		}
		if (Stk_or_Que[0] == '\0') break;
		node = Stk_or_Que[i]->GetLeft();
		Stk_or_Que[i] = '\0'; i--;
	}

	for (; j >= 0; j--) {
		Stack[j]->GetBST()->I_Postorder();
	}
}
void AlphabetBST::I_Levelorder(AlphabetNode* node) {		//levelorder
	int head = 0, tail = 0;
	while (node) {
		node->GetBST()->I_Levelorder();
		if (node->GetLeft()) Stk_or_Que[tail++] = node->GetLeft();
		if (node->GetRight()) Stk_or_Que[tail++] = node->GetRight();
		if (head == tail) return;
		node = Stk_or_Que[head];
		Stk_or_Que[head++] = '\0';
	}
}
