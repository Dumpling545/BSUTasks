#include<TreeNode.h>
#pragma once
template<class K>
class BinarySearchTree
{
    public:
        BinarySearchTree(){
            root = nullptr;
        }
        BinarySearchTree(K rootKey){
            root = new TreeNode<K>(rootKey);
        }
        BinarySearchTree(const BinarySearchTree& tree);
        ~BinarySearchTree(){
            delete root;
            root = nullptr;
        }
        void add(K key){
            if(root != nullptr){
                TreeNode<K> * temp = root;
                bool findParent = false;
                while(!findParent){
                    if(key > temp->key){
                        if(temp->right == nullptr){
                            findParent = true;
                        } else {
                            temp = temp->right;
                        }
                    } else if(key < temp->key){
                        if(temp->left == nullptr){
                            findParent = true;
                        } else {
                            temp = temp->left;
                        }
                    } else {
                        temp->value++;
                        break;
                    }
                }
                if(findParent){
                    if(temp->key < key){
                        temp->right = new TreeNode<K>(key);
                    } else {
                        temp->left = new TreeNode<K>(key);
                    }
                }
            } else {
                root = new TreeNode<K>(key);
            }
        }
        int find(K key){
            TreeNode<K> * temp = root;
            int result = 0;
            while(temp != nullptr){
                if(key > temp->key){
                    temp = temp->right;
                } else if(key < temp->key){
                    temp = temp->left;
                } else {
                    result = temp->value;
                    break;
                }
            }
            return result;
        }
    protected:
        TreeNode<K> * root;
};
