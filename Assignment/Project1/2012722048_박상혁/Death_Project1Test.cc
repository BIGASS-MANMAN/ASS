#include "/usr/local/Auto_Scoring_System/Assignment/Project1/2012722048_박상혁/AlphabetBST.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Project1/2012722048_박상혁/AlphabetNode.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Project1/2012722048_박상혁/CircularLinkedList.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Project1/2012722048_박상혁/Manager.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Project1/2012722048_박상혁/Queue.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Project1/2012722048_박상혁/WordBST.h"
#include "/usr/local/Auto_Scoring_System/Assignment/Project1/2012722048_박상혁/WordNode.h"
#include "gtest/gtest.h"

using namespace std;
class Project1Test : public testing::Test {
    protected:
	virtual void SetUp() {
	}

	char* To_Traversal(Manager m)
	{
	    char arr[8192]={0,};

	    if(m.queue->pHead == NULL)
		return NULL;
	    else
	    {
		WordNode* pCur = m.queue->pHead;
		while(pCur)
		{
		    strcat(arr,pCur->GetWord());
		    pCur = pCur->GetNext();
		}
	    }
	    remove("log.txt");
		return arr;
	}

	char* Ed_Traversal(Manager m)
	{
	    char arr[8192]={0,};

	    if(m.cll->pHead == NULL)
		return NULL;
	    else
	    {
			WordNode* pCur = m.cll->pHead;
	        while(1)
			{
			    strcat(arr,pCur->GetWord());
		 	  	if(pCur->GetNext() == m.cll->pHead)
				break;
		 	  	pCur = pCur->GetNext();
			}
	    }
	    remove("log.txt");
		return arr;
	}

	char* Ing_Traversal_pre(Manager m)
	{
	    char arr[8192]={0,};
	    return Ing_Sub_Traversal_pre(m.bst->root,arr);
	}

	char* Ing_Sub_Traversal_pre(AlphabetNode* Node, char* arr)
	{
	    WordBST* WB;

	    if(Node == NULL)
			return arr;

	    WB = Node->GetBST();
	    Word_Traversal_pre(WB->root,arr);
	    Ing_Sub_Traversal_pre(Node->GetLeft(), arr);
	    Ing_Sub_Traversal_pre(Node->GetRight(), arr);
	}

	char* Word_Traversal_pre(WordNode* Node, char* arr)
	{
	    if(Node == NULL){
			remove("log.txt");
			return arr;
		}
	    strcat(arr,Node->GetWord());
	    Word_Traversal_pre(Node->GetLeft(),arr);
	    Word_Traversal_pre(Node->GetRight(),arr);
	}

	char* Ing_Traversal_in(Manager m)
	{
		char arr[8192]={0,};
		return Ing_Sub_Traversal_in(m.bst->root,arr);
	}

	char* Ing_Sub_Traversal_in(AlphabetNode* Node, char* arr)
	{
	    WordBST* WB;

	    if(Node == NULL)
			return arr;

	    WB = Node->GetBST();
	    Ing_Sub_Traversal_in(Node->GetLeft(), arr);
		Word_Traversal_in(WB->root,arr);
	    Ing_Sub_Traversal_in(Node->GetRight(), arr);
	}

	char* Word_Traversal_in(WordNode* Node, char* arr)
	{
	    if(Node == NULL){
			remove("log.txt");
			return arr;
		}

	    Word_Traversal_in(Node->GetLeft(),arr);
	    strcat(arr,Node->GetWord());
	    Word_Traversal_in(Node->GetRight(),arr);
	}

	char* Ing_Traversal_post(Manager m)
	{
		char arr[8192]={0,};
		return Ing_Sub_Traversal_post(m.bst->root,arr);
	}

	char* Ing_Sub_Traversal_post(AlphabetNode* Node, char* arr)
	{
	    WordBST* WB;

	    if(Node == NULL)
			return arr;

	    WB = Node->GetBST();
	    Ing_Sub_Traversal_post(Node->GetLeft(), arr);
	    Ing_Sub_Traversal_post(Node->GetRight(), arr);
		Word_Traversal_post(WB->root,arr);
	}

	char* Word_Traversal_post(WordNode* Node, char* arr)
	{
	    if(Node == NULL){
			remove("log.txt");
			return arr;
		}

	    Word_Traversal_post(Node->GetLeft(),arr);
	    Word_Traversal_post(Node->GetRight(),arr);
		strcat(arr,Node->GetWord());
	}

	char* Search_Test_1(Manager m)
	{
		char arr[128]={0,};
		WordBST* WB = m.bst->root->GetRight()->GetLeft()->GetLeft()->GetRight()->GetBST();
		strcat(arr, WB->Search("street")->GetWord());
		remove("log.txt");
		return arr;
	}

	char* Update_Test_1(Manager m)
	{
		char arr[128]={0,};
		WordBST* WB = m.bst->root->GetLeft()->GetLeft()->GetLeft()->GetRight()->GetBST();
		strcat(arr, WB->Search("course")->GetMean());
		remove("log.txt");
		return arr;
	}

	char* Save_Test_ed(Manager m)
	{
		char arr[128]={0,};
		ifstream infile("memorized_word.txt");
		infile>>arr;
		infile.close();
		remove("log.txt");
		return arr;
	}

	char* Get_Print(Manager m)
	{
		// 50 in-order
		char arr[1024]={0,};
		
		char str1[128];
		int print = 0;

		ifstream infile;
		infile.open("log.txt");

		while(!infile.eof())
		{
			infile.getline(str1, 128);
			if(strstr(str1, "PRINT")){
				print = 1;
				break;
			}
			else if(strstr(str1, "print")){
				print = 1;
				break;
			}
			else if(strstr(str1, "Print")){
				print = 1;
				break;
			}
		}

		if(print == 1){
			while(!infile.eof())
			{
				infile >> str1;
				if (!isalpha(str1[0])) break;
				else strcat(arr, str1);
				infile >> str1;
			}
		}

		remove("log.txt");

		return arr;
	}

	Manager M1;

};
TEST_F(Project1Test,run_Death_test_TestCase1_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario1.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase2_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario2.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase3_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario3.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase4_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario4.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase5_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario5.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase6_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario6.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase7_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario7.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase8_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario8.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase9_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario9.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase10_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario10.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase11_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario11.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase12_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario12.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase13_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario13.txt"),"segmentation fault");
}
TEST_F(Project1Test,run_Death_test_TestCase14_0)
{
	ASSERT_DEATH(M1.run("/usr/local/Auto_Scoring_System/info/Project1/Scenario14.txt"),"segmentation fault");
}
