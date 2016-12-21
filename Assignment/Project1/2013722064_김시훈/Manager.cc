#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
using namespace std;

Manager::Manager()
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
	memset(arg1, '\0', sizeof(arg1));
	memset(arg2, '\0', sizeof(arg2));
	QueueNum = 0;
	CLLNum = 0;
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

	int i = 0, j = 0, k = 0;
	char alpha[26] = { 'P', 'H', 'X', 'D', 'L', 'T', 'Z', 'B', 'F', 'J', 'N', 'R', 'V', 'Y', 'A', 'C', 'E', 'G', 'I', 'K',
		'M', 'O', 'Q', 'S', 'U', 'W' };
	
	for (i = 0; i < 26; i++) {        // generate alphabet bst 
		AlphabetNode * InsertNode = new AlphabetNode();
		InsertNode->SetAlphabet(alpha[i]);
		bst->Insert(InsertNode);
	}

	ifstream fin;
	fin.open(command);            // file open
	ofstream fout;
	fout.open("log.txt");      // for log file	
	char arr[50];               // for command + parameter
	char* rest = NULL;         // for remained string after token
	char* token = NULL;
	char temp[50][50] = { '\0' };

	while (1) {
		fin.getline(arr, 50);      // read only one line

		if(strcmp(arr, "\0") == 0)
			continue;
		rest = NULL;		
		token = strtok_r(arr, " \t\r\n", &rest);      // token to space
									
		for (i = 0; i < 50; i++) { //initialize 2D array
			for (j = 0; j < 50; j++) {
				temp[i][j] = '\0';
			}
		}

		// save tokens in 2D array
		j = 0; k = 0;
		for (i = 0; i < 5; i++) {
			while (j < strlen(rest)) {
				if (rest[j] == ' ' || rest[j] == '\r' || rest[j] == '\0' || rest[j] == '\t') {
					k = 0;  j += 1; break;
				}
				temp[i][k] = rest[j];
				j++; k++;
			}
		}

		// check input command		
		if (strcmp(token, "LOAD") == 0) {
			if (strcmp(temp[0], "\0") != 0) {               // the number of parameter is exceeded
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "100" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "100" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else {
				LOAD();
			}
		}
		else if (strcmp(token, "ADD") == 0) {
			if (strcmp(temp[0], "\0") != 0) {               // the number of parameter is exceeded
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "200" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "200" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else {
				ADD();
			}
		}
		else if (strcmp(token, "MOVE") == 0) {
			if (strcmp(temp[0], "\0") == 0) {      // the number of parameter is lack
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "300" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "300" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else if (strcmp(temp[1], "\0") != 0) {               // the number of parameter is exceeded
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "300" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "300" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else {				
				strncpy(arg1, temp[0], sizeof(temp[0]));
				MOVE();
			}
		}
		else if (strcmp(token, "SAVE") == 0) {
			if (strcmp(temp[0], "\0") != 0) {               // the number of parameter is exceeded
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "400" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "400" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else {
				SAVE();
			}
		}
		else if (strcmp(token, "TEST") == 0) {
			if (strcmp(temp[1], "\0") == 0) {      // the number of parameter is lack
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "500" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "500" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else if (strcmp(temp[2], "\0") != 0) {               // the number of parameter is exceeded
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "500" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "500" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else {				
				strncpy(arg1, temp[0], sizeof(temp[0]));
				strncpy(arg2, temp[1], sizeof(temp[1]));
				TEST();
			}
		}
		else if (strcmp(token, "SEARCH") == 0) {
			if (strcmp(temp[0], "\0") == 0) {      // the number of parameter is lack
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "600" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "600" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else if (strcmp(temp[1], "\0") != 0) {               // the number of parameter is exceeded
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "600" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "600" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else {				
				strncpy(arg1, temp[0], sizeof(temp[0]));
				SEARCH();
			}
		}
		else if (strcmp(token, "PRINT") == 0) {
			if (strcmp(temp[0], "\0") == 0) {      // the number of parameter is lack
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "700" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "700" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else {
				if (strcmp(temp[0], "TO_MEMORIZE") == 0) {
					if (strcmp(temp[1], "\0") != 0) {               // the number of parameter is exceeded
						cout << "== == == == ERROR == == == ==" << endl;
						cout << "700" << endl;
						cout << "== == == == == == == == == == == =" << endl;

						fout << "== == == == ERROR == == == ==" << endl;
						fout << "700" << endl;
						fout << "== == == == == == == == == == == =" << endl;
					}
					else {						
						strncpy(arg1, temp[0], sizeof(temp[0]));
						PRINT();
					}
				}
				else if (strcmp(temp[0], "MEMORIZING") == 0) {
					if (strcmp(temp[1], "\0") == 0) {               // the number of parameter is lack
						cout << "== == == == ERROR == == == ==" << endl;
						cout << "700" << endl;
						cout << "== == == == == == == == == == == =" << endl;

						fout << "== == == == ERROR == == == ==" << endl;
						fout << "700" << endl;
						fout << "== == == == == == == == == == == =" << endl;
					}
					else if (strcmp(temp[2], "\0") != 0) {               // the number of parameter is exceeded
						cout << "== == == == ERROR == == == ==" << endl;
						cout << "700" << endl;
						cout << "== == == == == == == == == == == =" << endl;

						fout << "== == == == ERROR == == == ==" << endl;
						fout << "700" << endl;
						fout << "== == == == == == == == == == == =" << endl;
					}
					else {						
						strncpy(arg1, temp[0], sizeof(temp[0]));
						strncpy(arg2, temp[1], sizeof(temp[1]));
						PRINT();
					}
				}
				else if (strcmp(temp[0], "MEMORIZED") == 0) {
					if (strcmp(temp[1], "\0") != 0) {               // the number of parameter is exceeded
						cout << "== == == == ERROR == == == ==" << endl;
						cout << "700" << endl;
						cout << "== == == == == == == == == == == =" << endl;

						fout << "== == == == ERROR == == == ==" << endl;
						fout << "700" << endl;
						fout << "== == == == == == == == == == == =" << endl;
					}
					else {						
						strncpy(arg1, temp[0], sizeof(temp[0]));
						PRINT();
					}
				}
			}
		}
		else if (strcmp(token, "UPDATE") == 0) {
			if (strcmp(temp[1], "\0") == 0) {      // the number of parameter is lack
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "800" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "800" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else if (strcmp(temp[2], "\0") != 0) {               // the number of parameter is exceeded
				cout << "== == == == ERROR == == == ==" << endl;
				cout << "800" << endl;
				cout << "== == == == == == == == == == == =" << endl;

				fout << "== == == == ERROR == == == ==" << endl;
				fout << "800" << endl;
				fout << "== == == == == == == == == == == =" << endl;
			}
			else {				
				strncpy(arg1, temp[0], sizeof(temp[0]));
				strncpy(arg2, temp[1], sizeof(temp[1]));
				UPDATE();
			}
		}
		else if (strcmp(token, "EXIT") == 0) {		// program exit
			break;
		}
	}	
	fout.close();
	fin.close();               // file close	
}

bool Manager::ADD()
{
	WordNode* pNew;
	ifstream fin;
	fin.open("word.txt");      // for word file
	ofstream fout;
	fout.open("log.txt", ios::app);      // for log file

	char word_mean[50];
	char* rest = NULL;         // for remained string after token
	char* token;
	int check_dup[3] = {0,0,0};      // check for duplicate word 
									 //check_dup[0] : Queue, check_dup[1] : BST, check_dup[2] : CLL

	if (fin.fail()) {      // if not exist file
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "200" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "200" << endl;
		fout << "== == == == == == == == == == == =" << endl;

		return false;
	}
	else {
		// check for exist word in file or not
		fin.getline(word_mean, 50);

		if (strcmp(word_mean, "\0") == 0) {            // if not exist word
			cout << "== == == == ERROR == == == ==" << endl;
			cout << "200" << endl;
			cout << "== == == == == == == == == == == =" << endl;

			fout << "== == == == ERROR == == == ==" << endl;
			fout << "200" << endl;
			fout << "== == == == == == == == == == == =" << endl;

			return false;
		}
		else {
			rest = NULL;			
			token = strtok_r(word_mean, " \t", &rest);      // token to space
			
			if (queue->Search(token) == NULL) {      // not exist data in Queue
				check_dup[0] = 0;
			}
			else {
				check_dup[0] = 1;
			}

			if (bst->Search(token[0]) == NULL) {   // not exist data in Alphabet BST
				check_dup[1] = 0;
			}
			else {
				if (bst->Search(token[0])->GetBST()->Search(token) == NULL) {   // not exist data in Word BST
					check_dup[1] = 0;
				}
				else {
					check_dup[1] = 1;
				}
			}

			if (cll->Search(token) == NULL) {      // not exist data in Circular List
				check_dup[2] = 0;
			}
			else {
				check_dup[2] = 1;
			}

			if (check_dup[0] == 0 && check_dup[1] == 0 && check_dup[2] == 0) {
				pNew = new WordNode();
				pNew->SetWord(token);      // set word
				pNew->SetMean(rest);      // set mean
				queue->Push(pNew);         // push in queue (To_Memorize)
				QueueNum++;
			}

			while (!fin.eof()) {

				fin.getline(word_mean, 50);

				if(strcmp(word_mean, "\0") == 0) break;
				rest = NULL;				
				token = strtok_r(word_mean, " \t", &rest);      // token to space
														  // search in each data struture for excepting duplicate word
				if (queue->Search(token) == NULL) {      // not exist data in Queue
					check_dup[0] = 0;
				}
				else {
					check_dup[0] = 1;
				}

				if (bst->Search(token[0]) == NULL) {   // not exist data in Alphabet BST
					check_dup[1] = 0;
				}
				else {
					if (bst->Search(token[0])->GetBST()->Search(token) == NULL) {   // not exist data in Word BST
						check_dup[1] = 0;
					}
					else {
						check_dup[1] = 1;
					}
				}

				if (cll->Search(token) == NULL) {      // not exist data in Circular List
					check_dup[2] = 0;
				}
				else {
					check_dup[2] = 1;
				}

				if (check_dup[0] == 0 && check_dup[1] == 0 && check_dup[2] == 0) {
					pNew = new WordNode();
					pNew->SetWord(token);      // set word
					pNew->SetMean(rest);      // set mean
					queue->Push(pNew);         // push in queue (To_Memorize)
					QueueNum++;
				}
			}

			cout << "== == == == ADD == == == ==" << endl;
			cout << "Success" << endl;
			cout << "== == == == == == == == == == == =" << endl;

			fout << "== == == == ADD == == == ==" << endl;
			fout << "Success" << endl;
			fout << "== == == == == == == == == == == =" << endl;

			return true;
		}
	}
		
	fout.close();
	fin.close();
	
}

bool Manager::MOVE()
{
	int i = 0, j = 0;
	ofstream fout;
	fout.open("log.txt", ios::app);      // for log file

	int num = 0, mul;   // 'num' for amount of words to move, 'mul' for the number of digits
	for (i = strlen(arg1) - 1; i >= 0; i--) {
		mul = 1;            // initialize to 1
		for (j = 0; j < strlen(arg1) - i - 1; j++) mul *= 10;
		num += (arg1[i] - '0') * mul;
	}

	if (num > 100) { //when entered number is over 100
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "300" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "300" << endl;
		fout << "== == == == == == == == == == == =" << endl;
		return false;
	}
	if (QueueNum == 0) { //when queue is empty
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "300" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "300" << endl;
		fout << "== == == == == == == == == == == =" << endl;
		return false;
	}
	if (num + bst->GetWordCnt() > 100) //when sum of entered number and Memorizing number of words is over 100
	{
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "300" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "300" << endl;
		fout << "== == == == == == == == == == == =" << endl;
		return false;
	}

	if (num > QueueNum) { //when entered number is greater than number of queue's node
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "300" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "300" << endl;
		fout << "== == == == == == == == == == == =" << endl;
		return false;
	}

	for (int i = 0; i < num; i++) { //loop for MOVE command
		WordNode * moveNode = queue->Pop(); //save queue's node to moveNode
		bst->Search(moveNode->GetWord()[0])->GetBST()->Insert(moveNode); //Insert to BST
		bst->SetWordCnt(bst->GetWordCnt() + 1);      // increase the number of bst's word
		QueueNum--;
	}
	cout << "== == == == MOVE == == == ==" << endl;
	cout << "Success" << endl;
	cout << "== == == == == == == == == == == =" << endl;

	fout << "== == == == MOVE == == == ==" << endl;
	fout << "Success" << endl;
	fout << "== == == == == == == == == == == =" << endl;
	fout.close();

	return true;
}

bool Manager::TEST()
{
	ofstream fout;
	fout.open("log.txt", ios::app);      // for log file
	WordNode * SelNode; //Test Node

	if (bst->Search(arg1[0])->GetBST()->Search(arg1) == '\0') { //word is not exist in bst
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "500" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "500" << endl;
		fout << "== == == == == == == == == == == =" << endl;
		return false;
	}
	else {
		SelNode = bst->Search(arg1[0])->GetBST()->Search(arg1); //redefine SelNode

		if (strcmp(SelNode->GetMean(), arg2) != 0) { //bst word's mean isn't equal with entered word's mean
			cout << "== == == == ERROR == == == ==" << endl;
			cout << "500" << endl;
			cout << "== == == == == == == == == == == =" << endl;

			fout << "== == == == ERROR == == == ==" << endl;
			fout << "500" << endl;
			fout << "== == == == == == == == == == == =" << endl;
			return false;
		}
	}
	WordNode * newnew = bst->Search(arg1[0])->GetBST()->Delete(arg1); //Delete selected node from word bst
	cll->Insert(newnew); //insert to circular linked list
	bst->SetWordCnt(bst->GetWordCnt() - 1);      // decrease the number of bst's word
	CLLNum++;

	cout << "== == == == TEST == == == ==" << endl;
	cout << "PASS" << endl;
	cout << "== == == == == == == == == == == =" << endl;

	fout << "== == == == TEST == == == ==" << endl;
	fout << "PASS" << endl;
	fout << "== == == == == == == == == == == =" << endl;
	fout.close();

	return true;
}

bool Manager::SEARCH()
{
	int search[3] = {0, 0, 0};	// for searching word 
								//search[0] : Queue, search[1] : BST, search[2] : CLL						
	ofstream fout;
	fout.open("log.txt", ios::app);

	// search in each data struture
	if (queue->Search(arg1) == NULL) {      // not exist data in Queue
		search[0] = 0;
	}
	else {
		search[0] = 1;		
		strncpy(arg2, queue->Search(arg1)->GetMean(), sizeof(queue->Search(arg1)->GetMean()) + 1);
	}

	if (bst->Search(arg1[0]) == NULL) {   // not exist data in Alphabet BST
		search[1] = 0;
	}
	else {
		if (bst->Search(arg1[0])->GetBST()->Search(arg1) == NULL) {   // not exist data in Word BST
			search[1] = 0;
		}
		else {
			search[1] = 1;			
			strncpy(arg2, bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean(), sizeof(bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean()) + 1);
		}
	}

	if (cll->Search(arg1) == NULL) {      // not exist data in Circular List
		search[2] = 0;
	}
	else {
		search[2] = 1;		
		strncpy(arg2, cll->Search(arg1)->GetMean(), sizeof(cll->Search(arg1)->GetMean()) + 1);
	}

	if (search[0] == 1 || search[1] == 1 || search[2] == 1) {
		cout << "== == == == SEARCH == == == ==" << endl;
		cout << arg1 << " " << arg2 << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == SEARCH == == == ==" << endl;
		fout << arg1 << " " << arg2 << endl;
		fout << "== == == == == == == == == == == =" << endl;

		return true;
	}
	else {
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "600" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "600" << endl;
		fout << "== == == == == == == == == == == =" << endl;
		return false;
	}
	fout.close();
}

bool Manager::UPDATE()
{
	int search[3] = { 0, 0, 0 };	// for searching word 
									//search[0] : Queue, search[1] : BST, search[2] : CLL	
	char Prev_Mean[50] = { '\0' };
	ofstream fout;
	fout.open("log.txt", ios::app);

	// search in each data struture
	if (queue->Search(arg1) == NULL) {      // not exist data in Queue
		search[0] = 0;
	}
	else {
		search[0] = 1;		
		strncpy(Prev_Mean, queue->Search(arg1)->GetMean(), sizeof(queue->Search(arg1)->GetMean()) + 1);
		queue->Search(arg1)->SetMean(arg2);      //update new mean
	}

	if (bst->Search(arg1[0]) == NULL) {   // not exist data in Alphabet BST
		search[1] = 0;
	}
	else {
		if (bst->Search(arg1[0])->GetBST()->Search(arg1) == NULL) {   // not exist data in Word BST
			search[1] = 0;
		}
		else {
			search[1] = 1;			
			strncpy(Prev_Mean, bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean(), sizeof(bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean()) + 1);
			bst->Search(arg1[0])->GetBST()->Search(arg1)->SetMean(arg2);
		}
	}

	if (cll->Search(arg1) == NULL) {      // not exist data in Circular List
		search[2] = 0;
	}
	else {
		search[2] = 1;		
		strncpy(Prev_Mean, cll->Search(arg1)->GetMean(), sizeof(cll->Search(arg1)->GetMean()) + 1);
		cll->Search(arg1)->SetMean(arg2);
	}

	if (search[0] == 1 || search[1] == 1 || search[2] == 1) {
		cout << "== == == == UPDATE == == == ==" << endl;
		cout << arg1 << " " << Prev_Mean << "->" << arg2 << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == UPDATE == == == ==" << endl;
		fout << arg1 << " " << Prev_Mean << "->" << arg2 << endl;
		fout << "== == == == == == == == == == == =" << endl;

		return true;
	}
	else {
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "800" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "800" << endl;
		fout << "== == == == == == == == == == == =" << endl;
		return false;
	}
	fout.close();
}

bool Manager::LOAD() {
	ofstream fout;
	fout.open("log.txt", ios::app);
	ifstream queueData;
	queueData.open("to_memorize_word.txt");
	ifstream bstData;
	bstData.open("memorizing_word.txt");
	ifstream cirListData;
	cirListData.open("memorized_word.txt");
	
	char word_mean[50] = { '\0' };
	
	if (queueData.fail() || bstData.fail() || cirListData.fail()) { //file isn't exist in project folder
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "100" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "100" << endl;
		fout << "== == == == == == == == == == == =" << endl;

		fout.close();
		queueData.close();
		bstData.close();
		cirListData.close();
		return false;
	}
	
	if (QueueNum != 0 || CLLNum != 0 || bst->GetWordCnt() != 0) {
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "100" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "100" << endl;
		fout << "== == == == == == == == == == == =" << endl;

		fout.close();
		queueData.close();
		bstData.close();
		cirListData.close();
		return false;
	}
	
	queueData.getline(word_mean, 50);
	if (strcmp(word_mean, "\0") == 0) {            // if not exist word
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "100" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "100" << endl;
		fout << "== == == == == == == == == == == =" << endl;
		
		fout.close();
		queueData.close();
		bstData.close();
		cirListData.close();
		return false;
	}

	bstData.getline(word_mean, 50);
	if (strcmp(word_mean, "\0") == 0) {            // if not exist word
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "100" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "100" << endl;
		fout << "== == == == == == == == == == == =" << endl;

		fout.close();
		queueData.close();
		bstData.close();
		cirListData.close();
		return false;
	}

	cirListData.getline(word_mean, 50);
	if (strcmp(word_mean, "\0") == 0) {            // if not exist word
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "100" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "100" << endl;
		fout << "== == == == == == == == == == == =" << endl;

		fout.close();
		queueData.close();
		bstData.close();
		cirListData.close();
		return false;
	}
		
	queueData.seekg(0, ios::beg);		//Move file cursor to front of file
	bstData.seekg(0, ios::beg);		//
	cirListData.seekg(0, ios::beg);		//
	
	char* rest = NULL;         // for remained string after token
	char* token;

	while (!queueData.eof()) { //Queue is created
		queueData.getline(word_mean, 50);		
		rest = NULL;
		if (strcmp(word_mean, "") == 0)
			continue;		
		token = strtok_r(word_mean, " ", &rest);      // token to space

		WordNode* pNew = new WordNode();
		pNew->SetWord(token);
		pNew->SetMean(rest);
		queue->Push(pNew); //insert pNew to queue
		QueueNum++; //queue's number is increased
	}

	while (!bstData.eof()) { //bst is created
		bstData.getline(word_mean, 50);
		rest = NULL;
		if (strcmp(word_mean, "") == 0)
			continue;		
		token = strtok_r(word_mean, " ", &rest);      // token to space

		WordNode* pNew = new WordNode();
		pNew->SetWord(token);
		pNew->SetMean(rest);

		bst->Search(pNew->GetWord()[0])->GetBST()->Insert(pNew); //insert pNew to bst
		bst->SetWordCnt(bst->GetWordCnt() + 1);  //bst's number is increased
	}

	while (!cirListData.eof()) { //circularlinkedlist is created
		cirListData.getline(word_mean, 50);
		rest = NULL;
		if (strcmp(word_mean, "") == 0)
			continue;		
		token = strtok_r(word_mean, " ", &rest);      // token to space

		WordNode* pNew = new WordNode();
		pNew->SetWord(token);
		pNew->SetMean(rest);
		cll->Insert(pNew); //insert pNew to circularlinkedlist
		CLLNum++;  //cll's number is increased
	}
	cout << "== == == == LOAD == == == ==" << endl;
	cout << "Success" << endl;
	cout << "== == == == == == == == == == == =" << endl;

	fout << "== == == == LOAD == == == ==" << endl;
	fout << "Success" << endl;
	fout << "== == == == == == == == == == == =" << endl;

	fout.close();
	queueData.close();
	bstData.close();
	cirListData.close();

	return true;
}

bool Manager::SAVE()
{
	ofstream fout;
	fout.open("log.txt", ios::app);            //for log file
	bool cond1, cond2, cond3;

	cond1 = queue->Save();
	cond2 = bst->Save();
	cond3 = cll->Save();

	if (cond1 || cond2 || cond3)            //if one of those exist
	{
		cout << "== == == == SAVE == == == ==" << endl;
		cout << "Success" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == SAVE == == == ==" << endl;
		fout << "Success" << endl;
		fout << "== == == == == == == == == == == =" << endl;

		fout.close();
		return true;
	}
	else                              //if any data structure is not exist
	{
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "400" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "400" << endl;
		fout << "== == == == == == == == == == == =" << endl;

		fout.close();
		return false;
	}

}

bool Manager::PRINT()
{
	bool print = false;
	ofstream fout;
	fout.open("log.txt", ios::app);
	// print in each data struture

	if (strcmp(arg1, "TO_MEMORIZE") == 0)               // print To_Memorise
	{
		if (queue->pHead == NULL)
		{
			cout << "== == == == ERROR == == == ==" << endl;
			cout << "700" << endl;
			cout << "== == == == == == == == == == == =" << endl;

			fout << "== == == == ERROR == == == ==" << endl;
			fout << "700" << endl;
			fout << "== == == == == == == == == == == =" << endl;

			fout.close();
			return false;
		}
		else
		{
			cout << "== == == == PRINT == == == ==" << endl;
			fout << "== == == == PRINT == == == ==" << endl;
			print = queue->Print();
			cout << "== == == == == == == == == == == =" << endl;
			fout << "== == == == == == == == == == == =" << endl;

		}
	}
	else if (strcmp(arg1, "MEMORIZING") == 0)            // print Memorising
	{
		if (bst->GetWordCnt() == 0)
		{
			cout << "== == == == ERROR == == == ==" << endl;
			cout << "700" << endl;
			cout << "== == == == == == == == == == == =" << endl;

			fout << "== == == == ERROR == == == ==" << endl;
			fout << "700" << endl;
			fout << "== == == == == == == == == == == =" << endl;

			fout.close();
			return false;
		}
		else
		{
			cout << "== == == == PRINT == == == ==" << endl;
			fout << "== == == == PRINT == == == ==" << endl;
			print = bst->Print(arg2);
			cout << "== == == == == == == == == == == =" << endl;
			fout << "== == == == == == == == == == == =" << endl;
		}
	}
	else if (strcmp(arg1, "MEMORIZED") == 0)            // print Memorised
	{
		if (cll->pHead == NULL)
		{
			cout << "== == == == ERROR == == == ==" << endl;
			cout << "700" << endl;
			cout << "== == == == == == == == == == == =" << endl;

			fout << "== == == == ERROR == == == ==" << endl;
			fout << "700" << endl;
			fout << "== == == == == == == == == == == =" << endl;

			fout.close();
			return false;
		}
		else
		{
			cout << "== == == == PRINT == == == ==" << endl;
			fout << "== == == == PRINT == == == ==" << endl;
			print = cll->Print();
			cout << "== == == == == == == == == == == =" << endl;
			fout << "== == == == == == == == == == == =" << endl;
		}
	}

	if (print == false)                              // Data Structure doesn't have words
	{
		cout << "== == == == ERROR == == == ==" << endl;
		cout << "700" << endl;
		cout << "== == == == == == == == == == == =" << endl;

		fout << "== == == == ERROR == == == ==" << endl;
		fout << "700" << endl;
		fout << "== == == == == == == == == == == =" << endl;

		fout.close();
		return false;
	}
	else
	{
		fout.close();
		return print;
	}
}
