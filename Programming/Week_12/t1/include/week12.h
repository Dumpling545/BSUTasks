#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "fileException.h"
#include "emptyFileException.h"
#include "nonExistFileException.h"
#include "BinarySearchTree.h"
template<class T>
BinarySearchTree<T>* read(string filename){
    ifstream fin;
    try{
        if(fin.is_open()){
            fin.close();
        }
        fin.open(filename);
    } catch(...){
        throw FileException(filename);
    }
    if(!fin){
        throw NonExistFileException(filename);
    } else if(fin.peek() == ifstream::traits_type::eof()){
        throw EmptyFileException(filename);
    }
    try{
        BinarySearchTree<T>* tree = new BinarySearchTree<T>();
        T token;
        while(fin >> token){
            tree->add(token);
        }
        fin.close();
        return tree;
    } catch(FileException &ex){
        throw;
    }
}
template<class T>
void findWords(BinarySearchTree<T>* tree){
    T word;
    cout << "Find words you need: " <<endl;
    while(cin >> word){
        cout << "Word '" << word << "' met " << tree->find(word) << " times" << endl;
    }
    delete tree;
}
