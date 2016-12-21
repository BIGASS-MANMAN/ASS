#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <ctype.h>
#include <climits>

using namespace std;
Manager::Manager()
{
	cll = new CircularLinkedList;		// MEMORIZED
	bst = new AlphabetBST;				// MEMORIZING
	queue = new Queue;					// TO_MEMORIZE
}


Manager::~Manager()
{ return;

	delete cll;							// Delete MEMORIZED
	delete bst;							// Delete MEMORIZING
	delete queue;						// Delete TO_MEMORIZE
}

void Manager::run(const char * command)		// Program start
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	ifstream fin;							// file object
	fin.open(command, ios_base::in);		// open file for read
	if (!fin.is_open())return;				// if opening file is fail, exit program
	char com_str[100];						// char array to be saved string from file
	char menu[7];							// menu string		ex) LOAD, ADD, SAVE etc.
	char num[4];							// number to be moved to MEMORIZING from TO_MEMORIZE at MOVE
	int index[3];							// Index about white space of string
	int space;								// The number of white space
	int i, j;								// Iterative statement variable
	
	while (!fin.eof()) {					// if file counter is eof, exit program
		fin.getline(com_str, 100, '\n');	//  read file
		/* Set index, the number of white space */
		for (i = 0, j = 0, space = 0, index[0] = 0, index[1] = 0, index[2] = 0; ; i++) {
			if (com_str[i] == ' ' || com_str[i] == '\r') {		// If com_str[i] is white space, set index and white space
				index[j++] = i;									// Index for white space of string
				if (com_str[i] == '\r')break;					// Mark end of the string
				space++;										// The number of white space
			}
		}
		/* set first word(MENU) */
		copy(com_str, &com_str[index[0]], menu);	// Copy menu word
		menu[index[0]] = '\0';						// Mark end of the word

		if (!strcmp(menu, "LOAD")) {				// LOAD
			if (space != 0) {						// White space is not zero, LOAD is fail
				LOG(1, 0);							// Deliver error to LOG
				continue;							// Ignore below code
			}
			LOG(1, LOAD());							// Execute LOAD and record log
		}

		else if (!strcmp(menu, "ADD")) {			// ADD
			if (space != 0) {						// If not space 0
				LOG(2, 0);							// Input LOG 
				continue;							// continue
			}
			LOG(2, ADD());							// input LOG 2, ADD
		} 
		else if (!strcmp(menu, "MOVE")) {			// or string compare menu, MOVE
			if (space != 1) {						// If not space 1	
				LOG(3, 0);							// Input LOG 
				continue;							// Continue
			}
			copy(&com_str[index[0] + 1], &com_str[index[1]], num);	// string copy, index array
			num[index[1] - index[0] - 1] = '\0';					// index array set NULL
			m_Move = atoi(num);										// mMove set number of string charactor
			LOG(3, MOVE());											// input LOG
		}
		else if (!strcmp(menu, "SAVE")) {							// or string compare menu, SAVE
			if (space != 0) {										// if not space 0
				LOG(4, 0);											// input LOG 4
				continue;											// continue
			}
			LOG(4, SAVE());											// Input LOG
		}
		else if (!strcmp(menu, "TEST")) {							// or string compare menu, TEST
			if (space != 2) {										// if not space 1
				LOG(5, 0);											// input LOG
				continue;											// continue
			}
			copy(&com_str[index[0] + 1], &com_str[index[1]], m_Word);	// string copy
			m_Word[index[1] - index[0] - 1] = '\0';						// mword sub indexres set NULL
			copy(&com_str[index[1] + 1], &com_str[index[2]], m_Mean);	// string copy
			m_Mean[index[2] - index[1] - 1] = '\0';						// mword sub indexres set NULL
			LOG(5, TEST());												// Input LOG test
		}
		else if (!strcmp(menu, "SEARCH")) {				// string compare SEARCH
			if (space != 1) {							// if not space 1
				LOG(6, 0);								// input LOG
				continue;								// continue
			}
			copy(&com_str[index[0] + 1], &com_str[index[1]], m_Word);	// string copy mword
			m_Word[index[1] - index[0] - 1] = 0;						// mword sub inderes set 0
			for(int j = 0;m_Word[j] != 0; j++){
				m_Word[j] = tolower(m_Word[j]);		// set all of characters of m_Word to lower case
			}
			LOG(6, SEARCH());											// input LOG SEARCH
		}
		else if (!strcmp(menu, "PRINT")) {				// string compare PRINT
			if (space < 1 || space > 2) {				// space smaller than 1 or larger than 2
				LOG(7, 0);								// Input LOG 
				continue;								// continue
			}
			copy(&com_str[index[0] + 1], &com_str[index[1]], m_Print);		// string copy print
			m_Print[index[1] - index[0] - 1] = 0;							// mPrint sub indexers set 0
			if (!strcmp(m_Print, "MEMORIZING")) {							// string compare MEMORIZING
				if (space != 2) {											// if not space 2
					LOG(7, 0);												// Input LOG
					continue;												// continue
				}
				copy(&com_str[index[1] + 1], &com_str[index[2]], m_Print2);	// string copy print
				m_Print2[index[2] - index[1] - 1] = 0;						// print sub indexers set 0
			}
			LOG(7, PRINT());												// input LOG print
		}
		else if (!strcmp(menu, "UPDATE")) {		// or string compare UPDATE
			if (space != 2) {					// if not space 2
				LOG(8, 0);						// input LOG 
				continue;						// continue
			}
			copy(&com_str[index[0] + 1], &com_str[index[1]], m_Word);	// string copy word
			m_Word[index[1] - index[0] - 1] = 0;						// sub word indexers set 0
			copy(&com_str[index[1] + 1], &com_str[index[2]], m_Mean);	// stirng copy mean
			m_Mean[index[2] - index[1] - 1] = '\0';						// sub word indexers set NULL
			LOG(8, UPDATE());											// Input LOG UPDATE
		}
		else if (!strcmp(menu, "EXIT")) {								// or string compare EXIT
			return;														// end of function
		}
	}
	fin.close();		// file close
}

bool Manager::LOAD()
{
	// to_memorize_word.txt
	// memorizing_word.txt
	// memorized_word.txt
	if (!(queue->IsEmpty()))return 0;					// if queue linked empty is not, then end of function
	if (!(bst->IsEmpty()))return 0;						// if bst linked empty is not, then end of function
	if (!(cll->IsEmpty()))return 0;						// if cli linked empty is not, then end of function
	ifstream fin;										// inner file stream fin
	char* str1 = 0;										// charactor pointer str1 set 0
	char* str2 = 0;										// charactor pointer str2 set 0
	WordNode* temp;										// word node pointer temp
	char str[100];										// charator array range 100
	bool error = true;									// boolean error set ture
	fin.open("to_memorize_word.txt", ios_base::in);		// file open
	if (!fin.is_open())return 0;					// is not open,then bool error false
	while (fin >> str) {								// repetition
		temp = new WordNode;							// temp set dynamic allocation word node
		if (str1)temp->SetWord(str1);					// condigion str1, then temp linking serword
		str1 = new char[strlen(str) + 1];				// str1 set dynamic allocation charactor array
		strcpy(str1, str);								// string copy str1, str2
		temp->SetWord(str1);							// temp linking setword
		fin.clear();									// file clear
		fin >> str;										// insert str
		str2 = new char[strlen(str) + 1];				// str2 set dynamic allocation charactor array
		strcpy(str2, str);								// string copy str2, str1
		temp->SetMean(str2);							// temp linking set mean
		fin.clear();									// file clear		
		queue->Push(temp);								// queue push
	}
	fin.close();										// file close
	fin.open("memorizing_word.txt", ios_base::in);		// file open
	if (!fin.is_open())return 0;					// is not open, bool error false
	while (fin >> str) {								// repetition
		temp = new WordNode;							// condition, then temp linking setword
		str1 = new char[strlen(str) + 1];				// str1 set dynamic allocation charactor array
		strcpy(str1, str);								// string copy
		temp->SetWord(str1);							// temp linking set word
		fin.clear();									// file clear
		fin >> str;										// insert str
		str2 = new char[strlen(str) + 1];				// str2 set dynamic allocation charctor array
		strcpy(str2, str);								// string copy
		temp->SetMean(str2);							// temp linking set mean
		fin.clear();									// file clear
		bst->Insert(temp);								// bst linking Insert
	}
	fin.close();										// file close
	fin.open("memorized_word.txt", ios_base::in);		// file open
	if (!fin.is_open()) return 0;					// is not open, bool error set false
	while (fin >> str) {								// repetition
		temp = new WordNode;							// temp set dynamic allocation word node
		if (str1)temp->SetWord(str1);					// condition str1, then temp linking set word
		str1 = new char[strlen(str) + 1];				// str1 set dynamic allocation charctor array
		strcpy(str1, str);								// string copy
		temp->SetWord(str1);							// temp linking set word
		fin.clear();									// file clear
		fin >> str;										// insert str
		str2 = new char[strlen(str) + 1];				// str2 set dynamic allocation charctor array
		strcpy(str2, str);								// string copy
		temp->SetMean(str2);							// temp linking set mean
		fin.clear();									// file clear
		cll->Insert(temp);								// cli linking insert
	}
	fin.close();										// file close
	return error;										// return value error
}
bool Manager::ADD()								// ADD
{
	ifstream fin;								// input file stream fin
	char* str1 = 0;								// charctor pointer str1 set 0
	WordNode* temp;								// wordnode pointer temp 
	char str[100];								// charactor array set range 100
	fin.open("word.txt", ios_base::in);			// file open
	if (!fin.is_open())return 0;				// is not open, then end of function
	while (fin >> str) {						// repetiton
		temp = new WordNode;					// temp set dynamic allocation word node
		str1 = new char[strlen(str) + 1];		// str1 set dynamic allocation charaction array
		strcpy(str1, str);						// string copy
		strcpy(m_Word, str1);					// string copy
		if (SEARCH()) {							// if condition search
			delete temp;						// delete temp
			delete str1;						// delete str1
			fin >> str;							// insert str
			continue;							// continue
		}					
		temp->SetWord(str1);					// temp linking set word
		fin >> str;								// inser str
		str1 = new char[strlen(str) + 1];		// str1 set dynamic allocation charactor array
		strcpy(str1, str);						// string copy
		temp->SetMean(str1);					// temp linking set mean
		queue->Push(temp);						// queue push
	}
	if(!queue->WordNumber())return 0;			// is not, then end of function
	fin.close();								// file close
	return 1;									// return value 1
}
bool Manager::MOVE()									// MOVE
{	
	WordNode * temp;									// word node pointer temp
	if(m_Move > queue->WordNumber())return 0;			// in condition queue linked word number, then end of function		
	for (int i = 0; i < m_Move; i++) {					// condition repetition
		if (!bst->IsFull()) {							// bst is not full
			if (temp = queue->Pop())bst->Insert(temp);	// if temp set linked queue pop, then bst linking insert
			else return 0;								// or end of function
		}
		else return 0;									// of end of function
	}
	return 1;											// return value 1
}
bool Manager::SAVE()
{
	bool error = true;						// boolean type error set true
	if (!queue->Save())	error = false;		// TO_MEMORIZE	save failed
	if (!bst->Save())	error = false;		// MEMORIZING	save failed
	if (!cll->Save())	error = false;		// MEMORIZED	save failed
	return error;							// return bool error 
}
bool Manager::TEST()								// TEST
{
	WordNode * node;								// wordnode pointer node
	if ((node = bst->Search(m_Word))) {				// if node set bst linked search
		if (!strcmp(m_Mean, node->GetMean())) {		// if string compare
			cll->Insert(bst->Delete(node));			// cli linking insert
			return 1;								// return value 1
		}
	}
	return 0;										// end of function
}
bool Manager::SEARCH()							// SEARCH
{	
	WordNode * temp;							// word node pointer temp
	ofstream fout;								// open file stream fout
	if (temp = queue->Search(m_Word));			// if temp set queue linked search
	else if (temp = bst->Search(m_Word));		// or temp set linked bst to search
	else if (temp = cll->Search(m_Word));		// or temp set linked cli to search
	else return 0;								// or not end of function
	strcpy(m_Word, temp->GetWord());			// string copy word
	strcpy(m_Mean, temp->GetMean());			// string copy mean
	return 1;									// return value 1
}
bool Manager::PRINT()							// PRINT
{
	ofstream fout;								// open file stream fout
	fout.open("log.txt", ios_base::app);		// open file
	fout.close();								// file close

	if (!strcmp("TO_MEMORIZE", m_Print)) {		// PRINT TO_MEMORIZE
		if (!queue->Print())return 0;			// FAILED TO PRINT TO_MEMORIZE
	}
	else if (!strcmp("MEMORIZING", m_Print)) { 	// PRINT MEMORIZING
		if (!bst->Print(m_Print2))return 0;		//FAILED TO PRINT MEMORIZING
	}
	else if (!strcmp("MEMORIZED", m_Print)) {	// PRINT MEMORIZED
		if (!cll->Print())return 0;				//FAILED TO PRINT MEMORIZED
	}
	else return 0;								// INPUT ERROR

	return 1;									// return value 1
}	
bool Manager::UPDATE()							// UPDATE
{
	WordNode * node;							// word node pointer node
	if(node = queue->Search(m_Word)){}			// if condition, node set linked queue to search
	else if(node = cll->Search(m_Word)){}		// or node set linked cli to search
	else if (node = bst->Search(m_Word)) {}		// or node set linked bst to serach
	else return 0;								// or not end of function
	strcpy(m_search, node->GetMean());			// string copy
	node->SetMean(m_Mean);						// node linking set mean
	return 1;									// return value 1
}

void Manager::LOG(const int FUNCTION, const bool result)			// LOG
{
	ofstream fout;													// open file stream fout
	fout.open("log.txt", ios_base::app);							// open file
	if (!result) {													// if not result
		fout << "======== ERROR ========" << endl					
			<< FUNCTION << "00" << endl								
			<< "=======================" << endl;					
		cout << "======== ERROR ========" << endl					
			<< FUNCTION << "00" << endl							
			<< "=======================" << endl;					// promt
	}
	else
		switch (FUNCTION) {											// condition selecte
		case 1:														// LOAD
			fout << "======== LOAD ========" << endl				
				<< "Success" << endl								
				<< "======================" << endl;				
			cout << "======== LOAD ========" << endl				
				<< "Success" << endl								
				<< "======================" << endl;				// promt
			break;													// out of selection function
		case 2:														// ADD
			fout << "======== ADD ========" << endl					
				<< "Success" << endl								
				<< "=====================" << endl;					
			cout << "======== ADD ========" << endl					
				<< "Success" << endl								
				<< "=====================" << endl;					// promt
			break;													// out of selection function
		case 3:														// MOVE
			fout << "======== MOVE ========" << endl
				<< "Success" << endl
				<< "======================" << endl;
			cout << "======== MOVE ========" << endl
				<< "Success" << endl
				<< "======================" << endl;				// promt
			break;													// out of selection function
		case 4:														// SAVE
			fout << "======== SAVE ========" << endl
				<< "Success" << endl
				<< "======================" << endl;
			cout << "======== SAVE ========" << endl
				<< "Success" << endl
				<< "======================" << endl;				// promt
			break;													// out of selection function
		case 5:														// TEST
			fout << "======== TEST ========" << endl
				<< "Pass" << endl
				<< "======================" << endl;
			cout << "======== TEST ========" << endl
				<< "Pass" << endl
				<< "======================" << endl;				// promt
			break;													// out of selection function
		case 6:														// SEARCH
			fout << "======== SEARCH ========" << endl
				<< m_Word << " " << m_Mean << endl
				<< "========================" << endl;
			cout << "======== SEARCH ========" << endl
				<< m_Word << " " << m_Mean << endl
				<< "========================" << endl;				// promt
			break;													// out of selection function
		case 7:														// PRINT
			break;
		case 8:														// UPDATE
			fout << "======== UPDATE ========" << endl
				<< m_Word << " " << m_search << " -> " << m_Mean << endl
				<< "========================" << endl;
			cout << "======== UPDATE ========" << endl
				<< m_Word << " " << m_search << " -> " << m_Mean << endl
				<< "========================" << endl;				// promt
			break;													// out of selection function
		default:													// ERROR
			fout << "======== LOG ERROR ========" << endl;
			cout << "======== LOG ERROR ========" << endl;			// promt
			fout.close();											// file close
			return;													// return
		}
	fout.close();													// file close
}
