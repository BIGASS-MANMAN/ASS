#include "CircularLinkedList.h"



CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
	WordCnt = 0;
}
//in this case
//circularLL is no end of list, than using the tail pointer express end of list
//new insert node by point out pTail pointer
//than, pTail pointer SetNext <- pHead
void CircularLinkedList::Insert(WordNode *parm_pNode)
{
	if(parm_pNode == 0) return;//parameter variable is null, no insert node
	if(pHead != 0){		//if pHead is exist
		for(WordNode *cur = pHead; cur; cur = cur->GetNext()){
			if(!strcmp(cur->GetWord(), parm_pNode->GetWord())){
			delete parm_pNode;
			return;
			}	//overlab case
			if(cur == pTail){	//express end of list
				WordCnt++;	//counting CircularLL number of node
				parm_pNode->SetNext(pHead);
				pTail->SetNext(parm_pNode);
				pTail = parm_pNode;
				break;
			}
		}
	}
	else{				//if pHead isn't exist
		WordCnt++;
		pHead = parm_pNode;
		pTail = parm_pNode;
		pTail->SetNext(pHead);
	}
}
//in this case
//1. searching sequantial
//2. if find node, return target node;
//3. if BST have not root node, return 0;
WordNode * CircularLinkedList::Search(char * word)
{
	if(pHead){		//if pHead exist, excute under statement
		for(WordNode *cur = pHead; cur; cur = cur->GetNext()){
			if(!strcmp(cur->GetWord(), word))	//find node!
				return cur;
			
			if(cur == pTail) break;
		}

		return 0;	//can't find node...
	}
	else
		return 0;	//Head is empty
}
//in this case
//1. print sequantial
bool CircularLinkedList::Print()
{
	if(fout_word.is_open() == false){
	fout_word.open("log.txt", ios::app);
	}
	if(pHead){
		for(WordNode *cur = pHead; cur; cur = cur->GetNext()){
			cout<<cur->GetWord()<<"	"<<cur->GetMean()<<endl;
			if(fout_word)
			fout_word<<cur->GetWord()<<"	"<<cur->GetMean()<<endl;
			if(cur == pTail) break;
		}
		return true;
	}
	else
		return false;
}
bool CircularLinkedList::Save()
{
	ofstream fout;
	fout.open("memorized_word.txt", ios::out);
	if(pHead){
		for(WordNode *cur = pHead; ; cur = cur->GetNext()){
			fout<<cur->GetWord()<<"	"<<cur->GetMean()<<"\n";
			if(cur == pTail) break;
		}
		fout.close();
		return true;
	}
	else{
		fout.close();
		return false;	//if head is empty
	}
}
int CircularLinkedList::GetWordCnt()
{
	return WordCnt;
}
void CircularLinkedList::SetWordCnt(int count)
{
	WordCnt = count;
}
CircularLinkedList::~CircularLinkedList()
{
	/* You must fill here */
	if(fout_word) fout_word.close();
	WordNode * current = pHead;
	if(pHead){
	while(pHead != pTail){	//circularLL recursive in characteristic, delete isn't complete
		pHead = pHead->GetNext();
		delete current;
		current = pHead;
	}
	delete pTail;
	}			//so, when last pTail pointer deleting, success all deleting node
}
