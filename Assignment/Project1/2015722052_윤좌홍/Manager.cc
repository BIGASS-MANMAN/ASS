#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"


Manager::Manager()
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;

	wordmean.first = new char[32];
	wordmean.second = new char[32];
	//using pair in STL, for string to save dinamic allocation
	memset(wordmean.first, 0, sizeof(char) * 32);
	memset(wordmean.second, 0, sizeof(char) * 32);
	fout_log.open("log.txt", ios::app);
}


Manager::~Manager()
{ return;

	if(queue) delete queue;
	if(cll) delete cll;
	if(bst) delete bst;

	if(wordmean.first) delete wordmean.first;
	if(wordmean.second) delete wordmean.second;
	//if char * variable == null or error memory adress, program is interrupt so, exception handling
}
//in this case
//1. UPDATE, SEARCH, TEST order need regardless to upper case alphabet
//so, make lower case alphabet
//2. variable str have string first adress, so, reutrn str == string's first adress return
char * Manager::strlwr(char * str)
{
	for(int i = 0; i < strlen(str); i++){
	if(str[i] >= 65 && str[i] <= 90)
	str[i] += 32;
	}
	return str;
}
//in this case
//LOAD order
//1. if data in structure, function return false 
//2. if reading in text file failed, return false;
//3. when read text file, program is ignore null , carrage return character in string
//4. if any no reading text file, make text file
//using the variable char reading, when push or insert node, reading = 1
bool Manager::LOAD()
{
	char reading = 0;
	WordNode * push_node = 0;
	ifstream fin;
	fin.open("to_memorize_word.txt");
	if(queue->GetWordCnt() > 0){
	fin.close();
	return false;
	}	//if data structure has data, return false;
	if(bst->GetWordCnt() > 0){
	fin.close();
	return false;
	}
	if(cll->GetWordCnt() > 0){
	fin.close();
	return false;
	}
	
	if(!fin){
			ofstream fout;
			fout.open("to_memorize_word.txt");
			fout.close();		//if no reading text file, make text file
			fin.close();
	}
	else{
		while(!fin.eof()){
			fin.getline(wordmean.first, 32, '	');
			if(wordmean.first[0] == '\0'
				|| wordmean.first[0] == '\n') break;
			//ignore for null, carrage return character
			//no Data in text file
			fin.getline(wordmean.second, 32, '\n');
			push_node = new WordNode;
			push_node->SetWord(wordmean.first);
			push_node->SetMean(wordmean.second);
			queue->Push(push_node);
			reading = 1;
		}
	fin.close();
	}
	fin.open("memorizing_word.txt");
	if(!fin){
			ofstream fout;
			fout.open("memorizing_word.txt");
			fout.close();		//if no reading text file, make text file
			fin.close();
	}
	else{
		while(!fin.eof()){
			fin.getline(wordmean.first, 32, '	');
			if(wordmean.first[0] == '\0'||
				wordmean.first[0] == '\n') break;
			//no Data in text file
			fin.getline(wordmean.second, 32, '\n');
			push_node = new WordNode;
			push_node->SetWord(wordmean.first);
			push_node->SetMean(wordmean.second);
			bst->Insert(push_node);
			reading = 1;
		}
	fin.close();
	}

	fin.open("memorized_word.txt");
	if(!fin){
			ofstream fout;
			fout.open("memorized_word.txt");
			fout.close();		//if no reading text file, make text file
			fin.close();
	}
	else{
		while(!fin.eof()){
			fin.getline(wordmean.first, 32, '	');
			if(wordmean.first[0] == '\0'||
				wordmean.first[0] == '\n') break;
			//no Data in text file
			fin.getline(wordmean.second, 32, '\n');
			push_node = new WordNode;
			push_node->SetWord(wordmean.first);
			push_node->SetMean(wordmean.second);
			cll->Insert(push_node);
			reading = 1;
		}
	fin.close();
	}
	
	if(reading == 1){
	return true;
	}
	else
	return false;
}
//in this case
//1. reading text file is not exist
//2. reading success
//3. text file is empty
bool Manager::ADD()
{
	WordNode *overlab = 0;
	ifstream fin;
		fin.open("word.txt");

		if(!fin){		//text file is not exist
			fin.close();
			return false;
		}
		else{			//text file is exist
			while(!fin.eof()){
				fin.getline(wordmean.first,32, '	');
				fin.getline(wordmean.second, 32, '\n');
				if(wordmean.first[0] == '\0' || wordmean.first[0] == '\n')
				break;
				WordNode * push_node = new WordNode;
		if(wordmean.first[0] == '\n' || wordmean.first[0]=='\0'){
		break;	
		}

		overlab = queue->Search(wordmean.first);
		if(overlab) continue;
		overlab = bst->Search(wordmean.first[0] -32)->GetBST()->Search(wordmean.first);
		if(overlab) continue;
		overlab = cll->Search(wordmean.first);
		if(overlab) continue;

				push_node->SetWord(wordmean.first);
				push_node->SetMean(wordmean.second);

				queue->Push(push_node);
			}
			fin.close();
			return true;
		}
}
//in this case
//1. move function, number of input in text file + number of node in bst
//2. this function don't dinamic allocation memory, pointer variable push in structure
bool Manager::MOVE()
{
	if(option_1[0] < '0' || option_1[0] >'9') return false;
	int move_num = atoi(option_1);
	WordNode * push_node = 0;
	if(queue->GetWordCnt() <= 0 || queue->GetWordCnt() < move_num) return false;
	if(bst->GetWordCnt() + move_num <= 100 && bst->GetWordCnt() >= 0){
		//exception BST word number is less then 100, queue word number is greater than move_num
		for(int i = 0; i<move_num; i++){
			push_node = queue->Pop();
			bst->Insert(push_node);
		}
		return true;
	}
	else{
		return false;
	}

}
//in this case
//1. if save function is no data in structure, return false;
//2. queue traversal is sequantial
//3. bst traversal is recursive or iterator
//4. cll traversal is sequantial
//5. if save processing success return true;
bool Manager::SAVE()
{

	if(queue->GetWordCnt() + bst->GetWordCnt() + cll->GetWordCnt() == 0){
		return false;	//No data in three data structure
	}
	queue->Save();
	bst->Save();
	cll->Save();

	return true;			// Save success
}
//in this case
//1. Test function is delete in BST
//no used delete operation, point out changing a node
//2. if Test success, the number of node in bst -1
//3. function search in AlphabetBST's AlphabetNode
//than search again in AlphabetNode's standard root of WordBST
//4. searched after insert in circularLL  
bool Manager::TEST()
{
	if(option_2 == '\0') return false;
	char * test_word = strlwr(option_1);
	char * test_mean = option_2;
	char alphabet = option_1[0]-32;
	WordBST * target_bst = bst->Search(alphabet)->GetBST();		//to search alphabetnode, and search again at alphabetnode's WordBST
	WordNode * target = bst->Search(alphabet)->GetBST()->Search(test_word);
	if(target && !strcmp(target->GetMean(), test_mean)){		//if TEST success
		target = target_bst->Delete(test_word);
		bst->SetWordCnt(bst->GetWordCnt()-1);
		cll->Insert(target);					//delete and insert circular	
		return true;
	}
	else
		return false;	//if not exist searching node or different original mean return false
}
//in this case
//1. searching queue, if exist data, return true;
//2. searching bst, if exist data, return true;
//3. searching circularLL, if exist data, return true;
//4. exception: if searching finished, that mean's No word data
//so, return false;
bool Manager::SEARCH()
{
	if(option_1 == '\0') return false; //input order is ERROR
	char * test_word = strlwr(option_1);	//change lower case alphabet
	char * test_mean = option_2;
	char alphabet = option_1[0]-32;
	WordNode * target;

	target = queue->Search(test_word);
	if(target){	//if no word data, function return NULL;
	cout<<"======== SEARCH ========"<<endl;
	fout_log<<"======== SEARCH ========"<<endl;
	cout<<target->GetWord()<<" "<<target->GetMean()<<endl;
	fout_log<<target->GetWord()<<" "<<target->GetMean()<<endl;
	return true;
	}	

	WordBST * target_bst = bst->Search(alphabet)->GetBST();
	target = bst->Search(alphabet)->GetBST()->Search(test_word);
	if(target){		 //if no word data, function return NULL;
		 cout<<"======== SEARCH ========"<<endl;
		fout_log<<"======== SEARCH ========"<<endl;
		cout<<target->GetWord()<<" "<<target->GetMean()<<endl;
		fout_log<<target->GetWord()<<" "<<target->GetMean()<<endl;
		return true;
	}
	
	target = cll->Search(test_word);
	if(target){		 //if no word data, function return NULL;
		 cout<<"======== SEARCH ========"<<endl;
		fout_log<<"======== SEARCH ========"<<endl;
		cout<<target->GetWord()<<" "<<target->GetMean()<<endl;
		fout_log<<target->GetWord()<<" "<<target->GetMean()<<endl;
		return true;
	}
	
	return false;		//searching fisished, No Word 
}
bool Manager::PRINT()
{
	if(!strcmp("TO_MEMORIZE", option_1) && queue->GetWordCnt() > 0){
		cout<<"======== PRINT ========"<<endl;
		fout_log<<"======== PRINT ========"<<endl;
	}
	if(!strcmp("MEMORIZING", option_1) && bst->GetWordCnt() > 0){
		if(option_2 == '\0') return false;	//input order is ERROR
		cout<<"======== PRINT ========"<<endl;
		fout_log<<"======== PRINT ========"<<endl;
	}
	if(!strcmp("MEMORIZED", option_1) && cll->GetWordCnt() > 0){
		cout<<"======== PRINT ========"<<endl;
		fout_log<<"======== PRINT ========"<<endl;
	}
	//case print
	
	//this if statement confirm target of printing structure, when exist printing data in structure
	if(!strcmp("TO_MEMORIZE", option_1) && !queue->Print()){	//not exist, cannot print
		//return value use error find
		return false;
	}

	if(!strcmp("MEMORIZING", option_1) && !bst->Print(option_2)){
		return false;
	}

	if(!strcmp("MEMORIZED", option_1) && !cll->Print()){
		return false;
	}

	return true;
}
//in this case
//1. at first, search the node, if no data in structure return false;
//2. if exist data in all of structure, fix the node's mean
bool Manager::UPDATE()
{
	if(option_2 == '\0') return false;	//input order is ERROR
	char * update_word =strlwr(option_1);
	char * update_mean = option_2;
	char alphabet = update_word[0]-32;
	WordNode * update_node = 0;
	if(queue->GetWordCnt() > 0){	//confirm situation if empty in structure
		update_node = queue->Search(update_word);  
		if(update_node){				//if update node exist, then change mean
			cout<<"======== UPDATE ========"<<endl;
			fout_log<<"======== UPDATE ========"<<endl;
			cout<<update_node->GetWord()<<" ";
			cout<<update_node->GetMean()<<"->";
			fout_log<<update_node->GetWord()<<" ";
			fout_log<<update_node->GetMean()<<"->";
			update_node->SetMean(update_mean);
			cout<<" "<<update_node->GetMean()<<"\n";
			fout_log<<" "<<update_node->GetMean()<<"\n";
			return true;
		}
	}

	if(bst->GetWordCnt() > 0){
		update_node = bst->Search(alphabet)->GetBST()->Search(update_word);		//upper
		if(update_node){
			cout<<"======== UPDATE ========"<<endl;
			fout_log<<"======== UPDATE ========"<<endl;
			cout<<update_node->GetWord()<<" "<<update_node->GetMean()<<" -> ";
			fout_log<<update_node->GetWord()<<" "<<update_node->GetMean()<<" -> ";
			update_node->SetMean(update_mean);
			cout<<update_node->GetMean()<<"\n";
			fout_log<<update_node->GetMean()<<"\n";
			return true;
		}
	}

	if(cll->GetWordCnt() > 0){
		update_node = cll->Search(update_word);
		if(update_node){
			cout<<"======== UPDATE ========"<<endl;
			fout_log<<"======== UPDATE ========"<<endl;
			cout<<update_node->GetWord()<<" "<<update_node->GetMean()<<" -> ";
			fout_log<<update_node->GetWord()<<" "<<update_node->GetMean()<<" -> ";
			update_node->SetMean(update_mean);
			cout<<update_node->GetMean()<<"\n";
			fout_log<<update_node->GetMean()<<"\n";
			return true;
		}
	}
	cout<<"======== ERROR ========"<<endl;
	fout_log<<"======== ERROR ========"<<endl;
	return false;
}
//in this case
//1. ifstream variable use getline function to reading string
//2. target string using strcmp, order and option
void Manager::run(const char * command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	ifstream fin;
	char cmd_line[50];

	fin.open(command);
	if(!fin){
		cout<<"Error! : command.txt file is not exist"<<endl;
		return;
	}	//if not exist text file, excute this function

	while(!fin.eof()){					//find command
		fin.getline(cmd_line, 50, '\n');
		if(!cmd_line){
			cout<<"ERROR! : command file is empty!"<<endl;
			return;
		}
		order = strtok(cmd_line, " ");
		option_1 = strtok(NULL, " ");	//string toknizer, select command
		option_2 = strtok(NULL, " ");
		
		if(!strcmp("LOAD", order)){		//excute command
			if(!LOAD()){
				cout<<"======== ERROR ========"<<endl;
				cout<<"100"<<endl;
				cout<<"======================="<<endl;
				fout_log<<"======== ERROR ========"<<endl;
				fout_log<<"100"<<endl;
				fout_log<<"======================="<<endl;
			}
			else{
				cout<<"======== LOAD ========"<<endl;
				cout<<"Success"<<endl;
				cout<<"======================"<<endl;
				fout_log<<"======== LOAD ========"<<endl;
				fout_log<<"Success"<<endl;
				fout_log<<"======================"<<endl;
			}
		}
		else if(!strcmp("ADD", order)){
			if(!ADD()){
				cout<<"======== ERROR ========"<<endl;
				cout<<"200"<<endl;
				cout<<"======================="<<endl;
				fout_log<<"======== ERROR ========"<<endl;
				fout_log<<"200"<<endl;
				fout_log<<"======================="<<endl;	
			}
			else{
				cout<<"======== ADD ========"<<endl;
				cout<<"Success"<<endl;
				cout<<"======================"<<endl;
				fout_log<<"======== ADD ========"<<endl;
				fout_log<<"Success"<<endl;
				fout_log<<"======================="<<endl;
			}
		}
		else if(!strcmp("MOVE", order)){
			if(!MOVE()){
				cout<<"======== ERROR ========"<<endl;
				cout<<"300"<<endl;
				cout<<"======================="<<endl;
				fout_log<<"======== ERROR ========"<<endl;
				fout_log<<"300"<<endl;
				fout_log<<"======================="<<endl;
			}
			else{
				cout<<"======== MOVE ========"<<endl;
				cout<<"Success"<<endl;
				cout<<"======================"<<endl;
				fout_log<<"======== MOVE ========"<<endl;
				fout_log<<"Success"<<endl;
				fout_log<<"======================"<<endl;
			}
		}
		else if(!strcmp("SAVE", order)){
			if(!SAVE()){
				cout<<"======== ERROR ========"<<endl;
				cout<<"400"<<endl;
				cout<<"======================="<<endl;
				fout_log<<"======== ERROR ========"<<endl;
				fout_log<<"400"<<endl;
				fout_log<<"======================="<<endl;
			}
			else{
				cout<<"======== SAVE ========"<<endl;
				cout<<"Success"<<endl;
				cout<<"======================"<<endl;
				fout_log<<"======== SAVE ========"<<endl;
				fout_log<<"Success"<<endl;
				fout_log<<"======================"<<endl;
			}
		}
		else if(!strcmp("TEST", order)){
			if(!TEST()){
				cout<<"======== ERROR ========"<<endl;
				cout<<"500"<<endl;
				cout<<"======================="<<endl;
				fout_log<<"======== ERROR ========"<<endl;
				fout_log<<"500"<<endl;
				fout_log<<"======================="<<endl;
			}
			else{
				cout<<"======== TEST ========"<<endl;
				cout<<"Pass"<<endl;
				cout<<"======================"<<endl;
				fout_log<<"======== TEST ========"<<endl;
				fout_log<<"Pass"<<endl;
				fout_log<<"======================"<<endl;
			}
		}
		else if(!strcmp("SEARCH", order)){
			if(!SEARCH()){
				cout<<"======== ERROR ========"<<endl;
				cout<<"600"<<endl;
				cout<<"======================="<<endl;
				fout_log<<"======== ERROR ========"<<endl;
				fout_log<<"600"<<endl;
				fout_log<<"======================="<<endl;
			}
			else{
				cout<<"======================"<<endl;
				fout_log<<"======================"<<endl;
			}
		}
		else if(!strcmp("PRINT", order)){
			if(!PRINT()){
				cout<<"======== ERROR ========"<<endl;
				cout<<"700"<<endl;
				cout<<"======================="<<endl;
				fout_log<<"======== ERROR ========"<<endl;
				fout_log<<"700"<<endl;
				fout_log<<"======================="<<endl;
			}
			else{
				cout<<"======================"<<endl;
				fout_log<<"======================"<<endl;
			}
		}
		else if(!strcmp("UPDATE", order)){
			if(!UPDATE()){
				cout<<"800"<<endl;
				cout<<"======================="<<endl;
				fout_log<<"800"<<endl;
				fout_log<<"======================="<<endl;
			}
			else{
				cout<<"======================="<<endl;
				fout_log<<"======================="<<endl;
			}
		}
		else if(!strcmp("EXIT", order)){
			return;
		}
	}

	fin.close();
}
