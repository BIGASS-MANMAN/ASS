#include "Alphabet.h"
#include "Word.h"

Alphabet::Alphabet()
{
    WORD = new WORD_BST;
    m_Alp = 0;
    m_pLeft = NULL;
    m_pRight = NULL;
}

WORD_BST* Alphabet::getBST()
{
    return WORD;
}
Word* Alphabet::getRoot()
{
    return WORD->getRoot();
} 

void Alphabet::setAlp(char Alp)
{
    m_Alp = Alp;
}
void Alphabet::setLeft(Alphabet* left)
{
    m_pLeft = left;
}
void Alphabet::setRight(Alphabet* right)
{
    m_pRight = right;
}

char Alphabet::getAlp()
{
    return m_Alp;
}
Alphabet* Alphabet::getLeft()
{
    return m_pLeft;
}
Alphabet* Alphabet::getRight()
{
    return m_pRight;
}
