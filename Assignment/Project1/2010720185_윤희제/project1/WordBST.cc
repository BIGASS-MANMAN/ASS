#include "WordBST.h"



WordBST::WordBST()
{
	root = '\0'; // initialize root to NULL
}


WordBST::~WordBST()
{	
	if (root != '\0') // if root isn't empty
	{
		Stack s;                  // declare stack
		WordNode* current = '\0'; // declare current node and initialize to NULL
		WordNode* prev = '\0';    // declare previous current node and initialize to NULL
		s.Push_word(root);        // insert the root to stack

		while (s.word_top != '\0') // while stack isn't empty
		{
			current = s.word_top;  // input the word_top to current node

			if (prev == NULL || prev->GetLeft() == current || prev->GetRight() == current)
			{
				if (current->GetLeft())
					s.Push_word(current->GetLeft());
				else if (current->GetRight())
					s.Push_word(current->GetRight());
				else
				{
					delete s.Pop_word();
				}
			}

			if (current->GetLeft() == prev)
			{
				if (current->GetRight())
					s.Push_word(current->GetRight());
				else
				{
					delete s.Pop_word();
				}
			}

			if (current->GetRight() == prev)
			{
				delete s.Pop_word();
			}
			prev = current;
		}
	}			
}

void WordBST::Insert(WordNode * node)
{
	if (root == '\0')
	{
		root = new WordNode;
		root = node;
	}
	else
	{
		WordNode* temp = root;
		while (temp != '\0')
		{
			if (strcmp(temp->GetWord(), node->GetWord()) == 1) // temp가 node보다 사전적으로 뒤에 있음
			{
				if (temp->GetLeft() == '\0')
				{
					temp->SetLeft(node);
					break;
				}					
				else
					temp = temp->GetLeft();
			}
			if (strcmp(temp->GetWord(), node->GetWord()) < 0) // temp가 node보다 사전적으로 앞에 있음
			{
				if (temp->GetRight() == '\0')
				{
					temp->SetRight(node);
					break;
				}
				else
					temp = temp->GetRight();
			}
		}
	}	
}

WordNode* WordBST::Delete(char * word)
{
	WordNode* p = root;
	WordNode* q = '\0';

	while (p && (strcmp(word, p->GetWord()) != 0))
	{
		q = p;
		if ((strcmp(word, p->GetWord()) < 0))
			p = p->GetLeft();
		else
			p = p->GetRight();
	}
	if (p == 0)
		return 0;
	if (p->GetLeft() == 0 && p->GetRight() == 0)
	{
		if (q == 0)
			root = 0;
		return 0;
	}
}

WordNode* WordBST::Search(char * word)
{
	if (root == '\0')
		return 0;

	WordNode* search = root;
	int flag = 0;

	/* make upper case to lower case */
	for (int i = 0; word[i] != '\0'; i++)
	{
		if (word[i] >= 65 && word[i] <= 90) // if upper case
			word[i] += 32;                  // make lower case
	}

	while (search->GetLeft() != '\0' || search->GetRight() != '\0')
	{
		if (strcmp(search->GetWord(), word) == 0)
		{
			flag = 1;
			break;
		}
		if (search->GetWord() > word)
			search = search->GetLeft();
		if (search->GetWord() < word)
			search = search->GetRight();
	}
	if (strcmp(search->GetWord(), word) == 0)
		flag = 1;

	if (flag == 0)
		return 0;
	if (flag == 1)
		return search;
}

bool WordBST::Print(char * order)
{
	ofstream log_file("log.txt", ios::app);

	if (root == '\0') // if no node in word bst
	{
		return 0;
	}
	else
	{
		log_file << "======== PRINT ========" << endl;
		/* program prints all bst word by the user's choice */
		if (strcmp(order, "R_PRE") == 0)   // recursive pre-order
			R_Pre_order(root, order);
		if (strcmp(order, "I_PRE") == 0)   // interative pre-order
			I_Pre_order(order);
		if (strcmp(order, "R_IN") == 0)    // recursive in-order
			R_In_order(root, order);
		if (strcmp(order, "I_IN") == 0)    // interative in-order
			I_In_order(order);
		if (strcmp(order, "R_POST") == 0)  // recursive post-order
			R_Post_order(root, order);
		if (strcmp(order, "I_POST") == 0)  // interative post-order
			I_Post_order(order);
		if (strcmp(order, "I_LEVEL") == 0) // interative level-order
			I_Level_order(order);
		log_file << "=======================\n" << endl;
		return 1;
	}
}

bool WordBST::Save()
{
	if (root == '\0')
		return 0;
	else
	{
		ofstream output("memorizing_word.txt");
		Stack s;
		WordNode* current = '\0';

		s.Push_word(root);
		while (s.alphabet_top != '\0')
		{
			current = s.Pop_word();
			output << current->GetWord() << " " << current->GetMean() << endl;

			if (current->GetRight())
				s.Push_word(current->GetRight());
			if (current->GetLeft())
				s.Push_word(current->GetLeft());
		}
		output.close();
		return 1;
	}	
}

bool WordBST::R_Pre_order(WordNode* node, char* order)
{
	ofstream log_file("log.txt", ios::app);

	if (node == '\0')
		return 0;
	/* print all word bst nodes */
	if (node != '\0')
	{		
		log_file << node->GetWord() << " " << node->GetMean() << endl; // write word and mean into log.txt file
		R_Pre_order(node->GetLeft(), order);                         // go to the left child node
		R_Pre_order(node->GetRight(), order);                        // go to the right child node
		return 1;
	}
}

bool WordBST::I_Pre_order(char* order)
{
	if (root == '\0')
		return 0;
	else
	{
		ofstream log_file("log.txt", ios::app);
		Stack s;
		WordNode* current = '\0';

		s.Push_word(root);
		while (s.word_top != '\0')
		{
			current = s.Pop_word();
			log_file << current->GetWord() << " " << current->GetMean() << endl; // write word and mean into log.txt file

			if (current->GetRight())
				s.Push_word(current->GetRight());
			if (current->GetLeft())
				s.Push_word(current->GetLeft());
		}
		log_file.close();
		return 1;
	}	
}

bool WordBST::R_In_order(WordNode* node, char* order)
{
	ofstream log_file("log.txt", ios::app);

	if (node == '\0')
		return 0;
	/* print all word bst nodes */
	if (node != '\0')
	{
		R_In_order(node->GetLeft(), order);                          // go to the left child node
		log_file << node->GetWord() << " " << node->GetMean() << endl; // write word and mean into log.txt file
		R_In_order(node->GetRight(), order);                         // go to the right child node
		return 1;
	}
}

bool WordBST::I_In_order(char* order)
{
	if (root == '\0')
		return 0;
	else
	{
		ofstream log_file("log.txt", ios::app);
		Stack s;
		WordNode* current = root;

		while (s.word_top != '\0' || current)
		{
			if (current)
			{
				s.Push_word(current);
				current = current->GetLeft();
			}
			else
			{
				current = s.Pop_word();
				log_file << current->GetWord() << " " << current->GetMean() << endl; // write word and mean into log.txt file

				current = current->GetRight();
			}
		}
		log_file.close();
		return 1;
	}
}

bool WordBST::R_Post_order(WordNode* node, char* order)
{
	ofstream log_file("log.txt", ios::app);

	if (node == '\0')
		return 0;
	/* print all word bst nodes */
	if (node != '\0')
	{
		R_Post_order(node->GetLeft(), order);                          // go to the left child node
		R_Post_order(node->GetRight(), order);                         // go to the right child node
		log_file << node->GetWord() << " " << node->GetMean() << endl; // write word and mean into log.txt file
		return 1;
	}
}

bool WordBST::I_Post_order(char* order)
{
	if (root == '\0')
		return 0;
	else
	{
		ofstream log_file("log.txt", ios::app);
		Stack s;
		WordNode* current = '\0';

		s.Push_word(root);
		WordNode* prev = '\0';

		while (s.word_top != '\0')
		{
			if (prev == NULL || prev->GetLeft() == current || prev->GetRight() == current)
			{
				if (current->GetLeft())
					s.Push_word(current->GetLeft());
				else if (current->GetRight())
					s.Push_word(current->GetRight());
				else
				{
					log_file << current->GetWord() << " " << current->GetMean() << endl; // write word and mean into log.txt file
					s.Pop_word();
				}
			}

			if (current->GetLeft() == prev)
			{
				if (current->GetRight())
					s.Push_word(current->GetRight());
				else
				{
					log_file << current->GetWord() << " " << current->GetMean() << endl; // write word and mean into log.txt file
					s.Pop_word();
				}
			}

			if (current->GetRight() == prev)
			{
				log_file << current->GetWord() << " " << current->GetMean() << endl; // write word and mean into log.txt file
				s.Pop_word();
			}
			prev = current;
		}
		log_file.close();
		return 1;
	}
}

bool WordBST::I_Level_order(char* order)
{
	if (root == '\0')
		return 0;
	else
	{
		ofstream log_file("log.txt", ios::app);
		Queue q;
		WordNode* current = root;

		while (current)
		{
			log_file << current->GetWord() << " " << current->GetMean() << endl; // write word and mean into log.txt file

			if (current->GetLeft())
				q.Push(current->GetLeft());
			if (current->GetRight())
				q.Push(current->GetRight());
			if (q.pHead == '\0') return 0;
			current = q.pHead;
			q.Pop();
		}
		log_file.close();
		return 1;
	}
}