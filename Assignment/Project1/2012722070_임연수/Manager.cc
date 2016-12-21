#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"

Manager::Manager()
{
	/*	the constructor about Manager class.				*/
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
	/*	member variables indicate dynamic-allocation memory */
}

Manager::~Manager()
{ return;

	/*	the destructor about Manager class.					*/
	delete cll;
	delete bst;
	delete queue;
	/*	member variables return the memory.					*/
}

void Manager::run(const char * command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	/* this function works top-level routine. first of all,
	   implement alphabet node's structure from a to z.
	   and then, load the file that was indicated by 'command'
	   and excute some of major routines as line by line.					*/

	/* Step 1. implement alphabet node from a to z.							*/
	const char letter[] = InitLETTERING;
	AlphabetNode *alphabet = new AlphabetNode;
	for(int i=0;i<LETTERS;i++) {
		alphabet->SetAlphabet(letter[i]);
		bst->Insert(alphabet);
	} delete alphabet;
	
	/* Step 2. open the file that stored command-lines						*/
	ifstream commandFile(command);
	ofstream log;
	if(!commandFile) cout<<"can't open "<<command<<endl;
	// if there isn't the file named 'COMMAND_FILENAME', print error message.
	/* Step 3. it excutes each command that were matched to member function */
	else while(!commandFile.eof()) {
		const char *code[9] = {"LOAD", "ADD", "MOVE", "SAVE", "TEST", "SEARCH", "PRINT", "UPDATE", "EXIT"};
		char buf[256] = {0}, *fName =NULL;
		short int op=-1;
		log.open(LOG_FILENAME,ios::app);
		argv[0]=argv[1]=NULL;
		// buf gets one line, and then were token as 3 part.
		commandFile.getline(buf,sizeof(buf));
		if(!(fName = strtok(buf," "))) continue;  // if buf don't get anything, continue this loop.
		for(int i=0; i<2; i++) argv[i] = strtok(NULL," ");
		// find the option code that matched 'fName' in the command 
		for(int i=0; i<9; i++) if(!strcmp(fName,code[i])) op=i;

		if(op==4 || op==5 || op==7) {
			for(int j=0;j<strlen(argv[0]);j++) {
				*(argv[0]+j) = tolower(*(argv[0]+j));
			}
		
//			char *p = argv[0];
//			while(*p) {
//				*p = tolower(*p);
//				p++;
//			}
		}

		// excute member function that matched 'fName'. also, it checks how parameters are.
		switch(op) { 	
		case 0: // in case 'LOAD' with no parameter.
			if(argv[0]||argv[1]||!LOAD()) log<<"======== ERROR ========\n100\n=======================\n\n";
			else log<<"========= LOAD ========\nSuccess\n=======================\n\n";
			break;
		case 1: // in case 'ADD' with no parameter.
			if(argv[0]||argv[1]||!ADD()) log<<"======== ERROR ========\n200\n=======================\n\n";
			else log<<"========= ADD =========\nSuccess\n=======================\n\n";
			break;
		case 2: // in case 'MOVE' with one paramter.
			if(!argv[0]||argv[1]) log<<"======== ERROR ========\n300\n=======================\n\n";
			else if(atoi(argv[0])<=0 || atoi(argv[0])>100 || !MOVE()) log<<"======== ERROR ========\n300\n=======================\n\n";
			else log<<"========= MOVE ========\nSuccess\n=======================\n\n";
			break;
		case 3: // in case 'SAVE' with no paramter.
			if(argv[0]||argv[1]||!SAVE()) log<<"======== ERROR ========\n400\n=======================\n\n";
			else log<<"========= SAVE ========\nSuccess\n=======================\n\n";
			break;
		case 4: // in case 'TEST' with two paramter.
			if(strtok(NULL," ")||!(argv[0]&&argv[1])||!TEST()) log<<"======== ERROR ========\n500\n=======================\n\n";
			break;
		case 5: // in case 'SEARCH' with one paramter.
			if(!argv[0]||argv[1]) log<<"======== ERROR ========\n600\n=======================\n\n";
			else if(argv[0]&&!argv[1]&&!SEARCH()) log<<"======== ERROR ========\n600\n=======================\n\n";	
			break;
		case 6: // in case 'PRINT' with one or two paramter.
			if(!argv[0]||!PRINT()) log<<"======== ERROR ========\n700\n=======================\n\n";
			break;
		case 7: // in case 'UPDATE' with two paramter.
			if(strtok(NULL," ")||!(argv[0]&&argv[1])||!UPDATE()) log<<"======== ERROR ========\n800\n=======================\n\n";
			break;
		case 8: // in case 'EXIT'
			commandFile.close();
			return;
		default:
			if(op<0) break; // if the fName gets NO-registered command, break this loop.
		}
		log.close();
	}
	commandFile.close();
}

bool Manager::LOAD() {
	/* this function loads the files about Queue, BST, Circular Linked List structures.
	   if neither of them have the files, if not have vocabulary information, and if
	   these structures already have some of data-bases, return false.					*/

	// Step 1. check if anyone of them have some of data-bases
	if(!(queue->isEmpty() && bst->isEmpty() && cll->isEmpty())) return false;	

	// Step 2. open the files.
	ifstream queueFile(TO_MEMORIZE), bstFile(MEMORIZING), cllFile(MEMORIZED);

	// Step 3. insert(push) datas in each data-structures. 
	if(queueFile) while(!queueFile.eof()) {
		char word[32] = { 0 }, mean[32] = { 0 };
		queueFile >> word >> mean;		
		if(!strcmp(word,mean)) continue;
		//Allocating -> Set Pair -> Push.
		WordNode *voca = new WordNode; 
		voca->SetVoca(word,mean);
		queue->Push(voca);
	}
	if(bstFile) while(!bstFile.eof()) {
		char word[32] = { 0 }, mean[32] = { 0 };
		bstFile>>word>>mean;	
		if(!strcmp(word, mean)) continue;
		//Allocating -> Set Pair -> Insert & increment Count.
		WordNode *voca = new WordNode;
		voca->SetVoca(word,mean);
		bst->Search(word[0])->GetBST()->Insert(voca);
		bst->incCnt();
	}
	if(cllFile) while(!cllFile.eof()) {
		char word[32] = { 0 }, mean[32] = { 0 };
		cllFile>>word>>mean;
		if (!strcmp(word, mean)) continue;
		//Allocating -> Set Pair -> Insert.
		WordNode *voca = new WordNode;
		voca->SetVoca(word,mean);
		cll->Insert(voca);
	}

	// Step 4. close the file objects. and then, check whether it is success  
	//			if one of three data structures stores data, LOAD is success.
	queueFile.close();
	cllFile.close();
	bstFile.close();

	return queue->isEmpty() && bst->isEmpty() && cll->isEmpty() ? false : true;	
}
	
bool Manager::ADD() {
	/* this function loads the file named 'word.txt' which user maybe remember vocabulary 
	   if there isn't file, if it is empty file or word already have stored 
	   in data structures, return false.												 */

	// Step 1. open the files, and then check whether they exist.
	ifstream addFile(ADD_FILENAME);
	if(!addFile) return false; // Except Case : the file doesn't exist. 

	// step 2. push the data in queue if not word already have stored in data structures
	char word[32] = { 0 }, mean[32] = { 0 };
	while (!addFile.eof()) {
		addFile >> word >> mean;
		if (!strcmp(word, mean)) return false; // Except Case : Empty File.
		if (queue->Search(word) || bst->Search(word[0])->GetBST()->Search(word) 
			|| cll->Search(word)) continue;
		else {
			WordNode *voca = new WordNode;
			voca->SetVoca(word,mean);
			queue->Push(voca);
		}
	} return true;
}

bool Manager::MOVE() {
	/*It moves WordNodes from QUEUE to BST as size as argv[0].*/
	/*Consider of exception, is it more than 100 after move?  */
	/*does QUEUE have more than argv[0]?					  */
	if(atoi(argv[0])+bst->getCnt()>100) return false; // If word-count is more than 100, return false.
	for(int i=0; i<atoi(argv[0]); i++) { // loop as argv[0] ranged
		WordNode* data = queue->Pop();
		if(!data) return false;
		bst->incCnt();
		bst->Search(data->GetWord()[0])->GetBST()->Insert(data);
	} return true;
}

bool Manager::SAVE() {
	/*Call each Save()*/
	if(!(queue->isEmpty() && bst->isEmpty() && cll->isEmpty())) {
		queue->Save();
		bst->Save();
		cll->Save(); 
		return true;
	}
	else return false;
}

bool Manager::TEST() {
	/*TEST seems like SEARCH(), but it also compare argv[1] to WordNode's mean*/
	WordNode *Voca = bst->Search(argv[0][0])->GetBST()->Search(argv[0]);
	if(Voca && !strcmp(argv[1],Voca->GetMean())) {
		// Except Case : Voca is whether Search is success, strcmp is whether argument equals Voca's mean.
		ofstream log(LOG_FILENAME,ios::app);
		log<<"========= TEST ========\n"<<Voca->GetWord()<<"\n=======================\n\n";
		log.close();
		cll->Insert(bst->Search(argv[0][0])->GetBST()->Delete(argv[0]));
		bst->decCnt();
		return true;
	} return false;
}

bool Manager::SEARCH() {
	/*SEACH() finds WordNode about all sturctures. So, I defined 3-cases as searchList */
	/*If neither of them correct to argv[0], it returns false						   */
	AlphabetNode* alphabet = bst->Search(argv[0][0]);
	WordNode *searchList[3];
	ofstream log(LOG_FILENAME,ios::app);

	searchList[0]=queue->Search(argv[0]);
	searchList[1]=alphabet->GetBST()->Search(argv[0]);
	searchList[2]=cll->Search(argv[0]);

	for(int i=0;i<2; i++) if(searchList[i]) {
		if(argv[1] && argv[1][0]) { // in case UPDATE that calls SEARCH() with argument[1]
			log<<"======== UPDATE =======\n"<<searchList[i]->GetWord()<<" "<<searchList[i]->GetMean();
			searchList[i]->SetMean(argv[1]); 
			log<<" -> "<<searchList[i]->GetMean()<<"\n=======================\n\n";
		} 
		else log<<"======== SEARCH =======\n"<<searchList[i]->GetWord()<<" "<<searchList[i]->GetMean()<<"\n=======================\n\n";		
		log.close();
		return true; 
	} return false;
}

bool Manager::PRINT() {
	/*PRINT haves arguments 1 or 2. must do how many parameter are*/
	/*If it is corrent, call proper function.					  */ 
	if((!queue->isEmpty())&&!strcmp(argv[0],"TO_MEMORIZE")) return queue->Print();
		
	else if((!bst->isEmpty())&&argv[1]&&!strcmp(argv[0],"MEMORIZING")) {
		ofstream log(LOG_FILENAME,ios::app);
		log<<"======== PRINT ========\n";
		log.close();
		bst->Print(argv[1]);
		log.open(LOG_FILENAME,ios::app);
		log<<"=======================\n\n";
		log.close();
		return true;
	}
	else if((!cll->isEmpty())&&!strcmp(argv[0],"MEMORIZED")) return cll->Print();
	else return false;
}

bool Manager::UPDATE() {
	/*UPDATE implement using SEARCH() with argv[1]*/
	return SEARCH();
}
