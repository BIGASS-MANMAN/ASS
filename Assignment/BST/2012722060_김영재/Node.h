#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class Node
{
private:
    int Value;
    Node* pLeft, *pRight;

public:
    Node();
    
    int getValue();
    void setValue(int value);
    
    Node* getLeft();
    void setLeft(Node* left);
    
    Node* getRight();
    void setRight(Node* right);
};
