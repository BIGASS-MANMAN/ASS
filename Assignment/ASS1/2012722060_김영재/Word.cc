#include "Word.h"

Word::Word()
{
    memset(m_Word,0,128);
    memset(m_Mean,0,128);
    m_pLeft = NULL;
    m_pRight = NULL;
    m_pNext = NULL;
}

void Word::setWord(char* Word)
{
    strcpy(m_Word,Word);
}
void Word::setMean(char* Mean)
{
    strcpy(m_Mean,Mean);
}
void Word::setLeft(Word* Left)
{
    m_pLeft = Left;
}
void Word::setRight(Word* Right)
{
    m_pRight = Right;
}
void Word::setNext(Word* Next)
{
    m_pNext = Next;
}


char* Word::getWord()
{
    return m_Word;
}
char* Word::getMean()
{
    return m_Mean;
}
Word* Word::getLeft()
{
    return m_pLeft;
}
Word* Word::getRight()
{
    return m_pRight;
}
Word* Word::getNext()
{
    return m_pNext;
}
