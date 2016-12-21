#include "Node.h"

Node::Node()
{
    Value=0;
    pLeft = '\0';
    pRight = '\0';
}
int Node::getValue()
{
    return this->Value;
}
void Node::setValue(int value)
{
    this->Value = value;
}
Node* Node::getLeft()
{
    return this->pLeft;
}

void Node::setLeft(Node* left)
{
    this->pLeft = left;
}
Node* Node::getRight()
{
    return pRight;
}
void Node::setRight(Node* right)
{
    this->pRight = right;
}
