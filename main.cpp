#include <iostream>
#include "BST.h"

using namespace std;

int main()
{
    BST<int> bst;

    bst.display();

    bst.insertValue(5);
    bst.insertValue(4);
    bst.insertValue(6);
    bst.insertValue(3);
    bst.insertValue(5);
    bst.insertValue(5);

    bst.display();
    bst.remove(6);
    bst.remove(4);
    bst.remove(5);
    cout << endl;
    bst.display();
    cout << (bst.contains(6) ? "True" : "False") << endl;
    return 0;
}
