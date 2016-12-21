#include "/usr/local/Auto_Scoring_System/src/signal.h"
#pragma warning(disable:4996)

#include "Manager.h"
#include "stdlib.h"
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
	fout.open("log.txt", ios::app);
	if (!fout)
		return;

	char data[26] = { 'p','h','x','d','l','t','z','b','f','j','n','r','v','y','a','c','e','g','i','k','m','o','q','s','u','w' };   //Alphabet setting
	int i = 0;
	for (i = 0; i<26; i++) {
		//Loop bst insert letter in the alphabet
		AlphabetNode * temp = new AlphabetNode;
		temp->SetAlphabet(data[i]);
		bst->Insert(temp);
		
	}
	char data_command[32];
	char* token1 = NULL;
	char* token2 = NULL;
	char* token3 = NULL;
	ifstream fin;
	fin.open(command);

	if (!fin) {
		cout << "file is not open" << endl;      //when there is no file
		return;
	}
	while (fin.getline(data_command, 32)) {               //Loop end of the file
		   //Take line comes by
		token1 = strtok(data_command, " ");   //To distinguish the command seperate into token
		if (strcmp(token1, "LOAD") == 0) {      //when the LOAD instruction
			if (LOAD() == false) {            //Error message
				cout << "=======ERROR=======" << endl;
				cout << "100" << endl;
				cout << "===================" << endl;

				fout << "=======ERROR=======" << endl;
				fout << "100" << endl;
				fout << "===================" << endl;
			}

			else {                     //Success meassage
				cout << "=======LOAD=======" << endl;
				cout << "Success" << endl;
				cout << "==================" << endl;

				fout << "=======LOAD=======" << endl;
				fout << "Success" << endl;
				fout << "===================" << endl;
			}
		}

		else if (strcmp(token1, "ADD") == 0) {  
				 //when the ADD instruction
			if (ADD() == false) {            //Error message
				cout << "=======ERROR=======" << endl;
				cout << "200" << endl;
				cout << "===================" << endl;

				fout << "=======ERROR=======" << endl;
				fout << "200" << endl;
				fout << "===================" << endl;
			}



			else {                     //Success message
				cout << "=======ADD=======" << endl;
				cout << "Success" << endl;
				cout << "==================" << endl;

				fout << "=======ADD=======" << endl;
				fout << "Success" << endl;
				fout << "===================" << endl;

			}
		}
		else if (strcmp(token1, "MOVE") == 0) {   //when the MOVE instruction
			token2 = strtok(NULL, "");
			arg3 = atoi(token2);
			           //The number of move nodes
			if (MOVE() == false) {      //Error meassage
				cout << "=======ERROR=======" << endl;
				cout << "300" << endl;
				cout << "===================" << endl;

				fout << "=======ERROR=======" << endl;
				fout << "300" << endl;
				fout << "===================" << endl;
			}

			else {               //Success message
				cout << "=======MOVE=======" << endl;
				cout << "Success" << endl;
				cout << "==================" << endl;

				fout << "=======MOVE=======" << endl;
				fout << "Success" << endl;
				fout << "==================" << endl;
			}
		}

		else if (strcmp(token1, "SAVE") == 0) {   
    			//when the SAVE instruction
			if (SAVE() == false) {            //Error message
				printf("%s\n", token1);
				cout << "=======ERROR=======" << endl;
				cout << "400" << endl;
				cout << "===================" << endl;

				fout << "=======MOVE=======" << endl;
				fout << "Success" << endl;
				fout << "==================" << endl;
			}

			else {                     //Success message
				cout << "=======SAVE=======" << endl;
				cout << "Success" << endl;
				cout << "==================" << endl;

				fout << "=======SAVE=======" << endl;
				fout << "Success" << endl;
				fout << "==================" << endl;
			}
		}

		else if (strcmp(token1, "TEST") == 0) {   //when the TEST instruction
			token2 = strtok(NULL, "\t");
			token3 = strtok(NULL, "");

			arg1 = token2;      //To test word
			arg2 = token3;      //To test mean

			if (TEST() == false) {      //Error message
				cout << "=======ERROR=======" << endl;
				cout << "500" << endl;
				cout << "===================" << endl;

				fout << "=======ERROR=======" << endl;
				fout << "500" << endl;
				fout << "===================" << endl;
			}

			else {            //Pass message
				cout << "=======TEST=======" << endl;
				cout << "Pass" << endl;
				cout << "==================" << endl;

				fout << "=======TEST=======" << endl;
				fout << "Pass" << endl;
				fout << "==================" << endl;
			}
		}

		else if (strcmp(token1, "SEARCH") == 0) {   //when the SEARCH instruction
			token2 = strtok(NULL, "");

			arg1 = token2;      //To search word

			if (SEARCH() == false) {      //Error message
				cout << "=======ERROR=======" << endl;
				cout << "600" << endl;
				cout << "===================" << endl;

				fout << "=======ERROR=======" << endl;
				fout << "600" << endl;
				fout << "===================" << endl;
			}
		}

		else if (strcmp(token1, "PRINT") == 0) {  //when the PRINT instruction
			token2 = strtok(NULL, "\t");   //turn to "TO_MEMORIZE" or "MEMORIZING" or "MEMORIZED"
			token3 = strtok(NULL, "");   //you use any order

			if (strcmp(token2, "TO_MEMORIZE") == 0 || strcmp(token2, "MEMORIZED") == 0) {
				arg1 = token2; 
				if (PRINT() == false) {   //Error message
					cout << "=======ERROR=======" << endl;
					cout << "700" << endl;
					cout << "===================" << endl;

					fout << "=======ERROR=======" << endl;
					fout << "700" << endl;
					fout << "===================" << endl;
				}
			

			}

			else if (strcmp(token1, "MEMORIZING") == 0) {
				arg1 = token2;
				arg2 = token3;

				if (PRINT() == false) {   //Error message
					cout << "=======ERROR=======" << endl;
					cout << "700" << endl;
					cout << "===================" << endl;

					fout << "=======ERROR=======" << endl;
					fout << "700" << endl;
					fout << "===================" << endl;
				}
			}
		}

		else if (strcmp(token1, "UPDATE") == 0) {   //when the UPDATE instruction
			token2 = strtok(NULL, "\t");   // To search word
			token3 = strtok(NULL, "");   // Change the mean

			arg1 = token2;
			arg2 = token3;

			if (UPDATE() == false) {   //Error message
				cout << "=======ERROR=======" << endl;
				cout << "800" << endl;
				cout << "===================" << endl;

				fout << "=======ERROR=======" << endl;
				fout << "700" << endl;
				fout << "===================" << endl;
			}
		}

		else if (strcmp(token1, "EXIT") == 0)   //when the EXIT instruction
			{fin.close();
			return;}
	}
	
	fin.close();
}

bool Manager::LOAD() {
	WordNode* p = NULL;

	char data[50];
	char* word;
	char* mean;
	int cnt_q = 0;
	int cnt_b = 0;
	int cnt_c = 0;

	ifstream fin;
	fin.open("to_memorize_word.txt");

	if (!fin)      //when there is no file
	return false;

	while (1) {      //turn the loop end of file
		fin.getline(data, 50);   //It reads one line

		if (fin.getline(data, 50) == NULL)      //when there is no data
			break;

		word = strtok(data, "\t");
		mean = strtok(NULL, "");


		p = new WordNode();
		p->SetWord(word);
		p->SetMean(mean);
		queue->Push(p);      //queue Insert

		cnt_q++;
	}
	fin.close();

	fin.open("memorizing_word.txt");
	if (!fin)      //when there is no file
	return false;

	while (1) {      //turn the loop end of file
		fin.getline(data, 50);   //It reads one line

		if (fin.getline(data, 50) == NULL)      //when there is no data
			break;

		word = strtok(data, "\t");
		mean = strtok(NULL, "");

		p = new WordNode();
		p->SetWord(word);
		p->SetMean(mean);
		bst->Search(word[0])->GetBST()->Insert(p);   //bst insert

		cnt_b++;
	}
	fin.close();

	fin.open("memorized_word.txt");
	if (!fin)      //when there is no file
		return false;

	while (!fin.eof()) {      //turn the loop end of file
		fin.getline(data, 50);      //It reads one line
		if (fin.getline(data, 50) == NULL)      //when there is no data
			break;
		word = strtok(data, "\t");
		mean = strtok(NULL, "");


		p = new WordNode();
		p->SetWord(word);
		p->SetMean(mean);
		cll->Insert(p);      //Circular Linked-List insert

		cnt_c++;
	}

	fin.close();
	if (cnt_q != 0 || cnt_b != 0 || cnt_c != 0)   //If the load is untested
		return true;

	return false;
}

bool Manager::ADD() {
	WordNode* p;
	ifstream fin;
	fin.open("word");
	char data[32];
	char *token1;
	char *token2;

	if (!fin) {      //when there is no file
		return false;
	}
	while (1) {   //turn the loop end of file

		fin.getline(data, 32); //It reads one line

		if(fin.getline(data,32) == NULL)
			break;	

		token1 = strtok(data,"\t");
		token2 = strtok(NULL,"");
		
		
		if (token1 == NULL)   //when there is no data	
		return false;
			
		p = new WordNode();
		p->SetWord(token1);
		p->SetMean(token2);
		queue->Push(p);       //queue insert
	}	
	fin.close();
	return true;
}

bool Manager::MOVE() {
	WordNode* p = new WordNode;
	char* temp = NULL;
	int j, k = 0;
	
	if (queue->cnt() < arg3)   //Number of words in the queue < Number of words to move
		return false;

	for (k = 0; k<arg3; k++) {
		p = queue->Pop();
		temp = p->GetWord();
		bst->Search(temp[0])->GetBST()->Insert(p);   //It passes to the bst
	}
	
	return true;

}

bool Manager::SAVE() {
	if (queue->Save() == false)   //when it is not saved
		return false;

	else if (bst->Save() == false)
		return false;			

	else if (cll->Save() == false)
		return false;
	else
	return true;
}

bool Manager::TEST() {
	WordNode* p = new WordNode;

	if (bst->Search(arg1[0])->GetBST()->Search(arg1) == NULL)   //when there is not found the word
		return false;

	else {
		if (bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean() != arg2)   //when the word means not equal
			return false;

		else {
			p->SetWord(arg1);
			p->SetMean(arg2);
			cll->Insert(p);      //Because it passes the test, cll insert

			bst->Search(arg1[0])->GetBST()->Delete(arg1);   //Delete the words move from bst

			return true;
		}
	}
}

bool Manager::SEARCH() {
	ofstream fout;
	fout.open("log.txt", ios::app);

	if (!fout)
		return false;

	if (queue->Search(arg1)) {      //In case of queue
		cout << "=======SEARCH=======" << endl;
		cout << queue->Search(arg1)->GetWord() << " " << queue->Search(arg1)->GetMean() << endl;   //Print
		cout << "=====================" << endl;

		fout << "=======SEARCH=======" << endl;
		fout << queue->Search(arg1)->GetWord() << " " << queue->Search(arg1)->GetMean() << endl;   //Print
		fout << "=====================" << endl;

		return true;
	}

	else if (bst->Search(arg1[0])->GetBST()->Search(arg1)) {   //in case of bst
		cout << "=======SEARCH=======" << endl;
		cout << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetWord() << " " << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean() << endl;   //Print
		cout << "=====================" << endl;

		fout << "=======SEARCH=======" << endl;
		fout << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetWord() << " " << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean() << endl;   //Print
		fout << "=====================" << endl;
		return true;
	}

	else if (cll->Search(arg1)) {      //In case of cll
		cout << "=======SEARCH=======" << endl;
		cout << cll->Search(arg1)->GetWord() << " " << cll->Search(arg1)->GetMean() << endl;   //Print
		cout << "=====================" << endl;

		fout << "=======SEARCH=======" << endl;
		fout << cll->Search(arg1)->GetWord() << " " << cll->Search(arg1)->GetMean() << endl;   //Print
		fout << "=====================" << endl;
		return true;
	}

	return false;

}

bool Manager::PRINT() {
	ofstream fout;
	fout.open("log.txt", ios::app);
	if (fout == NULL)
	return false;
	
	if (strcmp(arg1, "TO_MEMORIZE") == 0) {   //in case of "TO_MEMORIZE"
		if (queue->Print() == '\0')   //when there is no output
			return false;

		cout << "=======PRINT=======" << endl;
		cout << queue->Print() << endl;         //Print
		cout << "===================" << endl;

		fout << "=======PRINT=======" << endl;
		fout << queue->Print() << endl;         //Print
		fout << "===================" << endl;
		return true;
	}

	else if (strcmp(arg1, "MEMORIZING") == 0) {   //In case of "MEMORIZING"
		if (bst->Print(arg2) == '\0')   //when there is no output
			return false;

		cout << "=======PRINT=======" << endl;
		cout << bst->Print(arg2) << endl;   //Print
		cout << "===================" << endl;

		fout << "=======PRINT=======" << endl;
		fout << bst->Print(arg2) << endl;   //Print
		fout << "===================" << endl;
		return true;
	}

	else if (strcmp(arg1, "MEMORIZED") == 0) {   //In case of "MEMORIZED"
		if (cll->Print() == '\0')   //when there is no output
			return false;

		cout << "=======PRINT=======" << endl;
		cout << cll->Print() << endl;      //Print
		cout << "===================" << endl;

		fout << "=======PRINT=======" << endl;
		fout << cll->Print() << endl;      //Print
		fout << "===================" << endl;
		return true;
	}

	return false;
}

bool Manager::UPDATE() {
	ofstream fout;
	fout.open("log.txt", ios::app);

	if (!fout)
		return false;

	if (queue->Search(arg1) != NULL) {      //In case of queue
		cout << "=======UPDATE=======" << endl;
		cout << queue->Search(arg1)->GetWord() << " " << queue->Search(arg1)->GetMean();   //Print

		fout << "=======UPDATE=======" << endl;
		fout << queue->Search(arg1)->GetWord() << " " << queue->Search(arg1)->GetMean();   //Print

		queue->Search(arg1)->SetMean(arg2);   //The update the mean of word

		cout << "->" << queue->Search(arg1)->GetMean() << endl;   //Print
		cout << "====================" << endl;

		fout << "->" << queue->Search(arg1)->GetMean() << endl;   //Print
		fout << "====================" << endl;
		return true;
	}

	if (bst->Search(arg1[0])->GetBST()->Search(arg1) != NULL) {   //In case of bst
		cout << "=======UPDATE=======" << endl;
		cout << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetWord() << " " << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean();   //Print

		fout << "=======UPDATE=======" << endl;
		fout << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetWord() << " " << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean();   //Print

		bst->Search(arg1[0])->GetBST()->Search(arg1)->SetMean(arg2);   //The update the mean of word

		cout << "->" << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean() << endl;   //Print
		cout << "====================" << endl;

		fout << "->" << bst->Search(arg1[0])->GetBST()->Search(arg1)->GetMean() << endl;   //Print
		fout << "====================" << endl;
		return true;
	}

	if (cll->Search(arg1) != NULL) {   //In case of cll
		cout << "=======UPDATE=======" << endl;
		cout << cll->Search(arg1)->GetWord() << " " << cll->Search(arg1)->GetMean() << endl;   //Print

		fout << "=======UPDATE=======" << endl;
		fout << cll->Search(arg1)->GetWord() << " " << cll->Search(arg1)->GetMean() << endl;   //Print

		cll->Search(arg1)->SetMean(arg2);   //The update the mean of word

		cout << "->" << cll->Search(arg1)->GetMean() << endl;   //Print
		cout << "====================" << endl;

		fout << "->" << cll->Search(arg1)->GetMean() << endl;   //Print
		fout << "====================" << endl;
		return true;
	}

	return false;
}
