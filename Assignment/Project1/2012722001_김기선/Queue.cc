#include "Queue.h"


Queue::Queue()         //constructor
{
   pHead = NULL;      //reset
   WordCnt = 0;      //reset
}


Queue::~Queue()            //destructor
{
   if (pHead == NULL)      //If  data does not exist, the return
      return;

   WordNode* pCur = pHead;      //create and reset
   WordNode* pTemp = pCur;      //create and reset

   while (1)               //loop
   {
      if (pCur == NULL)      //If  data does not exist, the return
         return;

      pTemp = pCur;            //save pCur
      pCur = pCur->GetNext();      //move pCur
      delete pTemp;            //destruct pTemp
   }
}

void Queue::Push(WordNode* node)   //push
{
   WordNode* pCur = pHead;         //create and reset

   if (pHead == NULL)            //when first push , save the first node to phead
   {
      pHead = node;
   }
   else
   {
      while (pCur->GetNext() != NULL)                     //repeat the end of the queue
      {
         if (strcmp(pCur->GetWord(), node->GetWord()) == 0)   //if get the same word, the return
            return;
         pCur = pCur->GetNext();                        //move the next node
      }
      if (strcmp(pCur->GetWord(), node->GetWord()) == 0)      //if get the same word, the return
         return;
      pCur->SetNext(node);                           //Be connected to the last node and the new coming node
   }
   WordCnt++;                                       //count ++
}

WordNode* Queue::Pop()                                 //pop
{
   if (pHead == NULL)
   {
      return NULL;                                 //If  data does not exist, the return
   }
   WordNode* pCur = pHead;                              //create and reset
   pHead = pHead->GetNext();                           //change phead
   pCur->SetNext(NULL);                        //disconnect  head and queue
   WordCnt--;                                 //count --
   return pCur;
}
WordNode *   Queue::Search(char * word)            //search
{
   WordNode* pCur = pHead;                     //create and reset
   if (pHead == NULL)                        //If  data does not exist, the return
      return 0;
   while (1)
   {
      if (strcmp(pCur->GetWord(), word) == 0)
         return pCur;
      pCur = pCur->GetNext();
      if (pCur == NULL)
         return 0;
   }

}
bool Queue::Print()                     // PRINT
{
   ofstream fout("log.txt", ios::app);      //open log.text for write
   WordNode* pCur = pHead;               //create and reset
   if (pHead == NULL)                  //If  data does not exist, return false
      return 0;
   else
   {
      fout << "======== PRINT ========" << endl;
      while (1)
      {
         fout << pCur->GetWord() << "\t" << pCur->GetMean() << endl;      //fout word and mean
         pCur = pCur->GetNext();                                 //move pCur to next node
         if (pCur == NULL)                                    //if pCur move to the last node, break
            break;
      }
      fout << "=======================" << endl << endl;
      fout.close();                                          //file close
      return 1;                                             //return true
   }
}

bool Queue::Save()                         // SAVE
{
   ofstream fout;                          //open text file for write
   fout.open("to_memorize_word.txt");
   if (pHead == NULL)                      //If  data does not exist, return false
   {
      fout.close();
      return 0;
   }
   WordNode* pCur = pHead;                  //create and reset
   while (1)
   {
      if (pCur->GetNext() == NULL)            
         fout << pCur->GetWord() << "\t" << pCur->GetMean();
      else
         fout << pCur->GetWord() << "\t" << pCur->GetMean() << endl;      //fout word and mean
      pCur = pCur->GetNext();                                    //move pCur to next node
      if (pCur == NULL)                                       //if pCur move to the last node, break
         break;
   }
   fout.close();                                             //file close
   return 1;

}

WordNode* Queue::GetHead()      //get head
{
   return pHead;            
}

int Queue::getWordCnt()         //get wordcount
{
   return WordCnt;         
}
