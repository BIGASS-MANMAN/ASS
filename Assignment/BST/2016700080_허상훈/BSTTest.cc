#include "/usr/local/Auto_Scoring_System/Assignment/BST/2016700080_허상훈/Node.h"
#include "/usr/local/Auto_Scoring_System/Assignment/BST/2016700080_허상훈/BST.h"
#include "gtest/gtest.h"

class BSTTest : public testing::Test {
    protected:
	virtual void SetUp() {
	    MyInsert(&Tree1,10);
	    MyInsert(&Tree1,5);
	    MyInsert(&Tree1,15);
	    MyInsert(&Tree1,13);

	    MyInsert(&Tree2,20);
	    MyInsert(&Tree2,10);
	    MyInsert(&Tree2,5);

	    MyInsert(&Tree3,20);
	    MyInsert(&Tree3,27);
	    MyInsert(&Tree3,35);
	    MyInsert(&Tree3,24);
	    MyInsert(&Tree3,28);
	}

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
TEST_F(BSTTest,Insert_GRP1){
	Tree1.Insert(100);
	EXPECT_STREQ(PRINTNODE(Tree1),"5101315100");
}
TEST_F(BSTTest,Delete_infinite){
	EXPECT_STREQ(PRINTNODE(Tree1),"51315");
}
