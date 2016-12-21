#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"


Manager::Manager()                                      // constructor   
{
	cll = new CircularLinkedList;                       // dynamic allocation, initialization
	bst = new AlphabetBST;
	queue = new Queue;
	arg1 = new char[64];
	arg2 = new char[64];
}


Manager::~Manager()                                     // destructor
{ return;

	delete cll;
	delete bst;
	delete queue;

}

bool Manager::LOAD()                                     // LOAD                       
{
	char *ptr1 = NULL;                                   // Instance, initialization
	char *ptr2 = NULL;
	char temp1[64] = {};

	if (queue->GetpHead())                               // there is data , return 0
		return 0;
	if (bst->GetWordCnt())
		return 0;
	if (cll->pHead)
		return 0;
	ifstream fin1;
	fin1.open("to_memorize_word.txt");                   // there is no file, return 0
	if (!fin1) return 0;
	ifstream fin2;
	fin2.open("memorizing_word.txt");
	if (!fin2) return 0;
	ifstream fin3;
	fin3.open("memorized_word.txt");
	if (!fin3) return 0;

	fin1.getline(temp1, 64);                             // there is no word in file, return 0
	if (!strcmp(temp1, ""))
	{
		fin2.getline(temp1, 64);
		if (!strcmp(temp1, ""))
		{
			fin3.getline(temp1, 64);
			if (!strcmp(temp1, ""))
				fin1.close();
			fin2.close();
			fin3.close();
			return 0;
		}
	}
	fin1.seekg(ios_base::beg);
	fin2.seekg(ios_base::beg);
	fin3.seekg(ios_base::beg);

	while (!fin1.eof())                                  // read word in file
	{
		fin1.getline(temp1, 64);

		if (strcmp(temp1, ""))
		{
			ptr1 = strtok(temp1, "\t");
			ptr2 = strtok(NULL, "");

			if (!queue->Search(ptr1))                    // if there is no word in data structures, insert word
			{
				WordNode* newWordNode = new WordNode();
				newWordNode->SetWord(ptr1);
				newWordNode->SetMean(ptr2);
				queue->Push(newWordNode);
			}
		}
	}

	fin1.close();


	while (!fin2.eof())                                  // read word in file
	{
		fin2.getline(temp1, 64);

		if (strcmp(temp1, ""))
		{
			ptr1 = strtok(temp1, "\t");
			ptr2 = strtok(NULL, "");
			if (!bst->Search(ptr1[0])->GetBST()->Search(ptr1))           // if there is no word in data structures, insert word
			{
				WordNode* newWordNode = new WordNode();
				newWordNode->SetWord(ptr1);
				newWordNode->SetMean(ptr2);
				bst->Search(ptr1[0])->GetBST()->Insert(newWordNode);
				bst->GetWordCntPlus();
			}
		}
	}

	fin2.close();

	while (!fin3.eof())                                  // read word in file
	{
		fin3.getline(temp1, 64);

		if (strcmp(temp1, ""))
		{
			ptr1 = strtok(temp1, "\t");
			ptr2 = strtok(NULL, "");

			if (!cll->Search(ptr1))                                     // if there is no word in data structures, insert word
			{
				WordNode* newWordNode = new WordNode();
				newWordNode->SetWord(ptr1);
				newWordNode->SetMean(ptr2);
				if (!cll->Search(ptr1))
					cll->Insert(newWordNode);
			}
		}
	}
	fin3.close();

	return 1;
}

bool Manager::TEST()                                     // LOAD          
{
	WordNode * temp = new WordNode;
	if (bst->Search(arg1[0])->GetBST()->Search(arg1)) {               // Search word

		if (!strcmp(bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean(), arg2))               // If meaning is the same
		{
			temp = bst->Search(arg1[0])->GetBST()->Delete(arg1);
			cll->Insert(temp);
			return 1;
		}
	}
	return 0;
}

bool Manager::ADD()                                     // LOAD          
{
	char temp[64] = {};                                 // Instance, initialization
	char *ptr1 = NULL;
	char *ptr2 = NULL;

	ifstream fin;                                       // read word in file
	fin.open("word.txt");
	if (!fin)
		return 0;

	fin.getline(temp, 64);
	if (!strcmp(temp, ""))
		return 0;
	ptr1 = strtok(temp, "\t");
	ptr2 = strtok(NULL, "");

	if (!queue->Search(ptr1) && !cll->Search(ptr1) && !bst->Search(ptr1[0])->GetBST()->Search(ptr1))     // if there is not same word in data structures, Insert word

	{
		WordNode* newWordNode = new WordNode();
		newWordNode->SetWord(ptr1);
		newWordNode->SetMean(ptr2);
		queue->Push(newWordNode);
	}


	while (!fin.eof())
	{
		fin.getline(temp, 64);

		if (!strcmp(temp, ""))
			return 1;

		ptr1 = strtok(temp, "\t");
		ptr2 = strtok(NULL, "");

		if (!queue->Search(ptr1) && !cll->Search(ptr1) && !bst->Search(ptr1[0])->GetBST()->Search(ptr1))   // if there is not same word in data structures, Insert word
		{
			WordNode* newWordNode = new WordNode();
			newWordNode->SetWord(ptr1);
			newWordNode->SetMean(ptr2);
			queue->Push(newWordNode);
		}
	}

	fin.close();

	return 1;
}


bool Manager::UPDATE()                                     // UPDATE
{
	if (queue->Search(arg1))                                                          // if search word, update mean
	{
		ofstream fout; fout.open("log.txt", ios::app);
		fout << "======== UPDATE =======" << endl;
		cout << "======== UPDATE =======" << endl;
		fout << arg1 << " " << queue->Search(arg1)->GetMean() << " -> " << arg2 << endl;
		cout << arg1 << " " << queue->Search(arg1)->GetMean() << " -> " << arg2 << endl;
		queue->Search(arg1)->SetMean(arg2);
		cout << "=======================" << endl;
		fout << "=======================" << endl;
		fout.close();
		return 1;
	}
	if (bst->Search(arg1[0])->GetBST()->Search(arg1))                                 // if search word, update mean
	{
		ofstream fout; fout.open("log.txt", ios::app);
		fout << "======== UPDATE =======" << endl;
		cout << "======== UPDATE =======" << endl;
		fout << arg1 << " " << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean() << " -> " << arg2 << endl;
		cout << arg1 << " " << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean() << " -> " << arg2 << endl;
		bst->Search(arg1[0])->GetBST()->Search(arg1)->SetMean(arg2);
		fout << "=======================" << endl;
		cout << "=======================" << endl;
		fout.close();
		return 1;
	}

	if (cll->Search(arg1))                                                            // if search word, update mean
	{
		ofstream fout; fout.open("log.txt", ios::app);
		fout << "======== UPDATE =======" << endl;
		cout << "======== UPDATE =======" << endl;
		fout << arg1 << " " << cll->Search(arg1)->GetMean() << " -> " << arg2 << endl;
		cout << arg1 << " " << cll->Search(arg1)->GetMean() << " -> " << arg2 << endl;
		cll->Search(arg1)->SetMean(arg2);
		fout << "=======================" << endl;
		cout << "=======================" << endl;
		fout.close();
		return 1;
	}
	return 0;
}
bool Manager::SEARCH() {                                                              // SEARCH

	if (queue->Search(arg1))                                                          // if search word, print mean
	{
		ofstream fout; fout.open("log.txt", ios::app);
		fout << "======== SEARCH =======" << endl;
		cout << "======== SEARCH =======" << endl;
		fout << queue->Search(arg1)->GetWord() << " " << queue->Search(arg1)->GetMean() << endl;
		cout << queue->Search(arg1)->GetWord() << " " << queue->Search(arg1)->GetMean() << endl;
		fout << "=======================" << endl;
		cout << "=======================" << endl;
		fout.close();
		return 1;
	}
	if (bst->Search(arg1[0])->GetBST()->Search(arg1))                                  // if search word, print mean
	{
		ofstream fout; fout.open("log.txt", ios::app);
		fout << "======== SEARCH =======" << endl;
		cout << "======== SEARCH =======" << endl;
		fout << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetWord() << " " << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean() << endl;
		cout << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetWord() << " " << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean() << endl;
		fout << "=======================" << endl;
		cout << "=======================" << endl;
		fout.close();
		return 1;
	}

	if (cll->Search(arg1))                                                             // if search word, print mean
	{
		ofstream fout; fout.open("log.txt", ios::app);
		fout << "======== SEARCH =======" << endl;
		cout << "======== SEARCH =======" << endl;
		cout << cll->Search(arg1)->GetWord() << " " << cll->Search(arg1)->GetMean() << endl;
		fout << cll->Search(arg1)->GetWord() << " " << cll->Search(arg1)->GetMean() << endl;
		cout << "=======================" << endl;
		fout << "=======================" << endl;
		fout.close();
		return 1;
	}
	return 0;
}

bool Manager::MOVE()                                                                   // MOVE
{
	WordNode* temp = NULL;
	if (bst->GetWordCnt() + atoi(arg1) > 100) {                                        // when word is more than 100, return 0;
		return 0;
	}
	temp = queue->Pop();
	if (bst->GetWordCnt() >= 100) {
		return 0;
	}
	if (temp) {
		bst->Search(temp->GetWord()[0])->GetBST()->Insert(temp);
		bst->GetWordCntPlus();
		return 1;
	}
	else
		return 0;
}

void Manager::run(const char * command)                                                // run
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	char read[50] = {};                                                                // Instance, initialization
	char *ptr1 = NULL;
	char *ptr2 = NULL;
	int i = 0;
	ifstream fin;
	fin.open(command);                                                                 // read command

	if (!fin)
		return;

	while (!fin.eof()) {                                                               // Execute command 

		fin.getline(read, 50);
		ptr1 = strtok(read, " ");
		if (strcmp(ptr1, "LOAD") == 0) {
			if (!LOAD()) {
				ofstream fout; fout.open("log.txt", ios::app);
				fout << "======== ERROR ========" << endl;
				fout << "100" << endl;
				fout << "=======================" << endl;
				cout << "======== ERROR ========" << endl;
				cout << "100" << endl;
				cout << "=======================" << endl;
				fout.close();
			}
			else {
				ofstream fout; fout.open("log.txt", ios::app);
				fout << "======== LOAD =========" << endl;
				fout << "Success" << endl;
				fout << "=======================" << endl;
				cout << "======== LOAD =========" << endl;
				cout << "Success" << endl;
				cout << "=======================" << endl;
				fout.close();
			}
		}
		else if (strcmp(ptr1, "ADD") == 0) {
			if (!ADD()) {
				ofstream fout; fout.open("log.txt", ios::app);
				fout << "======== ERROR ========" << endl;
				fout << "200" << endl;
				fout << "=======================" << endl;
				cout << "======== ERROR ========" << endl;
				cout << "200" << endl;
				cout << "=======================" << endl;
				fout.close();
			}
			else {
				ofstream fout; fout.open("log.txt", ios::app);
				cout << "========= ADD =========" << endl;
				cout << "Success" << endl;
				cout << "=======================" << endl;
				fout.close();
			}
		}
		else if (strcmp(ptr1, "MOVE") == 0) {
			int count = 0;
			ptr1 = strtok(NULL, " ");
			arg1 = ptr1;
			for (i; i < atoi(ptr1); i++) {
				if (!MOVE()) {
					ofstream fout; fout.open("log.txt", ios::app);
					fout << "======== ERROR ========" << endl;
					fout << "300" << endl;
					fout << "=======================" << endl;
					cout << "======== ERROR ========" << endl;
					cout << "300" << endl;
					cout << "=======================" << endl;
					count++;
					fout.close();
					break;
				}
			}
			if (count == 0) {
				ofstream fout; fout.open("log.txt", ios::app);
				fout << "========= MOVE ========" << endl;
				fout << "Success" << endl;
				fout << "=======================" << endl;
				cout << "========= MOVE ========" << endl;
				cout << "Success" << endl;
				cout << "=======================" << endl;
				fout.close();
			}
		}
		else if (strcmp(ptr1, "SAVE") == 0) {
			if (!SAVE()) {
				ofstream fout; fout.open("log.txt", ios::app);
				fout << "======== ERROR ========" << endl;
				fout << "400" << endl;
				fout << "=======================" << endl;
				cout << "======== ERROR ========" << endl;
				cout << "400" << endl;
				cout << "=======================" << endl;
				fout.close();
			}
			else {
				ofstream fout; fout.open("log.txt", ios::app);
				fout << "======== SAVE ========" << endl;
				fout << "Success" << endl;
				fout << "=======================" << endl;
				cout << "======== SAVE ========" << endl;
				cout << "Success" << endl;
				cout << "=======================" << endl;
				fout.close();
			}
		}
		else if (strcmp(ptr1, "TEST") == 0) {
			ptr1 = strtok(NULL, " ");
			ptr2 = strtok(NULL, " ");
			strcpy(arg1, ptr1);
			strcpy(arg2, ptr2);
			Set(arg1);
			if (!TEST()) {
				ofstream fout; fout.open("log.txt", ios::app);
				fout << "======== ERROR ========" << endl;
				fout << "500" << endl;
				fout << "=======================" << endl;
				cout << "======== ERROR ========" << endl;
				cout << "500" << endl;
				cout << "=======================" << endl;
				fout.close();
			}
			else {
				ofstream fout; fout.open("log.txt", ios::app);
				fout << "======== TEST ========" << endl;
				fout << "Pass" << endl;
				fout << "=======================" << endl;
				cout << "======== TEST ========" << endl;
				cout << "Pass" << endl;
				cout << "=======================" << endl;
				fout.close();
			}
		}
		else if (strcmp(ptr1, "SEARCH") == 0) {
			ptr1 = strtok(NULL, " ");
			strcpy(arg1, ptr1);
			Set(arg1);
			if (!SEARCH()) {
				ofstream fout; fout.open("log.txt", ios::app);
				fout << "======== ERROR ========" << endl;
				fout << "600" << endl;
				fout << "=======================" << endl;
				cout << "======== ERROR ========" << endl;
				cout << "600" << endl;
				cout << "=======================" << endl;
				fout.close();
			}

		}
		else if (strcmp(ptr1, "PRINT") == 0) {
			ptr1 = strtok(NULL, " ");
			if (!strcmp(ptr1, "TO_MEMORIZE") || !strcmp(ptr1, "MEMORIZED")) {
				strcpy(arg1, ptr1);
				if (!PRINT()) {
					ofstream fout; fout.open("log.txt", ios::app);
					fout << "======== ERROR ========" << endl;
					fout << "700" << endl;
					fout << "=======================" << endl;
					cout << "======== ERROR ========" << endl;
					cout << "700" << endl;
					cout << "=======================" << endl;
					fout.close();
				}
			}
			else if (!strcmp(ptr1, "MEMORIZING"))
			{
				ptr2 = strtok(NULL, " ");
				strcpy(arg1, ptr1);
				strcpy(arg2, ptr2);
				if (!PRINT()) {
					ofstream fout; fout.open("log.txt", ios::app);
					fout << "======== ERROR ========" << endl;
					fout << "700" << endl;
					fout << "=======================" << endl;
					cout << "======== ERROR ========" << endl;
					cout << "700" << endl;
					cout << "=======================" << endl;
					fout.close();
				}
			}
		}
		else if (strcmp(ptr1, "UPDATE") == 0) {
			ptr1 = strtok(NULL, " ");
			ptr2 = strtok(NULL, " ");
			strcpy(arg1, ptr1);
			strcpy(arg2, ptr2);
			Set(arg1);
			if (!UPDATE()) {
				ofstream fout; fout.open("log.txt", ios::app);
				fout << "======== ERROR ========" << endl;
				fout << "800" << endl;
				fout << "=======================" << endl;
				cout << "======== ERROR ========" << endl;
				cout << "800" << endl;
				cout << "=======================" << endl;
				fout.close();
			}
		}
		else if (strcmp(ptr1, "EXIT") == 0) {
			return;
		}
		cout << endl;
		ofstream fout; fout.open("log.txt", ios::app);
		fout << endl;
		fout.close();
	}
	fin.close();
}
bool Manager::PRINT() {                                                              // PRINT

	if (strcmp(arg1, "TO_MEMORIZE") == 0) {                                          // PRINT TO_MEMORIZE
		if (queue->Print() == true) return true;
		else return false;
	}
	else if (strcmp(arg1, "MEMORIZING") == 0) {                                      // PRINT MEMORIZING
		if (bst->Print(arg2) == true) return true;

		else return false;
	}
	else if (strcmp(arg1, "MEMORIZED") == 0) {                                       // PRINT MEMORIZED
		if (cll->Print() == true) return true;
		else false;
	}
	return false;
}

bool Manager::SAVE() {                                                              // SAVE
   ofstream fin_2;
   fin_2.open("memorizing_word.txt");
   fin_2.close();
   char check = queue->Save() + bst->Save() + cll->Save();
   if (!check) {
      return 0;
   }
   return 1;
}

void Manager::Set(char* string) {                                                   // converts small letter
	int i = 0;
	char temp[32] = {};
	for (i; string[i] != NULL; i++) {
		if (string[i] >= 65 && string[i] <= 90) {
			string[i] = string[i] + 32;
		}
	}
}
