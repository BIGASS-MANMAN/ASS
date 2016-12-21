#include "Queue.h"



Queue::Queue()
{
	pHead = '\0';
	WordCnt = 0;
}
//in this case
//1. when overlab word node search, routin break;
//2. FIFO;
//3. parameter node is NULL, End funtion
void Queue::Push(WordNode *push_node)
{
	if(push_node == 0) return;

	if(pHead != 0){
		for(WordNode *cur = pHead; cur; cur=cur->GetNext()){
			if(strcmp(cur->GetWord(), push_node->GetWord()) == 0){
				break;	//overlab word case
			}
			if(cur->GetNext() == 0){
				WordCnt++;
				cur->SetNext(push_node);
				break;
			}
		}
	}
	else{
		WordCnt++;
		pHead = push_node;
	}
}
WordNode * Queue::Pop()
{
	if(pHead){
	WordCnt--;
	WordNode *pop_node = pHead;		//first out
	pHead = pHead->GetNext();
	return pop_node;
	}
	else
		return 0;
}
WordNode * Queue::Search(char * word)
{
	for(WordNode *cur = pHead; cur; cur = cur->GetNext()){
		if(!strcmp(cur->GetWord(), word)){
			return cur;
		}
	}
	return 0;
}
bool Queue::Print()
{
	if(pHead){
		
	fout_word.open("log.txt", ios::app);
		for(WordNode *cur = pHead; cur; cur = cur->GetNext()){
			cout<<cur->GetWord()<<"	"<<cur->GetMean()<<"\n";
			fout_word<<cur->GetWord()<<"	"<<cur->GetMean()<<endl;
		}
		return true;
	}
	else
		return false;
}
bool Queue::Save()
{
	ofstream fout;
	fout.open("to_memorize_word.txt", ios::out);
	if(pHead){
	if(!fout){		//if reading file not exist
		return false;
	}

	for(WordNode *cur = pHead; cur; cur = cur->GetNext()){
		fout<<cur->GetWord()<<"	"<<cur->GetMean()<<endl;

	}
	fout.close();
	return true;
	}
	else{
		fout.close();		//if head node not exist
		return false;
	}
}
int Queue::GetWordCnt()
{
	return WordCnt;
}
void Queue::SetWordCnt(int count)
{
	WordCnt = count;
}
Queue::~Queue()
{
	/* You must fill here */
	if(fout_word) fout_word.close();
	if(pHead){
	WordNode* Head_Next = pHead->GetNext();
	while(pHead){
		delete pHead;
		pHead = Head_Next;
		if(Head_Next) // if Head_Next isn't NULL, then go next node
		Head_Next = Head_Next->GetNext();
	}
	}
}
