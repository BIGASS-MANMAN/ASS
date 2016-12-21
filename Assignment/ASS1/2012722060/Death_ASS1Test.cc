#include "/usr/local/Auto_Scoring_System/Assignment/ASS1/2012722060/ALP_BST.h"
#include "/usr/local/Auto_Scoring_System/Assignment/ASS1/2012722060/Alphabet.h"
#include "/usr/local/Auto_Scoring_System/Assignment/ASS1/2012722060/CircularQueue.h"
#include "/usr/local/Auto_Scoring_System/Assignment/ASS1/2012722060/Manager.h"
#include "/usr/local/Auto_Scoring_System/Assignment/ASS1/2012722060/Queue.h"
#include "/usr/local/Auto_Scoring_System/Assignment/ASS1/2012722060/WORD_BST.h"
#include "/usr/local/Auto_Scoring_System/Assignment/ASS1/2012722060/Word.h"
#include "gtest/gtest.h"

class ASS1Test : public testing::Test {
    protected:
	virtual void SetUp() {

	    char AlpList[] = "qazplmwsxoknedcijbrfvtguhy";

	    M1.InsertAlp(AlpList);
	    M2.InsertAlp(AlpList);
	    M3.InsertAlp(AlpList);
	}

	char* Ing_Traversal(Manager m)
	{
	    char arr[8192]={0,};
	    return Ing_Sub_Traversal(m.ALPTREE->getRoot(),arr);
	}

	char* Ed_Traversal(Manager m)
	{
	    char arr[8192]={0,};

	    if(m.Q->getHead() == NULL)
		return NULL;
	    else
	    {
		Word* pCur = m.Q->getHead();
		while(pCur)
		{
		    strcat(arr,pCur->getWord());
		    pCur = pCur->getNext();
		}
	    }
	    return arr;
	}

	char* To_Traversal(Manager m)
	{
	    char arr[8192]={0,};

	    if(m.CQ->getHead() == NULL)
		return NULL;
	    else
	    {
		Word* pCur = m.CQ->getHead();
	        while(1)
		{
		    strcat(arr,pCur->getWord());
		    if(pCur->getNext() == m.CQ->getHead())
			break;
		    pCur = pCur->getNext();
		}
	    }
	    return arr;
	}

	char* Ing_Sub_Traversal(Alphabet* Node, char* arr)
	{
	    WORD_BST* WB;

	    if(Node == NULL)
		return arr;

	    WB = Node->getBST();
	    Word_Traversal(WB->getRoot(),arr);
	    Ing_Sub_Traversal(Node->getLeft(), arr);
	    Ing_Sub_Traversal(Node->getRight(), arr);
	}

	char* Word_Traversal(Word* Node, char* arr)
	{
	    if(Node == NULL)
		return arr;

	    strcat(arr,Node->getWord());
	    Word_Traversal(Node->getLeft(),arr);
	    Word_Traversal(Node->getRight(),arr);
	}

	Manager M1;
	Manager M2;
	Manager M3;
};
TEST_F(ASS1Test,LOAD_Death_test_Scenario1_0)
{
	ASSERT_DEATH(M1.LOAD("words.txt"),"segmentation fault");
}
TEST_F(ASS1Test,COMMAND_Death_test_Scenario1_0)
{
	ASSERT_DEATH(M1.COMMAND("/usr/local/Auto_Scoring_System/ASS1/2012722060_김영재/Scenario1.txt"),"segmentation fault");
}
TEST_F(ASS1Test,COMMAND_Death_test_Scenario2_0)
{
	ASSERT_DEATH(M2.COMMAND("Scenario2.txt"),"segmentation fault");
}
TEST_F(ASS1Test,COMMAND_Death_test_Scenario3_0)
{
	ASSERT_DEATH(M3.COMMAND("Scenario3.txt"),"segmentation fault");
}
