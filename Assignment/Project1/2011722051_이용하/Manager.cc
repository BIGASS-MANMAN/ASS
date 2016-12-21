#include "/usr/local/Auto_Scoring_System/src/signal.h"
#pragma warning (disable : 4996)
#include "Manager.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

Manager::Manager()
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
	sig = 0;
}


Manager::~Manager()
{ return;

	delete cll;
	delete bst;
	delete queue;
}

void Manager::run(const char * command) // ifstream fin; fin.open(command); // and read all line
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	ifstream fin;
	ofstream log;
	char str[100];
	char * context = NULL;
	char * token, * token2;
	int num;
	char alphabet_arr[26] = { 'p','h','x','d','l','t','z','b','f','j','n','r','v','y','a','c','e','g','i','k','m','o','q','s','u','w' };
	
	AlphabetNode * al_node = new AlphabetNode;
	for (int alp = 0; alp < 26; alp++) // Alphabet Node setting
	{
		al_node->SetAlphabet(alphabet_arr[alp]); // alphabet
		bst->Insert(al_node); // insert alphabet node
	}

	fin.open(command); // command.txt open
	log.open("log.txt", ios::app); // log.txt open

	while (!fin.eof())
	{
		fin.getline(str, 100);
		token = strtok_r(str, " ", &context);
		if (strcmp(token, "LOAD") == 0) // LOAD
		{
			token = strtok_r('\0', " ", &context);
			if (token == '\0')
				LOAD();
			else // error code
			{
				cout << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
				log << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
			}		
		}
			
		else if (strcmp(token, "ADD") == 0) // ADD
		{
			token = strtok_r('\0', " ", &context);
			if (token == '\0')
				ADD();
			else // error code
			{
				cout << "======= ERROR ========" << endl << "200" << endl << "======================" << endl << endl;
				log << "======= ERROR ========" << endl << "200" << endl << "======================" << endl << endl;
			}
		}
			
		else if (strcmp(token, "PRINT") == 0) // PRINT
		{
			token = strtok_r('\0', " ", &context);
			if (strcmp(token, "TO_MEMORIZE") == 0) // QUEUE
			{
				token = strtok_r('\0', " ", &context);
				if (token != '\0') // error code
				{
					cout << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
					log << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
				}
				else // token == NULL
					PRINT("TO_MEMORIZE", token);
			}
			else if (strcmp(token, "MEMORIZED") == 0) // Circular Linkedlist
			{
				token = strtok_r('\0', " ", &context);
				if (token != '\0') // error code
				{
					cout << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
					log << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
				}
				else
					PRINT("MEMORIZED", token); // token == NULL
			}
			else if (strcmp(token, "MEMORIZING") == 0) // BST
			{
				token = strtok_r('\0', " ", &context);
				if (token == '\0') // error code
				{
					cout << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
					log << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
				}
				else
					PRINT("MEMORIZING", token); // token == order
			}
			else // error code
			{
				cout << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
				log << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
			}
		}

		else if (strcmp(token, "MOVE") == 0) // MOVE
		{
			token = strtok_r('\0', " ", &context);
			if (token == '\0') // error code
			{
				cout << "======= ERROR ========" << endl << "300" << endl << "======================" << endl << endl;
				log << "======= ERROR ========" << endl << "300" << endl << "======================" << endl << endl;
			}
			else // token == number
			{
				num = atoi(token); // change to integer numbers
				MOVE(num);
			}
		}

		else if (strcmp(token, "TEST") == 0) // TEST
		{
			token = strtok_r('\0', " ", &context); // token == word
			token2 = strtok_r('\0', " ", &context); // token2 == mean
			TEST(token, token2);
		}

		else if (strcmp(token, "SEARCH") == 0) // SEARCH
		{
			token = strtok_r('\0', " ", &context); // token == word
			SEARCH(token);
		}

		else if (strcmp(token, "UPDATE") == 0) // UPDATE
		{
			token = strtok_r('\0', " ", &context); // token == word
			token2 = strtok_r('\0', " ", &context); // token2 == mean
			UPDATE(token, token2);
		}

		else if (strcmp(token, "SAVE") == 0) // SAVE
		{
			token = strtok_r('\0', " ", &context);
			if (token == '\0')
				SAVE();
			else // error code
			{
				cout << "======= ERROR ========" << endl << "400" << endl << "======================" << endl << endl;
				log << "======= ERROR ========" << endl << "400" << endl << "======================" << endl << endl;
			}
		}

		else if (strcmp(token, "EXIT") == 0) // EXIT
		{
			log.close(); // log.txt close
			return;
		}
	}
}

bool Manager::LOAD()
{
	WordNode * node = new WordNode;
	WordBST * wordbst = new WordBST;
	ifstream fin1, fin2, fin3;
	ofstream log;
	log.open("log.txt", ios::app); // log.txt open
	if (sig == 0) // signal
		sig = 1;
	else
	{
		cout << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log.close();
		return 0;
	}
	/////////////////////////// queue //////////////////////////////
	fin1.open("to_memorize_word.txt"); // open to_memorize_word.txt
	if (fin1.fail()) // no file - ERROR
	{
		cout << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log.close();
		return 0;
	}
	char read[500][100] = { '\0' }, word[500][100] = { '\0' }, mean[500][100] = { '\0' };
	char read2[500][100] = { '\0' }, word2[500][100] = { '\0' }, mean2[500][100] = { '\0' };
	char read3[500][100] = { '\0' }, word3[500][100] = { '\0' }, mean3[500][100] = { '\0' };
	int cnt = 0, i, j;
	char alphabet;

	while (!fin1.eof())
	{
		fin1.getline(read[cnt], 100); // read line
		if (read[0][0] == '\0') // no data in the text file
			break;
		else if(read[cnt][0]=='\0') // end of file
			break;
		for (i = 0; read[cnt][i] != '\t'; i++) // store word
			word[cnt][i] = read[cnt][i];
		word[cnt][i] = '\0'; // add NULL
		for (i = i + 1, j = 0; read[cnt][i] != '\0'; i++, j++) // store mean
			mean[cnt][j] = read[cnt][i];
		mean[cnt][j] = '\0'; // add NULL
		cnt++;
	}

	if (queue->Print() != 0) // data is already exist in the Queue - ERROR
	{
		cout << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log.close();
		return 0;
	}

	for (i = 0; i < cnt; i++)
	{
		if (queue->Search(word[i]) == '\0') // prevent duplication
		{
			node->SetWord(word[i]); // insert word
			node->SetMean(mean[i]); // insert mean
			queue->Push(node); // insert node
		}
	}
	fin1.close(); // file close
	/////////////////////////// queue //////////////////////////////

	//////////////////////////// BST ///////////////////////////////
	fin2.open("memorizing_word.txt"); // open memorizing_word.txt
	if (fin2.fail()) // no file - ERROR
	{
		cout << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log.close();
		return 0;
	}
	cnt = 0, i = 0, j = 0;

	while (!fin2.eof())
	{
		fin2.getline(read2[cnt], 100); // read line
		if (read2[0][0] == '\0') // no data in the text file
			break;
		else if(read2[cnt][0]=='\0')
			break;
		for (i = 0; read2[cnt][i] != '\t'; i++) // store word
			word2[cnt][i] = read2[cnt][i];
		word2[cnt][i] = '\0'; // add NULL
		for (i = i + 1, j = 0; read2[cnt][i] != '\0'; i++, j++) // store mean
			mean2[cnt][j] = read2[cnt][i];
		mean2[cnt][j] = '\0'; // add NULL
		cnt++;
	}
	
	for (i = 0; i < cnt; i++)
	{
		alphabet = word2[i][0]; // first alphabet of word
		if (bst->Search(alphabet)->GetBST()->Search(word[i]) == '\0') // prevent duplication
		{
			node->SetWord(word2[i]); // insert word
			node->SetMean(mean2[i]); // insert mean
			bst->Search(alphabet)->GetBST()->Insert(node); // insert node
		}
	}
	fin2.close(); // file close
	//////////////////////////// BST ///////////////////////////////

	//////////////////// circular linkedlist ///////////////////////
	fin3.open("memorized_word.txt"); // open memorized_word.txt
	if (fin3.fail()) // no file - ERROR
	{
		cout << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log.close();
		return 0;
	}
	
	cnt = 0, i = 0, j = 0;

	while (!fin3.eof())
	{
		fin3.getline(read3[cnt], 100); // read line
		if (read3[0][0] == '\0') // no data in the text file
			break;
		else if(read3[cnt][0]=='\0')
			break;
		for (i = 0; read3[cnt][i] != '\t'; i++) // store word
			word3[cnt][i] = read3[cnt][i];
		word3[cnt][i] = '\0'; // add NULL
		for (i = i + 1, j = 0; read3[cnt][i] != '\0'; i++, j++) // store mean
			mean3[cnt][j] = read3[cnt][i];
		mean3[cnt][j] = '\0'; // add NULL
		cnt++;
	}

	if (cll->Print() != 0) // data is already exist in the CLL - ERROR
	{
		cout << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "100" << endl << "======================" << endl << endl;
		log.close();
		return 0;
	}

	for (i = 0; i < cnt; i++)
	{
		if (cll->Search(word[i]) == '\0') // prevent duplication
		{
			node->SetWord(word3[i]); // insert word
			node->SetMean(mean3[i]); // insert mean
			cll->Insert(node); // insert node
		}
	}
	fin3.close(); // file close
	//////////////////// circular linkedlist ///////////////////////

	cout << "======== LOAD ========" << endl << "Success" << endl << "======================" << endl << endl;
	log << "======== LOAD ========" << endl << "Success" << endl << "======================" << endl << endl;

	log.close(); // log.txt close
	return 1;
}

bool Manager::ADD()
{
	WordNode * node = new WordNode;
	ifstream fin;
	ofstream log;
	log.open("log.txt", ios::app); // log.txt open
	fin.open("word.txt"); // open "word.txt"
	if (fin.fail()) // no file - ERROR
	{
		cout << "======= ERROR ========" << endl << "200" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "200" << endl << "======================" << endl << endl;
		log.close();
		return 0;
	}
		
	char text[500][100];
	char word0[500][100], mean0[500][100];
	int cnt = 0, i, j;

	while (!fin.eof())
	{
		fin.getline(text[cnt], 500); // read line
		if (text[0][0] == '\0') // no word in the "word.txt" - ERROR
		{
			cout << "======= ERROR ========" << endl << "200" << endl << "======================" << endl << endl;
			log << "======= ERROR ========" << endl << "200" << endl << "======================" << endl << endl;
			log.close();
			return 0;
		}
		else if(text[cnt][0]=='\0')
			break;
		for (i = 0; text[cnt][i] != '\t'; i++) // store word
			word0[cnt][i] = text[cnt][i];
		word0[cnt][i] = '\0'; // add NULL
		for (i = i + 1, j = 0; text[cnt][i] != '\0'; i++, j++) // store mean
			mean0[cnt][j] = text[cnt][i];
		mean0[cnt][j] = '\0'; // add NULL

		cnt++;
	}

	for (i = 0; i < cnt; i++)
	{
		if (queue->Search(word0[i]) == '\0') // prevent duplication
		{
			node->SetWord(word0[i]); // insert word
			node->SetMean(mean0[i]); // insert mean
			queue->Push(node); // insert node
		}
	}

	cout << "======== ADD ========" << endl << "Success" << endl << "======================" << endl << endl;
	log << "======== ADD ========" << endl << "Success" << endl << "======================" << endl << endl;
	fin.close(); // close word.txt
	log.close(); // close log file
	return 1;
}

bool Manager::PRINT(char * arg1, char * arg2)
{
	ofstream log;
	log.open("log.txt", ios::app); // log.txt open
	if (strcmp(arg1, "TO_MEMORIZE") == 0) // QUEUE
	{
		if (queue->pHead == 0) // no data in the QUEUE
		{
			cout << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
			log << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
		}
		else // print QUEUE
		{
			cout << "======= PRINT ========" << endl;
			log << "======= PRINT ========" << endl;
			queue->Print();
			cout << "======================" << endl << endl;
			log << "======================" << endl << endl;
		}
	}	
	
	else if (strcmp(arg1, "MEMORIZED") == 0) // Circular Linkedlist
	{
		if (cll->pHead == 0) // no data in the Circular Linkedlist
		{
			cout << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
			log << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
		}
			
		else // print Circular Linkedlist
		{
			cout << "======= PRINT ========" << endl;
			log << "======= PRINT ========" << endl;
			cll->Print();
			cout << "======================" << endl << endl;
			log << "======================" << endl << endl;
		}
	}
		
	else if (strcmp(arg1, "MEMORIZING") == 0) // BST
	{
		if (bst->NULL_BST() == 0) // no word data in the bst
		{
			cout << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
			log << "======= ERROR ========" << endl << "700" << endl << "======================" << endl << endl;
		}
			
		else // print bst
		{
			cout << "======= PRINT ========" << endl;
			log << "======= PRINT ========" << endl;
			bst->Print(arg2);
			cout << "======================" << endl << endl;
			log << "======================" << endl << endl;
		}
	}
	log.close(); // close log file
	return 1;
}

bool Manager::MOVE(int num)
{
	ofstream log;
	log.open("log.txt", ios::app); // log.txt open
	WordNode * move;
	bst->SetWordCount();
	if (num < 0) // negative number
	{
		cout << "======= ERROR ========" << endl << "300" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "300" << endl << "======================" << endl << endl;
	}
	else if (num + bst->WordCnt > 100) // over 100 words
	{
		cout << "======= ERROR ========" << endl << "300" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "300" << endl << "======================" << endl << endl;
	}
	else if (num > queue->GetWordCount()) // input number is bigger than queue words
	{
		cout << "======= ERROR ========" << endl << "300" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "300" << endl << "======================" << endl << endl;
	}
	else if (queue->GetWordCount() == 0) // no word in the queue
	{
		cout << "======= ERROR ========" << endl << "300" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "300" << endl << "======================" << endl << endl;
	}
	else // SUCCESS
	{
		for (int i = 0; i<num; i++)
		{
			move = queue->Pop(); // pop in the queue
			bst->Search(move->GetWord()[0])->GetBST()->Insert(move); // insert node
		}
		cout << "======== MOVE ========" << endl << "Success" << endl << "======================" << endl << endl;
		log << "======== MOVE ========" << endl << "Success" << endl << "======================" << endl << endl;
		log.close(); // close log file
		return 1;
	}
	log.close(); // close log file
	return 0;
}

bool Manager::SAVE()
{
	ifstream fin;
	ofstream fclear;
	fin.open("memorizing_word.txt"); // open memorizing_word
	fclear.open("memorizing_word.txt"); // open memorizing_word
	fclear << ""; // clear the text file
	fin.close(); // close file
	fclear.close(); // close file

	ofstream log;
	log.open("log.txt", ios::app); // log.txt open
	
	int n1 = 0, n2 = 0, n3 = 0;
	n1 = queue->Save(); // queue save
	n2 = cll->Save(); // cll save
	n3 = bst->NULL_BST(); // check bst
	bst->Save(); // bst save
	if (n1 == 0 || n2 == 0 || n3 == 0) // no datae in the queue or bst or cll
	{
		cout << "======= ERROR ========" << endl << "400" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "400" << endl << "======================" << endl << endl;
		log.close(); // close log file
		return 0;
	}
	else // SUCCESS - data in the queue,bst,cll
	{
		cout << "======== SAVE ========" << endl << "Success" << endl << "======================" << endl << endl;
		log << "======== SAVE ========" << endl << "Success" << endl << "======================" << endl << endl;
		log.close(); // close log file
		return 1;
	}
}

bool Manager::TEST(char * arg1, char * arg2)
{
	ofstream log;
	log.open("log.txt", ios::app); // log.txt open
	WordNode * test;
	WordNode * give;
	char alp_temp;
	if (arg1[0] >= 65 && arg1[0] <= 90) // A~Z
		alp_temp = arg1[0] + 32; // a~z
	else
		alp_temp = arg1[0];
	test = bst->Search(alp_temp)->GetBST()->Search(arg1); // find word in the MEMORIZING
	if (test == '\0') // no word in the MEMORIZING
	{
		cout << "======= ERROR ========" << endl << "500" << endl << "======================" << endl << endl;
		log << "======= ERROR ========" << endl << "500" << endl << "======================" << endl << endl;
		log.close(); // close log file
		return 0;
	}
	else // found word in the MEMORIZING
	{
		if (strcmp(test->GetMean(), arg2) == 0) // correct
		{
			cout << "======== TEST ========" << endl << "Pass" << endl << "======================" << endl << endl;
			log << "======== TEST ========" << endl << "Pass" << endl << "======================" << endl << endl;
			give = bst->Search(alp_temp)->GetBST()->Delete(arg1); // delete test word
			cll->Insert(give); // insert test word to MEMORIZED
			log.close(); // close log file
			return 1;
		}
		else // no correct
		{
			cout << "======= ERROR ========" << endl << "500" << endl << "======================" << endl << endl;
			log << "======= ERROR ========" << endl << "500" << endl << "======================" << endl << endl;
			log.close(); // close log file
			return 0;
		}
	}
}

bool Manager::SEARCH(char * arg)
{
	ofstream log;
	log.open("log.txt", ios::app); // log.txt open
	WordNode * search;
	char alp_temp;
	search = queue->Search(arg); // search word in the queue
	if (search == NULL) // not found in the queue
	{
		if (arg[0] >= 65 && arg[0] <= 90) // A~Z
			alp_temp = arg[0] + 32; // a~z
		else
			alp_temp = arg[0];
		search = bst->Search(alp_temp)->GetBST()->Search(arg); // search word in the bst
		if (search == NULL) // not found in the bst
		{
			search = cll->Search(arg); // search word in the circular linkedlist
			if (search == NULL) // not found in the circular linkedlist
			{
				cout << "======= ERROR ========" << endl << "600" << endl << "======================" << endl << endl;
				log << "======= ERROR ========" << endl << "600" << endl << "======================" << endl << endl;
				log.close(); // close log file
				return 0;
			}
			else // found in the circular linkedlist
			{
				cout << "======= SEARCH =======" << endl << search->GetWord() << " " << search->GetMean() << endl << "======================" << endl << endl;
				log << "======= SEARCH =======" << endl << search->GetWord() << " " << search->GetMean() << endl << "======================" << endl << endl;
				log.close(); // close log file
				return 1;
			}
		}
		else // found in the bst
		{
			cout << "======= SEARCH =======" << endl << search->GetWord() << " " << search->GetMean() << endl << "======================" << endl << endl;
			log << "======= SEARCH =======" << endl << search->GetWord() << " " << search->GetMean() << endl << "======================" << endl << endl;
			log.close(); // close log file
			return 1;
		}

	}
	else // found in the queue
	{
		cout << "======= SEARCH =======" << endl << search->GetWord() << " " << search->GetMean() << endl << "======================" << endl << endl;
		log << "======= SEARCH =======" << endl << search->GetWord() << " " << search->GetMean() << endl << "======================" << endl << endl;
		log.close(); // close log file
		return 1;
	}
}

bool Manager::UPDATE(char * arg1, char * arg2)
{
	ofstream log;
	log.open("log.txt", ios::app); // log.txt open
	WordNode * update = new WordNode;
	char alp_temp;
	char * temp = new char;
	update = queue->Search(arg1); // search word in the queue
	if (update == NULL) // not found in the queue
	{
		if (arg1[0] >= 65 && arg1[0] <= 90) // A~Z
			alp_temp = arg1[0] + 32; // a~z
		else
			alp_temp = arg1[0];
		update = bst->Search(alp_temp)->GetBST()->Search(arg1); // search word in the bst
		if (update == NULL) // not found in the bst
		{
			update = cll->Search(arg1); // search word in the circular linkedlist
			if (update == NULL) // not found in the circular linkedlist
			{
				cout << "======= ERROR ========" << endl << "800" << endl << "======================" << endl << endl;
				log << "======= ERROR ========" << endl << "800" << endl << "======================" << endl << endl;
				log.close(); // close log file
				return 0;
			}
			else // found in the circular linkedlist
			{
				cout << "======= UPDATE =======" << endl;
				log << "======= UPDATE =======" << endl;
				cout << update->GetWord() << " " << update->GetMean() << " -> " << arg2 << endl;
				log << update->GetWord() << " " << update->GetMean() << " -> " << arg2 << endl;
				cout << "======================" << endl << endl;
				log << "======================" << endl << endl;
				strcpy(temp, arg2);
				cll->Search(arg1)->SetMean(temp); // change the mean
				log.close(); // close log file
				return 1;
			}
		}
		else // found in the bst
		{
			cout << "======= UPDATE =======" << endl;
			log << "======= UPDATE =======" << endl;
			cout << update->GetWord() << " " << update->GetMean() << " -> " << arg2 << endl;
			log << update->GetWord() << " " << update->GetMean() << " -> " << arg2 << endl;
			cout << "======================" << endl << endl;
			log << "======================" << endl << endl;
			strcpy(temp, arg2);
			bst->Search(alp_temp)->GetBST()->Search(arg1)->SetMean(temp); // change the mean
			log.close(); // close log file
			return 1;
		}
	}
	else // found in the queue
	{
		cout << "======= UPDATE =======" << endl;
		log << "======= UPDATE =======" << endl;
		cout << update->GetWord() << " " << update->GetMean() << " -> " << arg2 << endl;
		log << update->GetWord() << " " << update->GetMean() << " -> " << arg2 << endl;
		cout << "======================" << endl << endl;
		log << "======================" << endl << endl;
		strcpy(temp, arg2);
		queue->Search(arg1)->SetMean(temp); // change the mean
		log.close(); // close log file
		return 1;
	}
}
