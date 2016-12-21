#include "WordBST.h"



WordBST::WordBST()
{
	root = '\0';
	rightHeight = 0;
	leftHeight = 0;
	for (int i = 0; i < 100; i++) Stk_or_Que[i] = '\0';
	numOfWords = 0;
	logfile.open("log.txt", ios::app);
}


WordBST::~WordBST()		//delete all memories in word bst.
{
	WordNode* node=root;
	int i = -1;
	int j = -1;
	WordNode* Stack[100];
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
	logfile.close();
}

int WordBST::GetNum() {		//return the number of word in word bst.

	return numOfWords;
}

void WordBST::Insert(WordNode * node) {		//insert a word at word bst. this function is used with Alphabetbst.
	if (Search(node->GetWord()) != '\0') {
		delete node;
		return;
	}
	numOfWords++; //word count plus
	if (!root) root = node; //set a node which first input as root
	WordNode * cur = root;		//set root

	while (node && strcmp(node->GetWord(), cur->GetWord())) {		//BST inserting  //except the node has same word
		if (strcmp(node->GetWord(), cur->GetWord())<0) {		// case one : a word of the node is smaller than word of the current node 
			if (cur->GetLeft() == '\0') {		//if there is no more node, link with the parents node
				cur->SetLeft(node);
				return;
			}
			else cur = cur->GetLeft();		//go to left node
		}
		else {	// case two :  a word of the node is bigger than word of the current node
			if (cur->GetRight() == '\0') {		//if there is no more node, link with the parents node
				cur->SetRight(node);
				return;
			}
			else cur = cur->GetRight();		//go to right node
		}
	}
}			// LOAD, MOVE
WordNode * WordBST::Delete(char * word) {		//delete word in Wordbst. this function use with Insert function of CLL. this function do not delete memory but return word.
	WordNode *node = root, *parents = '\0';
	while (node && strcmp(word, node->GetWord())) {		//this can escape when finding same word, or the node is '\0'
		parents = node;
		if (strcmp(word, node->GetWord())<0) node = node->GetLeft();
		else node = node->GetRight();
	}
	if (node == '\0') return '\0';				//the node is '\0', this mean it didn't find same word
	
	if (node->GetLeft() == '\0' && node->GetRight() == '\0') {		//node doesn't has child node
		if (parents == '\0') root = '\0';			//when the node is root
		else if (parents->GetLeft() == node) parents->SetLeft('\0');	//when node is leftchild of parents
		else parents->SetRight('\0');//when the node is rightchild of parents
		numOfWords--;	//delete(return) the node
		return node;
	}
	
	if (node->GetLeft() == '\0') {		//the node has right child
		if (parents == '\0') root = node->GetRight();		//when the node is root
		else if (parents->GetLeft()==node) parents->SetLeft(node->GetRight());		//when the node is leftchild of parents
		else parents->SetRight(node->GetRight());		//when the node is rightchild of parents
		numOfWords--;
		node->SetRight('\0');
		return node; //delete(return)
	}
	
	if (node->GetRight() == '\0') {		//the node has left child
		if (parents == '\0') root = node->GetLeft();		//when the node is root
		else if (parents->GetLeft()==node) parents->SetLeft(node->GetLeft());		//when the node is leftchild of parents
		else parents->SetRight(node->GetLeft());			//when the node is rightchild of parents
		numOfWords--;
		node->SetLeft('\0');
		return node; //delete(return)
	}

	//the node has left, and right child
	WordNode * prev = node;					//prevnode of the current node		
	WordNode * cur = node->GetLeft();		//the current node which will be fill the node to be deleted
	WordNode * next = node->GetLeft()->GetRight();//next node for check if there is more rightchild or not
	WordNode * temp = '\0';

	while (next) {					//until there is no right child, get right child
		prev = cur;
		cur = next;
		next = next->GetRight();
	}

	if (cur == node->GetLeft()) 		//if cur is node's left child
		cur->SetRight(node->GetRight());
	else {								//another case.
		prev->SetRight(cur->GetLeft());
		cur->SetLeft(node->GetLeft());
		cur->SetRight(node->GetRight());
	}									//setting cur's child

	if (parents == '\0') root = cur;	//when node is root
	else if (parents->GetLeft() == node) parents->SetLeft(cur); //when node is parents' left child.
	else parents->SetRight(cur);	//when node is parents' rigght child.
	
	node->SetRight('\0');		//disconnect all link of node
	node->SetLeft('\0');
	numOfWords--;
	return node;		//delete(return)
}				// TEST
WordNode * WordBST::Search(char * word) {		//search a word in Wordbst.
	WordNode * finder = root;		
	while (finder) {		//if word is smaller than finder's word, go to left, the other case go right
		if (!strcmp(word, finder->GetWord())) return finder;	//if it find same word return finder.
		else if (strcmp(word, finder->GetWord()) < 0) finder = finder->GetLeft();
		else finder = finder->GetRight();
	}
	return '\0';
}				// ADD, TEST, SEARCH, UPDATE
bool WordBST::Print(char * order) {			//print all words in wordbst by option.
	if (!strcmp(order, "r_pre")) this->R_Preorder(root);
	else if (!strcmp(order, "i_pre")) this->I_Preorder(root);
	else if (!strcmp(order, "r_in")) this->R_Inorder(root);
	else if (!strcmp(order, "i_in")) this->I_Inorder(root);
	else if (!strcmp(order, "r_post")) this->R_Postorder(root);
	else if (!strcmp(order, "i_post")) this->I_Postorder(root);
	else if (!strcmp(order, "r_lev")) this->I_Levelorder(root);
	else return false;

	return true;
}							// PRINT
bool WordBST::Save() {			//Save all words in "memorizing_word.txt" file.
	ofstream file;
	file.open("memorizing_word.txt", ios::app);		//do not overwriting. because this file will be called 26 times. if overwrite file, former Alphabet's word will be delete.

	if (file.is_open() == false || root=='\0')	return false;		//if fail to open file or there are no words in bst return false
	WordNode* node = root;

	int i = -1;					//using preorder, if don't use preorder, when load files next time, tree shape is different from former tree.
	while (1) {
		while (node) {
			file << node->GetWord() << "\t" << node->GetMean() << endl;
			Stk_or_Que[++i] = node; 
			node = node->GetLeft();
		}
		if (Stk_or_Que[0] == '\0') break;
		node = Stk_or_Que[i];
		Stk_or_Que[i] = '\0'; i--;
		node = node->GetRight();
	}
	file.close();
	return true;
}								// SAVE

void WordBST::R_Preorder() { R_Preorder(root); }		//Overloading for Alphabet bst.
void WordBST::I_Preorder() { I_Preorder(root); }
void WordBST::R_Inorder() { R_Inorder(root); }
void WordBST::I_Inorder() { I_Inorder(root); }
void WordBST::R_Postorder() { R_Postorder(root); }
void WordBST::I_Postorder() { I_Postorder(root); }
void WordBST::I_Levelorder() { I_Levelorder(root); }

void WordBST::R_Preorder(WordNode * node) {		//preorder
	if (node) {
		cout << node->GetWord() << " " << node->GetMean() << endl;
		logfile << node->GetWord() << " " << node->GetMean() << endl;
		R_Preorder(node->GetLeft());
		R_Preorder(node->GetRight());
	}
}
void WordBST::I_Preorder(WordNode* node) {		//preorder
	int i = -1;
	while (1) {
		while (node) {
			cout << node->GetWord() << " " << node->GetMean() << endl;
			logfile << node->GetWord() << " " << node->GetMean() << endl;
			Stk_or_Que[++i] = node; 
			node = node->GetLeft();
		}
		if (Stk_or_Que[0] == '\0') return;
		node = Stk_or_Que[i];
		Stk_or_Que[i] = '\0'; i--;
		node = node->GetRight();
	}
}
void WordBST::R_Inorder(WordNode * node) {		//inorder
	if (node) {
		R_Inorder(node->GetLeft());
		cout << node->GetWord() << " " << node->GetMean() << endl;
		logfile << node->GetWord() << " " << node->GetMean() << endl;
		R_Inorder(node->GetRight());
	}
}
void WordBST::I_Inorder(WordNode* node) {		//inorder
	int i = -1;
	while (1) {
		while (node) {
			Stk_or_Que[++i] = node; 
			node = node->GetLeft();
		}
		if (Stk_or_Que[0] == '\0') return;
		node = Stk_or_Que[i];
		Stk_or_Que[i] = 0; i--;
		cout << node->GetWord() << " " << node->GetMean() << endl;
		logfile << node->GetWord() << " " << node->GetMean() << endl;
		node = node->GetRight();
	}

}
void WordBST::R_Postorder(WordNode * node) {	//postorder
	if (node) {
		R_Postorder(node->GetLeft());
		R_Postorder(node->GetRight());
		cout << node->GetWord() << " " << node->GetMean() << endl;
		logfile << node->GetWord() << " " << node->GetMean() << endl;
	}
}
void WordBST::I_Postorder(WordNode* node) {		//postorder
	int i = -1;
	int j = -1;
	WordNode* Stack[100];
	while (1) {
		while (node) {
			Stack[++j]=node; 
			Stk_or_Que[++i] = node;
			node = node->GetRight();
		}
		if (Stk_or_Que[0] == '\0') break;
		node = Stk_or_Que[i]->GetLeft();
		Stk_or_Que[i] = '\0'; i--;
	}
	
	for (; j >= 0; j--) {
		cout << Stack[j]->GetWord() << " " << Stack[j]->GetMean() << endl;
		logfile << Stack[j]->GetWord() << " " << Stack[j]->GetMean() << endl;
	}
}
void WordBST::I_Levelorder(WordNode* node) {		//levelorder
	int head=0, tail=0;
	while (node) {
			cout << node->GetWord() << " " << node->GetMean() << endl;
			logfile << node->GetWord() << " " << node->GetMean() << endl;
			if (node->GetLeft()) Stk_or_Que[tail++]=node->GetLeft();
			if (node->GetRight()) Stk_or_Que[tail++]=node->GetRight();
			if (head==tail) return;
			node = Stk_or_Que[head];
			Stk_or_Que[head++] = '\0';
	}
}
