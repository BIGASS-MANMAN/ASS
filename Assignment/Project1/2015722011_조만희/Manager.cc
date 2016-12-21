#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
#include <string.h>
#include <iostream>
using namespace std;

char line[256];
char *tok;

Manager::Manager()   //constructor
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
	Manager::logfile.open("log.txt");
}


Manager::~Manager()   //destructor
{ return;

	delete cll;
	delete bst;
	delete queue;
	Manager::logfile.close();
}

void Manager::run(const char * command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	ifstream infile(command);   //initiate file input stream

	int i;

	while (infile.getline(line, 256)) {
		tok = strtok(line, " ");

		for (i = 0; i < sizeof(cmds) / sizeof(char*); i++)
			if (!strcmp(cmds[i], tok))
				switch (i) {
				case 0: // LOAD
					if (LOAD()) {   // Print error on screen & file if LOAD fails
						cout << "======== ERROR ========" << endl << 100 << endl << "=======================" << endl << endl;
						logfile << "======== ERROR ========" << endl << 100 << endl << "=======================" << endl << endl;
					}
					else {   // Print Success
						cout << "======== LOAD ========" << endl << "Success" << endl << "=======================" << endl << endl;
						logfile << "======== LOAD ========" << endl << "Success" << endl << "=======================" << endl << endl;
					}
					break;
				case 1: // ADD
					if (ADD()) {   // Print error on screen & file if ADD fails
						cout << "======== ERROR ========" << endl << 200 << endl << "=======================" << endl << endl;
						logfile << "======== ERROR ========" << endl << 200 << endl << "=======================" << endl << endl;
					}
					else {   // Print Success
						cout << "======== ADD ========" << endl << "Success" << endl << "=======================" << endl << endl;
						logfile << "======== ADD ========" << endl << "Success" << endl << "=======================" << endl << endl;
					}
					break;
				case 2: // MOVE
					if (MOVE()) {   // Print error on screen & file if MOVE fails
						cout << "======== ERROR ========" << endl << 300 << endl << "=======================" << endl << endl;
						logfile << "======== ERROR ========" << endl << 300 << endl << "=======================" << endl << endl;
					}
					else    // Print Success
						cout << "======== MOVE ========" << endl << "Success" << endl << "=======================" << endl << endl;
					logfile << "======== MOVE ========" << endl << "Success" << endl << "=======================" << endl << endl;

					break;
				case 3: // SAVE
					if (SAVE()) {   // Print error on screen & file if SAVE fails
						cout << "======== ERROR ========" << endl << 400 << endl << "=======================" << endl << endl;
						logfile << "======== ERROR ========" << endl << 400 << endl << "=======================" << endl << endl;

					}
					else {   // Print Success
						cout << "======== SAVE ========" << endl << "Success" << endl << "=======================" << endl << endl;
						logfile << "======== SAVE ========" << endl << "Success" << endl << "=======================" << endl << endl;
					}
					break;
				case 4: // TEST
					if (TEST()) {   // Print error on screen & file if TEST fails
						cout << "======== ERROR ========" << endl << 500 << endl << "=======================" << endl << endl;
						logfile << "======== ERROR ========" << endl << 500 << endl << "=======================" << endl << endl;
					}
					else {   // Print Success
						cout << "======== TEST ========" << endl << "Pass" << endl << "=======================" << endl << endl;
						logfile << "======== TEST ========" << endl << "Pass" << endl << "=======================" << endl << endl;
					}
					break;
				case 5: // SEARCH
					if (SEARCH()) {   // Print error on screen & file if SEARCH fails
						cout << "======== ERROR ========" << endl << 600 << endl << "=======================" << endl << endl;
						logfile << "======== ERROR ========" << endl << 600 << endl << "=======================" << endl << endl;
					}
					break;
				case 6: // PRINT
					if (PRINT()) {   // Print error on screen & file if PRINT fails
						cout << "======== ERROR ========" << endl << 700 << endl << "=======================" << endl << endl;
						logfile << "======== ERROR ========" << endl << 700 << endl << "=======================" << endl << endl;
					}
					break;
				case 7: // UPDATE
					if (UPDATE()) {   // Print error on screen & file if UPDATE fails
						cout << "======== ERROR ========" << endl << 800 << endl << "=======================" << endl << endl;
						logfile << "======== ERROR ========" << endl << 800 << endl << "=======================" << endl << endl;
					}
					break;
				}
	}
	infile.close();   // file input stream close
}

bool Manager::LOAD()   //Load word infomation
{
	ifstream memorize, memorizing, memorized;
	bool err = false;
	char words[256];

	memorize.open("to_memorize_word.txt");
	if (!memorize.is_open()) err = true;
	memorizing.open("memorizing_word.txt");
	if (!memorizing.is_open()) err = true;
	memorized.open("memorized_word.txt");
	if (!memorized.is_open()) err = true;

	if (err) {
		memorize.close(); memorizing.close(); memorized.close();
		return true;
	}
	else {
		while (memorize.getline(words, 256)) {
			WordNode *WN = new WordNode;
			WN->SetWord(strtok(words, "\t"));
			WN->SetMean(strtok(NULL, "\t"));
			queue->Push(WN);
		}

		while (memorizing.getline(words, 256)) {
			WordNode *WN = new WordNode;
			WN->SetWord(strtok(words, "\t"));
			WN->SetMean(strtok(NULL, "\t"));
			bst->Search(WN->GetWord()[0])->GetBST()->Insert(WN);
		}

		while (memorized.getline(words, 256)) {
			WordNode *WN = new WordNode;
			WN->SetWord(strtok(words, "\t"));
			WN->SetMean(strtok(NULL, "\t"));
			cll->Insert(WN);
		}
		return false;
	}
}

bool Manager::ADD()   //Add word in Queue
{
	ifstream loadfile;
	char loadline[256];
	char *loadtok;

	loadfile.open("word.txt");

	if (!loadfile.is_open())
		return true;

	loadfile.getline(loadline, 256);
	if (!strlen(loadline))
		return true;

	do {
		WordNode *WN = new WordNode;
		loadtok = strtok(loadline, "\t");
		WN->SetWord(loadtok);
		loadtok = strtok(NULL, "\t");
		WN->SetMean(loadtok);
		queue->Push(WN);
	} while (loadfile.getline(loadline, 256));

	return false;
}

bool Manager::MOVE() //Move word from Queue to BST
{
	// If number of Word bigger than MAX_WORD
	if (bst->WordCnt >= MAX_WORD || queue->Empty()) {
		return true;
	}

	tok = strtok(NULL, " ");
	for (int moveCnt = atoi(tok); moveCnt > 0; moveCnt--) {
		bst->Search(queue->Front()->GetWord()[0])->GetBST()->Insert(queue->Front());
		queue->Pop();
		bst->WordCnt++;
	}
	return false;
}

bool Manager::SAVE()   //Save word information
{
	if (queue->Empty() || !bst->WordCnt || cll->pHead == NULL)
		return true;
	queue->Save();   bst->Save(bst->root);   cll->Save();
	return false;
}

bool Manager::TEST()   //Move word from BST to CLL if the inputs match the data
{
	char *word, *mean;
	WordNode *WN;

	word = strtok(NULL, " ");
	mean = strtok(NULL, " ");
	
	WN = bst->Search(word[0])->GetBST()->Search(word);

	if (WN && !strcmp(WN->GetMean(), mean)) {
		cll->Insert(WN); bst->Search(word[0])->GetBST()->Delete(word); bst->WordCnt--; return false;
	}
	else
		return true;
}

bool Manager::SEARCH()   //Search input word in the list
{
	tok = strtok(NULL, " ");
	WordNode *WN;

	if (!queue->Search(tok) && !bst->Search(tok[0])->GetBST()->Search(tok) && !cll->Search(tok))
		return true;

	cout << "======== SEARCH ========" << endl;
	logfile << "======== SEARCH ========" << endl;

	WN = queue->Search(tok);   //Search in Queue
	if (WN){ cout << WN->GetWord() << "\t" << WN->GetMean() << endl; logfile << WN->GetWord() << "\t" << WN->GetMean() << endl;}
	else {
		WN = bst->Search(tok[0])->GetBST()->Search(tok);   //Search in BST
		if (WN){ cout << WN->GetWord() << "\t" << WN->GetMean() << endl; logfile << WN->GetWord() << "\t" << WN->GetMean() << endl;}
		else { 
			WN = cll->Search(tok);   //Search in CLL
			if (WN){ cout << WN->GetWord() << "\t" << WN->GetMean() << endl; logfile << WN->GetWord() << "\t" << WN->GetMean() << endl;}
			else
				return true;
		}
	}

	cout << "=======================" << endl << endl;
	logfile << "=======================" << endl << endl;

	return false;
}

bool Manager::PRINT()   //Print TO_MEMORIZE or MEMORIZING or MEMORIZED list
{
	tok = strtok(NULL, " ");
	if (!strcmp(tok, "TO_MEMORIZE")) {
		if (queue->Empty())
			return true;
		cout << "======== PRINT ========" << endl;
		logfile << "======== PRINT ========" << endl;
		queue->Print(logfile);   //Print Queue
		cout << "=======================" << endl << endl;
		logfile << "=======================" << endl << endl;
	}
	else if(!strcmp(tok, "MEMORIZING")){
		if (!bst->WordCnt)
			return true;
		cout << "======== PRINT ========" << endl;
		logfile << "======== PRINT ========" << endl;
		tok = strtok(NULL, " ");
		bst->Print(tok, logfile);   //Print BST
		cout << "=======================" << endl << endl;
		logfile << "=======================" << endl << endl;
	}
	else if (!strcmp(tok, "MEMORIZED")) {
		if (!cll->pHead)
			return true;
		cout << "======== PRINT ========" << endl;
		logfile << "======== PRINT ========" << endl;
		cll->Print(logfile); // Print Circular Linked List
		cout << "=======================" << endl << endl;
		logfile << "=======================" << endl << endl;
	}
	return false;
}

bool Manager::UPDATE()   //Change word mean to input data
{
	char *word, *mean;
	WordNode *WN;

	word = strtok(NULL, " ");
	mean = strtok(NULL, " ");

	WN = queue->Search(word);   //word to change in Queue

	if (WN) WN->SetMean(mean);
	else {
		WN = bst->Search(word[0])->GetBST()->Search(word);   //word to change in BST
		if (WN) WN->SetMean(mean);
		else {
			WN = cll->Search(word);   //word to change in CLL
			if (WN) WN->SetMean(mean);
			else
				return true;
		}
	}
	// Print to screen & file
	cout << "======== UPDATE ========" << endl;
	logfile << "======== UPDATE ========" << endl;
	cout << word << " -> " << mean << endl;
	logfile << word << " -> " << mean << endl;
	cout << "=======================" << endl << endl;
	logfile << "=======================" << endl << endl;

	return false;
}
