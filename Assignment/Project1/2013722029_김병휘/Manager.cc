#include "/usr/local/Auto_Scoring_System/src/signal.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "Manager.h"
using namespace std;


Manager::Manager()
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
}


Manager::~Manager()
{ return;

	delete cll;
	delete bst;
	delete queue;
}

/* ***************** global variables for functions ***************** */
int		move_num = 0;				// MOVE() num

char	test_par1[128] = { 0 };		// TEST() word mean
char	test_par2[128] = { 0 };		// TEST() word mean

char	search_par[128] = { 0 };	// SEARCH() word

char	print_par1[128] = { 0 };	// PRINT() DS order
char	print_par2[128] = { 0 };	// PRINT() DS order

char	update_par1[128] = { 0 };	// UPDATE() word new_mean
char	update_par2[128] = { 0 };	// UPDATE() word new_mean
/* ****************************************************************** */

int _atoi(const char* num)
{
	bool isPositive = true; // is positive number
	int result = 0; // result value

	if (*num == '-') // if find -
	{
		isPositive = false; // this is negative
		num++;
	}

	for (; *num;) // to the last word, '\0'
	{
		if ('0' <= *num && *num <= '9') // if this is the number
		{
			result *= 10; // shift the previous number

			switch (*num)
			{
			case '0': result += 0; break; // insert 0
			case '1': result += 1; break; // insert 1
			case '2': result += 2; break; // insert 2
			case '3': result += 3; break; // insert 3
			case '4': result += 4; break; // insert 4
			case '5': result += 5; break; // insert 5
			case '6': result += 6; break; // insert 6
			case '7': result += 7; break; // insert 7
			case '8': result += 8; break; // insert 8
			case '9': result += 9; break; // insert 9
			default: return 0; // characters that are not numbers are ignored
			}
			num++;
		}
		else
			return 0;
	}

	if (isPositive) return result; // return positive value
	else return (-1) * result; // return negative value
}

void _strlower(char* word)
{
	for (int i = 0; i < strlen(word); i++)
	{
		if (word[i] >= 'A' && word[i] <= 'Z')
			word[i] += 'a' - 'A'; // lower the character
	}

	return;
}

void Manager::run(const char * command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	ofstream output("log.txt", ios::app); // for log.txt

	ifstream fin; // read command.txt
	fin.open(command);

	char cmd[128]; // command line
	memset(cmd, 0, 128); // Initialization

	for (; !fin.eof();) // to the end of file, i.e. when meeting EXIT
	{
		fin.getline(cmd, 128); // read command
		char* function = strtok(cmd, " "); // take first argument

		if (!strcmp(function, "LOAD")) // LOAD
		{
			char* errchk = strtok('\0', " \n"); // it should be '\0'

			if (!errchk && LOAD()) // if success
			{
				output << "======== LOAD ========" << endl;
				output << "Success" << endl;
				output << "====================" << endl;
			}
			else // if failed
			{
				output << "======== ERROR ========" << endl;
				output << "100" << endl;
				output << "======================" << endl;
			}
		}
		else if (!strcmp(function, "ADD")) // ADD
		{
			char* errchk = strtok('\0', " \n"); // it should be '\0'

			if (!errchk && ADD()) // if success
			{
				output << "======== ADD ========" << endl;
				output << "Success" << endl;
				output << "====================" << endl;
			}
			else // if failed
			{
				output << "======== ERROR ========" << endl;
				output << "200" << endl;
				output << "======================" << endl;
			}
		}
		else if (!strcmp(function, "MOVE")) // MOVE
		{
			char *to_num = strtok('\0', " "); // take second argument
			if (to_num) // there is argument
			{
				move_num = _atoi(to_num); // convert the string into the number

				char* errchk = strtok('\0', " \n"); // it should be '\0'

				if (!errchk && MOVE()) // if success
				{
					output << "======== MOVE ========" << endl;
					output << "Success" << endl;
					output << "====================" << endl;
				}
				else // if failed
				{
					output << "======== ERROR ========" << endl;
					output << "300" << endl;
					output << "======================" << endl;
				}
			}
			else // there is no argument
			{
				output << "======== ERROR ========" << endl;
				output << "300" << endl;
				output << "======================" << endl;
			}
		}
		else if (!strcmp(function, "SAVE")) // SAVE
		{
			char* errchk = strtok('\0', " \n"); // it should be '\0'

			if (!errchk && SAVE()) // if success
			{
				output << "======== SAVE ========" << endl;
				output << "Success" << endl;
				output << "====================" << endl;
			}
			else // if failed
			{
				output << "======== ERROR ========" << endl;
				output << "400" << endl;
				output << "======================" << endl;
			}
		}
		else if (!strcmp(function, "TEST")) // TEST
		{
			char* word = strtok('\0', " \n"); // take second argument
			char* mean = strtok('\0', " \n"); // take third argument

			if (word && mean) // there are two arguments
			{
				strcpy(test_par1, word); // take word
				strcpy(test_par2, mean); // take mean

				_strlower(test_par1);  // for independance of capitals

				char* errchk = strtok('\0', " \n"); // it should be '\0'

				if (!errchk && TEST()) // if success
				{
					output << "======== TEST ========" << endl;
					output << "Pass" << endl;
					output << "====================" << endl;
				}
				else // if failed
				{
					output << "======== ERROR ========" << endl;
					output << "500" << endl;
					output << "======================" << endl;
				}
			}
			else // there is no argument
			{
				output << "======== ERROR ========" << endl;
				output << "500" << endl;
				output << "======================" << endl;
			}
		}
		else if (!strcmp(function, "SEARCH")) // SEARCH
		{
			char* word = strtok('\0', " "); // take second argument
			if (word) // there is argument
			{
				strcpy(search_par, word); // take argument
				
				_strlower(search_par); // for independance of capitals

				char* errchk = strtok('\0', " \n"); // it should be '\0'

				if (!errchk && SEARCH()); // if success
				else // if failed
				{
					output << "======== ERROR ========" << endl;
					output << "600" << endl;
					output << "======================" << endl;
				}
			}
			else // there is no argument
			{
				output << "======== ERROR ========" << endl;
				output << "600" << endl;
				output << "======================" << endl;
			}
		}
		else if (!strcmp(function, "PRINT")) // PRINT
		{
			char* ds = strtok('\0', " \n"); // take second argument
			char* order = strtok('\0', " \n"); // take third argument
			
			if (ds || order) // there is argument
			{
				if (ds && !order) // for TO_MEMORIZE and MEMORIZED
				{
					strcpy(print_par1, ds); // take second argument
				}
				else if (ds && order) // for MEMORIZING
				{
					strcpy(print_par1, ds); // take second argument
					strcpy(print_par2, order); // take third argument
				}
				else;

				char* errchk = strtok('\0', " \n"); // it should be '\0'

				if (!errchk && PRINT()) // if success
				{
					output << "======================" << endl;
				}
				else // if failed
				{
					output << "======== ERROR ========" << endl;
					output << "700" << endl;
					output << "======================" << endl;
				}
			}
			else // there is no argument
			{
				output << "======== ERROR ========" << endl;
				output << "700" << endl;
				output << "======================" << endl;
			}
		}
		else if (!strcmp(function, "UPDATE")) // UPDATE
		{
			char* word = strtok('\0', " \n"); // take second argument
			char* mean = strtok('\0', " \n"); // take third argument

			if (word && mean) // there are two arguments
			{
				strcpy(update_par1, word);
				strcpy(update_par2, mean);

				_strlower(update_par1); // for independance of capitals

				char* errchk = strtok('\0', " \n"); // it should be '\0'

				if (!errchk && UPDATE()); // if success
				else // if failed
				{
					output << "======== ERROR ========" << endl;
					output << "800" << endl;
					output << "======================" << endl;
				}
			}
			else // there is no argument
			{
				output << "======== ERROR ========" << endl;
				output << "800" << endl;
				output << "======================" << endl;
			}
		}
		else if (!strcmp(function, "EXIT")) // EXIT
		{
			char* errchk = strtok('\0', " \n"); // it should be '\0'

			if (!errchk) // if success
			{
				output.close();
				fin.close();
				return;
			}
			else; // EXIT error is undefined
		}
		else; // undefined function, ignore

		// reset all global variables
		memset(cmd, 0, 128);
		move_num = 0;
		memset(test_par1, 0, 128);
		memset(test_par2, 0, 128);
		memset(search_par, 0, 128);
		memset(print_par1, 0, 128);
		memset(print_par2, 0, 128);
		memset(update_par1, 0, 128);
		memset(update_par2, 0, 128);
		output << endl;
	}

	output.close();
	fin.close();
}

bool Manager::LOAD()
{
	// for Queue Load
	ifstream fin_queue;
	fin_queue.open("to_memorize_word.txt", ios::in);

	// for BST Load
	ifstream fin_bst_temp;
	fin_bst_temp.open("memorizing_word.txt", ios::in);

	// for Circular Linked List Load
	ifstream fin_cll;
	fin_cll.open("memorized_word.txt", ios::in);

	// there is no file
	if (!(fin_queue.is_open() && fin_bst_temp.is_open() && fin_cll.is_open()))
	{
		if (fin_queue.is_open())
			fin_queue.close();
		if (fin_bst_temp.is_open())
			fin_bst_temp.close();
		if (fin_cll.is_open())
			fin_cll.close();
		return false;
	}
	else
	{
		bool isEmpty = true; // all data structures are empty?

		char templist[128] = { 0 }; // temp string
		int word_num = 0; // the number of words in txt

		// BST Size Check
		for (; !fin_bst_temp.eof(); word_num++)
		{
			fin_bst_temp.getline(templist, 128);

			if (word_num >= 100) // it contains words more than 100
			{
				if (fin_queue.is_open())
					fin_queue.close();
				if (fin_bst_temp.is_open())
					fin_bst_temp.close();
				if (fin_cll.is_open())
					fin_cll.close();
				return false;
			}
		}

		// if word num is larger than the maximum size of BST
		if (bst->WordCnt + word_num > MAX_WORD)
		{
			if (fin_queue.is_open())
				fin_queue.close();
			if (fin_bst_temp.is_open())
				fin_bst_temp.close();
			if (fin_cll.is_open())
				fin_cll.close();
			return false;
		}

		fin_bst_temp.close();

		// read word list
		ifstream fin_bst;
		fin_bst.open("memorizing_word.txt", ios::in);

		// BST Load
		for (; !fin_bst.eof();)
		{
			char wordmean[128];
			memset(wordmean, 0, 128);

			fin_bst.getline(wordmean, 128); // get word and mean

			char* word = strtok(wordmean, "\t \n"); // take word
			char* mean = strtok('\0', "\t \n"); // take mean

			if (word && mean) // there are word and mean
			{
				// redundancy check
				if (!bst->Search(word[0])->GetBST()->Search(word)) {
					WordNode* node = new WordNode();
					node->SetWord(word);
					node->SetMean(mean);
					bst->Search(word[0])->GetBST()->Insert(node); // Insertion
					bst->WordCnt++;
					isEmpty = false;
				}
			}
		}

		// Queue Load
		for (; !fin_queue.eof();)
		{
			char wordmean[128];
			memset(wordmean, 0, 128);

			fin_queue.getline(wordmean, 128); // get word and mean

			char* word = strtok(wordmean, "\t \n"); // take word
			char* mean = strtok('\0', "\t \n"); // take mean

			if (word && mean) // there are word and mean
			{
				// redundancy check
				if (!queue->Search(word))
				{
					WordNode* node = new WordNode();
					node->SetWord(word);
					node->SetMean(mean);
					queue->Push(node); // Insertion
					isEmpty = false;
				}
			}
		}

		// Circular Linked List Load
		for (; !fin_cll.eof();)
		{
			char wordmean[128];
			memset(wordmean, 0, 128);

			fin_cll.getline(wordmean, 128); // get word and mean

			char* word = strtok(wordmean, "\t \n"); // take word
			char* mean = strtok('\0', "\t \n"); // take mean

			if (word && mean)
			{
				// redundancy check
				if (!cll->Search(word))
				{
					WordNode* node = new WordNode();
					node->SetWord(word);
					node->SetMean(mean);
					cll->Insert(node); // Insertion
					isEmpty = false;
				}
			}
		}

		if (isEmpty) return false;

		// file close
		fin_queue.close();
		fin_bst.close();
		fin_cll.close();
		return true;
	}
}

bool Manager::ADD()
{
	ifstream fin("word.txt");
	
	if (fin.is_open()) // file exist
	{
		if (fin.eof()) // include no word
		{
			fin.close();
			return false;
		}

		// check file is empty
		for (; !fin.eof();)
		{
			char wordmean[128];
			memset(wordmean, 0, 128);

			fin.getline(wordmean, 128); // get word and mean

			char* word = strtok(wordmean, "\t \n"); // take word
			char* mean = strtok('\0', "\t \n"); // take mean

			if (word && mean)
			{
				// redundancy check
				if (!queue->Search(word) && !cll->Search(word)) // cannot find the word
				{
					if (!bst->Search(word[0])) // there is no word in bst
					{
						WordNode* node = new WordNode();
						node->SetWord(word);
						node->SetMean(mean);
						queue->Push(node); // Push
					}
					else if (!bst->Search(word[0])->GetBST()->Search(word)) // there is no word in bst
					{
						WordNode* node = new WordNode();
						node->SetWord(word);
						node->SetMean(mean);
						queue->Push(node); // Push
					}
				}
			}
		}

		fin.close();
		return true;
	}
	else // file doesn't exist
	{
		if(fin.is_open())
			fin.close();
		return false;
	}
}

bool Manager::MOVE()
{
	if (queue->cnt < move_num) return false;

	if (1 <= move_num && move_num <= 100) // the number is in range 1 to 100
	{
		if (bst->WordCnt + move_num <= MAX_WORD) // it doesn't oversize
		{
			bst->WordCnt += move_num;

			for (int i = 0; i < move_num; i++)
			{
				WordNode* node = queue->Pop(); // remove word from Queue

				if (bst->Search(node->GetWord()[0])) // Insert node, i.e. word
					bst->Search(node->GetWord()[0])->GetBST()->Insert(node);
				else
					return false;
			}
			return true;
		}
	}

	return false;
}

bool Manager::SAVE()
{
	// Check all data structures are empty
	if (!queue->cnt && !bst->WordCnt && !cll->pHead)
		return false;
	else
	{
		queue->Save();
		bst->Save();
		cll->Save();
		return true;
	}
}

bool Manager::TEST()
{
	if (bst->Search(test_par1[0])) // There is a node with character
	{
		WordBST* w_bst = bst->Search(test_par1[0])->GetBST(); // get word bst

		if (w_bst->Search(test_par1)) // find first alphabet, i.e. capital
		{
			if (!strcmp(w_bst->Search(test_par1)->GetMean(), test_par2)) // find the word in the capital alphabet bst
			{
				cll->Insert(w_bst->Delete(test_par1)); // move it to Circluar Linked List
				bst->WordCnt -= 1; // count -1
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

bool Manager::SEARCH()
{
	ofstream output("log.txt", ios::app);

	if (output.is_open()) // file is open
	{
		if (queue->Search(search_par)) // if find it in Queue
		{
			WordNode* node = queue->Search(search_par); // get node

			// print the word and mean
			output << "======== SEARCH ========" << endl;
			output << node->GetWord() << " " << node->GetMean() << endl;
			output << "=======================" << endl;

			output.close();
			return true;
		}
		
		if (bst->Search(search_par[0])) // if find the first alphabet
		{
			WordNode* node = bst->Search(search_par[0])->GetBST()->Search(search_par); // find it in word bst
			if (node) // if find it in WordBST
			{
				// print the word and mean
				output << "======== SEARCH ========" << endl;
				output << node->GetWord() << " " << node->GetMean() << endl;
				output << "=======================" << endl;

				output.close();
				return true;
			}
		}
		
		if (cll->Search(search_par)) // if find it in Circular Linked List
		{
			WordNode* node = cll->Search(search_par); // get node

			// print the word and mean
			output << "======== SEARCH ========" << endl;
			output << node->GetWord() << " " << node->GetMean() << endl;
			output << "=======================" << endl;
			
			output.close();
			return true;
		}
		
		output.close();
		return false;
	}
	else
		return false;
}

bool Manager::PRINT()
{
	if (!strcmp(print_par1, "TO_MEMORIZE")) // PRINT TO_MEMORIZE
	{
		if (print_par2[0] == '\0') // if only one parameter
			return queue->Print();
		else
			return false;
	}
	else if (!strcmp(print_par1, "MEMORIZING")) // PRINT MEMORIZING PAR2 (e.g. PRINT MEMORIZING R_IN)
	{
		if (bst->WordCnt <= 0) // there is no word
		{
			return false;
		}
		else
		{
			return bst->Print(print_par2);
		}
	}
	else if (!strcmp(print_par1, "MEMORIZED")) // PRINT MEMORIZED
	{
		if (print_par2[0] == '\0') // if only one parameter
			return cll->Print();
		else
			return false;
	}
	else
		return false;
}

bool Manager::UPDATE()
{
	ofstream output("log.txt", ios::app);

	if (output.is_open()) // file is open
	{
		if (queue->Search(update_par1)) // if find the word in Queue
		{
			// get the information from Queue and udpate it
			output << "======== UPDATE ========" << endl;
			output << update_par1 << " ";
			output << queue->Search(update_par1)->GetMean() << " -> ";
			output << update_par2 << endl;
			output << "=======================" << endl;
			
			// update
			queue->Search(update_par1)->SetMean(update_par2);
			
			output.close();
			return true;
		}
		
		if (bst->Search(update_par1[0]))
		{
			WordNode* node = bst->Search(update_par1[0])->GetBST()->Search(update_par1);

			if (node) // if bst is not empty
			{
				// get the information from BST and update it
				output << "======== UPDATE ========" << endl;
				output << update_par1 << " ";
				output << node->GetMean() << " -> ";
				output << update_par2 << endl;
				output << "=======================" << endl;

				// update
				node->SetMean(update_par2);

				output.close();
				return true;
			}
		}
		
		if (cll->Search(update_par1))
		{
			// get the information from Circular Linked List and update it
			output << "======== UPDATE ========" << endl;
			output << update_par1 << " ";
			output << cll->Search(update_par1)->GetMean() << " -> ";
			output << update_par2 << endl;
			output << "=======================" << endl;
			
			// update
			cll->Search(update_par1)->SetMean(update_par2);
			
			output.close();
			return true;
		}
	
		output.close();
		return false;
	}
	else
	{
		output.close();
		return false;
	}
}
