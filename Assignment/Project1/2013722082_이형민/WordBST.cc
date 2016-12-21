
#include "WordBST.h"


WordBST::WordBST()//constructor
{
	root = '\0';
}

WordBST::~WordBST()// destructor
{
	postorder_delete(root);
}

void WordBST::postorder_delete(WordNode * currentNode)// delete for destructing
{
	if (currentNode) {
		postorder_delete(currentNode->GetLeft());
		postorder_delete(currentNode->GetRight());
		delete currentNode;
	}
}

void WordBST::Insert(WordNode * node)//insert
{
	if (root == 0)
	{
		root = node;
		return;
	}
	WordNode *temp= root;
	while (temp)
	{
		if (strcmp(temp->GetWord(), node->GetWord()) > 0)// when go to left subtree
		{
			if (temp->GetLeft() == 0)
			{
				temp->SetLeft(node);
				return;
			}
			temp = temp->GetLeft();
		}
		else if (strcmp(temp->GetWord(), node->GetWord()) < 0)//when go to right subtree
		{
			if (temp->GetRight() == 0)
			{
				temp->SetRight(node);
				return;
			}
			temp = temp->GetRight();
		}
		else
		{
			temp->SetMean(node->GetWord());
			return;
		}
	}

}

WordNode * WordBST::Delete(char * word)//Delete
{
	WordNode * temp = root, *ptemp = 0;
	while (temp != 0 && strcmp(temp->GetWord(), word) != 0)// search for deleting
	{
		ptemp = temp;// ptemp is previous node of temp
		if (strcmp(temp->GetWord(), word) > 0)
			temp = temp->GetLeft();
		else
			temp = temp->GetRight();
	}
	if (temp == 0)
		return 0;

	if (temp->GetLeft() == 0 && temp->GetRight() == 0)//leaf 
	{
		if (ptemp == 0)
			root = 0;
		else if (ptemp->GetLeft() == temp)
			ptemp->SetLeft(0);
		else
			ptemp->SetRight(0);
		return temp;
	}

	if (temp->GetRight() == 0)//left child only
	{
		if (ptemp == 0) {
			root = temp->GetLeft();
			temp->SetLeft(0);
			temp->SetRight(0);
			return temp;
		}
		else
		{
			WordNode * prevprev = temp, *prev = temp->GetLeft(), *curr = prev->GetRight();
			//curr is search for the most big node of left sub tree
			while (curr) {
				prevprev = prev;//prevprev is previous node for prev
				prev = curr;//prev is previous node of curr
				curr = curr->GetRight();
			}
			if (ptemp->GetLeft() == temp) {
				ptemp->SetLeft(prev);
				if (temp != prevprev) {// modification of links
					prevprev->SetRight(prev->GetLeft());
					prev->SetLeft(temp->GetLeft());
				}
				temp->SetLeft(0);
				temp->SetRight(0);
				return temp;// temp deleting 

			}
			else
			{
				ptemp->SetRight(prev);
				if (temp != prevprev) {
					prevprev->SetRight(prev->GetLeft());//modificatrion of links
					prev->SetLeft(temp->GetLeft());
				}

				temp->SetLeft(0);
				temp->SetRight(0);
				return temp;//temp deleting
			}
		}
	}
	if (temp->GetLeft() == 0)//right child
	{
		if (ptemp == 0) {
			root = temp->GetRight();

			temp->SetLeft(0);
			temp->SetRight(0);
			return temp;
		}
		else
		{
			WordNode * prevprev = temp, *prev = temp->GetRight(), *curr = prev->GetLeft();
			while (curr) {
				prevprev = prev;
				prev = curr;
				curr = curr->GetLeft();
			}
			if (ptemp->GetLeft() == temp)
			{
				ptemp->SetLeft(prev);
				if (temp != prevprev) {
					prevprev->SetLeft(prev->GetRight());
					prev->SetRight(temp->GetRight());
				}

				temp->SetLeft(0);
				temp->SetRight(0);
				return temp;
			}
			else
			{
				ptemp->SetRight(prev);
				if (temp != prevprev) {
					prevprev->SetLeft(prev->GetRight());
					prev->SetRight(temp->GetRight());
				}

				temp->SetLeft(0);
				temp->SetRight(0);
				return temp;
			}
		}
	}

	else//both child
	{
		{

			WordNode * prevprev = temp, *prev = temp->GetLeft(), *curr = prev->GetRight();
			while (curr) {
				prevprev = prev;
				prev = curr;
				curr = curr->GetRight();
			}
			if (ptemp == 0)//when temp is root
			{
				if (prevprev != temp) {// modification of links
					prevprev->SetRight(prev->GetLeft());
					prev->SetLeft(temp->GetLeft());
				}
				prev->SetRight(temp->GetRight());
				root = prev;

				temp->SetLeft(0);
				temp->SetRight(0);
				return temp;
			}
			else if (ptemp->GetLeft() == temp) {
				ptemp->SetLeft(prev);
				if (prevprev != temp) {
					prevprev->SetRight(prev->GetLeft());
					prev->SetLeft(temp->GetLeft());
				}
				prev->SetRight(temp->GetRight());


				temp->SetLeft(0);
				temp->SetRight(0);
				return temp;
			}
			else
			{
				ptemp->SetRight(prev);
				if (prevprev != temp) {
					prevprev->SetRight(prev->GetLeft());
					prev->SetLeft(temp->GetLeft());
				}
				prev->SetRight(temp->GetRight());

				temp->SetLeft(0);
				temp->SetRight(0);
				return temp;
			}
		}
		return 0;
	}
}

WordNode* WordBST::Search(char * word)//SEARCH
{
	WordNode * temp = root;
	char pword[32], pgetword[32];
	strcpy(pword,word);
	while (temp)
	{
		strcpy(pgetword, temp->GetWord());

		if (strcmp(GetBigWord(pgetword),GetBigWord( pword)) >0)// change small word to big word
			temp = temp->GetLeft();
		else if (strcmp(pgetword,pword)<0)
			temp = temp->GetRight();
		else
			return temp;// find the search node
	}
	return 0;

}

bool  WordBST::Inorder(WordNode *subroot)//print order
{
	if (root == 0)
		return 0;

	if (subroot) {
		Inorder(subroot->GetLeft()); //go down left
		std::ofstream log("log.txt", std::ios::app);
		log << subroot->GetWord() << "\t" << subroot->GetMean() << "\n";//Visit(subroot);//print
		cout << subroot->GetWord() << "\t" << subroot->GetMean() << "\n";//Visit(subroot);//print
		log.close();	
		Inorder(subroot->GetRight()); //go down right
	}

	return 1;
}

bool WordBST::Preorder(WordNode * subroot)//print order
{
	if (root == 0)
		return 0;

	if (subroot) {
		std::ofstream log("log.txt", std::ios::app);
		log << subroot->GetWord() << "\t" << subroot->GetMean() << "\n";//Visit(subroot);//print
		cout << subroot->GetWord() << "\t" << subroot->GetMean() << "\n";//Visit(subroot);//print
		log.close();	
		
		Preorder(subroot->GetLeft()); //go down left
		Preorder(subroot->GetRight()); //go down right
	}
	return 1;
}

bool WordBST::Postorder(WordNode * subroot)//print order
{
	if (root == 0)
		return 0;

	if (subroot) {
		Postorder(subroot->GetLeft()); //go down left
		Postorder(subroot->GetRight()); //go down right
		std::ofstream log("log.txt", std::ios::app);
		log << subroot->GetWord() << "\t" << subroot->GetMean() << "\n";//Visit(subroot);//print
		cout << subroot->GetWord() << "\t" << subroot->GetMean() << "\n";//Visit(subroot);//print
		log.close();	
		
	}
	return 1;
}

bool WordBST::Nonrec_Inorder()//print order
{
	Stack<WordNode> s;
	WordNode * temp = root;
	if (root == 0)
		return 0;
	std::ofstream log("log.txt", std::ios::app);
	while (1)
	{
		while (temp)
		{
			s.push(temp);
			temp = temp->GetLeft();
		}
		if (s.isEmpty()){
			log.close();
			return 1;
		}
		temp = s.pop();
		//s.pop();
		log << temp->GetWord() << "\t" << temp->GetMean() << "\n";//Visit(subroot);//print
		cout << temp->GetWord() << "\t" << temp->GetMean() << "\n";//Visit(subroot);//print
		temp = temp->GetRight();
	}
	return 1;
}

bool WordBST::Nonrec_Postorder()//print order
{
	Stack<WordNode> s1;
	Stack<WordNode> s2;
	std::ofstream log("log.txt", std::ios::app);
	WordNode * temp = root;
	if (temp == 0)
		return 0;

	s1.push(temp);
	while (!s1.isEmpty())
	{
		temp = s1.pop();
		s2.push(temp);
		if (temp->GetLeft() != 0)
			s1.push(temp->GetLeft());
		if (temp->GetRight() != 0)
			s1.push(temp->GetRight());
	}
	while (!s2.isEmpty())
	{
		temp = s2.pop();
		log << temp->GetWord() << "\t" << temp->GetMean() << "\n";//Visit(subroot);//print
		cout << temp->GetWord() << "\t" << temp->GetMean() << "\n";//Visit(subroot);//print
	
	}
	log.close();
	return 1;
}

bool WordBST::Nonrec_Preorder()//print order
{
	Stack<WordNode> s;
	WordNode * temp = root;
	if (root == 0)
		return 0;
	std::ofstream log("log.txt", std::ios::app);
	while (1) {

		while (temp)
		{
			log << temp->GetWord() << "\t" << temp->GetMean() << "\n";//Visit(subroot);//print
			cout << temp->GetWord() << "\t" << temp->GetMean() << "\n";//Visit(subroot);//print
			s.push(temp);
			temp = temp->GetLeft();
		}
		if (s.isEmpty())
		{
			log.close();		
			return 1;
		}
		temp = s.pop();
		//s.pop();
		//
		temp = temp->GetRight();
	}
	return 1;
}

bool WordBST::Level_order()//print order
{
	LevelQueue<WordNode> q;// queue to save node temporarily
	WordNode *currentNode = root;
	if (root == 0)
		return 0;
	std::ofstream log("log.txt", std::ios::app);
	while (currentNode)
	{
		log << currentNode->GetWord() << "\t" << currentNode->GetMean() << "\n";//Visit(subroot);//print
		cout << currentNode->GetWord() << "\t" << currentNode->GetMean() << "\n";//Visit(subroot);//print
		if (currentNode->GetLeft())
			q.push(currentNode->GetLeft());//save leftchild node
		if (currentNode->GetRight())
			q.push(currentNode->GetRight());//save rightchild node
		if (q.isEmpty())
		{
			log.close();
			return 1;
		}
		currentNode = q.front();
		q.pop();//pop from queue
	}
	return 1;
}

bool WordBST::Print(char * order)//receiving the order print
{
	if (strcmp(order, "R_PRE") == 0)
	{
		return Preorder(root);
	}
	else if (strcmp(order, "R_IN") == 0)
	{
		return Inorder(root);
	}
	else if (strcmp(order, "R_POST") == 0)
	{
		return Postorder(root);
	}
	else if (strcmp(order, "I_PRE") == 0)
	{
		return Nonrec_Preorder();
	}
	else if (strcmp(order, "I_IN") == 0)
	{
		return Nonrec_Inorder();
	}
	else if (strcmp(order, "I_POST") == 0)
	{
		return Nonrec_Postorder();
	}
	else if (strcmp(order, "I_LEVEL") == 0)
	{
		return Level_order();
	}
	return 0;
}

bool WordBST::Save()//save
{
	if (root == 0)
		return 0;
	return preorder_save(root);
}

bool WordBST::preorder_save(WordNode * currentNode)//save order
{
	if (!currentNode)//when wordbst has nothing
		return 0;
	if (currentNode) {

		std::ofstream f("memorizing_word.txt", std::ios::app);
		f << currentNode->GetWord() << "\t" << currentNode->GetMean() << "\n";// save the file "memorizing_word"
		f.close();

		preorder_save(currentNode->GetLeft()); //go down left
		preorder_save(currentNode->GetRight()); //go down right
	}
	return 1;
}

char * WordBST::GetBigWord(char * word)// change small word to big word
{
	int loop = 0;
	while (word[loop] != '\0')
	{
		word[loop] = (char)toupper(word[loop]);// a => A, b => B
		loop++;
	}
	return word;//big word

}


