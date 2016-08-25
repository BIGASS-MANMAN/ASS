#include "BST.h"

int main()
{
    char arr[1000] = {0,};
    BST Tree1;
    BST Tree2;
    BST Tree3;
    Tree1.Insert(10);
    Tree1.Insert(5);
    Tree1.Insert(15);
    Tree1.Insert(13);

    Tree2.Insert(20);
    Tree2.Insert(10);
    Tree2.Insert(5);

    Tree3.Insert(20);
    Tree3.Insert(27);
    Tree3.Insert(24);
    Tree3.Insert(35);
    Tree3.Insert(28);
    

    cout<<Tree1.traversal(Tree1.getRoot(), arr)<<endl;
    cout<<Tree2.traversal(Tree2.getRoot(), arr)<<endl;
    cout<<Tree3.traversal(Tree3.getRoot(), arr)<<endl;

    Tree1.Delete(15);
    Tree1.Delete(10);
    cout<<Tree1.traversal(Tree1.getRoot(), arr)<<endl;

    Tree2.Delete(20);
    cout<<Tree2.traversal(Tree2.getRoot(), arr)<<endl;

    Tree3.Delete(27);
    cout<<Tree3.traversal(Tree3.getRoot(), arr)<<endl;
    Tree3.Delete(28);
    cout<<Tree3.traversal(Tree3.getRoot(), arr)<<endl;
    Tree3.Delete(35);
    cout<<Tree3.traversal(Tree3.getRoot(), arr)<<endl;


    return 0;
}
