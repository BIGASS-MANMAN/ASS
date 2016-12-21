#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
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

	ofstream fout;
	fout.open("log.txt", ios::app); // open log.txt

	bst_cnt = 0; // reset bst_cnt to 0

	if (!fout)
	{
		cout << "ERROR : program can't open the log.txt" << endl << endl;
		fout.close();
		return;
	}

	int cnt, num; // use to copy array

	ifstream fin;
	fin.open(command);

	if (!fin)
	{
		cout << "ERROR : program can't open the command.txt" << endl << endl;
		fin.close();
		return;
	}

	while (!fin.eof())
	{
		cnt = 0; num = 0;

		/* reset 2-array com to NULL */
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				com[i][j] = '\0';
			}
		}

		fin.getline(m_command, 50); // getline from text file
	
		if (m_command[0] == '\0') // no command.
			break;
		else
		{
			/* devide the m_command to three word */
			for (int i = 0; i < 50; i++)
			{
				com[cnt][num++] = m_command[i];
				if (m_command[i] == ' ' || m_command[i]=='\r') // devide point.
				{
					com[cnt][num-1] = NULL; // array's last character is NULL
					num = 0;
					cnt += 1;
				}
				else if (m_command[i] == NULL) // no command.
					break;
			}
		} // end of devide.

		// com[0]=>command com[1]=>Word or Print Type com[2]=>Mean or Print Method

		if (strcmp(com[0], "LOAD") == 0)
		{
			if ( com[1][0] != NULL || LOAD() == false || com[2][0] != NULL)
			{
				cout << "======== ERROR ========" << endl;
				cout << "100" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== ERROR ========" << endl;
				fout << "100" << endl;
				fout << "=======================" << endl << endl;
			}
			else
			{
				cout << "======== LOAD ========" << endl;
				cout << "Success" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== LOAD ========" << endl;
				fout << "Success" << endl;
				fout << "=======================" << endl << endl;
			}
		}
		else if (strcmp(com[0], "ADD") == 0)
		{
			if (ADD() == false || com[1][0] != NULL || com[2][0] != NULL)
			{
				cout << "======== ERROR ========" << endl;
				cout << "200" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== ERROR ========" << endl;
				fout << "200" << endl;
				fout << "=======================" << endl << endl;
			}
			else
			{
				cout << "======== ADD ========" << endl;
				cout << "Success" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== ADD ========" << endl;
				fout << "Success" << endl;
				fout << "=======================" << endl << endl;
			}
		}
		else if (strcmp(com[0], "MOVE") == 0)
		{
			if (MOVE() == false || com[2][0] != NULL)
			{
				cout << "======== ERROR ========" << endl;
				cout << "300" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== ERROR ========" << endl;
				fout << "300" << endl;
				fout << "=======================" << endl << endl;
			}
			else
			{
				cout << "======== MOVE ========" << endl;
				cout << "Success" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== MOVE ========" << endl;
				fout << "Success" << endl;
				fout << "=======================" << endl << endl;
			}
		}
		else if (strcmp(com[0], "SAVE") == 0)
		{
			if (SAVE() == false || com[1][0] !=NULL || com[2][0] != NULL)
			{
				cout << "======== ERROR ========" << endl;
				cout << "400" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== ERROR ========" << endl;
				fout << "400" << endl;
				fout << "=======================" << endl << endl;
			}
			else
			{
				cout << "======== SAVE ========" << endl;
				cout << "Success" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== SAVE ========" << endl;
				fout << "Success" << endl;
				fout << "=======================" << endl << endl;
			}
		}
		else if (strcmp(com[0], "TEST") == 0)
		{
			if (TEST() == false)
			{
				cout << "======== ERROR ========" << endl;
				cout << "500" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== ERROR ========" << endl;
				fout << "500" << endl;
				fout << "=======================" << endl << endl;
			}
			else
			{
				cout << "======== TEST ========" << endl;
				cout << "Pass" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== TEST ========" << endl;
				fout << "Pass" << endl;
				fout << "=======================" << endl << endl;
			}
		}
		else if (strcmp(com[0], "SEARCH") == 0)
		{
			if(com[2][0] != NULL)
			{
				cout << "======== ERROR ========" << endl;
				cout << "600" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== ERROR ========" << endl;
				fout << "600" << endl;
				fout << "=======================" << endl << endl;
			}
			else if (SEARCH() == false)
			{
				cout << "======== ERROR ========" << endl;
				cout << "600" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== ERROR ========" << endl;
				fout << "600" << endl;
				fout << "=======================" << endl << endl;
			}
			else
			{
				cout << "======== SEARCH ========" << endl;
				cout << com[1] << " " << com[2] << endl;
				cout << "=======================" << endl << endl;

				fout << "======== SEARCH ========" << endl;
				fout << com[1] << " " << com[2] << endl;
				fout << "=======================" << endl << endl;
			}
		}
		else if (strcmp(com[0], "PRINT") == 0)
		{
			if (PRINT() == false)
			{
				cout << "======== ERROR ========" << endl;
				cout << "700" << endl;
				cout << "=======================" << endl << endl;
			}
		}
		else if (strcmp(com[0], "UPDATE") == 0)
		{
			if (UPDATE() == false)
			{
				cout << "======== ERROR ========" << endl;
				cout << "800" << endl;
				cout << "=======================" << endl << endl;

				fout << "======== ERROR ========" << endl;
				fout << "800" << endl;
				fout << "=======================" << endl << endl;
			}
			else
			{
				cout << "======== UPDATE ========" << endl;
				cout << com[1] << " " << com[0] << " -> " << com[2] << endl;
				cout << "=======================" << endl << endl;

				fout << "======== UPDATE ========" << endl;
				fout << com[1] << " " << com[0] << " -> " << com[2] << endl;
				fout << "=======================" << endl << endl;
			}
		}
		else if (strcmp(com[0], "EXIT") == 0)
		{
			break; // EXIT THE PROGRAM
		}
		else // ERROR
		{
			cout << "ERROR : not exist that command in WORDBOOK." << endl << endl;
			fout << "ERROR : not exist that command in WORDBOOK." << endl << endl;
		}
	}

	fout << "PROGRAM EXIT" << endl << endl;
	fout.close();
	fin.close();
}

bool Manager::LOAD()
{
	ifstream fin11;
	ifstream fin22;
	ifstream fin33;

	char exep[50] = {'\0',}; // reset to NULL

	fin11.open("to_memorize_word.txt");
	fin11.getline(exep, 50);
	if (exep[0] == NULL) { // no word in txt
		fin11.close();
		return false;
	}
	fin11.close();

	fin22.open("memorizing_word.txt");
	fin22.getline(exep, 50);
	if (exep[0] == NULL) { // no word in txt
		fin22.close();
		return false;
	}
	fin22.close();

	fin33.open("memorized_word.txt");
	fin33.getline(exep, 50);
	if (exep[0] == NULL) { // no word in txt
		fin33.close();
		return false;
	}
	fin33.close();

	ofstream fout;
	fout.open("log.txt", ios::app); // open log.txt

	char word[32];
	char mean[32];

	/* Load Queue */
	ifstream fin1;
	fin1.open("to_memorize_word.txt");

	if (!fin1)
	{
		cout << "ERROR : program can't open the to_memorize_word.txt" << endl << endl;
		fout << "ERROR : program can't open the to_memorize_word.txt" << endl << endl;
		return false;
	}
	while (!fin1.eof())
	{
		fin1.getline(word, 32,',');
		fin1.getline(mean, 32);
		if (word[0] == NULL)
			break;

		// save load word's information to pNew node.
		WordNode * pNew = new WordNode;
		pNew->SetWord(word);
		pNew->SetMean(mean);

		queue->Push(pNew); // push pNew to queue
	}
	fin1.close();

	/* Load BST */
	ifstream fin2;
	fin2.open("memorizing_word.txt");

	if (!fin2)
	{
		cout << "ERROR : program can't open the memorizing_word.txt" << endl << endl;
		fout << "ERROR : program can't open the memorizing_word.txt" << endl << endl;
		return false;
	}

	while (!fin2.eof())
	{
		fin2.getline(word, 32, ',');
		fin2.getline(mean, 32);

		if (word[0] == NULL)
			break;

		if (bst_cnt == MAX_WORD)
			return false;

		WordNode * pNew = new WordNode;
		pNew->SetWord(word);
		pNew->SetMean(mean);

		bst->Search(word[0])->GetBST()->Insert(pNew);
		bst_cnt += 1;
	}
	fin2.close();

	/* Load CircularList */
	ifstream fin3;
	fin3.open("memorized_word.txt");

	if (!fin3)
	{
		cout << "ERROR : program can't open the memorized_word.txt" << endl << endl;
		fout << "ERROR : program can't open the memorized_word.txt" << endl << endl;
		return false;
	}

	while (!fin3.eof())
	{
		fin3.getline(word, 32, ',');
		fin3.getline(mean, 32);

		if (word[0] == NULL)
			break;

		WordNode * pNew = new WordNode;
		pNew->SetWord(word);
		pNew->SetMean(mean);

		cll->Insert(pNew);
	}
	fin3.close();

	return true;
}

bool Manager::ADD()
{
	ofstream fout;
	fout.open("log.txt", ios::app);

	char word[32];
	char mean[32];

	ifstream fin;
	fin.open("word.txt");

	if (!fin)
	{
		cout << "ERROR : program can't open the word.txt" << endl << endl;
		fout << "ERROR : program can't open the word.txt" << endl << endl;
		fin.close();
		return false;
	}

	while (!fin.eof())
	{
		fin.getline(word, 32, '	');
		fin.getline(mean, 32);

		WordNode * pNew = new WordNode;
		pNew->SetWord(word);
		pNew->SetMean(mean);

		queue->Push(pNew);
	}
	fin.close();

	if (queue->pHead == NULL)
		return false;

	return true;
}

bool Manager::SAVE()
{
	if (queue->pHead == NULL)
		return false;
	if (bst_cnt == 0)
		return false;
	if (cll->pHead == NULL)
		return false;

	queue->Save();
	bst->Save();
	cll->Save();

	return true;
}

bool Manager::TEST()
{
	WordNode * pWord;
	AlphabetNode * pAlpha;
	pWord = bst->Search(com[1][0])->GetBST()->Search(com[1]);
	pAlpha = bst->Search(com[1][0]);
	
	if (pWord == NULL) // if word is not exist
		return false;

	if ((strcasecmp(pWord->GetWord(), com[1]) == 0) && (strcasecmp(pWord->GetMean(), com[2]) == 0)) // if correct word and mean
	{
		pAlpha->GetBST()->Delete(pWord->GetWord()); // Delete in BST

		// reset pWord's BST node pointer
		pWord->SetLeft(NULL);
		pWord->SetRight(NULL);

		bst_cnt -= 1;
		cll->Insert(pWord); // Insert word to CircularLinkedList
		return true;
	}
	else // fail to test
		return false;
}

bool Manager::SEARCH()
{
	WordNode * pWord;
	AlphabetNode * pAlpha;
	pAlpha = bst->Search(com[1][0]); // pAlpha = first alphabet of Word that to search

	pWord = queue->Search(com[1]); // Search
	if (pWord == NULL) // fail to search
	{
		pWord = pAlpha->GetBST()->Search(com[1]); // Search
		if ( pWord == NULL) // fail to search
		{
			pWord = cll->Search(com[1]); // Search
			if( pWord == NULL ) // fail to search
			{
				return false;
			}
		}
	}

	// save information of word to com[1], com[2]
	for (int i = 0; i < 20; i++)
	{
		com[1][i] = pWord->GetWord()[i];
		com[2][i] = pWord->GetMean()[i];
	}

	return true;
}

bool Manager::MOVE()
{
	if (queue->pHead == NULL) // no node in Queue,
		return false;

	int num;
	char alpha;
	num = atoi(com[1]);

	for (int i = 0; i < num; i++)
	{
		WordNode * pMove; // Node that to move
		pMove = queue->Pop();
		alpha = *pMove->GetWord(); // Move word's first alphabet

		if (pMove == NULL || bst_cnt == MAX_WORD) // no word in Queue or 100 words in BST
			return false;

		bst->Search(alpha)->GetBST()->Insert(pMove); // pMove insert to BST
		bst_cnt += 1;
	}

	return true;
}

bool Manager::UPDATE()
{
	/* same with Search */
	WordNode * pWord;
	AlphabetNode * pAlpha;
	pAlpha = bst->Search(com[1][0]);

	pWord = queue->Search(com[1]);
	if (pWord == NULL)
	{
		pWord = pAlpha->GetBST()->Search(com[1]);
		if (pWord == NULL)
		{
			pWord = cll->Search(com[1]);
			if (pWord == NULL)
			{
				return false;
			}
		}
	} // pWord = searched word

	for (int i = 0; i < 20; i++)
	{
		// copy existing mean.
		com[0][i] = pWord->GetMean()[i];
		com[1][i] = pWord->GetWord()[i];
	}

	pWord->SetMean(com[2]); // set new mean

	return true;
}

bool Manager::PRINT()
{
	/* if Print QUEUE */
	if (strcmp(com[1], "TO_MEMORIZE") == 0) {
		if (queue->Print() == false)
			return false;
		else
			return true;
	}
	/* if Print BST */
	else if (strcmp(com[1], "MEMORIZING") == 0) {
		if (bst_cnt > 0) {
			ofstream foutb;
			foutb.open("log.txt", ios::app);
			cout << "======== PRINT ========" << endl;
			foutb << "======== PRINT ========" << endl;
			bst->Print(com[2]); // Print BST
			cout << "=======================" << endl << endl;
			foutb << "=======================" << endl << endl;
			foutb.close();
			return true;
		}
		else if (bst_cnt == 0)
			return false;
		else
			return false;

	}
	/* if Print CLL */
	else if (strcmp(com[1], "MEMORIZED") == 0) {
		if (cll->Print() == false)
			return false;
		else
			return true;
	}
	else
		return false;
}
