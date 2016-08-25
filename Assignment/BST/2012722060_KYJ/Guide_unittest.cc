#include "/usr/local/Auto_Scoring_System/Assignment/BST/2012722060_김영재/Node.h"
#include "/usr/local/Auto_Scoring_System/Assignment/BST/2012722060_김영재/BST.h"
#include "gtest/gtest.h"

class BSTTest : public testing::Test {
    protected:
	virtual void SetUp() {
	    MyInsert(&Tree1,10);
	    Tree1.Insert(5);
	    Tree1.Insert(15);
	    Tree1.Insert(13);

	    Tree2.Insert(20);
	    Tree2.Insert(10);
	    Tree2.Insert(5);

	    Tree3.Insert(20);
	    Tree3.Insert(27);
	    Tree3.Insert(35);
	    Tree3.Insert(24);
	    Tree3.Insert(28);
	}

	//SetUp part use indefective code
	Node* MyInsert(BST* Tree, int value)
	{
	    Node* a = new Node;
	    Node* pCur = Tree->getRoot();

	    a->setValue(value);
	    if(Tree->getRoot() == '\0')
	    {
		Tree->setRoot(a);
		return '\0';
	    }

	    while(1)
	    {
		if(pCur->getValue() < a->getValue())
		{
		    if(pCur->getRight() == '\0')
		    {
			pCur->setRight(a);
			return '\0';
		    }
		    else
			pCur = pCur->getRight();
		}
		else
		{
		    if(pCur->getLeft() == '\0')
		    {
			pCur->setLeft(a);
			return '\0';
		    }
		    else
			pCur = pCur->getLeft();
		}
	    }
	}

	//If You want to test tree structure
	//You set up helper code(ex. traversal..)
	char* PRINTNODE(BST Tree)
	{
	    char arr[1000]={0,};
	    return traversal(Tree.getRoot(),arr);
	}

	char* traversal(Node* pCur, char* arr)
	{
	    char buf[100] = {0,};
	    if(pCur == '\0')
	    {
		return arr;
	    }

	    traversal(pCur->getLeft(), arr);

	    sprintf(buf, "%d", pCur->getValue());
	    strcat(arr, buf);

	    traversal(pCur->getRight(), arr);
	    return arr;
	}


	char arr[100];
	BST Tree1;
	BST Tree2;
	BST Tree3;
};
TEST_F(BSTTest,Delete){
	Tree1.Delete(10);
	EXPECT_STREQ(PRINTNODE(Tree1),"51315");
	Tree2.Delete(20);
	EXPECT_STREQ(PRINTNODE(Tree2),"510");
	Tree3.Delete(27);
	EXPECT_STREQ(PRINTNODE(Tree3),"20242835");
}
