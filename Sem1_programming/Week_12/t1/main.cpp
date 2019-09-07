#include <iostream>
#include "BinarySearchTree.h"
#include "week12.h"
using namespace std;

int main()
{
    try{
        BinarySearchTree<string>* tree = read<string>("input.txt");
        findWords(tree);
    }catch(FileException &ex){
        cout << ex.what();
    }
    return 0;
}
