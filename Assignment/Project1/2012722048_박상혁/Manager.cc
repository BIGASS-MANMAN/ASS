#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <iostream>

using namespace std;

Manager::Manager()
{
	/* Each Data structure */
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

	ifstream fin(command);			// Open the command.txt
	ofstream fout("log.txt", ios::app);	// Open the log.txt

	if (!fin)		// if cannot open the log.txt
		return;
	
	/* Initializing Alphabet BST */
	char ch[26] = { 'P','H','X','D','L','T','Z','B','F','J','N','R','V','Y','A','C','E','G','I','K','M','O','Q','S','U','W' };
	for (int i = 0; i < 26; i++)
	{
		AlphabetNode * pNew = new AlphabetNode;
		pNew->SetAlphabet(ch[i]);
		bst->Insert(pNew);
	}

	/* line: command line   cmd: line's first token   param1~3: line's second ~ 4th token */
	char line[64] = {}, cmd[32] = {}, param1[32] = {}, param2[32] = {}, param3[32] = {};
	int num = 0;		// MOVE command's parameter
	int i, j, k, l = 0;

	while (!fin.eof())	// Until end of file
	{
		fin.getline(line, sizeof(line), '\n');	// input command line
		
		/* Tokenize the command line */
		for (i = 0; line[i] != '\0'; i++)
		{
			if (line[i] == ' ')
			{
				cmd[i] = '\0';
				i++;
				break;
			}
			else
				cmd[i] = line[i];
		}
		cmd[i] = '\0';

		for (j = 0; line[i] != '\0'; i++, j++)
		{
			if (line[i] == ' ')
			{
				param1[j] = '\0';
				i++;
				break;
			}
			else
				param1[j] = line[i];
		}
		param1[j] = '\0';

		for (k = 0; line[i] != '\0'; i++, k++)
		{
			if (line[i] == ' ')
			{
				param2[k] = '\0';
				i++;
				break;
			}
			else
				param2[k] = line[i];
		}
		param2[k] = '\0';

		for (l = 0; line[i] != '\0'; i++, l++)
		{
			if (line[i] == ' ')
			{
				param3[l] = '\0';
				i++;
				break;
			}
			else
				param3[l] = line[i];
		}
		param3[l] = '\0';
		/* Tokenize complete */


		if (!strcmp(cmd, "LOAD"))		// If command is LOAD
		{
			if (param1[0] != '\0') {	// many parameter
				fout << "======== ERROR ========" << endl << "100" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "100" << endl << "=======================" << endl << endl;
			}
			else if (LOAD() == false) {	// LOAD failure
				fout << "======== ERROR ========" << endl << "100" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "100" << endl << "=======================" << endl << endl;
			}
			else {				// LOAD Success
				fout << "======== LOAD ========" << endl << "Success" << endl << "======================" << endl << endl;
				cout << "======== LOAD ========" << endl << "Success" << endl << "======================" << endl << endl;
			}
		}
		else if (!strcmp(cmd, "ADD"))		// If command is ADD
		{
			if (param1[0] != '\0') {	// many parameter
				fout << "======== ERROR ========" << endl << "200" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "200" << endl << "=======================" << endl << endl;
			}
			else if (ADD() == false) {	// ADD failure
				fout << "======== ERROR ========" << endl << "200" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "200" << endl << "=======================" << endl << endl;
			}
			else {				// ADD Success
				fout << "======== ADD ========" << endl << "Success" << endl << "=====================" << endl << endl;
				cout << "======== ADD ========" << endl << "Success" << endl << "=====================" << endl << endl;
			}
		}
		else if (!strcmp(cmd, "MOVE"))		// If command is MOVE
		{
			num = atoi(param1);		// num: param1's integer form
			if (param2[0] != '\0' || param1[0] == '\0') {	// many/less parameter
				fout << "======== ERROR ========" << endl << "300" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "300" << endl << "=======================" << endl << endl;
			}
			else if (MOVE(num) == false) {			// MOVE failure
				fout << "======== ERROR ========" << endl << "300" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "300" << endl << "=======================" << endl << endl;
			}
			else {						// MOVE Success
				fout << "======== MOVE ========" << endl << "Success" << endl << "======================" << endl << endl;
				cout << "======== MOVE ========" << endl << "Success" << endl << "======================" << endl << endl;
			}
		}
		else if (!strcmp(cmd, "SAVE"))		// If command is SAVE
		{
			if (param1[0] != '\0') {	// many parameter
				fout << "======== ERROR ========" << endl << "400" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "400" << endl << "=======================" << endl << endl;
			}
			else if (SAVE() == false) {	// SAVE failure
				fout << "======== ERROR ========" << endl << "400" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "400" << endl << "=======================" << endl << endl;
			}
			else {				// SAVE Success
				fout << "======== SAVE ========" << endl << "Success" << endl << "======================" << endl << endl;
				cout << "======== SAVE ========" << endl << "Success" << endl << "======================" << endl << endl;
			}
		}
		else if (!strcmp(cmd, "TEST"))		// If command is TEST
		{
			if (param3[0] != '\0') {	// many parameter
				fout << "======== ERROR ========" << endl << "500" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "500" << endl << "=======================" << endl << endl;
			}
			else if (param1[0] == '\0' || param2[0] == '\0') {	// less parameter
				fout << "======== ERROR ========" << endl << "500" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "500" << endl << "=======================" << endl << endl;
			}
			else if (TEST(param1, param2) == false) {		// TEST failure
				fout << "======== ERROR ========" << endl << "500" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "500" << endl << "=======================" << endl << endl;
			}
			else {				// TEST Success
				fout << "======== TEST ========" << endl << "Pass" << endl << "======================" << endl << endl;
				cout << "======== TEST ========" << endl << "Pass" << endl << "======================" << endl << endl;
			}
		}
		else if (!strcmp(cmd, "SEARCH"))	// If command is SEARCH
		{
			if (param1[0] == '\0' || param2[0] != '\0') {	// many/less parameter
				fout << "======== ERROR ========" << endl << "600" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "600" << endl << "=======================" << endl << endl;
			}
			else if (SEARCH(param1) == false) {		// SEARCH failure
				fout << "======== ERROR ========" << endl << "600" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "600" << endl << "=======================" << endl << endl;
			}
		}
		else if (!strcmp(cmd, "PRINT"))		// If command is PRINT
		{
			if (param1[0] == '\0') {	// less parameter
				fout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
			}
			else if (!strcmp(param1, "TO_MEMORIZE") && param2[0] != '\0') {	// TO_MEMORIZE + many parameter
				fout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
			}
			else if (!strcmp(param1, "MEMORIZING") && param2[0] == '\0') {	// MEMORIZING + less parameter
				fout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
			}
			else if (!strcmp(param1, "MEMORIZING") && param3[0] != '\0') {	// MEMORIZING + many parameter
				fout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
			}
			else if (!strcmp(param1, "MEMORIZED") && param2[0] != '\0') {	// MEMORIZED + many parameter
				fout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
			}
			else if (PRINT(param1, param2) == false) {			// PRINT failure
				fout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "700" << endl << "=======================" << endl << endl;
			}
		}
		else if (!strcmp(cmd, "UPDATE"))	// If command is UPDATE
		{
			if (param3[0] != '\0') {	// many parameter
				fout << "======== ERROR ========" << endl << "800" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "800" << endl << "=======================" << endl << endl;
			}
			else if (param1[0] == '\0' || param2[0] == '\0') {	// less parameter
				fout << "======== ERROR ========" << endl << "800" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "800" << endl << "=======================" << endl << endl;
			}
			else if (UPDATE(param1, param2) == false) {		// UPDATE failure
				fout << "======== ERROR ========" << endl << "800" << endl << "=======================" << endl << endl;
				cout << "======== ERROR ========" << endl << "800" << endl << "=======================" << endl << endl;
			}
		}
		else if (!strcmp(cmd, "EXIT"))		// If command is EXIT
		{
			if (param1[0] != '\0')		// many parameter
				continue;
			else
				return;
		}
		else					// If Invalid command
			continue;
	}
	fin.close();
	fout.close();
	return;
}


bool Manager::LOAD()
{
	if (queue->pHead)		// If Queue is not empty
		return false;
	if (bst->WordCnt)		// If BST's words is not empty
		return false;
	if (cll->pHead)			// If CLL is not empty
		return false;

	char word[32] = {};
	char mean[32] = {};

	ifstream fin("to_memorize_word.txt");		// Open the file
	if (!fin)
		return false;

	while (!fin.eof())				// Until end of file
	{
		WordNode * pNew = new WordNode;
		fin >> word;

		if (word[0] == '\0')			// If reach the end of file
			break;

		pNew->SetWord(word);
		fin >> mean;
		pNew->SetMean(mean);

		queue->Push(pNew);			// Insert
	}
	fin.close();
	
	fin.open("memorizing_word.txt");		// Open the file
	if (!fin)
		return false;
	
	while (!fin.eof())				// Until end of file
	{
		WordNode * pNew = new WordNode;
		fin >> word;

		if (word[0] == '\0')			// If reach the end of file
			break;
		
		pNew->SetWord(word);
		fin >> mean;
		pNew->SetMean(mean);
		
		((bst->Search(word[0]))->GetBST())->Insert(pNew);	// Insert
		bst->WordCnt++;
	}
	fin.close();

	fin.open("memorized_word.txt");			// Open the file
	if (!fin)
		return false;

	while (!fin.eof())				// Until end of file
	{
		WordNode * pNew = new WordNode;
		fin >> word;

		if (word[0] == '\0')			// If reach the end of file
			break;

		pNew->SetWord(word);
		fin >> mean;
		pNew->SetMean(mean);

		cll->Insert(pNew);			// Insert
	}
	fin.close();
}


bool Manager::ADD()
{
	char word[32] = {};
	char mean[32] = {};

	ifstream fin("word.txt");	// Open the file
	if (!fin)
		return false;

	fin >> word;
	if (word[0] == '\0')		// If word.txt is empty
		return false;

	while (!fin.eof())		// Until end of file
	{
		WordNode * pNew = new WordNode;

		pNew->SetWord(word);
		fin >> mean;
		pNew->SetMean(mean);

		if((bst->Search(word[0])->GetBST())->Search(word) == 0 && cll->Search(word) == 0)	// Duplication check
		queue->Push(pNew);	// Insert to Queue

		fin >> word;
	}
	fin.close();
	return true;
}


bool Manager::MOVE(int num)
{
	int queueCnt = 0;		// Number of Queue's words
	WordNode * pCur = queue->pHead;
	while (pCur)			// Count the Queue's words
	{
		pCur = pCur->GetNext();
		queueCnt++;
	}

	if (!queue->pHead)			// If Queue is empty
		return false;
	else if (num + bst->WordCnt > 100)	// Input num + BST's word's number is more than 100
		return false;
	else if (queueCnt < num)		// Input num is more than Queue's words
		return false;

	pCur = 0;
	char str[32] = {};

	/* Move, Queue->BST */
	for (int i = 0; i < num; i++)
	{
		pCur = queue->Pop();
		strcpy(str, pCur->GetWord());
		
		((bst->Search(str[0]))->GetBST())->Insert(pCur);
		bst->WordCnt++;
	}

	return true;
}


bool Manager::SAVE()
{
	// a: Failure of Queue's Save
	// b: Failure of BST's Save
	// c: Failure of CLL's Save
	int a = !queue->Save();
	int b = !bst->Save();
	int c = !cll->Save();
	int d = a && b && c;	// d: Failure of all structure's Save

	if (d > 0)
		return false;
	else
		return true;
}


bool Manager::TEST(char * word, char * mean)
{
	WordNode * pCur = ((bst->Search(word[0]))->GetBST())->Search(word);	// pCur: Result of SEARCH, If cannot search word -> pCur = 0
	if (!pCur)					// Failure of SEARCH
		return false;
	else if (strcmp(pCur->GetMean(), mean) != 0)	// Word SEARCH Success, but mean is different 
		return false;
	else						// Word, mean is same
	{
		((bst->Search(word[0]))->GetBST())->Delete(word);	// Delete word from BST
		cll->Insert(pCur); 					// Insert to CLL
		bst->WordCnt--;						// BST's word count --
		return true;
	}
}


bool Manager::SEARCH(char * word)
{
	ofstream fout("log.txt", ios::app);		// Open the log.txt
	WordNode * pCur = queue->Search(word);		// pCur: Result of SEARCH in Queue
	if (pCur)	// Search Success
	{
		cout << "======== SEARCH ========" << endl; 
		cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		cout << "========================" << endl << endl;
		fout << "======== SEARCH ========" << endl;
		fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		fout << "========================" << endl << endl;
		return true;
	}

	pCur = ((bst->Search(word[0]))->GetBST())->Search(word);	// pCur: Result of SEARCH in BST
	if (pCur)	// Search Success
	{
		cout << "======== SEARCH ========" << endl; 
		cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		cout << "========================" << endl << endl;
		fout << "======== SEARCH ========" << endl;
		fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		fout << "========================" << endl << endl;
		return true;
	}

	pCur = cll->Search(word);					// pCur: Result of SEARCH in CLL
	if (pCur)	// Search Success
	{
		cout << "======== SEARCH ========" << endl; 
		cout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		cout << "========================" << endl << endl;
		fout << "======== SEARCH ========" << endl;
		fout << pCur->GetWord() << " " << pCur->GetMean() << endl;
		fout << "========================" << endl << endl;
		return true;
	}

	/* Search Failure */
	fout.close();
	return false;
}


bool Manager::PRINT(char * name, char * order)
{
	if (!strcmp(name, "TO_MEMORIZE"))	// If input order is TO_MEMORIZE
		return queue->Print();		// Return Success of Queue's Print
	else if (!strcmp(name, "MEMORIZING"))	// If input order is MEMORIZING
		return bst->Print(order);	// Return Success of BST's Print
	else if (!strcmp(name, "MEMORIZED"))	// If input order is MEMORIZIed
		return cll->Print();		// Return Success of CLL's Print

	return false;				// Input order not match
}


bool Manager::UPDATE(char * word, char * mean)
{
	ofstream fout("log.txt", ios::app);		// Open the file
	WordNode * pCur = queue->Search(word);		// pCur: Result of SEARCH in QUEUE
	if (pCur)	// SEARCH Success
	{
		cout << "======== UPDATE ========" << endl;
		cout << pCur->GetWord() << " " << pCur->GetMean() << " -> ";
		fout << "======== UPDATE ========" << endl;
		fout << pCur->GetWord() << " " << pCur->GetMean() << " -> ";
		pCur->SetMean(mean);			// Changing word's mean
		cout << pCur->GetMean() << endl;
		cout << "========================" << endl << endl;
		fout << pCur->GetMean() << endl;
		fout << "========================" << endl << endl;
		return true;
	}

	pCur = ((bst->Search(word[0]))->GetBST())->Search(word);	// pCur: Result of SEARCH in BST
	if (pCur)	// SEARCH Success
	{
		cout << "======== UPDATE ========" << endl;
		cout << pCur->GetWord() << " " << pCur->GetMean() << " -> ";
		fout << "======== UPDATE ========" << endl;
		fout << pCur->GetWord() << " " << pCur->GetMean() << " -> ";
		pCur->SetMean(mean);			// Changing word's mean
		cout << pCur->GetMean() << endl;
		cout << "========================" << endl << endl;
		fout << pCur->GetMean() << endl;
		fout << "========================" << endl << endl;
		return true;
	}

	pCur = cll->Search(word);			// pCur: Result of SEARCH in CLL
	if (pCur)	// SEARCH Success
	{
		cout << "======== UPDATE ========" << endl;
		cout << pCur->GetWord() << " " << pCur->GetMean() << " -> ";
		fout << "======== UPDATE ========" << endl;
		fout << pCur->GetWord() << " " << pCur->GetMean() << " -> ";
		pCur->SetMean(mean);			// Changing word's mean
		cout << pCur->GetMean() << endl;
		cout << "========================" << endl << endl;
		fout << pCur->GetMean() << endl;
		fout << "========================" << endl << endl;
		return true;
	}

	/* Search Failure */
	fout.close();
	return false;
}

