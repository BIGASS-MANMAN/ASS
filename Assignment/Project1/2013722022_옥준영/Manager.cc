#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
#include <string.h>
#include <iostream>
#include <cstring>

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

void Manager::run(const char * command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	bst->alphabet_insert();		// alphabet node insert in AlphabetBST
	ifstream fin;
	char buf[100];		// line array of command.txt file
	char list[100];		// command array
	
	int i = 0, j = 0;	// location variable
	int number = 0;		// command number

	fin.open(command);	// open command file

	while (!fin.eof())		// until end of file
	{
		// initialize variables
		memset(buf, 0, 100);
		memset(list, 0, 100);
		arg1 = '\0', arg2 = '\0';	
		i = 0, j = 0,number=0;
		fin.getline(buf, sizeof(buf));		// read command.txt file line by line
		while (buf[i] && buf[i]!=' ')		// copy command to list array
		{
			if (buf[i] >= 'A' && buf[i] <= 'Z')
				list[j++] = buf[i++];
			else
				i++;
		}
		
		if (strcmp(list, "LOAD") == 0)
		{
			if (LOAD() == 1)		// LOAD function success
				Success("LOAD");		// Print success message
			else		// LOAD function failure
				Error(100);		// Print error message
		}
		else if (strcmp(list, "ADD") == 0)
		{
			if (ADD() == 1)		// ADD function success
				Success("ADD");		// Print success message
			else		// ADD function failure
				Error(200);		// Print error message
		}
		else if (strcmp(list, "MOVE") == 0)
		{
			memset(list, 0, 100);
			j = 0;
			while (buf[i] == ' ')
				i++;
			while (buf[i] != 0)		// copy number to list array
				list[j++] = buf[i++];

			i = 0;
			while (list[i])		// convert array to integer type
			{
				if (list[i] >= '0' && list[i] <= '9')
					number = (number * 10) + list[i++] - '0';
			}

			if (number > 0 && number <= MAX_WORD)		// 0 < number <= 100
			{	
				int error = 0;
				for (int n = 0; n < number; n++)
				{
					if (MOVE() != 0)		// MOVE function success
						bst->WordCnt++;		// increase number of 'MEMORIZING WORD'
					else
						error++;
				}
				if(error==0)
					Success("MOVE");		// Print success message
				else
					Error(300);		// Print error message
			}
			else // number <= 0 or number > 100
				Error(300);		// Print error message
		}
		else if (strcmp(list, "SAVE") == 0)
		{
			if(SAVE() == 1)		// SAVE function success
				Success("SAVE");		// Print success message
			else         // SAVE function failure
				Error(400);		// Print error message
		}

		else if (strcmp(list, "TEST") == 0)
		{
			char list2[50];		// mean array for test
			memset(list, 0, 100);
			memset(list2, 0, 50);
			j = 0;
			while (buf[i] == ' ')
				i++;
			while (buf[i] != 0 && buf[i] != ' ' && buf[i] != '\t')	// copy word to list array
			{
				if (buf[i] >= 'A' && buf[i] <= 'Z')		// convert capital letter to small letter
					list[j++] = buf[i++] + ('a' - 'A');
				else
					list[j++] = buf[i++];
			}

			arg1 = list;		// save word for test
			while (buf[i] == ' ' || buf[i] == '\t')
				i++;
			strcpy(list2, &buf[i]);		// copy mean to list2 array
			arg2 = list2;		// save mean for test

			if (TEST() == 1)		// TEST function sucess
				Success("TEST");		// Print success message
			else              // TEST function failure
				Error(500);		// Print error message
		}

		else if (strcmp(list, "SEARCH") == 0)
		{
			memset(list, 0, 100);
			j = 0;
			while (buf[i] == ' ')
				i++;
			while (buf[i] != 0 && buf[i] != ' ' && buf[i] != '\t')	// copy word to list array
			{
				if (buf[i] >= 'A' && buf[i] <= 'Z')		// convert capital letter to small letter
					list[j++] = buf[i++] + ('a' - 'A');
				else
					list[j++] = buf[i++];
			}
			arg1 = list;		// save word for search
			if (SEARCH() == 0)		// SEARCH function failure
				Error(600);		// Print error message
		}

		else if (strcmp(list, "PRINT") == 0)
		{
			char list2[30];		// type of order array for print
			memset(list, 0, 100);
			memset(list2, 0, 30);
			j = 0;
			while (buf[i] == ' ')
				i++;
			while (buf[i] != 0 && buf[i] != ' ')		// copy type of list to list array
			{
				if (buf[i] >= 'A' && buf[i] <= 'Z')		
					list[j++] = buf[i++];
				else if (buf[i] == '_')
					list[j++] = buf[i++];
				else
					i++;
			}
			arg1 = list;		// save type of list for print

			if (strcmp(list, "MEMORIZING") == 0)	// MEMORIZING CASE
			{
				j = 0;
				while (buf[i] == ' ')
					i++;
				while (buf[i] != 0)		// copy type of order to list2 array
					list2[j++] = buf[i++];
				arg2 = list2;		// save type of order for print
			}
	
			if (PRINT() == 0)		// PRINT function failure
				Error(700);		// Print error message
		}
		else if (strcmp(list, "UPDATE") == 0)
		{
			char list2[50];		// mean array for update
			memset(list, 0, 100);
			memset(list2, 0, 50);
			j = 0;
			while (buf[i] == ' ')
				i++;
			while (buf[i] != 0 && buf[i] != ' ')	// copy word to list array
			{
				if (buf[i] >= 'A' && buf[i] <= 'Z')		// convert capital letter to small letter
					list[j++] = buf[i++] + ('a' - 'A');
				else
					list[j++] = buf[i++];
			}

			arg1 = list;		// save word for update
			
			while (buf[i] == ' ')
				i++;
			strcpy(list2, &buf[i]);		// copy mean to list2 array
			arg2 = list2;		// save mean for update

			if (UPDATE() == 0)		// UPDATE function failure
				Error(800);		// Print error message
		}
		else if (strcmp(list, "EXIT") == 0)		// Program EXIT
			break;
	}
	fin.close();
}


bool Manager::LOAD()
{
	char word_line[100];
	ifstream fload;
	int error_cnt = 0;		// error count variable
	fload.open("to_memorize_word.txt");
	if (fload.is_open() == 1)		// File open success
	{
		while (!fload.eof())
		{	// initialize variables
			char word[50], mean[50];
			int n1 = 0, n2 = 0;

			memset(word_line, 0, sizeof(word_line));	// line array reset
			memset(word, 0, sizeof(word));	// word array reset
			memset(mean, 0, sizeof(mean));	// mean array reset

			fload.getline(word_line, sizeof(word_line),'\t');		// read word.txt file line by line

			if (word_line[0] != 0 && word_line[0] != ' ')
			{
				while (word_line[n1] != '\0')		// convert capital letter to small letter
				{
					if (word_line[n1] >= 'A'&&word_line[n1] <= 'Z')
						word[n2++] = word_line[n1++] + ('a' - 'A');
					else if (word_line[n1] >= 'a' && word_line[n1] <= 'z')
						word[n2++] = word_line[n1++];
					else
						n1++;
				}

				if (queue->Search(word) == 0)		// if word does not exist in 'momorized' list
				{
					char *d_word = new char[100];	// set word array to dynamic allocation 
					char *d_mean = new char[100];	// set mean array to dynamic allocation

					memset(d_word, 0, 100);	// word array reset
					memset(d_mean, 0, 100);	// mean array reset
					strcpy(d_word, word);		// copy word to d_word array

					memset(word_line, 0, sizeof(word_line));	// line array reset

					fload.getline(word_line, sizeof(word_line), '\n');
					strcpy(d_mean, word_line);		// copy mean to d_mean array

					WordNode *new_word = new WordNode;		// create new WordNode
					new_word->SetWord(d_word);		// set word
					new_word->SetMean(d_mean);		// set mean
					queue->Push(new_word);		//  insert new node to CircularLinkedList
				}
				else
				{
					fload.getline(word_line, sizeof(word_line), '\n');
					error_cnt++;
				}
			}
		}
		fload.close();
	}
	else     // File open failure
		error_cnt++;
	

	fload.open("memorizing_word.txt");
	if (fload.is_open() == 1)		// File open success
	{
		while (!fload.eof())
		{	// initialize variables
			char word[50], mean[50];
			int n1 = 0, n2 = 0;

			memset(word_line, 0, sizeof(word_line));	// line array reset
			memset(word, 0, sizeof(word));	// word array reset
			memset(mean, 0, sizeof(mean));	// mean array reset

			fload.getline(word_line, sizeof(word_line), '\t');		// read word.txt file line by line

			if (word_line[0] != 0 && word_line[0] != ' ')
			{
				while (word_line[n1] != '\0')		// convert capital letter to small letter
				{
					if (word_line[n1] >= 'A'&&word_line[n1] <= 'Z')
						word[n2++] = word_line[n1++] + ('a' - 'A');
					else if (word_line[n1] >= 'a' && word_line[n1] <= 'z')
						word[n2++] = word_line[n1++];
					else
						n1++;
				}
				// if word does not exist in 'momorized' list and the number of word below 100
				if (cll->Search(word) == 0 && bst->WordCnt <= MAX_WORD)		
				{
					char *d_word = new char[100];	// set word array to dynamic allocation 
					char *d_mean = new char[100];	// set mean array to dynamic allocation

					memset(d_word, 0, 100);	// word array reset
					memset(d_mean, 0, 100);	// mean array reset
					strcpy(d_word, word);		// copy word to d_word array

					memset(word_line, 0, sizeof(word_line));	// line array reset

					fload.getline(word_line, sizeof(word_line), '\n');
					strcpy(d_mean, word_line);		// copy mean to d_mean array

					WordNode *new_word = new WordNode;		// create new WordNode
					new_word->SetWord(d_word);		// set word
					new_word->SetMean(d_mean);		// set mean
					//  insert new node to CircularLinkedList
					bst->Search(d_word[0] - ('a' - 'A'))->GetBST()->Insert(new_word);
					bst->WordCnt++;		// increase number of memorizng word
				}
				else
				{
					fload.getline(word_line, sizeof(word_line), '\n');
					error_cnt++;
				}
			}
		}
		fload.close();
	}
	else     // File open failure
		error_cnt++;
	

	fload.open("memorized_word.txt");
	if (fload.is_open() == 1)		// File open success
	{
		while (!fload.eof())
		{	// initialize variables
			char word[50], mean[50];
			int n1 = 0, n2 = 0;

			memset(word_line, 0, sizeof(word_line));	// line array reset
			memset(word, 0, sizeof(word));	// word array reset
			memset(mean, 0, sizeof(mean));	// mean array reset

			fload.getline(word_line, sizeof(word_line), '\t');		// read word.txt file line by line

			if (word_line[0] != 0 && word_line[0] != ' ')
			{
				while (word_line[n1] != '\0')		// convert capital letter to small letter
				{
					if (word_line[n1] >= 'A'&&word_line[n1] <= 'Z')
						word[n2++] = word_line[n1++] + ('a' - 'A');
					else if (word_line[n1] >= 'a' && word_line[n1] <= 'z')
						word[n2++] = word_line[n1++];
					else
						n1++;
				}

				if (cll->Search(word) == 0)		// if word does not exist in 'momorized' list
				{
					char *d_word = new char[100];	// set word array to dynamic allocation 
					char *d_mean = new char[100];	// set mean array to dynamic allocation

					memset(d_word, 0, 100);	// word array reset
					memset(d_mean, 0, 100);	// mean array reset
					strcpy(d_word, word);		// copy word to d_word array

					memset(word_line, 0, sizeof(word_line));	// line array reset

					fload.getline(word_line, sizeof(word_line), '\n');
					strcpy(d_mean, word_line);		// copy mean to d_mean array

					WordNode *new_word = new WordNode;		// create new WordNode
					new_word->SetWord(d_word);		// set word
					new_word->SetMean(d_mean);		// set mean
					cll->Insert(new_word);		//  insert new node to CircularLinkedList
				}
				else
				{
					fload.getline(word_line, sizeof(word_line), '\n');
					error_cnt++;
				}
			}
		}
		fload.close();
	}
	else     // File open failure
		error_cnt++;
	
	if (error_cnt > 0)		// LOAD failure
		return 0;
	else           // LOAD success
		return 1;

}


bool Manager::ADD()
{
	char word_line[100];
	int check = 0;		// check added word
	ifstream fadd;
	fadd.open("word.txt");
	if (fadd.is_open() == 1)
	{
		while (!fadd.eof())
		{	// initialize variables
			char word[50], mean[50];
			int n1 = 0, n2 = 0;

			memset(word_line, 0, sizeof(word_line));	// line array reset
			memset(word, 0, sizeof(word));	// word array reset
			memset(mean, 0, sizeof(mean));	// mean array reset

			fadd.getline(word_line, sizeof(word_line), '\t');		// read word.txt file
			
			if (word_line[0] != '\0' && word_line[0] != ' ')
			{
				while (word_line[n1] != '\0')		// convert capital letter to small letter
				{
					if (word_line[n1] >= 'A'&&word_line[n1] <= 'Z')
						word[n2++] = word_line[n1++] + ('a' - 'A');
					else if (word_line[n1] >= 'a' && word_line[n1] <= 'z')
						word[n2++] = word_line[n1++];
					else
						n1++;
				}
				if (word[0] == '\0' || queue->Search(word) != 0)	// no word or already word exist
					continue;

				char *d_word = new char[100];	// set word array to dynamic allocation 
				char *d_mean = new char[100];	// set mean array to dynamic allocation
				memset(d_word, 0, 100);	// word array reset
				memset(d_mean, 0, 100);	// mean array reset

				strcpy(d_word, word);

				memset(word_line, 0, sizeof(word_line));	// line array reset

				fadd.getline(word_line, sizeof(word_line), '\n');
				strcpy(d_mean, word_line);
				WordNode *new_word = new WordNode;		// create new WordNode
				new_word->SetWord(d_word);		// set word
				new_word->SetMean(d_mean);		// set mean
				queue->Push(new_word);		//  insert new node to CircularLinkedList
				check++;		// incease added word
			}
		}
		fadd.close();
		if (check == 0)		// No added word
			return 0;
		else     // ADD success
			return 1;
	}
	else     // File open failure
		return 0;
	
}


bool Manager::MOVE()
{
	if (bst->WordCnt == MAX_WORD)		// if number of word in bst class equal 100
		return 0;

	WordNode *temp = queue->Pop();		// pop word in 'to memorize' list
	char convert_word = 0; 
	if (temp == '\0')		// no data in 'to memorize' list
		return 0;
	else
	{
		convert_word = temp->GetWord()[0] - ('a' - 'A');		// convert small letter to capital letter
		bst->Search(convert_word)->GetBST()->Insert(temp);		// search alphabet and insert word
		return 1;
	}
}


bool Manager::SAVE()
{
	int error_cnt = 0;		// count number of failure
	if (queue->Save() == 0)		
		error_cnt++;
	if (bst->Save() == 0)
		error_cnt++;
	if (cll->Save() == 0)
		error_cnt++;

	if (error_cnt > 0)		// save failure
		return 0;
	else    // save success
		return 1;
}


bool Manager::TEST()
{
	char s_alphabet = arg1[0] - ('a' - 'A');	// s_alphabet is converted first letter
	WordNode* temp = bst->Search(s_alphabet)->GetBST()->Search(arg1);
	if (temp != 0)
	{
		if (strcmp(temp->GetMean(), arg2) == 0)		// check mean of word
		{
			bst->WordCnt--;		// decrease memorizing word
			temp = bst->Search(s_alphabet)->GetBST()->Delete(arg1);
			WordNode *new_word = new WordNode;		// create new WordNode
			new_word->SetWord(temp->GetWord());		// set word
			new_word->SetMean(temp->GetMean());		// set mean
			cll->Insert(new_word);			// Insert word to 'memorized' list
			delete temp;		// deallocate bst node
			return 1;
		}
		else
			return 0;		// incorrect mean of word
	}
	return 0;		// not found test word
}


bool Manager::SEARCH()
{
	WordNode* temp;
	temp = queue->Search(arg1);
	if (temp != 0)
	{	// print search message to "log.txt" file and display
		ofstream log;
		log.open("log.txt", ios::app);		// add message to end of "log.txt" file
		log << "======== SEARCH ========" << endl;
		cout << "======== SEARCH ========" << endl;
		log << temp->GetWord() << " " << temp->GetMean() << endl;
		cout << temp->GetWord() << " " << temp->GetMean() << endl;
		log << "=======================" << endl << endl;
		cout << "=======================" << endl << endl;
		log.close();
		return 1;
	}
	char s_alphabet = arg1[0] - ('a' - 'A');
	temp = bst->Search(s_alphabet)->GetBST()->Search(arg1);
	if (temp != 0)
	{	// print search message to "log.txt" file and display
		ofstream log;
		log.open("log.txt", ios::app);		// add message to end of "log.txt" file
		log << "======== SEARCH ========" << endl;
		cout << "======== SEARCH ========" << endl;
		log << temp->GetWord() << " " << temp->GetMean() << endl;
		cout << temp->GetWord() << " " << temp->GetMean() << endl;
		log << "=======================" << endl << endl;
		cout << "=======================" << endl << endl;
		log.close();
		return 1;
	}
	temp = cll->Search(arg1);
	if (temp != 0)
	{	// print search message to "log.txt" file and display
		ofstream log;
		log.open("log.txt", ios::app);		// add message to end of "log.txt" file
		log << "======== SEARCH ========" << endl;
		cout << "======== SEARCH ========" << endl;
		log << temp->GetWord() << " " << temp->GetMean() << endl;
		cout << temp->GetWord() << " " << temp->GetMean() << endl;
		log << "=======================" << endl << endl;
		cout << "=======================" << endl << endl;
		log.close();
		return 1;
	}
	return 0;		//  SEARCH failure
}


bool Manager::PRINT()
{
	if (strcmp(arg1, "TO_MEMORIZE")==0)
	{
		if (queue->Print() == 1)		// Print success
			return 1;
		else        // Print failure
			return 0;
	}
	if (strcmp(arg1, "MEMORIZING") == 0)
	{
		if (bst->Print(arg2) == 1)		// Print success
			return 1;
		else        // Print failure
			return 0;
	}
	if (strcmp(arg1, "MEMORIZED") == 0)
	{
		if (cll->Print() == 1)		// Print success
			return 1;
		else        // Print failure
			return 0;
	}
	return 0;		// Incorrect order
}


bool Manager::UPDATE()
{
	WordNode *temp=0;
	temp = queue->Search(arg1);
	int n = 0;
	if (temp != 0)
	{	// print update message to "log.txt" file and display
		ofstream log;
		log.open("log.txt", ios::app);		// add message to end of "log.txt" file
		log << "======== UPDATE ========" << endl;		
		cout << "======== UPDATE ========" << endl;
		log << temp->GetWord() << " " << temp->GetMean() << " -> " << arg2 << endl;
		cout << temp->GetWord() << " " << temp->GetMean() << " -> " << arg2 << endl;
		log << "=========================" << endl << endl;
		cout << "=========================" << endl << endl;
		log.close();

		char *d_mean = new char[50];
		memset(d_mean, 0, 50);
		strcpy(d_mean, arg2);		// copy mean to d_mean array
		delete[] temp->GetMean();	// deallocate mean of temp node
		temp->SetMean(d_mean);		// Set updated mean
		return 1;
	}

	char s_alphabet = arg1[0] - ('a' - 'A');	// s_alphabet is converted first letter
	temp = bst->Search(s_alphabet)->GetBST()->Search(arg1);
	if (temp != 0)
	{	// print update message to "log.txt" file and display
		ofstream log;
		log.open("log.txt", ios::app);		// add message to end of "log.txt" file
		log << "======== UPDATE ========" << endl;
		cout << "======== UPDATE ========" << endl;
		log << temp->GetWord() << " " << temp->GetMean() << " -> " << arg2 << endl;
		cout << temp->GetWord() << " " << temp->GetMean() << " -> " << arg2 << endl;
		log << "=========================" << endl << endl;
		cout << "=========================" << endl << endl;
		log.close();

		char *d_mean = new char[50];
		memset(d_mean, 0, 50);
		strcpy(d_mean, arg2);		// copy mean to d_mean array
		delete[] temp->GetMean();	// deallocate mean of temp node
		temp->SetMean(d_mean);		// Set updated mean
		return 1;
	}

	temp = cll->Search(arg1);
	if (temp != 0)
	{	// print update message to "log.txt" file and display
		ofstream log;
		log.open("log.txt", ios::app);		// add message to end of "log.txt" file
		log << "======== UPDATE ========" << endl;
		cout << "======== UPDATE ========" << endl;
		log << temp->GetWord() << " " << temp->GetMean() << " -> " << arg2 << endl;
		cout << temp->GetWord() << " " << temp->GetMean() << " -> " << arg2 << endl;
		log << "=========================" << endl << endl;
		cout << "=========================" << endl << endl;
		log.close();

		char *d_mean = new char[50];
		memset(d_mean, 0, 50);
		strcpy(d_mean, arg2);		// copy mean to d_mean array
		delete[] temp->GetMean();	// deallocate mean of temp node
		temp->SetMean(d_mean);		// Set updated mean
		return 1;
	}
	return 0;		// UPDATE failure
}


void Manager::Error(const int number)
{	// print error message to "log.txt" file and display
	ofstream log;
	log.open("log.txt", ios::app);		// add message to end of "log.txt" file
	log << "======== " << "ERROR" << " ========" << endl;		
	cout << "======== " << "ERROR" << " ========" << endl;		
	log << number << endl;		
	cout << number << endl;		
	log << "======================" << endl << endl;
	cout << "======================" << endl << endl;
	log.close();
}

void Manager::Success(const char *name)
{	// print success message to "log.txt" file and display
	ofstream log;
	log.open("log.txt", ios::app);		// add message to end of "log.txt" file
	log << "======== " << name << " ========" << endl;		
	cout << "======== " << name << " ========" << endl;		
	if (strcmp(name, "TEST") == 0)		// case of TEST
	{
		log << "Pass" << endl;		
		cout << "Pass" << endl;		
	}
	else
	{
		log << "Success" << endl;		
		cout << "Success" << endl;		
	}
	log << "======================" << endl << endl;
	cout << "======================" << endl << endl;
	log.close();
}

