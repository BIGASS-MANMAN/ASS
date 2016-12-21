#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include"Manager.h"
#include<fstream>
#include<iostream>
#include<cstring>
using namespace std;
int atoi(char const *c) {
	int num = 0;
	if (c == NULL) return 0;
	while (*c) {
		if (*c >= '0' && *c <= '9')
			num = (num * 10) + (*c) - '0';
		c++;
	}
	return num;
}
Manager::Manager()
{
	cll = new CircularLinkedList;
	queue = new Queue;
	bst = new AlphabetBST;


}
Manager::~Manager()
{ return;

	delete bst;
	delete queue;
	delete cll;
}
void Manager::run(const char *command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	ofstream flog;
	flog.open("log.txt", ios::app);
	char string[100][100];
	char FuncName[100][30];
	char c0[100][30],c1[100][30], c2[100][30];
	char *token;
	ifstream fin;
	fin.open(command);
	if (!fin) {
		cout << "file is not open" << endl;
		return;
	}
	int i = 0;
	while (fin) {
		fin.getline(string[i++], 100);
	}
	i--;
	for (int j = 0; j < i; j++) {
		token = strtok(string[j]," ");
		if(token)
		strcpy(FuncName[j],token);
		else
			strcpy(FuncName[j], NULL);

		token = strtok(NULL, " ");
		if (token)
			strcpy(c0[j], token);
		else
			c0[j][0] = 0;

		token=strtok(NULL, " ");
		if (token)
			strcpy(c1[j], token);
		else
			c1[j][0] = 0;

		token = strtok(NULL, " ");
		if (token)
			strcpy(c2[j], token);
		else
			c2[j][0] = 0;
	
	}
	for (int j = 0; j < i; j++) {
		if (!strcmp(FuncName[j], "LOAD")) {

			if (c0[j][0] != 0 || c1[j][0] != 0 || c2[j][0] != 0) {
				cout << "command is wrong" << endl;
				flog << "command is wrong" << endl;
			}
			else{

				LOAD();

}
		}
		else if (!strcmp(FuncName[j], "ADD")) {
			if (c0[j][0] != 0 || c1[j][0] != 0 || c2[j][0] != 0) {
				cout << "command is wrong" << endl;
				flog << "coomand is wrong" << endl;
			}
			else {
				if (ADD()) {
					cout << "======== ADD ========" << endl;
					cout << "Success" << endl;
					cout << "=====================\n" << endl;

					flog << "======== ADD ========" << endl;
					flog << "Success" << endl;
					flog << "=====================\n" << endl;
				}
				else {
					cout << "======== ERROR ========" << endl;
					cout << "200" << endl;
					cout << "=====================\n" << endl;

					flog << "======== ERROR ========" << endl;
					flog << "200" << endl;
					flog << "=====================\n" << endl;
				}
			}
		}
		else if (!strcmp(FuncName[j], "MOVE")) {
			if (c0[j][0] == 0 || c1[j][0] != 0 || c2[j][0] != 0) {
				cout << "command is wrong" << endl;
				flog << "command is wrong" << endl;
			}
			else {
				strcpy(command1, c0[j]);
				MOVE();
			}
		}
		else if (!strcmp(FuncName[j], "PRINT")) {
			if ((c0[j][0] == 0 || c2[j][0] != 0)) {
				cout << "command is wrong" << endl;
				flog << "command is wrong" << endl;
			}
			else {
				strcpy(command1, c0[j]);
				if (c1[j][0]!=0) {
					strcpy(command2, c1[j]);
				}
				PRINT();
			}
		}
		else if (!strcmp(FuncName[j], "UPDATE")) {
			if (c0[j][0] == 0 || c1[j][0] == 0 || c2[j][0] != 0) {
				cout << "command is wrong" << endl;
				flog << "command is wrong" << endl;
			}
			else {
				strcpy(command1, c0[j]);
				strcpy(command2, c1[j]);
				UPDATE();
			}
		}
		else if (!strcmp(FuncName[j], "SEARCH")) {
			if (c0[j][0] == 0 || c1[j][0] != 0 || c2[j][0] != 0) {
				cout << "command is wrong" << endl;
				flog << "command is wrong" << endl;
			}
			else {
				strcpy(command1, c0[j]);
				SEARCH();
			}
		}
		else if (!strcmp(FuncName[j], "TEST")) {
			if (c0[j][0] == 0 || c1[j][0] == 0 || c2[j][0] != 0) {
				cout << "command is wrong" << endl;
				flog << "command is wrong" << endl;
			}
			else {
				strcpy(command1, c0[j]);
				strcpy(command2, c1[j]);
				if (!TEST()) {
					cout << "======== ERROR ========" << endl;
					cout << "500" << endl;
					cout << "=====================\n" << endl;

					flog << "======== ERROR ========\n" << endl;
					flog << "500" << endl;
					flog << "=====================\n" << endl;
				}
			}
		}
		else if (!strcmp(FuncName[j], "SAVE")) {
			if (c0[j][0] != 0 || c1[j][0] != 0 || c2[j][0] != 0) {
				cout << "command is wrong" << endl;
				flog << "command is wrong" << endl;
			}
			else {
				SAVE();
			}
		}
		else if (!strcmp(FuncName[j], "EXIT")) {
			if (c0[j][0] != 0 || c1[j][0] != 0 || c2[j][0] != 0) {
				cout << "command is wrong" << endl;
				flog << "command is wrong" << endl;
			}
			else
				return;
		}
		else {
			cout << "command is wrong" << endl;
			flog << "command is wrong" << endl;
			flog.close();
			return;
		}
	}
	flog.close();
	return;
}
bool Manager::LOAD()
{
	
	ifstream fin1, fin2, fin3;
	ofstream flog;
	flog.open("log.txt", ios::app);
	fin1.open("to_memorize_word.txt"); // queue
	fin2.open("memorizing_word.txt"); // BST
	fin3.open("memorized_word.txt"); // Linked-list
	if (!fin1 || !fin2 || !fin3) {
		cout << "======== ERROR ========" << endl;
		cout << "100" << endl;
		cout << "=====================\n" << endl;
		flog << "======== ERROR ========\n100\n=====================\n"<<endl;
		fin1.close();
		fin2.close();
		fin3.close();
		flog.close();
		return 0;
	}
	int check = 0;
	int i = 0;
	char a;
	AlphabetNode* s = 0;
	WordNode* temp[300];
	char *context = 0;
	char *token=0;
	char *string=0;
	char *fword[300];
	char *fmean[300];
	while (1) {
		string = new char[60];
		fmean[i] = new char[30];
		fword[i] = new char[30];
		fin1.getline(string, 60);
		token = strtok_r(string, " ", &context);
		if (!token)
			break;
		strcpy(fword[i], token);
		token = strtok_r(NULL, " ", &context);
if(!token)
			break;
		strcpy(fmean[i], token);
		temp[i] = new WordNode;
		temp[i]->SetWord(fword[i]);
		temp[i]->SetMean(fmean[i]);
		a = fword[i][0];
		if (a >= 97 && a <= 122)
			a = a - 32;
		else if (!(a >= 65 && a <= 90))
			return 0;
		s = bst->Search(a);
		if (!cll->Search(fword[i]) && !s->GetWordBST()->Search(temp[i]->GetWord()) && !queue->Search(fword[i]))
		queue->Push(temp[i]);
		i++;
		delete[] string;
	}
	while (1) {		
		string = new char[60];
		fmean[i] = new char[30];
		fword[i] = new char[30];
		temp[i] = new WordNode;
		fin2.getline(string, 60);
		if (string == 0)
			break;
		token = strtok_r(string, " ", &context);
		if (!token)
			break;
		strcpy(fword[i], token);
		token = strtok_r(NULL, " ", &context);
if(!token)
			break;
		strcpy(fmean[i], token);
		temp[i] = new WordNode;
		temp[i]->SetWord(fword[i]);
		temp[i]->SetMean(fmean[i]);
		a = fword[i][0];
		if (a >= 97 && a <= 122)
			a = a - 32;
		else if (!(a >= 65 && a <= 90))
			return 0;
		s = bst->Search(a);
		if (s != NULL) {
			if (bst->WordCnt < 100) {
				if (!cll->Search(fword[i]) && !s->GetWordBST()->Search(temp[i]->GetWord()) && !queue->Search(fword[i]))
				{
					s->GetWordBST()->Insert(temp[i]);
					bst->WordCnt++;
				}
				else {
					cout << "======== ERROR ========" << endl;
					cout << "100" << endl;
					cout << "=====================\n" << endl;
					flog << "======== ERROR ========\n100\n=====================\n" << endl;
					fin1.close();
					fin2.close();
					fin3.close();
					flog.close();
					return 0;
				}
			}
			else {
				cout << "======== ERROR ========" << endl;
				cout << "100" << endl;
				cout << "=====================\n" << endl;
				flog << "======== ERROR ========\n100\n=====================\n" << endl;
				fin1.close();
				fin2.close();
				fin3.close();
				flog.close();
				return 0;
			}
			}
		i++;
		delete[] string;
	}
	while (1) {
		string = new char[60];
		fmean[i] = new char[30];
		fword[i] = new char[30];
		temp[i] = new WordNode;
		fin3.getline(string, 60);
		if (string == 0)
			break;
		token = strtok_r(string, " ", &context);
		if (!token)
			break;
		strcpy(fword[i], token);
		token = strtok_r(NULL, " ", &context);
		if(!token)
			break;
		strcpy(fmean[i], token);
		temp[i] = new WordNode;
		temp[i]->SetWord(fword[i]);
		temp[i]->SetMean(fmean[i]);
		a = fword[i][0];
		if (a >= 97 && a <= 122)
			a = a - 32;
		else if (!(a >= 65 && a <= 90))
			return 0;
		s = bst->Search(a);
		if(!cll->Search(fword[i]) && !s->GetWordBST()->Search(temp[i]->GetWord()) && !queue->Search(fword[i]))
		cll->Insert(temp[i]);
		delete string;
		i++;
	}
	cout << "======== LOAD ========" << endl;
	cout << "Success" << endl;
	cout << "=====================\n" << endl;
	flog << "======== LOAD ========\nSuccess\n=====================\n" << endl;
	fin1.close();
	fin2.close();
	fin3.close();
	return 1;
}

bool Manager::ADD()
{
	ifstream fin;
	fstream fout;
	ifstream fin1;
	fin.open("word.txt");
	if (!fin) {
		fout.close();
		return 0;
	}
	fout.open("to_memorize_word.txt");
	if(!fout) {
		fin.close();
		return 0;
	}
	int check = 0, check_same=0;
	char *context = 0;
	char *token = 0;
	char *string;
	char *fword;
	char *fmean;
	char temp[100];
	char temp1[100];
	while (!fin.eof()) {
		string = new char[200];
		fword = new char[100];
		fmean = new char[100];
		fin.getline(string, 60);
		strcpy(temp, string);
		token=strtok_r(string, " ", &context);
		if (token) 
			strcpy(fword, token);
		token = strtok_r(NULL, " ", &context);
		if (token) {
			strcpy(fmean, token);
			check++;
		}
		fin1.open("to_memorize_word.txt");
		if (!fin1) {
			fin1.close();
			return 0;
		}
		while (!fin1.eof()) {
			fin1.getline(temp1, 60);
			if (strcmp(temp1, temp) == 0)
				check_same = 1;
		}
		fin1.close();
		if (check_same == 0) {
			fout << fword << " " << fmean << endl;
		}
		else
			check_same = 0;
		delete[] string;
		delete[] fword;
		delete[] fmean;
	}
	if (check == 0) {
		fin.close();
		fout.close();
		return 0;
	}
	fin.close();
	fout.close();
	return 1;
}

bool Manager::MOVE()
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	int word_num = atoi(command1);
	if ((bst->WordCnt + word_num) > 100) {
		cout << "======== ERROR ========" << endl;
		cout << "300" << endl;
		cout << "=====================\n" << endl;
		flog << "======== ERROR ========\n300\n=====================\n" << endl;
		flog.close();
		return 0;
	}
	if (queue->IsEmpty()) {
		cout << "======== ERROR ========" << endl;
		cout << "300" << endl;
		cout << "=====================\n" << endl;
		flog << "======== ERROR ========\n300\n=====================\n" << endl;
		flog.close();
		return 0;
	}
	if (queue->CountNode() < word_num) {
		cout << "======== ERROR ========" << endl;
		cout << "300" << endl;
		cout << "=====================\n" << endl;
		flog << "======== ERROR ========\n300\n=====================\n" << endl;
		flog.close();
		return 0;
	}
	WordNode* temp = 0;
	AlphabetNode* temp1 = 0;
	char a;
	char *word;
	for (int i = 0; i < word_num; i++)
	{
		temp = queue->Pop();
		word = temp->GetWord();
		a = word[0];
		if (a >= 97 && a <= 122)
			a = a - 32;
		else if (!(a >= 65 && a <= 90))
			return 0;
		temp1 = bst->Search(a);
		temp1->GetBST()->Insert(temp);
	}
	cout << "======== MOVE ========" << endl;
	cout << "Success" << endl;
	cout << "=====================\n" << endl;
	flog << "======== MOVE ========\nSuccess\n=====================\n" << endl;
	flog.close();
	return 1;
}


bool Manager::SAVE()
{
	ofstream flog;
	flog.open("log.txt",ios::app);
	if (!queue->Save() || !cll->Save() || !bst->Save()) {
		cout << "======== ERROR ========" << endl;
		cout << "400" << endl;
		cout << "=====================\n" << endl;
		flog << "======== ERROR ========\n400\n=====================\n" << endl;
		flog.close();
		return 0;
	}
	else {
		cout << "======== SAVE ========" << endl;
		cout << "Success" << endl;
		cout << "=====================" << endl;
		flog << "======== SAVE ========\nSuccess\n=====================\n" << endl;
		flog.close();
		return 1;
	}
}

bool Manager::TEST()
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	char a = command1[0];
	AlphabetNode* temp = 0;
	WordNode* temp1 = 0;
	if (a >= 97 && a <= 122)
		a = a - 32;
	else if(!(a>=65 && a<=90))
		return 0;
	temp = bst->Search(a);
	if (!temp)
		return 0;
	temp1 = temp->GetBST()->Search(command1);
	if (!temp1)
		return 0;
	if (strcmp(temp1->GetMean(), command2))
		return 0;
		cll->Insert(temp1);
		temp->GetBST()->Delete(temp1->GetWord());
		cout << "======== TEST ========" << endl;
		cout << "pass" << endl;
		cout << "=====================\n" << endl;
		flog << "======== TEST ========\npass\n=====================\n" << endl;
		flog.close();
	return 1;
}

bool Manager::SEARCH()
{
	ofstream flog;
	flog.open("log.txt",ios::app);
	char a = command1[0];
if (a >= 97 && a <= 122)
			a = a - 32;
else if (!(a >= 65 && a <= 90))
return 0;
	WordNode* temp_q = queue->Search(command1);
	AlphabetNode* temp_b = bst->Search(a);
	WordNode* temp_b1;
	WordNode* temp_c = cll->Search(command1);
	if (temp_q) {
		if (!strcmp(temp_q->GetWord(), command1)) {
			cout << "======== SEARCH ========" << endl;
			cout << temp_q->GetWord() << " " << temp_q->GetMean() << endl;
			cout << "=======================\n" << endl;
			flog << "======== SEARCH ========" << endl;
			flog << temp_q->GetWord() << " " << temp_q->GetMean() << endl;
			flog<< "=====================\n" << endl;
			flog.close();
			return 1;
		}
	}
	if (temp_b) {
		temp_b1 = temp_b->GetBST()->Search(command1);
		if (temp_b1) {
			if (!strcmp(temp_b1->GetWord(), command1)) {
				cout << "======== SEARCH ========" << endl;
				cout << temp_b1->GetWord() << " " << temp_b1->GetMean() << endl;
				cout << "=======================\n" << endl;
				flog << "======== SEARCH ========" << endl;
				flog << temp_b1->GetWord() << " " << temp_b1->GetMean() << endl;
				flog << "=====================\n" << endl;
				flog.close();
				return 1;
			}
		}
	}
	if (temp_c) {
		if (!strcmp(temp_c->GetWord(), command1)) {
			cout << "======== SEARCH ========" << endl;
			cout << temp_c->GetWord() << " " << temp_c->GetMean() << endl;
			cout << "=======================\n" << endl;
			flog << "======== SEARCH ========" << endl;
			flog << temp_c->GetWord() << " " << temp_c->GetMean() << endl;
			flog << "=====================\n" << endl;
			flog.close();
			return 1;
		}
	}
		cout << "======== ERROR ========" << endl;
		cout << "600" << endl;
		cout << "=======================\n" << endl;
		flog << "======== ERROR ========\n600\n=====================\n" << endl;
		flog.close();
	return 0;
}

bool Manager::PRINT()
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	if (!strcmp(command1, "TO_MEMORIZE")) {
		if (!queue->Print()) {
			cout << "======== ERROR ========" << endl;
			cout << "700" << endl;
			cout << "=======================\n" << endl;
			flog << "======== ERROR ========\n700\n=====================\n" << endl;
		}
	}
	else if (!strcmp(command1, "MEMORIZING")) {
		if (!bst->Print(command2)) {
			cout << "======== ERROR ========" << endl;
			cout << "700" << endl;
			cout << "=======================\n" << endl;
			flog << "======== ERROR ========\n700\n=====================\n" << endl;
		}
	}
	else if (!strcmp(command1, "MEMORIZED")) {
		if (!cll->Print()) {
			cout << "======== ERROR ========" << endl;
			cout << "700" << endl;
			cout << "=======================\n" << endl;
			flog << "======== ERROR ========\n700\n=====================\n" << endl;
		}
	}
	flog.close();
	return 1;
}

bool Manager::UPDATE()
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	char a = command1[0];
	if (a >= 97 && a <= 122)
		a = a - 32;
	else if (!(a >= 65 && a <= 90))
		return 0;
	char *mean;
	char temp[100];
	mean = new char[30];
	strcpy(mean, command2);
	WordNode* temp_q = queue->Search(command1);
	AlphabetNode* temp_b = bst->Search(a);
	WordNode* temp_b1;
	WordNode* temp_c = cll->Search(command1);
	if (temp_q) {
		strcpy(temp,temp_q->GetMean());
		temp_q->SetMean(mean);
		cout << "======== UPDATE ========" << endl;
		cout << temp_q->GetWord() << " " << temp<< " -> " << command2<< endl;
		cout << "=======================\n" << endl;
		flog << "======== UPDATE ========" << endl;
		flog << temp_q->GetWord() << " " << temp<<" -> "<<command2<< endl;
		flog << "=====================\n" << endl;
		flog.close();
		return 1;
	}
	if (temp_c) {
		temp_c->SetMean(mean);
		cout << "======== UPDATE ========" << endl;
		cout << temp_c->GetWord() << " " << temp_c->GetMean() << " -> " << command2 << endl;
		cout << "=======================\n" << endl;

		flog << "======== UPDATE ========" << endl;
		flog << temp_c->GetWord() << " " << temp_c->GetMean() << " -> " << command2 << endl;
		flog << "=====================\n" << endl;
		flog.close();
		return 1;
	}
	if (temp_b) {
		temp_b1 = temp_b->GetBST()->Search(command1);
		if (temp_b1) {
			temp_b1->SetMean(mean);
			cout << "======== UPDATE ========" << endl;
			cout << temp_b1->GetWord() << " " << temp_b1->GetMean() << " -> " << command2 << endl;
			cout << "=======================\n" << endl;

			flog << "======== UPDATE ========" << endl;
			flog << temp_b1->GetWord() << " " << temp_b1->GetMean() << " -> " << command2 << endl;
			flog << "=====================\n" << endl;
			flog.close();
			return 1;
		}
	}
	cout << "======== ERROR ========" << endl;
	cout << "800" << endl;
	cout << "=======================\n" << endl;
	flog << "======== ERROR ========\n800\n=====================\n" << endl;
	flog.close();
	return 0;
}
