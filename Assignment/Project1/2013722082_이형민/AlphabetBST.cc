#include "AlphabetBST.h"

AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;
	AlphabetNode *node;
	char arr[] = { "PHXDLTZBFJNRVYACEGIKMOQSUW" };
	for (int i = 0; i < 26; i++)//make alphabet bst
	{
		node = new AlphabetNode();//dynamic allocation
		node->SetAlphabet(arr[i]);
		this->Insert(node);// alphabet insert
	}
}

AlphabetBST::~AlphabetBST()//destructor
{
	Postorder_delete(root);//deleting order
}

void AlphabetBST::Insert(AlphabetNode* node)//insert
{

	AlphabetNode * temp = root;
	if (root == 0)
	{
		root = node;
		return;
	}
	while (temp)
	{
		if (temp->GetAlphabet() > node->GetAlphabet())//size comparison
		{
			if (temp->GetLeft() == 0)
			{
				temp->SetLeft(node);
				return;
			}
			temp = temp->GetLeft();//temp move left reapeatly
		}
		else if (temp->GetAlphabet() < node->GetAlphabet())//size comparison
		{
			if (temp->GetRight() == 0)
			{
				temp->SetRight(node);
				//WordCnt++;
				return;
			}
			temp = temp->GetRight();//temp move right reapeatly
		}
		else// when node is same 
			temp->SetAlphabet(node->GetAlphabet());
	}
}

bool AlphabetBST::Print(char * order)// by order print
{
	bool a=0;

	std::ofstream log("log.txt", std::ios::app);
	if (WordCnt != 0){
		cout << "=========PRINT=======" << std::endl;
		log << "=========PRINT=======" << std::endl;
		}	
	else
	{
		log.close();
		return 0;
	}	
	if (strcmp(order, "R_PRE") == 0)
	{

		a = Preorder(root, order);//print order
		cout << "=====================\n\n" << std::endl;
		log << "=====================\n\n" << std::endl;
		log.close();
		return a;
	}
	else if (strcmp(order, "R_IN") == 0)
	{
		a = Inorder(root, order);//print order
		cout << "=====================\n\n" << std::endl;
		log << "=====================\n\n" << std::endl;
		log.close();
		return a;
	}
	else if (strcmp(order, "R_POST") == 0)
	{
		a = Postorder(root, order);//print order
		log << "=====================\n\n" << std::endl;
		log.close();
		return a;
	}
	else if (strcmp(order, "I_PRE") == 0)
	{
		a = Nonrec_Preorder(order);//print order
		cout << "=====================\n\n" << std::endl;
		log << "=====================\n\n" << std::endl;
		log.close();
		return a;
	}
	else if (strcmp(order, "I_IN") == 0)
	{
		a = Nonrec_Inorder(order);//print order
		log << "=====================\n\n" << std::endl;
		log.close();
		return a;
	}	
	else if (strcmp(order, "I_POST") == 0)
	{
		a = Nonrec_Postorder(order);//print order
		cout << "=====================\n\n" << std::endl;
		log << "=====================\n\n" << std::endl;
		log.close();
		return a;
	}
	else if (strcmp(order, "I_LEVEL") == 0)
	{
		a = Level_order(order);//print order
		cout << "=====================\n\n" << std::endl;
		log << "=====================\n\n" << std::endl;
		log.close();
		return a;
	}

	return 0;

}

AlphabetNode * AlphabetBST::Search(char alpabet)//search
{
	char bigalpabet;
	if ('A' <= alpabet && alpabet <= 'Z')//case of big word
		bigalpabet = alpabet;
	else
		bigalpabet = alpabet - ('a' - 'A');//case of small word

	AlphabetNode * temp = root;
	while (temp)// start search
	{
		if (temp->GetAlphabet() > bigalpabet)
			temp = temp->GetLeft();
		else if (temp->GetAlphabet() < bigalpabet)
			temp = temp->GetRight();
		else
			return temp;//when find the sarch word

	}
	return 0;
}

bool AlphabetBST::Save()
{
	std::ofstream f;
	f.open("memorizing_word.txt", std::ios::trunc);
	f.close();
	return Inorder_save(root);
}

bool AlphabetBST::Inorder_save(AlphabetNode * currentNode)
{
	if(WordCnt==0)
		return 0;
	if (currentNode) {
		Inorder_save(currentNode->GetLeft()); //go down left
		currentNode->GetBST()->Save();
		Inorder_save(currentNode->GetRight()); //go down right
	}
	return 1;
}

void AlphabetBST::Postorder_delete(AlphabetNode * currentNode)
{
	if (currentNode) {
		Postorder_delete(currentNode->GetLeft()); //go down left
		Postorder_delete(currentNode->GetRight()); //go down right
		delete currentNode;
	}
}

int AlphabetBST::GetwordCnt()//for couting word
{
	return WordCnt;
}

void AlphabetBST::SetWordCnt(int pWordCnt)//for counting word
{
	WordCnt = pWordCnt;
}

bool AlphabetBST::Inorder(AlphabetNode * currentNode, char * order)
{
	if (WordCnt == 0)
		return 0;


	if (currentNode) {
		Inorder(currentNode->GetLeft(), order); //go down left
		currentNode->GetBST()->Print(order); //log << currentNode ->GetAlphabet();//Visit(currentNode);//print
		Inorder(currentNode->GetRight(), order); //go down right
	}
	return 1;
}

bool AlphabetBST::Preorder(AlphabetNode * currentNode, char * order)
{
	if (WordCnt == 0)
		return 0;

	else if (currentNode) {
		currentNode->GetBST()->Print(order); //log << currentNode ->GetAlphabet();//Visit(currentNode);//print
		Preorder(currentNode->GetLeft(), order); //go down left
		Preorder(currentNode->GetRight(), order); //go down right
	}
	return 1;
}

bool AlphabetBST::Postorder(AlphabetNode * currentNode, char * order)
{
	if (WordCnt == 0)
		return 0;

	if (currentNode) {
		Postorder(currentNode->GetLeft(), order); //go down left
		Postorder(currentNode->GetRight(), order); //go down right
		currentNode->GetBST()->Print(order); //log << currentNode ->GetAlphabet();//Visit(currentNode);//print

	}
	return 1;

}

bool AlphabetBST::Nonrec_Inorder(char * order)
{
	Stack<AlphabetNode> s;//using stack
	AlphabetNode * temp = root;
	if (WordCnt == 0)// exception point
		return 0;
	while (1)
	{
		while (temp)
		{
			s.push(temp);
			temp = temp->GetLeft();//temp move left down
		}
		if (s.isEmpty())//if stack is empty
			return 1;
		temp = s.pop();
		//s.pop();
		temp->GetBST()->Print(order);//word BST print
		temp = temp->GetRight();
	}
	return 1;
}

bool AlphabetBST::Nonrec_Postorder(char * order)
{

	Stack<AlphabetNode> s1;//using 2 stack
	Stack<AlphabetNode> s2;

	AlphabetNode * temp = root;
	if (WordCnt == 0)// if wordbst is empty
		return 0;

	s1.push(temp);
	while (!s1.isEmpty())//postorder implemented by repeatedly cycle
	{
		temp = s1.pop();
		s2.push(temp);
		if (temp->GetLeft() != 0)
			s1.push(temp->GetLeft());
		if (temp->GetRight() != 0)
			s1.push(temp->GetRight());
	}
	while (!s2.isEmpty())
		s2.pop()->GetBST()->Print(order);//word BST print
	return 1;
}

bool AlphabetBST::Nonrec_Preorder(char * order)
{
	Stack<AlphabetNode> s;//using stack
	AlphabetNode * temp = root;
	if (WordCnt == 0)
		return 0;
	while (1) {//postorder implemented by repeatedly cycle

		while (temp)
		{
			temp->GetBST()->Print(order);// wordBST print
			s.push(temp);
			temp = temp->GetLeft();
		}
		if (s.isEmpty())
			return 1;
		temp = s.pop();

		temp = temp->GetRight();
	}
	return 1;
}

bool AlphabetBST::Level_order(char * order)
{
	LevelQueue<AlphabetNode> q;// queue to save node temporarily
	AlphabetNode *currentNode = root;
	if (WordCnt == 0)
		return 0;
	while (currentNode)
	{
		currentNode->GetBST()->Print(order);
		if (currentNode->GetLeft())
			q.push(currentNode->GetLeft());//save leftchild node
		if (currentNode->GetRight())
			q.push(currentNode->GetRight());//save rightchild node
		if (q.isEmpty())
			return 1;
		currentNode = q.front();
		q.pop();//pop from queue
	}
	return 1;
}


