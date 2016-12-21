#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"


Manager::Manager()
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
	logfile.open("log.txt", ios::app);
	//create to memorize, memorizing, and memorized class.
}


Manager::~Manager()
{ return;

	delete cll;
	delete bst;
	delete queue;
	logfile.close();
}			//destruct CircularLinkedList, all trees, queue.

void Manager::run(const char * command)			//this fuction control program with command.txt.
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	ifstream file;
	file.open(command);								//using command.txt file.
	if (file.is_open() == false) return;
	
	char input[27] = "PHXDLTZBFJNRVYACEGIKMOQSUW";		//input alphabets by preorder to Alphabet bst.
	for (int i = 0; i < 26; i++) {
		AlphabetNode * node = new AlphabetNode;
		node->SetAlphabet(input[i]);
		bst->Insert(node);
	}														//Set Alphabet bst.

	if (file.is_open() == false) return;

	char readLine[50];
	while (file.eof() == false) {						//read line of command.txt
		for (int i = 0; i < 50; i++) readLine[i] = '\0';
		file.getline(readLine, 100);
		int i = 0, j = 0;
		for (; readLine[j] != ' '&& readLine[j] != '\0'; i++, j++) token1[i] = readLine[j];			//set token1
		token1[i] = '\0'; j++;
		for (i = 0; readLine[j] != ' ' && readLine[j] != '\0'; i++, j++) token2[i] = readLine[j];	//set token2
		token2[i] = '\0'; j++;
		for (i = 0; readLine[j] != ' '&& readLine[j] != '\0'; i++, j++) token3[i] = readLine[j];	//set token3
		token3[i] = '\0';

		if (!strcmp(token1, "LOAD")) {										//if program gets 'LOAD' command and fit to conditions, get all datas from file to program
			if ( token2[0]=='\0' && token3[0]=='\0' && LOAD() == true) {	//if tokens doesn't fit at conditions do not call LOAD function
				cout << "======== LOAD ========" << endl;
				cout << "Success" << endl;
				cout << "=====================" << endl << endl;

				logfile << "======== LOAD ========" << endl;
				logfile << "Success" << endl;
				logfile << "=====================" << endl << endl;
			}																
			else {
				cout << "======== ERROR ========" << endl;
				cout << 100 << endl;
				cout << "======================" << endl << endl;

				logfile << "======== ERROR ========" << endl;
				logfile << 100 << endl;
				logfile << "======================" << endl << endl;
			}
		}
		else if (!strcmp(token1, "ADD")) {									//if program gets 'ADD' command and fit to conditions, get all words from word.txt file to program
			if ( token2[0] == '\0' && token3[0] == '\0' && ADD() == true) {	//if tokens doesn't fit at conditions do not call ADD fuction
				cout << "======== ADD ========" << endl;
				cout << "Success" << endl;
				cout << "====================" << endl << endl;

				logfile << "======== ADD ========" << endl;
				logfile << "Success" << endl;
				logfile << "====================" << endl << endl;
			}
			else {
				cout << "======== ERROR ========" << endl;
				cout << 200 << endl;
				cout << "======================" << endl << endl;

				logfile << "======== ERROR ========" << endl;
				logfile << 200 << endl;
				logfile << "======================" << endl << endl;

			}
		}																	//if program gets 'MOVE' command and fit to conditions, move words which text said from queue to bst
		else if (!strcmp(token1, "MOVE")) {
			if (token2[0]!='\0' && token3[0] == '\0' && MOVE() == true) {
				cout << "======== MOVE ========" << endl;
				cout << "Success" << endl;
				cout << "=====================" << endl << endl;

				logfile << "======== MOVE ========" << endl;
				logfile << "Success" << endl;
				logfile << "=====================" << endl << endl;
			}																//if tokens doesn't fit at conditions do not call MOVE function
			else {
				cout << "======== ERROR ========" << endl;
				cout << 300 << endl;
				cout << "======================" << endl << endl;
				
				logfile << "======== ERROR ========" << endl;
				logfile << 300 << endl;
				logfile << "======================" << endl << endl;
			}
		}
		else if (!strcmp(token1, "SAVE")) {									//if program gets 'SAVE' command and fit to conditions, save all datas in program
			if ( token2[0] == '\0' && token3[0] == '\0' && SAVE() == true) {
				cout << "======== SAVE ========" << endl;
				cout << "Success" << endl;
				cout << "=====================" << endl << endl;

				logfile << "======== SAVE ========" << endl;
				logfile << "Success" << endl;
				logfile << "=====================" << endl << endl;

			}
			else {
				cout << "======== ERROR ========" << endl;
				cout << 400 << endl;
				cout << "======================" << endl << endl;

				logfile << "======== ERROR ========" << endl;
				logfile << 400 << endl;
				logfile << "======================" << endl << endl;

			}
		}
		else if (!strcmp(token1, "TEST")) {								//if program gets 'TEST' command and fit to conditions, 
			if ( token2[0] != '\0' && token3[0] != '\0' && TEST() == true) {	//search words same with token2 in program
				cout << "======== TEST ========" << endl;						//if there is same word and same mean with token3
				cout << "Pass" << endl;											//print 'Pass' and move that word from bst to cll
				cout << "=====================" << endl << endl;

				logfile << "======== TEST ========" << endl;						//if there is same word and same mean with token3
				logfile << "Pass" << endl;											//print 'Pass' and move that word from bst to cll
				logfile << "=====================" << endl << endl;

			}
			else {
				cout << "======== ERROR ========" << endl;
				cout << 500 << endl;
				cout << "======================" << endl << endl;

				logfile << "======== ERROR ========" << endl;
				logfile << 500 << endl;
				logfile << "======================" << endl << endl;

			}
		}
		else if (!strcmp(token1, "SEARCH")) {							//if program gets 'SEARCH' command and fit to conditions, search token2 in progream.
			if (SEARCH_CHECK() == false || token2[0] == '\0' || token3[0] != '\0') {//if there is same word, print the word.
				cout << "======== ERROR ========" << endl;
				cout << 600 << endl;
				cout << "======================" << endl << endl;
			
				logfile << "======== ERROR ========" << endl;
				logfile << 600 << endl;
				logfile << "======================" << endl << endl;

			}
			else {
				cout << "======== SEARCH ========" << endl;
				logfile << "======== SEARCH ========" << endl;
				SEARCH();
				cout << "=======================" << endl << endl;
				logfile << "=======================" << endl << endl;

			}
		}
		else if (!strcmp(token1, "PRINT")) {						//if, program gets 'Print' command and fit to conditions, print data, by token2, and token3
			if (PRINT_CHECK() == false || token2[0] == '\0' ) {		//token2 means data structure, and token3 means order of print
				cout << "======== ERROR ========" << endl;
				cout << 700 << endl;
				cout << "======================" << endl << endl;

				logfile << "======== ERROR ========" << endl;
				logfile << 700 << endl;
				logfile << "======================" << endl << endl;

			}
			else {
				cout << "======== PRINT ========" << endl;
				logfile << "======== PRINT ========" << endl;
				PRINT();
				cout << "======================" << endl << endl;
				logfile << "======================" << endl << endl;

			}
		}
		else if (!strcmp(token1, "UPDATE")) {					//if, program gets 'UPDATE' command and fit to conditions, change mean of the word
			if (UPDATE_CHECK() == false || token2[0] == '\0' || token3[0] == '\0') {	//check token2 if there is same word or not. if there is same word
				cout << "======== ERROR ========" << endl;								//change the mean of the word to token3
				cout << 800 << endl;
				cout << "======================" << endl << endl;

				logfile << "======== ERROR ========" << endl;								//change the mean of the word to token3
				logfile << 800 << endl;
				logfile << "======================" << endl << endl;
			}
			else {
				cout << "======== UPDATE ========" << endl;
				logfile << "======== UPDATE ========" << endl;
				UPDATE();
				cout << "=======================" << endl<<endl;
				logfile << "=======================" << endl << endl;
			}
		}
		else if (!strcmp(token1, "EXIT") && token2[0] == '\0' && token3[0] == '\0') {		//if program gets 'EXIT' command and fit to conditon,
			file.close();																	//exit the program.
			break;
		}
		for (int i = 0; i < 30; i++) {			//initialize all tokens
			token1[i] = '\0';
			token2[i] = '\0';
			token3[i] = '\0';
		}
	}
}

bool Manager::LOAD() {					//: load files to program, not load word.txt file
	ifstream file1, file2, file3;				//open files
	file1.open("to_memorize_word.txt");
	file2.open("memorizing_word.txt");
	file3.open("memorized_word.txt");

	if (file1.is_open() == false || file2.is_open() == false || file3.is_open() == false) return false;		//if file is not exist, retrun false
	if (queue->GetNum() != 0 || bst->GetNumOfWords() != 0 || cll->GetNum() != 0) return false;	//if there is already exist word return false
	char eng[30];			//store english part of word
	char mean[30];			//store mean part of word
	char temp[60];			//store word and mean

	while (file1.eof() == false) {		//if reach end of file, escape loop
		WordNode* word = new WordNode;	
		file1.getline(temp, 60);			//get word and mean together in temp. depart word and mean
		if (temp[0] == '\0') break;
		int i = 0, j = 0;
		for (;temp[j]!='\t'; i++, j++) eng[i] = temp[j];
		eng[i] = '\0';
		for (i = 0, j++;; i++, j++) {
			mean[i] = temp[j];
			if (temp[j] == '\0')
				break;
		}
		word->SetWord(eng);				//set english part
		word->SetMean(mean);			//set mean part

		queue->Push(word);				//push the word to Queue.
	}

	while (file2.eof() == false) {		//if reach end of file, escape loop.
		WordNode* word = new WordNode;
		file2.getline(temp, 60);
		if (temp[0] == '\0') break;		//all algorism is same with above.
		int i = 0, j = 0;
		for (; temp[j] != '\t'; i++, j++) eng[i] = temp[j];
		eng[i] = '\0';
		for (i = 0, j++;; i++, j++) {
			mean[i] = temp[j];
			if (temp[j] == '\0')
				break;
		}
		word->SetWord(eng);
		word->SetMean(mean);
		bst->Search(eng[0])->GetBST()->Insert(word);		//insert word correct alphabet bst.
	}

	while (file3.eof() == false) {			//if reach end of file, escape loop.
		WordNode* word = new WordNode;
		file3.getline(temp, 60);
		if (temp[0] == '\0') break;
		int i = 0, j = 0;
		for (; temp[j] != '\t'; i++, j++) eng[i] = temp[j];
		eng[i] = '\0';
		for (i = 0, j++;; i++, j++) {
			mean[i] = temp[j];
			if (temp[j] == '\0')
				break;
		}
		word->SetWord(eng);
		word->SetMean(mean);

		cll->Insert(word);		//insert word to CircularLinkedList.
	}

	file1.close();			//close all files
	file2.close();
	file3.close();

	return true;
	
}
bool Manager::ADD() {			//: read "word.txt" file to Queue
	ifstream file("word.txt");
	if (file.is_open() == false) return false;		//if there isn't correct file return false
	char word[60];
	char eng[30];
	char kor[30];

	file.getline(word, 60);
	if (word[0] == '\0') return false;		//if there is no word in file return false
	
	while (!(file.eof())) {					//algorism is almost same with LOAD
		WordNode* temp = new WordNode;
		int j = 0;
		for (int i = 0;; i++, j++) {
			eng[i] = word[j];
			if (word[j] == '\t') {
				eng[i] = '\0';
				break;
			}
		}j++;
		for (int i = 0;; i++, j++) {
			kor[i] = word[j];
			if (word[j] == '\0') break;
		}
		temp->SetWord(eng);
		temp->SetMean(kor);
		if (queue->Search(eng) != '\0' || bst->Search(eng[0])->GetBST()->Search(eng) !='\0' || cll->Search(eng) !='\0') {		
			delete temp;
		}		//if aleady exist same word, do not insert that word, and delete memory.
		else queue->Push(temp);
		file.getline(word, 60);
		if (word[0] == '\0') break;
	}
	file.close();
	return true;
}
bool Manager::MOVE() {			//:MOVE words as much as the user wants

	int numOfWord = atoi(token2);		//the token2 mean the number of word user want to move

	if ((numOfWord + bst->GetNumOfWords()) > 100  ||  //if the number of word of bst is over 100 after move can't move words
		queue->GetNum() < numOfWord || queue->GetNum()<=0)	return false;			// if words over 100 or the number of words in queue is less than the number of words which user want to move or there is no word in queue, return false
	
	char str[60];

	WordNode* word;
	for (int i = 0; i < numOfWord; i++) { //Move words from queue to bst.
		word = queue->Pop();
		strcpy(str, word->GetWord());
		bst->Search(str[0])->GetBST()->Insert(word);
	}
	return true;
}
bool Manager::SAVE() {
	if (queue->GetNum() == 0 && bst->GetNumOfWords() == 0 && cll->GetNum() == 0) return false;	//if there is no data, return false
	ofstream file("memorizing_word.txt");
	file.close();			//delete datas of old memorizing_word.txt file, the reason of using this sentence is that bst do not use overwriting when it saves wrods.

	queue->Save();		//call Save function of Queue. if there is no data, cnt=cnt+0;
	bst->Save();		//call Save function of bst, if there is no data, cnt=cnt+0;
	cll->Save();		//call Save function of cll, if there is no data, cnt=cnt+0;

	return true;
}
bool Manager::TEST() {			//:Check the word of memorizing. If it's correct move word from bst to cll
	for (int i = 0; i < 30; i++) {			//change the upper alphabets to lower alphabets.
		if (token2[i] >= 65 && token2[i] <= 90)
			token2[i] += 32;
	}
	WordBST * wBST = bst->Search(token2[0])->GetBST();		//search bst
	WordNode * word=wBST->Search(token2);			//search word
	if (word == '\0') return false;					//there isn't same word
	if (!strcmp(word->GetMean(), token3)) {			//correct word, and mean
		cll->Insert(wBST->Delete(token2));			//delete the word at bst and insert the word to cll
		return true; 
	}	
	else return false;			//wrong mean
}
bool Manager::SEARCH() {		//:Search a word in program
	for (int i = 0; i < 30; i++) {		//change upper alphabets to lower alphabets
		if (token2[i] >= 65 && token2[i] <= 90)
			token2[i] += 32;
	}
	WordNode* word;				//check if the word is exist in program or not.
	if ((word = queue->Search(token2)) == '\0') {
		if ((word = bst->Search(token2[0])->GetBST()->Search(token2)) == '\0') {
			if ((word = cll->Search(token2)) == '\0') {
				return false;
			}
		}
	}
	cout << word->GetWord() << " " << word->GetMean() << endl;		//if the word is exist print the word
	logfile << word->GetWord() << " " << word->GetMean() << endl;
	return true;
}
bool Manager::SEARCH_CHECK() {		//this function is only check if the word exist or not. it doesn't print the word. 
	for (int i = 0; i < 30; i++) {
		if (token2[i] >= 65 && token2[i] <= 90)
			token2[i] += 32;
	}
	WordNode* word;		//check
	if ((word = queue->Search(token2)) == '\0') {
		if ((word = bst->Search(token2[0])->GetBST()->Search(token2)) == '\0') {
			if ((word = cll->Search(token2)) == '\0') {
				return false;
			}
		}
	}
	return true;
}
bool Manager::PRINT() {			//: print words
	if (!strcmp(token2, "TO_MEMORIZE")) {		//print words after checking option
		queue->Print();							//show queue
		return true;
	}		
	else if (!strcmp(token2, "MEMORIZING")) {		
		if (!strcmp(token3, "R_PRE")) { bst->Print("r_pre"); return true; }			//R_preorder
		if (!strcmp(token3, "I_PRE")) { bst->Print("i_pre"); return true; }			//I_preorder
		if (!strcmp(token3, "R_IN")) { bst->Print("r_in"); return true; }			//R_inorder
		if (!strcmp(token3, "I_IN")) { bst->Print("i_in"); return true; }			//I_inorder
		if (!strcmp(token3, "R_POST")) { bst->Print("r_post"); return true; }		//R_postorder
		if (!strcmp(token3, "I_POST")) { bst->Print("i_post"); return true; }		//I_postorder
		if (!strcmp(token3, "I_LEVEL")) { bst->Print("i_lev"); return true; }		//I_levelorder
	}
	else if (!strcmp(token2, "MEMORIZED")) {cll->Print(); return true;}			//show cll

	return false;
}
bool Manager::PRINT_CHECK(){		//this function only check true or false, it doesn't print words.
	int i = 0;
	if (!strcmp(token2, "TO_MEMORIZE")) {
		i++;
		if (queue->GetNum() == 0 || token3[0]!='\0')
			return false;
	}
	else if (!strcmp(token2, "MEMORIZING")) {
		if (bst->GetNumOfWords() == 0)
			return false;
		if (!strcmp(token3, "R_PRE") || !strcmp(token3, "I_PRE") || !strcmp(token3, "R_IN") ||
			!strcmp(token3, "I_IN") || !strcmp(token3, "R_POST") || !strcmp(token3, "I_POST") ||
			!strcmp(token3, "I_LEVEL")) i++;
	}
	else if (!strcmp(token2, "MEMORIZED")) {
		i++;
		if (cll->GetNum() == 0 || token3[0] != '\0')
			return false;
	}
	if (i == 0)				//if i is 0, it means the option which user inputted isn't correct. so return false
		return false;
	else
		return true;
	
}
bool Manager::UPDATE() {			//:Search a word and update it's mean
	for (int i = 0; i < 30; i++) {			//change upper alphabets to lower alphabets
		if (token2[i] >= 65 && token2[i] <= 90)
			token2[i] += 32;
	}
	WordNode* word;		//check if the word exist in program
	if ((word = queue->Search(token2)) == '\0') {
		if ((word = bst->Search(token2[0])->GetBST()->Search(token2)) == '\0') {
			if ((word = cll->Search(token2)) == '\0') {
				return false;
			}
		}
	}
	cout << word->GetWord() << " " << word->GetMean() << " -> ";
	logfile << word->GetWord() << " " << word->GetMean() << " -> ";

	word->SetMean(token3);		
	cout << word->GetMean() << endl;			//Change mean of word
	logfile << word->GetMean() << endl;			//Change mean of word
	return true;
}
bool Manager::UPDATE_CHECK() {		//this function only check if the word is exist or not.
	for (int i = 0; i < 30; i++) {
		if (token2[i] >= 65 && token2[i] <= 90)
			token2[i] += 32;
	}
	WordNode* word;				//if there isn't same word return false.
	if ((word = queue->Search(token2)) == '\0') {
		if ((word = bst->Search(token2[0])->GetBST()->Search(token2)) == '\0') {
			if ((word = cll->Search(token2)) == '\0') {
				return false;
			}
		}
	}
	return true;
}
