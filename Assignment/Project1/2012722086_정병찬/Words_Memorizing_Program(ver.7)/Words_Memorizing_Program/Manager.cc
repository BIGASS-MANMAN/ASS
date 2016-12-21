
#include "Manager.h"
#include <iostream>
#include <fstream>
using namespace std;

Manager::Manager()
{	// Do dynamic allocation for cll(circular linked list), bst(binary search tree) and queue in constructor function
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
}


Manager::~Manager()
{	// In destructor function, delete dynamic allocated variables
	delete cll;
	delete bst;
	delete queue;

}

void Manager::run(const char * command)
{
	AlphabetNode * temp = new AlphabetNode;

	temp->SetAlphabet('P');			// Set the alphabet of the root node
	bst->Insert(temp);				// Insert the node so it can become the root node
	temp = new AlphabetNode;		// Do dynamic allocation again to create more node
	temp->SetAlphabet('H');
	bst->Insert(temp);
	temp = new AlphabetNode;
	temp->SetAlphabet('X');
	bst->Insert(temp);
	char ch = 'D';
	for (int i = 1; i <= 4; i++) {	// Insert the nodes of third level of alphabet BST
		if (i == 4) { ch = 'Z'; }
		temp = new AlphabetNode;
		temp->SetAlphabet(ch);
		bst->Insert(temp);
		ch += 8;
	}
	ch = 'B';
	for (int i = 1; i <= 7; i++) {	// Insert the nodes of fourth level of alphabet BST
		if (i == 7) { ch = 'Y'; }
		temp = new AlphabetNode;
		temp->SetAlphabet(ch);
		bst->Insert(temp);
		ch += 4;
	}
	ch = 'A';
	for (int i = 1; i <= 12; i++) {	// Insert the nodes of fifth level of alphabet BST
		temp = new AlphabetNode;
		temp->SetAlphabet(ch);
		bst->Insert(temp);
		ch += 2;
	}
	temp = new AlphabetNode;
	temp->SetAlphabet('W');
	bst->Insert(temp);

	delete temp;

	char* separate;
	char cmd[100];
	ifstream fin;
	fin.open(command);	// open command text file
	if (!fin)		// If it failed to open the file
	{
		cout << "======== ERROR ========" << endl << "commend.txt doesn't exist" << endl;
		cout << "=======================" << endl;
	}
	while (!fin.eof())	// Until the end of file
		{
			fin.getline(cmd, 100);
			separate = strtok(cmd, " ");	// Use "strtok" function to put command in 'separate'

			while (separate != NULL)
			{
				if (!strcmp(separate, "LOAD"))		// if 'separate' is "LOAD" command
				{
					separate = strtok(NULL, " ");
					arg1 = separate;
					separate = strtok(NULL, " ");
					if (!LOAD() || arg1 != NULL)	// If "LOAD" command failed
					{
						cout << "======== ERROR ========" << endl << "100" << endl;
						cout << "=======================" << endl;
						continue;

					}
					else
					{
						cout << "======== LOAD ========" << endl << "Success" << endl;
						cout << "=======================" << endl;
						continue;
					}
				
				}
				else if (!strcmp(separate, "ADD"))	// if 'separate' is "ADD" command
				{
					separate = strtok(NULL, " ");
					arg1 = separate;
					if (!ADD() || arg1 != NULL)		// If "ADD" command failed
					{
						cout << "======== ERROR ========" << endl << "200" << endl;
						cout << "=======================" << endl;
						continue;
					}
					else
					{
						cout << "======== ADD ========" << endl << "Success" << endl;
						cout << "=======================" << endl;
						continue;
					}
				}
				else if (!strcmp(separate, "MOVE"))		// if 'separate' is "MOVE" command
				{
					separate = strtok(NULL, " ");
					arg1 = separate;
					separate = strtok(NULL, " ");

					if (!MOVE())
					{
						cout << "======== ERROR ========" << endl << "300" << endl;
						cout << "=======================" << endl;
						continue;
					}
					else
					{
						cout << "======== MOVE ========" << endl << "Success" << endl;
						cout << "=======================" << endl;
						continue;
					}
				}
				else if (!strcmp(separate, "PRINT"))	// if 'separate' is "PRINT" command
				{
					separate = strtok(NULL, " ");
					arg1 = separate;
					separate = strtok(NULL, " ");
					arg2 = separate;
					separate = strtok(NULL, " ");
					if (!PRINT())
					{
						cout << "======== ERROR ========" << endl << "700" << endl;
						cout << "=======================" << endl;
						continue;
					}
		
				}
				else if (!strcmp(separate, "UPDATE"))	// if 'separate' is "UPDATE" command
				{
					separate = strtok(NULL, " ");
					arg1 = separate;
					separate = strtok(NULL, " ");
					arg2 = separate;
					separate = strtok(NULL, " ");
					if (!UPDATE())
					{
						cout << "======== ERROR ========" << endl << "800" << endl;
						cout << "=======================" << endl;
						continue;
					}
				}
				else if (!strcmp(separate, "SEARCH"))	// if 'separate' is "SEARCH" command
				{
					separate = strtok(NULL, " ");
					arg1 = separate;
					separate = strtok(NULL, " ");
					arg2 = separate;
					separate = strtok(NULL, " ");
					if (!SEARCH())
					{
						cout << "======== ERROR ========" << endl << "600" << endl;
						cout << "=======================" << endl;
						continue;
					}

				}
				else if (!strcmp(separate, "TEST"))		// if 'separate' is "TEST" command
				{
					separate = strtok(NULL, " ");
					arg1 = separate;
					separate = strtok(NULL, " ");
					arg2 = separate;
					separate = strtok(NULL, " ");
					if (!TEST())
					{
						cout << "======== ERROR ========" << endl << "500" << endl;
						cout << "=======================" << endl;
						continue;
					}

				}
				else if (!strcmp(separate, "SAVE"))		// if 'separate' is "SAVE" command
				{
					separate = strtok(NULL, " ");
					arg1 = separate;
					if (!SAVE())
					{
						cout << "======== ERROR ========" << endl << "400" << endl;
						cout << "=======================" << endl;
						continue;
					}
					else
					{
						cout << "======== SAVE ========" << endl << "Success" << endl;
						cout << "=======================" << endl;
						continue;
					}
				}
				else if (!strcmp(separate, "EXIT")) break;		// if 'separate' is "EXIT" command
				else
				{
					cout << "======== ERROR ========" << endl << "Wrong commend" << endl;
					cout << "=======================" << endl;
					continue;
				}
			}
		}

	fin.close();

}

bool Manager::LOAD()
{
	char data[100];
	char *word = NULL;
	char *word_LC = NULL;
	char *mean = NULL;
	int q_cnt = 0;
	int c_cnt = 0;
	int b_cnt = 0;

	ifstream fin;
	fin.open("to_memorize_word.txt");		// Open "to_memorize_word" text file
	if (!fin) { return false; }

	while (!fin.eof())
	{

		fin.getline(data, 100);
		if (data[0] == NULL) { break; }
		word = strtok(data, " ");
		My_cmp(word);
		word_LC = My_cmp(word);			// Change the capital letters to lower case letters and put the word in "word_LC"
		mean = strtok(NULL, " ");	

		node = new WordNode;
		node->SetWord(word);	// Set the word
		node->SetMean(mean);	// Set the meaning of the word
		queue->Push(node);		// Push the node in queue
		q_cnt++;

	}
	fin.close();		// Close "to_memorize_word" text file

	fin.open("memorizing_word.txt");	// Open "memorizing_word" text file
	if (!fin) { return false; }

	while (!fin.eof())		// Until the end of file, set the word and meaning of the word like I did for "to_memorize_word"
	{
		
		fin.getline(data, 100);
		if (data[0] == NULL) { break; }
		word = strtok(data, " ");
		My_cmp(word);
		word_LC = My_cmp(word);
		mean = strtok(NULL, " ");

		node = new WordNode;

		node->SetWord(word);
		node->SetMean(mean);
		bst->Search(word_LC[0])->GetBST()->Insert(node);	// Search where to put the node and insert the node
		b_cnt++;
	}

	fin.close();		// Close "memorizing_word" text file

	fin.open("memorized_word.txt");		// Open "memorized_word" text file
	if (!fin) { return false; }

	while (!fin.eof())		// Set the word and meaning of the word until the end of file like I did for "to_memorize_word" and "memorizing_word" text file
	{

		fin.getline(data, 100);
		if (data[0] == NULL) { break; }
		word = strtok(data, " ");
		mean = strtok(NULL, " ");

		node = new WordNode;
		node->SetWord(word);
		node->SetMean(mean);
		cll->Insert(node);		// Insert the node in circular linked list
		c_cnt++;
	}
	fin.close();		// Close "memorized_word" text file
	if (q_cnt == 0 || c_cnt == 0 || b_cnt == 0) return false;	// If there are no contents in any of files, return false
	return true;
}

bool Manager::ADD()
{

	ifstream fin;
	
		char data[100];
		char * sep;
	

		int count = 0;
		int count_error = 0;
		fin.open("word.txt");
		if (!fin) { return false; }


		while (!fin.eof())
		{
			fin.getline(data, 100);
			WordNode * node = new WordNode;
			
			sep = strtok(data, "\t");		// Use "strtok" function to separate word and meaning and put word in "sep"
			if (sep == NULL) break;
			char* temp = My_cmp(sep);
			if (cll->Search(temp) || queue->Search(temp) || bst->Search(temp[0])->GetBST()->Search(temp)) continue;

			node->SetWord(sep);		// Set the word of the node

			sep = strtok(NULL, "\t");
			node->SetMean(sep);		// Set the meaning of the node
			queue->Push(node);		// Push the node to queue

			count_error++;
		}

		if (count_error == 0)
		{
			return false;
		}
		return true;
	}

bool Manager::MOVE()
{
	int i = 0;
	int num = 0;
	int total = 0;
	while (arg1[i] >= '0'&&arg1[i] <= '9')   // Count how many numbers are in "arg1" array
	{

		num++;
		i++;

	}
	i = num;

	int k = 1;
	int j = 0;
	for (int j = 0; j < num; j++)         // This does the function of "atoi"
	{
		k *= 10;
		total += (arg1[j] - '0')*(k);

	}
	int count = total;
	int count_queue = 0;
	int couunt_BST = 0;

	if (queue->count() < count)
	{
		return false;
	}
	else if (bst->Alpha_bst_count() + count>100)	// If the number of words exceeds 100, return false
	{
		return false;
	}

	for (int i = 0; i < count; i++)		// Move the number of words written in command text file
	{
		WordNode * data = new WordNode;
		data = queue->Pop();
		char * temp = data->GetWord();
		bst->Search(temp[0])->GetBST()->Insert(data);

	}
	return true;
}

bool Manager::SAVE()	// Save the current state of the vocabulary note 
{
	cll->Save();
	queue->Save();
	bst->Save();
	if (!cll->Save() || !queue->Save() || !bst->Save())
		return false;

	return true;
}

bool Manager::TEST()
{
	char* temp = My_cmp(arg1);
	char* temp2;
	int count = 0;
	if (bst->Search(temp[0])->GetBST()->Search(temp) == NULL)      // If the word does not exist
	{
		return false;
	}
	temp2 = bst->Search(temp[0])->GetBST()->Search(temp)->GetMean();	// Put the meaning of the word in "temp2"

	if (strcmp(temp2, arg2))	// Check if the meaning of the word is correct
		return false;
	node = new WordNode;
	node->SetWord(temp);
	node->SetMean(arg2);

	cll->Insert(node);		// Move the word to "MEMORIZED"
	bst->Search(temp[0])->GetBST()->Delete(temp);		// Delete the word node in BST
	cout << "======== TEST ========" << endl << "Pass" << endl;
	cout << "======================" << endl;

	return true;
}

bool Manager::SEARCH()
{
	char* temp = My_cmp(arg1);		// put the word in "temp"
	if (cll->Search(temp))		// If the word is in "MEMORIZED"
	{
		cout << "======== SEARCH ========" << endl;
		cout << cll->Search(temp)->GetWord() << " " << cll->Search(temp)->GetMean() << endl;
		cout << "========================" << endl;
		return true;
	}
	else if (queue->Search(temp))	// If the word is in "TO_MEMORIZE"
	{
		cout << "======== SEARCH ========" << endl;
		cout << queue->Search(temp)->GetWord() << " " << queue->Search(temp)->GetMean() << endl;
		cout << "=======================" << endl;
		return true;
	}
	else if (bst->Search(temp[0])->GetBST()->Search(temp))		// If the word is in "MEMORIZING"
	{
		cout << "======== SEARCH ========" << endl;
		cout << bst->Search(temp[0])->GetBST()->Search(temp)->GetWord() << " "
				<< bst->Search(temp[0])->GetBST()->Search(temp)->GetMean() << endl;
		cout << "=======================" << endl;
		return true;
	}
	return false;
	
}

bool Manager::PRINT()
{
	
	if (!strcmp(arg1, "TO_MEMORIZE"))	// If want to print "TO_MEMORIZE"
	{
		if (!queue->Print()) return false;
		
		return true;
	}
	else if (!strcmp(arg1, "MEMORIZING"))	// If want to print "MEMORIZING"
	{
		if (bst->Alpha_bst_count() == 0) return false;
		if (!bst->Print(arg2)) return false;
		
		return true;
	}
	else if (!strcmp(arg1, "MEMORIZED"))	// If want to print "MEMORIZED"
	{
		if (!cll->Print()) return false;
		return true;
	}

	else return false;
}

bool Manager::UPDATE()
{
	char* temp = My_cmp(arg1);		// put the word in "temp"
	if (cll->Search(temp))		// If the word is in "MEMORIZED"
	{
		cout << "======== UPDATE ========" << endl;
		cout << cll->Search(temp)->GetWord() << " " << cll->Search(temp)->GetMean() << " -> ";
		cll->Search(temp)->SetMean(arg2);		// change the meaning of the word
		cout << cll->Search(temp)->GetMean() << endl;
		cout << "=======================" << endl;
		return true;
	}
	else if (queue->Search(temp))		// If the word is in "TO_MEMORIZE"
	{
		cout << "======== UPDATE ========" << endl;
		cout << queue->Search(temp)->GetWord() << " " << queue->Search(temp)->GetMean() << " -> ";
		queue->Search(temp)->SetMean(arg2);		// change the meaning of the word
		cout << queue->Search(temp)->GetMean() << endl;
		cout << "=======================" << endl;
		return true;
	}
	else if (bst->Search(temp[0])->GetBST()->Search(temp))		// If the word is in "MEMORIZING"
	{
		cout << "======== UPDATE ========" << endl;
		cout << bst->Search(temp[0])->GetBST()->Search(temp)->GetWord() << " "
			<< bst->Search(temp[0])->GetBST()->Search(temp)->GetMean() << " -> ";
		bst->Search(temp[0])->GetBST()->Search(temp)->SetMean(arg2);		// change the meaning of the word
		cout << bst->Search(temp[0])->GetBST()->Search(temp)->GetMean() << endl;
		cout << "=======================" << endl;
		return true;
	}
	return false;


}

char * Manager::My_cmp(char * word)		// Change the capital letters to lower case letters
{
	temp = new char[45];
	strcpy(temp, word);

	for (int i = 0; i<45; i++) {
		if (temp[i] >= 'A' && temp[i] <= 'Z') {
			temp[i] = temp[i] + 32;
		}
	}
	return temp;
}
